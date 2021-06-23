
all:
	gcc -Wall -g -O0 ./pipeline.c ./instruction.c ./cpu.c ./iwc64.c -o ./run

clean:
	rm ./run
