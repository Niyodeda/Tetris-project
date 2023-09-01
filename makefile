all: tetris

tetris: tetris.c
	gcc -I SDL2-devel-2.28.2-mingw/SDL2/x86_64-w64-mingw32/include -L SDL2-devel-2.28.2-mingw/SDL2/x86_64-w64-mingw32/lib -o Tetris Tetris.c -lmingw32 -lSDL2main -lSDL2 -lSDl2_image

clean:
	rm -f tetris