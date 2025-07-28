CFLAGS= -ggdb3 -Wall -Werror -pedantic -std=gnu99 -g

test_future: deck.o test_future.o cards.o eval.o future.o input.o
	gcc -o test_future test_future.c deck.o cards.o eval.o future.o input.o $(CLAGS) 

deck.o: deck.c
	gcc -c deck.c $(CFLAGS)

test_future.o: test_future.c
	gcc -c test_future.c $(CFLAGS)

cards.o: cards.c
	gcc -c cards.c $(CFLAGS)

eval.o: eval.c
	gcc -c eval.c $(CFLAGS)

future.o: future.c
	gcc -c future.c $(CFLAGS)

input.o: input.c
	gcc -c input.c $(CFLAGS)

deck.o:deck.h
eval.o:eval.h
cards.o:cards.h
input.o:input.h