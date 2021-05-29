exec = Monke.out
sources = $(wildcard src/*.c)
objects = $(sources:.c=.o)
flags = -g

$(exec): $(objects)
	gcc $(objects) $(flags) -o $(exec)

%.o: %.c include/%.h
	gcc -c $(flags) $< -o $@

install:
	make
	cp ./Monke.out /usr/local/bin/Monke

clean:
	-rm *.out
	-rm *.o
	-rm src/*.o
