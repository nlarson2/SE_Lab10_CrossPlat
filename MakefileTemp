all: game

game: main.cpp src/Image.h src/Image.cpp src/Menu.h src/Menu.cpp src/Game.h src/Game.cpp src/Map.h src/Map.cpp src/Enemy.h src/Enemy.cpp src/Player.h src/Player.cpp src/Battle.h src/Battle.cpp src/Winner.h src/Winner.cpp src/GameOver.h src/GameOver.cpp src/GameScene.h
	g++ main.cpp -g src/Image.cpp src/Menu.cpp src/Game.cpp src/Map.cpp src/Enemy.cpp src/Player.cpp src/Winner.cpp src/Battle.cpp src/GameOver.cpp libraries/libggfonts.a -lGL -lGLU -lX11 -lm -Wall -ogame

clean:
	rm -rf game