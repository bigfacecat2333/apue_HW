all:relay  # all 后面室执行文件
CFLAGS += -Wall -g
LDFLAGS += -lpthread -lstdc++ 

relay:main.c relay.o
	gcc $^ $(CFLAGS) $(LDFLAGS) -o $@

relay.o:relay.c
	gcc $^ $(CFLAGS) $(LDFLAGS) -c -o $@
clean:
	rm -rf *.o relay