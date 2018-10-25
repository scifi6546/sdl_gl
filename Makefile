CC=g++
LIBS=-lSDL2 -lGLEW  -lGL
CFLAGS=-I -w -ggdb
main: main.cpp
	$(CC) -c $(CFLAGS) main.cpp -o main.o
	$(MAKE) game_engine
	$(MAKE) shader
	$(MAKE) loadfile
	$(CC) -c $(CFLAGS) display.cpp -o display.o
	$(CC) -c $(CFLAGS) texture.cpp -o texture.o
	$(CC) -c $(CFLAGS) mesh.cpp -o mesh.o
	$(CC) -c $(CFLAGS) stb_image.c -o stb_image.o
	$(CC) -c $(CFLAGS) camera.cpp -o camera.o
	$(CC) -c $(CFLAGS) event.cpp -o event.o
	$(CC) -c $(CFLAGS) block.cpp -o block.o
	$(CC) $(CFLAGS) main.o game_engine.o shader.o loadfile.o display.o mesh.o texture.o stb_image.o camera.o event.o block.o -o out $(LIBS)
run:
	$(MAKE) main
	optirun ./out
game_engine: game_engine.cpp
	$(CC) -c $(CFLAGS) game_engine.cpp -o game_engine.o
shader: shader.cpp
	$(CC) -c $(CFLAGS) shader.cpp -o shader.o
loadfile: loadfile.cpp
	$(CC) -c $(CFLAGS) loadfile.cpp -o loadfile.o
debug:
	$(MAKE) main
	optirun gdb out
all:
	$(MAKE) main
