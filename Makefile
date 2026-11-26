VERSION = 0.1.4
ICON = assets/icon.png

NAME = NUMAI
DESCRIPTION = "NumAI"
COMPRESSED = YES
HAS_LIBCXX = NO
BINDIR = build/bin
OBJDIR = build/obj
CFLAGS = -Wall -Wextra -Oz -Ibuild/data -DPLATFORM_DEVICE=1 -DNUMAI_VERSION='"$(VERSION)"'

include $(shell cedev-config --makefile)


build/data/course_sizes.inc: tools/pack_courses.py src/course_source.inc src/aqa_catalog.inc src/maths_details.inc
	python3 tools/pack_courses.py src/course_source.inc build/data

build/obj/src/topics.c.bc: build/data/course_sizes.inc

.PHONY: package
package: build/bin/NUMAI.8xp build/data/course_sizes.inc
	python3 tools/package.py "$(VERSION)" build release "${CE_LIBRARIES}"
