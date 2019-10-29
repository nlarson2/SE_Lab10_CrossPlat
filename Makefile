L_INCLUDES = -I./glad/include -I./glfwLinux/include
L_LIBRARY = -L./glfwLinux/src -lglfw3 -lGL -lX11 -lpthread -lXrandr -lXi -ldl

W_INCLUDES = -I./glad/include -I./glfwWindows/include
W_LIBRARY = -L./glfwWindows/lib-mingw-w64 -lglfw3 -lopengl32 -lgdi32 -lkernel32 -lpthread
#LIBRARY = -L./glfw/src -lglfw3 -lGL -lX11 -lpthread -lXrandr -lXi -ldl

ifeq ($(OS),Windows_NT)
PLATFORM=windows
else
UNAME_S := $(shell uname -s)
endif

all: main

main: main.cpp src/Image.h src/Image.cpp src/Menu.h src/Menu.cpp \
src/Game.h src/Game.cpp src/Map.h src/Map.cpp src/Enemy.h src/Enemy.cpp \
src/Player.h src/Player.cpp src/Battle.h src/Battle.cpp src/Winner.h \
src/Winner.cpp src/GameOver.h src/GameOver.cpp src/GameScene.h

ifeq ($(OS),Windows_NT)
	g++ -g glad/src/glad.c main.cpp src/Image.cpp src/Menu.cpp src/Game.cpp \
	src/Map.cpp src/Enemy.cpp src/Player.cpp src/Winner.cpp src/Battle.cpp \
	src/GameOver.cpp -Llibraries/ -Ilibrarires/-lggfonts  -L./glfwWindows/lib-mingw-w64 \
	-lglfw3 -lopengl32 -lgdi32 -lkernel32 -lpthread -I./glad/include \
	-I./glfwWindows/include -ogame  -DWINDOWS
endif 
ifeq ($(UNAME_S),Linux)
	g++ -g glad/src/glad.c main.cpp src/Image.cpp src/Menu.cpp src/Game.cpp \
	src/Map.cpp src/Enemy.cpp src/Player.cpp src/Winner.cpp src/Battle.cpp \
	src/GameOver.cpp libraries/libggfonts.a -L./glfwLinux/src -lglfw3 -lGL \
	-lX11  -lXrandr -lXi -ldl -lpthread  -I./glad/include -I./glfwLinux/include \
	-ogame
endif

run:

ifeq ($(OS),Windows_NT)
	game
endif
ifeq ($(UNAME_S),Linux)
	game
endif

clean:
ifeq ($(OS),Windows_NT)
	DEL game.exe
endif
ifeq ($(UNAME_S),Linux)
	rm -rf game*
endif
