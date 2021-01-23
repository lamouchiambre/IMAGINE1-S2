CXX		= g++
CXX_FLAGS	= -Wall -g -O0 -ansi -pedantic -std=c99 

LD_FLAGS 	=

PROGS		= histogram3c #seuillage4p #test_grey

SOURCES		= histogram3c.cpp # seuillage4p.cpp #test_grey.cpp

HEADERS		= image.hpp

DEPFILE		= .depend

ifeq ($(wildcard $(DEPFILE)), )

all: $(DEPFILE)
	make

else

all: $(PROGS)

include $(DEPFILE)

endif

include $(DEPFILE)

.SUFFIXES: .c .h .o 

$(PROGS): $(SOURCES:.c=.o)
	$(CXX) $(LD_FLAGS) $^ -o $@

.c.o:
	$(CXX) $(CXX_FLAGS)$< -c

$(DEPFILE): $(SOURCES)
	$(CXX) -MM $^ > $@ 

clean:
	rm -f *~ $(SOURCES:.c=.o) $(PROGS)
