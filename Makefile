all:
	@g++ -Wno-narrowing -I include -L lib -o main \
	src/main.cpp src/game.cpp src/rendering.cpp \
	src/util/random.cpp src/util/time.cpp \
	src/data/TextureHandler.cpp src/data/vec2f.cpp src/data/sprite.cpp \
	-lmingw32 -lSDL2main -llibSDL2 -lSDL2_image
	@main.exe
	@del main.exe