#include <stdio.h>
#include "deck.h"
#include "cards.h"
#include "eval.h"

unsigned * get_match_counts(deck_t * hand);

int main(void) {
	deck_t *deck = malloc(sizeof(deck_t));
	deck->n_cards = 0;
	deck->cards = NULL;
	card_t c = {.value = 3, .suit = CLUBS};
	add_card_to(deck, c);
	deck_t *tmp = build_remaining_deck(&deck, 1);
	unsigned *t = get_match_counts(tmp);
	for (int i = 0; i < tmp->n_cards; i++) {
		printf("%d ", t[i]);
	}
	free_deck(tmp);
	free_deck(deck);
	return 0;
}
