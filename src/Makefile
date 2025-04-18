CC = gcc
CFLAGS = -Wall -Werror -Wextra -g

SRC_DIR = ../
BUILD_DIR = $(SRC_DIR)/build

OBJ_FILES = dijkstra.o queue.o stack.o draw_graph.o calculation.o graph.o

all: build

build: $(OBJ_FILES)
	$(CC) $(CFLAGS) $(OBJ_FILES) -o ../build/graph

dij: $(OBJ_FILES)
	$(CC) $(CFLAGS) $(OBJ_FILES) -o $(BUILD_DIR)/graph

dijkstra.o: dijkstra.c
	$(CC) $(CFLAGS) -c dijkstra.c

queue.o: queue.c
	$(CC) $(CFLAGS) -c queue.c

stack.o: stack.c
	$(CC) $(CFLAGS) -c stack.c

draw_graph.o: draw_graph.c
	$(CC) $(CFLAGS) -c draw_graph.c

graph.o: graph.c
	$(CC) $(CFLAGS) -c graph.c

calculation.o: calculation.c
	$(CC) $(CFLAGS) -c calculation.c


# Очистка
clean:
	rm -rf *.o rm -rf ../build/*

# Пересборка
rebuild: clean build

clean_build: 
	rm -rf *.o

check: rebuild
	clang-format -n *.c
	clang-format -n *.h
	clang-format -i *.c
	clang-format -i *.h
	cppcheck --enable=all --suppress=missingIncludeSystem .

run_leaks:
	leaks -atExit -- ../build/graph