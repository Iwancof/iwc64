
all:
	gcc -Wall -g -O3 ./common.c ./pipeline.c ./instruction.c ./cpu.c ./iwc64.c -o ./iwc64

clean:
	rm ./iwc64
