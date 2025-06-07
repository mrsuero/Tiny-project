# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++11 -I./PartA/include -Wall -O2

# Source files and target executable
SRC = LinearRegressionPrediction.cpp PartA/source/matrix.cpp PartA/source/vector.cpp
TARGET = LinearRegressionPrediction

# Default target: build the executable
all: $(TARGET)

# Build rule: compile and link all source files
$(TARGET): $(SRC)
    $(CXX) $(CXXFLAGS) -o $@ $(SRC)

# Clean rule: remove the executable file
clean:
    rm -f $(TARGET)

# Run rule: execute the program
run: $(TARGET)
	./$(TARGET)