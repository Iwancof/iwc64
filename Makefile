
all:
	gcc -Wall -g -O3 ./pipeline.c ./instruction.c ./cpu.c ./iwc64.c -o ./run

clean:
	rm ./run
