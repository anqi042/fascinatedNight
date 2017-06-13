#
# Makefile for UN*X-like systems
#

UNITTEST_PROJ = $(shell pwd)

TEST_BASE_DIR=${UNITTEST_PROJ}/cxxtest-4.3

# Change this line if you want a different compiler
GXX = g++ -Wall -W -Werror -I. -I..

TESTGEN = ${TEST_BASE_DIR}/bin/cxxtestgen

# For the X11 GUI
X11_FLAGS = -I/usr/X11R6/include -L/usr/X11R6/lib -lX11

INCLUDE = -I/${UNITTEST_PROJ}/../myclass \
          -I/${TEST_BASE_DIR} \
          -I/${UNITTEST_PROJ}/../testcase/asioServerTest

LIBRARYS = -lpthread -Wl,-rpath=/usr/local/lib/  -lglog  -lboost_thread -lboost_system

TARGETS = asioServersuit 
TESTS = *.h



all: $(TARGETS)

clean:
	rm -f *~ *.o *.obj $(TARGETS)
	rm -f *.cpp

run: asioServersuit
	./asioServersuit

asioServersuit.cpp: $(TESTS)
	$(TESTGEN) -o $@ --error-printer $(TESTS)
        
%: %.cpp
	$(GXX) ${INCLUDE} -o $@ $<  ${LIBRARYS}

#
# Local Variables:
# compile-command: "make -fMakefile.unix"
# End:
#
