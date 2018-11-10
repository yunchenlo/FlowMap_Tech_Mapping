CPP = g++
CPPFLAGS = -Wall -g -std=c++11 -O0
OBJS = main.o Graph_FlowNetWorks.o
DEPS = Graph_FlowNetWorks.cpp

BIG_K=4
ALU4_AAG="alu4.aag"
ALU4_OUT="alu4.aag_output"

BIG_AAG="bigkey.aag"
BIG_OUT="bigkey.aag_output"

C1908_AAG="c1908.aag"
C1908_OUT="c1908.aag_output"

C5315_AAG="c5315.aag"
C5315_OUT="c5315.aag_output"

debug:FlowMap.exe
	./FlowMap.exe my_alu.aag 4 output.aag

FlowMap.exe:${OBJS}
	${CPP} ${CPPFLAGS} -o $@ ${OBJS}

%o.: %.cpp ${DEPS}
	${CPP} -c -o $@ $< ${CPPFLAGS}

clean: 
	-rm -r *.o *.exe