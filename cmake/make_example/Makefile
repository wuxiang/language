CC = g++

#dependence dir
DIRS = dir src
LD = -L. -Ldir -Lsrc -ldir -lsrc

#output
OUTPUT = test
OBJS = test.o

all: compile link

${OBJS}: test.cpp
	${CC} -c test.cpp

compile:${OBJS}
	for DIR in ${DIRS}; do\
		echo $${DIR};\
		cd $${DIR};\
		echo $${DIR};\
		make -C $${DIR} compile;\
	done

link:
	for DIR in ${DIRS}; do\
		make -C $${DIR} link;\
	done
	g++ -o ${OUTPUT} ${OBJS} ${LD}

clean:
	for DIR in ${DIRS}; do\
		make -C $${DIR} clean;\
	done
	rm -f ${OBJS}
