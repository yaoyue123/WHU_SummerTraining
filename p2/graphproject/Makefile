# 井号开头的行是一个注释
# 设置 C 语言的编译器
cc = gcc

# -g 增加调试信息
# -Wall 打开大部分警告信息
CFLAGS = -g -Wall

# 整理一下 main 依赖哪些目标文件
MAINOBJS = main.o search.o stats.o

search-cli: main.o
	cc -o search-cli main.o
search.o: search.c search.h
	cc -c -o search.o search.c
stats.o: stats.c stats.h
	cc -c -o stats.o stats.c
main.o: main.c search.h stats.h
	cc -c main.c search.c stats.c
.PHONY:clean
clean:
	rm -rf stats.o search.o main.o search-cli
