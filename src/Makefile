XXFLAGS = -std=c++11 -Wall -Wextra -pedantic
LDFLAGS = -L/usr/local/lib
LIBS = -lsimlib

SRC_DIR := ./
SRCS := $(wildcard $(SRC_DIR)/*.cpp)
OBJS := $(patsubst $(SRC_DIR)/%.cpp, %.o, $(SRCS))

TARGET = xbuchm02

all: $(TARGET)

$(TARGET): $(OBJS)
        $(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS) $(LIBS)

%.o: $(SRC_DIR)/%.cpp
        $(CXX) $(CXXFLAGS) -c $< -o $@

clean:
        rm -f $(OBJS) $(TARGET)
