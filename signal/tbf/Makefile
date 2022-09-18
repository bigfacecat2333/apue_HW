all:mytbf
CFLAGS += -lstdc++ -Wall -g


mytbf:main.c mytbf.o
	gcc $^ -g -o $@ ${CFLAGS}

mytbf.o:mytbf.c
	gcc $^ -g -c -o $@ ${CFLAGS}
clean:
	rm -rf *.o mytbf