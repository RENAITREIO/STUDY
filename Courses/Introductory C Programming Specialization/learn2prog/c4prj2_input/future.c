#include "future.h"

void add_future_card(future_cards_t *fc, size_t index, card_t *ptr) {
    if (index >= fc->n_decks) {
        fc->decks = realloc(fc->decks, (index + 1) * sizeof(deck_t));
        for (int i = fc->n_decks; i <= index; i++) {
            fc->decks[i].cards = NULL;
            fc->decks[i].n_cards = 0;
        }
        fc->n_decks = index + 1;
    }
    fc->decks[index].cards = realloc(fc->decks[index].cards, (fc->decks[index].n_cards + 1) * sizeof(card_t *));
    fc->decks[index].cards[fc->decks[index].n_cards] = ptr;
    fc->decks[index].n_cards++;
}

void future_cards_from_deck(deck_t * deck, future_cards_t * fc) {
    for (int i = 0; i < fc->n_decks; i++) {
        if (fc->decks[i].n_cards > 0) {
            for (int j = 0; j < fc->decks[i].n_cards; j++) {
                fc->decks[i].cards[j]->value = deck->cards[i]->value;
                fc->decks[i].cards[j]->suit = deck->cards[i]->suit;
            }
        }
    }
}