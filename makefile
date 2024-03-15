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
	g++ -o test/test_object.o test/test_object.cpp src/object.cpp src/util.cpp -I./src
	./test/test_object.o
	g++ -o test/test_util.o test/test_util.cpp src/util.cpp -I./src
	./test/test_util.o

run:
	g++ -o main.o main.cpp src/object.cpp src/solarsystem.cpp src/util.cpp -I./src
	./main.o

clean:
	rm -f $(OBJ) $(TARGET)