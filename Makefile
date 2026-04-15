CC = gcc
CFLAGS = -Wall -c -g
LFLAGS = -Wall
SOURCES = main.c tc/tc.c snake/snake.c
OBJECT = main.o tc.o snake.o
TAGS = tags tc/tags snake/tags
EXE = snake_2.out

$(EXE): $(OBJECT)
	$(CC) -o $@ $(LFLAGS) $^

main.o: main.c tc/tc.h snake/snake.h
	$(CC) -o $@ $(CFLAGS) main.c

tc.o: tc/tc.h tc/tc.c
	$(CC) -o $@ $(CFLAGS) tc/tc.c

snake.o: tc/tc.h snake/snake.h snake/snake.c
	$(CC) -o $@ $(CFLAGS) snake/snake.c

clean:
	rm -f $(OBJECT) $(TAGS) $(EXE)

all: clean $(OBJECT) $(EXE)

clean_build: all

build_clean: $(OBJECT) $(EXE)
	rm -f $(OBJECT) $(TAGS)
