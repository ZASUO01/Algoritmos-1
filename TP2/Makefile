CC = g++
CFLAGS = -Wall -Wextra -Iinclude -std=c++20

SRC = src
OBJ = obj
BIN = bin

TARGET = $(BIN)/main

SRCS = $(wildcard $(SRC)/*.cpp)
OBJS = $(SRCS:$(SRC)/%.cpp=$(OBJ)/%.o)

all: $(TARGET)

TARGET = $(BIN)/main

SRCS = $(wildcard $(SRC)/*.cpp)
OBJS = $(SRCS:$(SRC)/%.cpp=$(OBJ)/%.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) 

$(OBJ)/%.o: $(SRC)/%.cpp | $(OBJ)
	$(CC) $(CFLAGS) -c $< -o $@

test: $(TARGET)
	$(TARGET) < ./test/input1.txt
	$(TARGET) < ./test/input2.txt
	$(TARGET) < ./test/input3.txt
        
clean:
	rm -f $(TARGET) $(OBJS)
