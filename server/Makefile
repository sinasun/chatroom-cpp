# Compiler options
CXX = g++
CXXFLAGS = -std=c++17 -Wall

# Source files
SRCS = server.cpp user.cpp file.cpp room.cpp

# Object files
OBJS = $(SRCS:.cpp=.o)

# Executable name
EXEC = server

# Rule to build the executable
$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(EXEC)

# Rule to build object files
%.o: %.cpp %.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean rule
clean:
	rm -f $(OBJS) $(EXEC)
