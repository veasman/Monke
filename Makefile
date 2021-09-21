exec = monke.out
sources = $(wildcard src/*.c)
objects = $(sources:.c=.o)
flags = -g

$(exec): $(objects)
	gcc $(objects) $(flags) -o $(exec)

%.o: %.c include/%.h
	gcc -c $(flags) $< -o $@

install:
	make
	cp ./monke.out /usr/local/bin/monke

clean:
	-rm *.out
	-rm *.o
	-rm src/*.o
