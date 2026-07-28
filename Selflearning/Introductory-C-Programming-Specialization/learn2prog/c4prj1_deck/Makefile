CFLAGS= -ggdb3 -Wall -Werror -pedantic -std=gnu99 -g

test_deck: deck.o test_deck.o cards.o eval.o
	gcc -o test_deck test_deck.c deck.o cards.o eval.o $(CLAGS) 

deck.o: deck.c
	gcc -c deck.c $(CFLAGS)

test_deck.o: test_deck.c
	gcc -c test_deck.c $(CFLAGS)

cards.o: cards.c
	gcc -c cards.c $(CFLAGS)

eval.o: eval.c
	gcc -c eval.c $(CFLAGS)

deck.o:deck.h
eval.o:eval.h
cards.o:cards.h
