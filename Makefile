all:
	@g++ -Wno-narrowing -I include -L lib -o main \
	src/main.cpp src/rendering.cpp \
	src/util/structs/vec2f.cpp \
	src/util/random.cpp src/util/stringUtils.cpp src/util/time.cpp \
	src/assets/sprite.cpp src/assets/TextureHandler.cpp \
	src/game/map/map.cpp src/game/map/maploader.cpp \
	src/game/game.cpp \
	-lmingw32 -lSDL2main -llibSDL2 -lSDL2_image
	@main.exe
	@del main.exe