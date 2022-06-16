all: main sem_child chan enc

main: main.c shared_memory.o read_write.o
	gcc -o exe main.c shared_memory.o read_write.o -lm -lpthread -lrt -lcrypto

sem_child: shared_memory.o read_write.o sem_child.c
	gcc -o sem_child shared_memory.o read_write.o sem_child.c -lm -lpthread -lrt -lcrypto

chan : shared_memory.o read_write.o chan.c
	gcc -o chan shared_memory.o read_write.o chan.c -lm -lpthread -lrt -lcrypto

enc : enc.h shared_memory.o read_write.o enc.c
	gcc -o enc enc.h shared_memory.o read_write.o enc.c -lm -lpthread -lrt -lcrypto

clean:
	rm chan enc exe sem_child read_write.o shared_memory.o
