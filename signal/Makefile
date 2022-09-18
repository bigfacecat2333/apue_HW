CFLAGS+=-Wall -g -lstdc++ -lpthread -D_FILE_OFFSET_BITS=64 -D_GUN_SOURCE -fopenmp -O0
bin = ./bin/
src = $(wildcard *.c)  # wildcard 表示遍历所有.c文件
obj = $(patsubst %.c,%.o,$(src))  # $(patsubst 原模式， 目标模式， 文件列表)
# 在$(patsubst %.c,%.o,$(src) )中，patsubst把$(src)中的变量符合后缀是.c的全部替换成.o
ALL:$(obj)

%:%.c
	gcc $< -o $(bin)$@ $(CFLAGS)

clean:
	-rm -i $(bin)*

.PHONY:clean ALL