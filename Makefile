
CC=g++
CFLAGS=-Wall
LDFLAGS=
EXEC=algo
LIBS=-lX11 -ljpeg -lpthread


all: $(EXEC)

algo: graph.o LinkedBlockList.o maxflow.o GCoptimization.o main.o
	$(CC) -o $@ $^ $(LDFLAGS) $(LIBS)

main.o: header.h

GCoptimization.o: GCoptimization.h LinkedBlockList.h

LinkedBlockList.o: LinkedBlockList.h

graph.o: graph.h

maxflow.o: graph.h

%.o: %.cpp
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm -rf *.o

mrproper: clean
	rm -rf $(EXEC)