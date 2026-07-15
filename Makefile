# Compiler settings
CXX = g++
CXXFLAGS = -I inc -O3 -Wall -Wextra

# Files and output
SRCS = src/main.cpp src/board.cpp src/ai.cpp
OBJS = $(SRCS:.cpp=.o)
TARGET = reversi

# Default target
all: $(TARGET)

# Link the object files into the final executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Compile .cpp files into .o object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Run the game
run: $(TARGET)
	./$(TARGET)

# Clean up build files
clean:
	rm -f $(OBJS) $(TARGET)