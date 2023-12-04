CXX := g++
CXXFLAGS := -std=c++11 -Wall -Wextra -pedantic

SRC_DIR := .
SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp, %.o, $(SRC_FILES))

.PHONY: all clean

all: xbuchm02

xbuchm02: $(OBJ_FILES)
	$(CXX) $(CXXFLAGS) $^ -o $@ $l -lsimlib3

%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ_FILES) xbuchm02
