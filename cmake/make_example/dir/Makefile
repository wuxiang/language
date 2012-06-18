LIB = libdir.so
SRC = src/hello.cpp
OBJS = hello.o
CC = g++

all: compile link

#${OBJS}: ${SRC}
#	${CC} -fPIC -c ${SRC}
#
#compile: ${OBJS}
compile:
	${CC} -fPIC -c ${SRC}

link:
	${CC} -shared -o${LIB} ${OBJS}


