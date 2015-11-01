all: paralelo.c
	gcc -g -Wall -o paralelo paralelo.c -lpthread

clean:
	$(RM) paralelo
