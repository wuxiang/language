CC = g++
LIB = pthread
DIS = main
SOURCE = main.cpp

all: lru 

lru: lru.o
	${CC} lru.o ${SOURCE} -o ${DIS} -l${LIB}

lru.o: lru.h lru.cpp
	${CC} -c lru.cpp

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


