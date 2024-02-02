main: main.c helloworld.c helloworld.h
	gcc -o helloworld main.c helloworld.c -I.

all: main.c seeing.c helloworld.c findmax.c geometry.c fish.c helloworld.h
	gcc -c main.c seeing.c helloworld.c findmax.c geometry.c fish.c -I.

aux: seeing.c helloworld.c findmax.c geometry.c fish.c helloworld.h
	gcc -c seeing.c helloworld.c findmax.c geometry.c fish.c -I.

seeing: seeing.o helloworld.o
	gcc -I. -o seeing seeing.o helloworld.o

findmax: findmax.o helloworld.o
	gcc -I. -o findmax findmax.o helloworld.o

geometry: geometry.o helloworld.o
	gcc -I. -o geometry geometry.o helloworld.o

fish: fish.o helloworld.o
	gcc -I. -o fish fish.o helloworld.o

clean:
	rm -f *.o *.exe *.stackdump

git:
	git add .
	git commit && git push -u origin main
