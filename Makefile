
all:
	gcc -Wall -g -O3 ./common.c ./pipeline.c ./instruction.c ./cpu.c ./iwc64.c -o ./iwc64
	gcc -Wall -g -O3 ./common.c ./objdump.c ./instruction.c ./norn.c -o objdump


clean:
	rm ./iwc64
