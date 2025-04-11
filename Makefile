# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -std=c++17

# Source files and object files
SRCS = main.cpp os.cpp filesystem/FileSystem.cpp shell/Shell.cpp cmdunit/CMDunit.cpp
OBJS = $(SRCS:.cpp=.o)

# Header directories
INCLUDES = -I. -I./filesystem -I./shell -I./cmdunit

# Target executable
TARGET = simulos

# Default target
all: $(TARGET)

# Linking rule
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compilation rule
%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# Clean rule
clean:
	rm -f $(OBJS) $(TARGET)

# Dependencies
main.o: main.cpp os.h
os.o: os.cpp os.h filesystem/FileSystem.h shell/Shell.h
filesystem/FileSystem.o: filesystem/FileSystem.cpp filesystem/FileSystem.h
shell/Shell.o: shell/Shell.cpp shell/Shell.h filesystem/FileSystem.h cmdunit/CMDunit.h
cmdunit/CMDunit.o: cmdunit/CMDunit.cpp cmdunit/CMDunit.h shell/Shell.h filesystem/FileSystem.h 

.PHONY: all clean
