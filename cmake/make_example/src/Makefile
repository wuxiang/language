LIB = libsrc.so
SRC = src/welcome.cpp
OBJS = welcome.o
CC = g++

all: compile link

compile:
	${CC} -fPIC -c ${SRC}

link:
	${CC} -shared -o ${LIB} ${OBJS}

