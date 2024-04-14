CXX = g++
CXXFLAGS = -Wall -g
SRC = main.cpp
OBJ = $(SRC:.cpp=.o)
TARGET = exec
GNUPLOT := gnuplot

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

names := $(filter-out $@,$(MAKECMDGOALS))

.PHONY: plot3d
plot3d: check-objects
	@echo "Tracé du graphique 3D pour les objets: $(OBJECTS)"
	OBJECTS=$(subst :,\:,$(OBJECTS))
	$(eval CSV_STR := $(foreach obj,$(OBJECTS),'results/$(obj).csv' using 1:2:3 with points, ))
	$(GNUPLOT) -e "splot $(CSV_STR)" -p

check-objects:
ifndef OBJECTS
	$(error Veuillez spécifier les noms des objets. Utilisation: make plot3d OBJECTS=sun,mars,jupiter)
endif

graph:
	gnuplot graph.gnu -e -p


 disp_tot_energy:
	gnuplot tot_nrj.gnu -e -p