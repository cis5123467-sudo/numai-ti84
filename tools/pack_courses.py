"""Build relocatable course tables and TI AppVars from the original C catalog."""
import ast
import re
import subprocess
import sys
import tempfile
from pathlib import Path

source, out = map(Path, sys.argv[1:])
out.mkdir(parents=True, exist_ok=True)
code = subprocess.check_output(
    ["cc", "-E", "-P", "-I", str(source.parent), "-x", "c", "-"],
    input=f'#include "topics.h"\nNUMAI_CATALOG_START\n#include "{source.name}"\n',
    text=True,
).split("NUMAI_CATALOG_START", 1)[1]
literal = r'"(?:[^"\\]|\\.)*"'
tokens = re.compile(r'(?://[^\n]*|/\*[\s\S]*?\*/)|(?:' + literal + r'\s*)+')
chunks = [bytearray(b"N14\0")]
dedup = {}

def pack(match):
    if match[0].startswith("/"):
        return match[0]
    value = "".join(ast.literal_eval(t) for t in re.findall(literal, match[0])).encode() + b"\0"
    if value not in dedup:
        if len(chunks[-1]) + len(value) > 60000:
            chunks.append(bytearray(b"N14\0"))
        dedup[value] = ((len(chunks)-1)<<16) | len(chunks[-1])
        chunks[-1].extend(value)
    return f"(const char *){dedup[value]}UL "

def le(value):
    return value.to_bytes(2, "little")

def entry(name, payload):
    data = le(len(payload)) + payload
    return le(13) + le(len(data)) + b"\x15" + name.encode().ljust(8,b"\0") + b"\0\x80" + le(len(data)) + data

code = tokens.sub(pack, code)
code = re.sub(r'\bconst (MathsDetail|Topic|Chapter|Course)\b', r'\1', code)
# The host compiler expands the original initializers. The serializer writes
# a portable three-byte format, independent of host pointer width or padding.
serializer = r"""
static void u24(uintptr_t n) {
    putchar(n & 255); putchar((n >> 8) & 255); putchar((n >> 16) & 255);
}
#define TEXT(p) u24((uintptr_t)(p))
int main(void) {
    int chapters=0, topics=0, details=0;
    for(int c=0;c<course_count;c++){
        chapters+=courses[c].count;
        for(int h=0;h<courses[c].count;h++){
            Chapter *chapter=&courses[c].chapters[h];
            topics+=chapter->count;
            for(int t=0;t<chapter->count;t++)details+=chapter->topics[t].detail!=NULL;
        }
    }
    u24(course_count);u24(chapters);u24(topics);u24(details);
    for(int c=0;c<course_count;c++){
        Course *course=&courses[c];
        TEXT(course->title);TEXT(course->code);u24(course->count);
        for(int h=0;h<course->count;h++){
            Chapter *chapter=&course->chapters[h];
            TEXT(chapter->title);u24(chapter->count);
            for(int t=0;t<chapter->count;t++){
                Topic *topic=&chapter->topics[t];
                TEXT(topic->title);TEXT(topic->course);TEXT(topic->method);
                TEXT(topic->example);TEXT(topic->formula);u24(topic->operation);
                for(int f=0;f<MAX_FIELDS;f++){TEXT(topic->labels[f]);TEXT(topic->values[f]);}
                u24(topic->detail!=NULL);
                if(topic->detail){
                    TEXT(topic->detail->notes);
                    for(int e=0;e<EXTRA_EXAMPLES;e++){
                        TEXT(topic->detail->examples[e].title);
                        TEXT(topic->detail->examples[e].working);
                    }
                }
            }
        }
    }
    return 0;
}
"""
with tempfile.TemporaryDirectory() as directory:
    binary = Path(directory)/"serialize"
    subprocess.run(
        ["cc", "-I", str(source.parent), "-x", "c", "-", "-o", str(binary)],
        input='#include <stdint.h>\n#include <stdio.h>\n#include "topics.h"\n' + code + serializer,
        text=True, check=True,
    )
    tables = subprocess.check_output([str(binary)])
counts = [int.from_bytes(tables[i:i+3], "little") for i in range(0,12,3)]
keys = ("COURSE_COUNT", "CHAPTER_COUNT", "TOPIC_COUNT", "DETAIL_COUNT")
(out/"course_sizes.inc").write_text(
    "".join(f"#define {key} {value}\n" for key,value in zip(keys,counts))
    + f"#define TABLE_SIZE {len(tables)-8}\n"
    + "#define TEXT_SIZES " + ",".join(map(str,map(len,chunks))) + "\n"
)
record = entry("NMTABLE", b"NT4\0" + tables[12:])
header = b"**TI83F*\x1a\x0a\0" + b"NumAI v0.1.4 course data".ljust(42,b"\0")
(out/"NMTABLE.8xv").write_bytes(header + le(len(record)) + record + le(sum(record)&65535))
for i, chunk in enumerate(chunks):
    record = entry(f"NMC{i:03d}",chunk)
    header = b"**TI83F*\x1a\x0a\0" + b"NumAI v0.1.4 course data".ljust(42,b"\0")
    (out/f"NMC{i:03d}.8xv").write_bytes(header + le(len(record)) + record + le(sum(record)&65535))
print(f"{counts[2]} topics; {len(dedup)} unique strings in {len(chunks)+1} archived course files")
