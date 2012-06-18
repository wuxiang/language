CC = g++

#dependence dir
DIRS = dir src
LD = -L. -Ldir -Lsrc -ldir -lsrc

#output
OUTPUT = test
OBJS = test.o

all: compile link position

${OBJS}: test.cpp
	${CC} -c test.cpp

compile:${OBJS}
	for DIR in ${DIRS}; do\
		make -C $${DIR} compile;\
	done

link:
	for DIR in ${DIRS}; do\
		make -C $${DIR} link;\
	done

position:
	for DIR in ${DIRS}; do\
		mv $${DIR}/*.so .;\
		make -C $${DIR} clean;\
		done
	g++ -o ${OUTPUT} ${OBJS} ${LD}
	rm -r ${OBJS}

clean:
	for DIR in ${DIRS}; do\
		make -C $${DIR} clean;\
	done
	rm -f ${OBJS}
