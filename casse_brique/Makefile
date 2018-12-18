CC=gcc
CFLAGS=-O2 `sdl2-config --cflags`
LINK=-O2 `sdl2-config --libs` -lSDL2_image -lSDL2main -lSDL2 -lSDL2_ttf -lSDL2_mixer -lm
SRC=main.c
OBJ=$(SRC:.c=.o)

%.o:	%.c
	$(CC) -c $(CFLAGS) $<

casse_brique:	$(OBJ)
	$(CC) $(OBJ) $(LINK) -o $@

clean:
	rm *.o main



