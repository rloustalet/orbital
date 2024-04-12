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
	mkdir -p build
	mkdir -p results
	g++ -o build/main.o main.cpp src/object.cpp src/solarsystem.cpp -I./src -lcurl
	./build/main.o

documentation:
	doxygen docs/Doxyfile

clean:
	rm -f $(OBJ) $(TARGET)

graph:
	gnuplot graph.gnu -persist