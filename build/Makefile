default: desktop	
	Game.exe

desktop:
	@g++ \
	../src/*.cpp \
	../src/assets/*.cpp \
	../src/game/*.cpp \
	../src/game/map/*.cpp \
	../src/util/*.cpp \
	../src/util/structs/*.cpp \
	-o Game.exe -O2 -Wall -Wno-missing-braces -I ../include/win/ -L ../lib/win/ -lraylib -lopengl32 -lgdi32 -lwinmm

web: 
	@emcc \
	../src/main.cpp \
	../src/rendering.cpp \
	../src/assets/sprite.cpp \
	../src/assets/TextureHandler.cpp \
	../src/game/game.cpp \
	../src/game/map/map.cpp \
	../src/game/map/maploader.cpp \
	../src/util/random.cpp \
	../src/util/stringUtils.cpp \
	../src/util/time.cpp \
	../src/util/structs/vec2f.cpp \
	-o game.html -Os -Wall -Wno-narrowing -Wno-missing-braces ../lib/web/libraylib.a -I ../include/web/ -L ../lib/web/ -s USE_GLFW=3 -s ASYNCIFY -DPLATFORM_WEB \
	--preload-file res/ \
	-s EXPORTED_FUNCTIONS="['_main', '_malloc']" \
	-s EXPORTED_RUNTIME_METHODS=["ccall"] \
	-s TOTAL_MEMORY=512mb \
	-s INITIAL_MEMORY=256mb \
	-sALLOW_MEMORY_GROWTH \
	-sASSERTIONS --profiling-funcs -g \
	--shell-file ./shell.html

build: desktop web