"""Assemble the install files for a NumAI TI-84 release."""
import re
import shutil
import sys
from pathlib import Path

version, build, release, libraries = sys.argv[1:]
build, release, libraries = map(Path, (build, release, libraries))
if not re.fullmatch(r"[0-9]+\.[0-9]+\.[0-9]+", version):
    raise SystemExit("Invalid release version")

def le(n):
    return n.to_bytes(2, "little")

def records(path):
    b = path.read_bytes()
    if (not b.startswith(b"**TI83F*\x1a\x0a\0") or le(len(b)-57) != b[53:55]
            or le(sum(b[55:-2])&65535) != b[-2:]):
        raise ValueError(f"Bad TI file header: {path}")
    data = memoryview(b)[55:-2]
    while data:
        header = int.from_bytes(data[:2],"little")
        size = int.from_bytes(data[2:4],"little")
        if header != 13 or size == 0 or len(data) < 17+size or data[15:17] != le(size):
            raise ValueError(f"Bad TI variable record: {path}")
        record, data = data[:17+size], data[17+size:]
        yield bytes(record[5:13]).rstrip(b"\0").decode(), bytes(record)

def write_group(path, entries, label):
    data = b"".join(entries)
    header = b"**TI83F*\x1a\x0a\0" + label.encode().ljust(42,b"\0")
    path.write_bytes(header + le(len(data)) + data + le(sum(data)&65535))

program = build/"bin"/"NUMAI.8xp"
(name, record), = records(program)
if name != "NUMAI" or record[4] != 6 or record[14] != 128 or record[19:21] != b"\xef\x7b":
    raise ValueError("Expected archived native NUMAI program")
if list((build/"bin").glob("NUMAI.8xp.*.8xv")):
    raise ValueError("Delete stale split-program output with make clean first")
wanted = {"LibLoad", "GRAPHX", "KEYPADC", "FILEIOC"}
libs = {name:record for name,record in records(libraries) if name in wanted}
if set(libs) != wanted or any(r[4] != 21 or r[14] != 128 for r in libs.values()):
    raise ValueError("Required archived CE libraries are missing")
course_files = sorted((build/"data").glob("NMC*.8xv")) + [build/"data"/"NMTABLE.8xv"]
for path in course_files:
    (name, record), = records(path)
    if name != path.stem or record[4]!=21 or record[14]!=128:
        raise ValueError(f"Bad course AppVar {path}")
release.mkdir(parents=True, exist_ok=True)
shutil.copyfile(program,release/f"numai-ti84-v{version}.8xp")
for path in course_files:
    shutil.copyfile(path,release/path.name)
write_group(release/"numai-ce-libs-v15.0.8xg",libs.values(),"NumAI CE Libraries v15.0")
print(f"Packaged {program.stat().st_size:,}-byte program, {len(course_files)} AppVars and four CE libraries")
