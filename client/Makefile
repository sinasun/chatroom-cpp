# Compiler options
CXX = g++
CXXFLAGS = -std=c++17 -Wall

# Source files
SRCS = client.cpp menu.cpp user.cpp

# Object files
OBJS = $(SRCS:.cpp=.o)

# Executable name
EXEC = client

# Rule to build the executable
$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(EXEC)

# Rule to build object files
%.o: %.cpp %.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean rule
clean:
	rm -f $(OBJS) $(EXEC)
