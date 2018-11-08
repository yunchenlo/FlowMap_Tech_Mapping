CPP = g++
CPPFLAGS = -Wall -g 
OBJS = main.o 

run:FlowMap.exe
	./FlowMap.exe my_alu.aag 3 output.aag

FlowMap.exe:${OBJS}
	${CPP} ${CPPFLAGS} -o $@ ${OBJS} 

%o.: %.cpp ${DEPS}
	${CPP} -c -o $@ $< ${CPPFLAGS}

clean: 
	-rm -r *.o *.exe