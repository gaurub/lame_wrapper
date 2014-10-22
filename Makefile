#declaring properties
RM = rm -rf

BIN_DIR = bin

OBJECTS = encode

OFILES = $(OBJECTS:%=%.o)

OFILES_BIN = $(OBJECTS:%=$(BIN_DIR)/%.o)

CCC = clang -dynamiclib

LIBRARY = encode.dylib

LFLAGS = -L./lib -L/usr/local/Cellar/lame/3.99.5/lib

LIBS = -lmp3lame

IFLAGS = -I/usr/local/Cellar/lame/3.99.5/include

BASEDIR =

COMPILEFLAGS += -Wall -g -std=gnu99 -DDEBUG  

DYLIB_FLAGS = -current_version 1.0 -compatibility_version 1.0 -fvisibility=hidden -o libencode.1.dylib

all : $(LIBRARY) $(TEST_LIBRARY)

$(LIBRARY) : $(OFILES)
	@echo
	$(CCC) -o $(LIBRARY) $(COMPILEFLAGS) $(OFILES) $(IFLAGS) $(LFLAGS) $(LIBS) $(DYLIB_FLAGS)

%.o : %.c
	$(CCC) $(COMPILEFLAGS) $(IFLAGS) $(CCFLAG) -c $< -o $@
	
%c : %.h

clean:
	$(RM) $(OFILES)
	$(RM) $(LIBRARY)
