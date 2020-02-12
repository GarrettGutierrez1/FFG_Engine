# A Makefile for building FFG_Engine.
#
# To setup:
# - Change BOOST_INCLUDE_DIR to the boost directory.
# - Change SDL2_INCLUDE_DIR to the include directory of your SDL2 development library installation.
# - Change SDL2_LIBRARY_DIR to the lib directory of your SDL2 development library installation.
#
# To build: 
#	make              (builds main.cpp in the root and FFG dependencies as well)
#	make test_simple  (builds a simple test, single window with minimal functionality)
#	make test_build   (builds a comprehensive functionality test)
#	make temp         (builds main.cpp in the root)
#	make docs
#
# To run:
#	./main.exe
#	./test_simple.exe
#	./test.exe

# ---------- COMPILER ----------
CC = g++

# ---------- DIRECTORIES ----------
BOOST_INCLUDE_DIR = C:\boost_1_69_0
SDL2_INCLUDE_DIR = C:\MinGW\include
SDL2_LIBRARY_DIR = C:\MinGW\lib
FFG_SOURCE_DIR = FFG\source
FFG_INCLUDE_DIR = FFG\include
FFG_EXT_SOURCE_DIR = FFG_EXT\source
FFG_EXT_INCLUDE_DIR = FFG_EXT\include
TEST_SOURCE_DIR = test\source
TEST_INCLUDE_DIR = test\include

# ---------- OBJECTS ----------
FFG_OBJS += $(FFG_SOURCE_DIR)\FFG_Engine.cpp
FFG_OBJS += $(FFG_SOURCE_DIR)\FFG_Event.cpp
FFG_OBJS += $(FFG_SOURCE_DIR)\FFG_Renderer.cpp
FFG_OBJS += $(FFG_SOURCE_DIR)\FFG_StateManager.cpp
FFG_OBJS += $(FFG_SOURCE_DIR)\FFG_Texture.cpp
FFG_OBJS += $(FFG_SOURCE_DIR)\FFG_Timer.cpp

TEST_SIMPLE_OBJS += $(TEST_SOURCE_DIR)\EmptyState.cpp

TEST_OBJS += $(TEST_SOURCE_DIR)\Draw1TestState.cpp
TEST_OBJS += $(TEST_SOURCE_DIR)\Draw2TestState.cpp
TEST_OBJS += $(TEST_SOURCE_DIR)\Draw3TestState.cpp
TEST_OBJS += $(TEST_SOURCE_DIR)\EventTestState.cpp
TEST_OBJS += $(TEST_SOURCE_DIR)\PrimitiveTestState.cpp
TEST_OBJS += $(TEST_SOURCE_DIR)\TargetTestState.cpp
TEST_OBJS += $(TEST_SOURCE_DIR)\TimerTestState.cpp
TEST_OBJS += $(TEST_SOURCE_DIR)\WindowTestState.cpp

FFG_EXT_OBJS += $(FFG_EXT_SOURCE_DIR)\FFG_XML.cpp
FFG_EXT_OBJS += $(FFG_EXT_SOURCE_DIR)\FFG_Allocator.cpp

# ---------- MAIN OBJECTS ----------
ALL_MAIN += main.cpp
TEST_SIMPLE_MAIN += $(TEST_SOURCE_DIR)\test_simple.cpp
TEST_MAIN += $(TEST_SOURCE_DIR)\test.cpp

# ---------- INCLUDE PATHS ----------
INCLUDE_PATHS += -I$(BOOST_INCLUDE_DIR)
INCLUDE_PATHS += -I$(SDL2_INCLUDE_DIR)
INCLUDE_PATHS += -I$(FFG_INCLUDE_DIR)
INCLUDE_PATHS += -I$(FFG_EXT_INCLUDE_DIR)
INCLUDE_PATHS += -I$(TEST_INCLUDE_DIR)

# ---------- LIBRARY PATHS ----------
LIBRARY_PATHS += -L$(SDL2_LIBRARY_DIR)

# ---------- COMPILER FLAGS ----------
# Suppresses warnings:
# COMPILER_FLAGS += -w

# Create as GUI application:
# COMPILER_FLAGS += -Wl,-subsystem,windows

# Create as a GUI application (alternate):
# COMPILER_FLAGS += -mwindows

# ---------- LINKER FLAGS ----------
LINKER_FLAGS += -lmingw32 -lSDL2main -lSDL2 -lSDL2_image

# ---------- OBJECT NAME ----------
ALL_NAME = main
TEST_SIMPLE_NAME = test_simple
TEST_NAME = test

# ---------- TARGETS ----------
all: $(FFG_OBJS) $(ALL_MAIN)
	$(CC) $(FFG_OBJS) $(ALL_MAIN) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(ALL_NAME)

test_simple: $(FFG_OBJS) $(TEST_SIMPLE_OBJS) $(TEST_SIMPLE_MAIN)
	$(CC) $(FFG_OBJS) $(TEST_SIMPLE_OBJS) $(TEST_SIMPLE_MAIN) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(LINKER_FLAGS) -o $(TEST_SIMPLE_NAME)

test_build: $(FFG_OBJS) $(TEST_OBJS) $(TEST_MAIN)
	$(CC) $(FFG_OBJS) $(TEST_OBJS) $(TEST_MAIN) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(LINKER_FLAGS) -o $(TEST_NAME)

temp: main.cpp
	$(CC) $(FFG_EXT_OBJS) $(INCLUDE_PATHS) main.cpp -o temp
	./temp.exe

docs: doxygen
	doxygen