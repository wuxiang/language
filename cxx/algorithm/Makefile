CC = g++
LIB = pthread
DIS = main
SOURCE = main.cpp

all: 2Q

2Q: 2Q.o
	${CC} 2Q.o ${SOURCE} -o ${DIS} -l${LIB}

2Q.o: 2Q.h 2Q.cpp
	${CC} -c 2Q.cpp

#all: compile link

#${OBJS}: ${SRC}
#	${CC} -fPIC -c ${SRC}
#
#compile: ${OBJS}
#compile:
#	${CC} -fPIC -c ${SRC}
#
#link:
#	${CC} -shared -o${LIB} ${OBJS}
#
clean:
	rm -rf *.o ${DIS}


