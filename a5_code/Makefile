CXX = g++-14 -std=c++20 -fmodules-ts
CXXFLAGS = -Wall -g
HEADERFLAGS = -c -x c++-system-header

SOURCES = level/level.cc level/level-impl.cc level/level0.cc level/level0-impl.cc level/level1.cc level/level1-impl.cc level/level2.cc level/level2-impl.cc level/level3.cc level/level3-impl.cc level/level4.cc level/level4-impl.cc level/levelFactory.cc level/levelFactory-impl.cc block/block.cc block/block-impl.cc block/iBlock.cc block/iBlock-impl.cc block/jBlock.cc block/jBlock-impl.cc block/lBlock.cc block/lBlock-impl.cc block/oBlock.cc block/oBlock-impl.cc block/sBlock.cc block/sBlock-impl.cc block/starBlock.cc block/starBlock-impl.cc block/tBlock.cc block/tBlock-impl.cc block/zBlock.cc block/zBlock-impl.cc board/board.cc board/board-impl.cc player/player.cc player/player-impl.cc game_display/display.cc game_display/display-impl.cc game_display/graphicDisplay.cc game_display/graphicDisplay-impl.cc game_display/textDisplay.cc game_display/textDisplay-impl.cc command/commandCenter.cc command/commandCenter-impl.cc game/game.cc game/game-impl.cc main/main.cc

OBJECTS = level/level.o level/level-impl.o level/level0.o level/level0-impl.o level/level1.o level/level1-impl.o level/level2.o level/level2-impl.o level/level3.o level/level3-impl.o level/level4.o level/level4-impl.o level/levelFactory.o level/levelFactory-impl.o block/block.o block/block-impl.o block/iBlock.o block/iBlock-impl.o block/jBlock.o block/jBlock-impl.o block/lBlock.o block/lBlock-impl.o block/oBlock.o block/oBlock-impl.o block/sBlock.o block/sBlock-impl.o block/starBlock.o block/starBlock-impl.o block/tBlock.o block/tBlock-impl.o block/zBlock.o block/zBlock-impl.o board/board.o board/board-impl.o player/player.o player/player-impl.o game_display/display.o game_display/display-impl.o game_display/graphicDisplay.o game_display/graphicDisplay-impl.o game_display/textDisplay.o game_display/textDisplay-impl.o command/commandCenter.o command/commandCenter-impl.o game/game.o game/game-impl.o main/main.o

HEADERS = vector memory iostream sstream cmath fstream utility cstdlib string

EXEC = exec

$(EXEC): $(SOURCES)
	$(CXX) $(HEADERFLAGS) $(HEADERS)
	$(CXX) $(CXXFLAGS) $(SOURCES) -c
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(EXEC)

.PHONY: clean
clean:
	rm -f $(OBJECTS) $(EXEC)
	rm -rf ./gcm.cache/