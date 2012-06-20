#makefile for postgres client

CC = g++
SOURCE = client.cpp pg_con.cpp
TARGET = main
DIRS = /usr/include/postgresql/
LIB = pq

all:
	${CC} ${SOURCE} -o${TARGET} -I${DIRS} -l${LIB}
