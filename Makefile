CCC = g++
CCFLAGS = -O3 -ansi -Wall -pedantic

all: characteristics neighborhood popularity

characteristics: characteristics.o graph.o random.o
	$(CCC) $(CCFLAGS) -lm characteristics.o graph.o random.o -lm -o characteristics

characteristics.o: characteristics.cpp
	$(CCC) -c $(CCFLAGS) characteristics.cpp -o characteristics.o

neighborhood: neighborhood.o graph.o random.o
	$(CCC) $(CCFLAGS) -lm neighborhood.o graph.o random.o -lm -o neighborhood

neighborhood.o: neighborhood.cpp
	$(CCC) -c $(CCFLAGS) neighborhood.cpp -o neighborhood.o

popularity: popularity.o graph.o random.o
	$(CCC) $(CCFLAGS) -lm popularity.o graph.o random.o -lm -o popularity

popularity.o: popularity.cpp 
	$(CCC) -c $(CCFLAGS) popularity.cpp -o popularity.o

random.o: random.cpp random.h
	$(CCC) -c $(CCFLAGS) random.cpp -o random.o

graph.o: graph.cpp graph.h
	$(CCC) -c $(CCFLAGS) graph.cpp -o graph.o

clean:
	/bin/rm -rf *.o *~ characteristics neighborhood popularity
