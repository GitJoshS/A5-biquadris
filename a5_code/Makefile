CXX = g++-14 -std=c++20 -fmodules-ts
CXXFLAGS = -Wall -g
HEADERFLAGS = -c -x c++-system-header

EXEC = exec

# Precompiled modules
MODULES = vector memory iostream utility string

# Source directories
BLOCK_DIR = block
BOARD_DIR = board
COMMAND_DIR = command
GAME_DIR = game
DISPLAY_DIR = game_display
LEVEL_DIR = level
MAIN_DIR = main
PLAYER_DIR = player

# Interface files (non-impl .cc files, compiled first as modules)
BLOCK_IFACE = $(filter-out $(BLOCK_DIR)/%impl.cc, $(wildcard $(BLOCK_DIR)/*.cc))
BOARD_IFACE = $(filter-out $(BOARD_DIR)/%impl.cc, $(wildcard $(BOARD_DIR)/*.cc))
COMMAND_IFACE = $(filter-out $(COMMAND_DIR)/%impl.cc, $(wildcard $(COMMAND_DIR)/*.cc))
GAME_IFACE = $(filter-out $(GAME_DIR)/%impl.cc, $(wildcard $(GAME_DIR)/*.cc))
DISPLAY_IFACE = $(filter-out $(DISPLAY_DIR)/%impl.cc, $(wildcard $(DISPLAY_DIR)/*.cc))
LEVEL_IFACE = $(filter-out $(LEVEL_DIR)/%impl.cc, $(wildcard $(LEVEL_DIR)/*.cc))
PLAYER_IFACE = $(filter-out $(PLAYER_DIR)/%impl.cc, $(wildcard $(PLAYER_DIR)/*.cc))

# All interface files
INTERFACES = $(BLOCK_IFACE) $(BOARD_IFACE) $(COMMAND_IFACE) $(GAME_IFACE) $(DISPLAY_IFACE) $(LEVEL_IFACE) $(PLAYER_IFACE)

# Implementation files (must be compiled after interfaces)
BLOCK_IMPL = $(wildcard $(BLOCK_DIR)/*-impl.cc)
BOARD_IMPL = $(wildcard $(BOARD_DIR)/*-impl.cc)
COMMAND_IMPL = $(wildcard $(COMMAND_DIR)/*-impl.cc)
GAME_IMPL = $(wildcard $(GAME_DIR)/*-impl.cc)
DISPLAY_IMPL = $(wildcard $(DISPLAY_DIR)/*-impl.cc)
LEVEL_IMPL = $(wildcard $(LEVEL_DIR)/*-impl.cc)
MAIN_IMPL = $(wildcard $(MAIN_DIR)/*.cc)
PLAYER_IMPL = $(wildcard $(PLAYER_DIR)/*-impl.cc)

# All implementation files
IMPLEMENTATIONS = $(BLOCK_IMPL) $(BOARD_IMPL) $(COMMAND_IMPL) $(GAME_IMPL) $(DISPLAY_IMPL) $(LEVEL_IMPL) $(MAIN_IMPL) $(PLAYER_IMPL)

# Object files from interface and implementation files
IFACE_OBJECTS = $(INTERFACES:.cc=.o)
IMPL_OBJECTS = $(IMPLEMENTATIONS:.cc=.o)
OBJECTS = $(IFACE_OBJECTS) $(IMPL_OBJECTS)

# Dependency files
DEPENDS = $(OBJECTS:.o=.d)

# Module cache files
MODULE_CACHE = $(addsuffix .gcm, $(MODULES))
IFACE_CACHE = $(INTERFACES:.cc=.gcm)

# Default target
.PHONY: all
all: modules interfaces $(EXEC)

# Precompile standard library modules
.PHONY: modules
modules:
	@for module in $(MODULES); do \
		if [ ! -f $$module.gcm ]; then \
			echo "Precompiling module: $$module"; \
			$(CXX) $(HEADERFLAGS) $$module; \
		fi \
	done

# Compile interface files first (they become modules)
.PHONY: interfaces
interfaces: modules $(IFACE_OBJECTS)

# Link object files to create executable
$(EXEC): $(IMPL_OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(EXEC)

# Compile interface files to object files (and create module cache)
$(IFACE_OBJECTS): %.o: %.cc
	$(CXX) $(CXXFLAGS) -MMD -c $< -o $@

# Compile implementation files to object files (after interfaces are built)
$(IMPL_OBJECTS): %.o: %.cc $(IFACE_OBJECTS)
	$(CXX) $(CXXFLAGS) -MMD -c $< -o $@

# Include dependency files
-include $(DEPENDS)

# Clean target
.PHONY: clean
clean:
	rm -f $(OBJECTS) $(DEPENDS) $(EXEC) $(MODULE_CACHE) $(IFACE_CACHE)

# Clean and rebuild
.PHONY: rebuild
rebuild: clean all
