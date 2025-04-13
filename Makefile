# By Claude.ai
# Find all source files, excluding tests folder
SRCS := $(shell find . -name "*.cpp" -not -path "./tests/*")
OBJS := $(SRCS:.cpp=.o)

# Compile and link
simulos: $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up directive
clean:
	rm -f $(OBJS) simulos
