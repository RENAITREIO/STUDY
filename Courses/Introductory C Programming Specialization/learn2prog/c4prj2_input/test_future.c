#include <stdio.h>
#include "future.h"
#include "input.h"

int main(void) {
    future_cards_t fc;
    fc.decks = NULL;
    fc.n_decks = 0;

    // card_t ptr;
    // ptr.suit = 3;
    // ptr.value = 3;
    
    // deck_t deck = {.n_cards = 0};
    // deck.cards = NULL;
    
    FILE *input = fopen("input.txt", "r");
    size_t n_hands = 0;
    deck_t **res = read_input(input, &n_hands, &fc);

    for (int i = 0; i < n_hands; i++) {
        print_hand(res[i]);
    }
    printf("\n\n\n");
    for (int i = 0; i < fc.n_decks; i++) {
        printf("%ld ", fc.decks[i].n_cards);
    }
    // for (size_t i = 0; i < n_hands; i++)
    // {
    //     free_deck(res[i]);
    // }
    // for (size_t i = 0; i < fc.n_decks; i++)
    // {
    //     if (fc.decks[i].n_cards != 0) {
    //         free(fc.decks[i].cards);
    //     }
    // }
    // free_deck(fc.decks);
    fclose(input);
    
    return 0;
}