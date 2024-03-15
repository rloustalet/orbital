CXX = g++
CXXFLAGS = -Wall -g
SRC = main.cpp
OBJ = $(SRC:.cpp=.o)
TARGET = exec

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

testing:
	g++ -o test/test_object.o test/test_object.cpp src/object.cpp -I./src
	./test/test_object.o
	g++ -o test/test_util.o test/test_util.cpp src/util.cpp -I./src
	./test/test_util.o
clean:
	rm -f $(OBJ) $(TARGET)