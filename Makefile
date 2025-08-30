CXX := g++
TARGET := myProject_bin

# Use pkg-config if available (recommended)
RAYLIB_CFLAGS  := $(shell pkg-config --cflags raylib 2>/dev/null)
RAYLIB_LIBS    := $(shell pkg-config --libs raylib 2>/dev/null)
SFML_CFLAGS    := $(shell pkg-config --cflags sfml-graphics sfml-window sfml-system sfml-audio sfml-network 2>/dev/null)
SFML_LIBS      := $(shell pkg-config --libs   sfml-graphics sfml-window sfml-system sfml-audio sfml-network 2>/dev/null)

# Fallbacks if pkg-config isn’t set up
ifeq ($(strip $(RAYLIB_LIBS)),)
  RAYLIB_LIBS := -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
endif
ifeq ($(strip $(SFML_LIBS)),)
  SFML_LIBS := -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lsfml-network
endif

CXXFLAGS := -std=c++17 -O0 -g -Wall -Wextra -fno-sanitize-recover=all $(RAYLIB_CFLAGS) $(SFML_CFLAGS)
LDFLAGS  := $(RAYLIB_LIBS) $(SFML_LIBS)

SRC := $(wildcard *.cpp)
OBJ := $(SRC:.cpp=.o)

.PHONY: all clean rebuild

# Always clean first, then rebuild everything (default target for F5)
all: rebuild

rebuild: clean $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(OBJ) -o $@ $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)
