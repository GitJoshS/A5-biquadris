CXX = g++-14 -std=c++20 -fmodules-ts
CXXFLAGS = -Wall -g
HEADERFLAGS = -c -x c++-system-header

SOURCES = level/level.cc level/level-impl.cc level/level0.cc level/level0-impl.cc level/level1.cc level/level1-impl.cc level/level2.cc level/level2-impl.cc level/level3.cc level/level3-impl.cc level/level4.cc level/level4-impl.cc level/levelFactory.cc level/levelFactory-impl.cc block/block.cc block/block-impl.cc block/iBlock.cc block/iBlock-impl.cc block/jBlock.cc block/jBlock-impl.cc block/lBlock.cc block/lBlock-impl.cc block/oBlock.cc block/oBlock-impl.cc block/sBlock.cc block/sBlock-impl.cc block/starBlock.cc block/starBlock-impl.cc block/tBlock.cc block/tBlock-impl.cc block/zBlock.cc block/zBlock-impl.cc board/board.cc board/board-impl.cc player/player.cc player/player-impl.cc game_display/display.cc game_display/display-impl.cc game_display/window.cc game_display/window-impl.cc game_display/graphicDisplay.cc game_display/graphicDisplay-impl.cc game_display/textDisplay.cc game_display/textDisplay-impl.cc command/commandCenter.cc command/commandCenter-impl.cc game/game.cc game/game-impl.cc main/main.cc

OBJECTS = level.o level-impl.o level0.o level0-impl.o level1.o level1-impl.o level2.o level2-impl.o level3.o level3-impl.o level4.o level4-impl.o levelFactory.o levelFactory-impl.o block.o block-impl.o iBlock.o iBlock-impl.o jBlock.o jBlock-impl.o lBlock.o lBlock-impl.o oBlock.o oBlock-impl.o sBlock.o sBlock-impl.o starBlock.o starBlock-impl.o tBlock.o tBlock-impl.o zBlock.o zBlock-impl.o board.o board-impl.o player.o player-impl.o display.o display-impl.o window.o window-impl.o graphicDisplay.o graphicDisplay-impl.o textDisplay.o textDisplay-impl.o commandCenter.o commandCenter-impl.o game.o game-impl.o main.o

HEADERS = vector memory iostream sstream algorithm climits cmath fstream utility cstdlib string



EXEC = biquadris

$(EXEC): $(SOURCES)
	$(CXX) $(HEADERFLAGS) $(HEADERS)
	$(CXX) $(CXXFLAGS) $(SOURCES) -c
	$(CXX) $(CXXFLAGS) $(OBJECTS) -lX11 -o $(EXEC)

.PHONY: clean
clean:
	rm -f $(OBJECTS) $(EXEC)
	rm -rf ./gcm.cache/
