CC  = clang++
CXX = clang++

# INCLUDES = -I../../lab3/solutions/part1

CFLAGS   = -g -Wall $(INCLUDES)
CXXFLAGS = -g -Wall $(INCLUDES) -std=c++11

# LDFLAGS = -g -L../../lab3/solutions/part1
# LDLIBS  = -lmylist

executables = Runner
objects = Runner.o FileTool.o Editor.o

.PHONY: default
default: $(executables)

$(executables): Runner.o FileTool.o Editor.o

$(objects): FileTool.h Editor.h

.PHONY: clean
clean:
	rm -f *~ a.out core $(objects) $(executables)

.PHONY: all
all: clean default
