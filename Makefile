CC = gcc
LDFLAGS = -lSDL2

OUT = out
OBJ = main.o event.o render.o

.PHONY: clean

$(OUT): $(OBJ)
	$(CC) -o $(OUT) *.o $(LDFLAGS)

clean:
	rm -rf *.o $(OUT)

main.o: main.c main.h event.o render.o
	$(CC) -o main.o -c main.c

event.o: event.c event.h main.h
	$(CC) -o event.o -c event.c

render.o: render.c render.h main.h
	$(CC) -o render.o -c render.c
