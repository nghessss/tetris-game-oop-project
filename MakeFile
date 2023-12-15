all:
	g++ -Isrc/include -Lsrc/lib -o main code/*.cpp code/menu/*.cpp -lmingw32 -lSDL2_image -lSDL2main -lSDL2 -lSDL2_ttf -lSDL2_mixer && start main
