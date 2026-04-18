#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include "cards.h"
#include "deck.h"
#include "eval.h"
#include "future.h"
#include "input.h"



int main(int argc, char ** argv) {
  //YOUR CODE GOES HERE
  int num_trials;
  if (argc == 2) {
    num_trials = 10000;
  }
  else if (argc == 3) {
    num_trials = atoi(argv[2]);
  }
  else {
    fprintf(stderr, "Usage: %s file [times]\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  FILE *input = fopen(argv[1], "r");
  if (input == NULL) {
    fprintf(stderr, "Fail to open file %s\n", argv[1]);
    exit(EXIT_FAILURE);
  }

  size_t n_hands = 0;
  future_cards_t *fc = malloc(sizeof(*fc));
  fc->n_decks = 0;
  fc->decks = NULL;
  deck_t ** hands = read_input(input, &n_hands, fc);
  deck_t * remain_deck = build_remaining_deck(hands, n_hands);
  

  size_t score[n_hands + 1];
  for (int i = 0; i < n_hands + 1; i++)
    score[i] = 0;
  
  for (int i = 0; i < num_trials; i++) {
    shuffle(remain_deck);
    future_cards_from_deck(remain_deck, fc);
    // print_hand(hands[0]);
    // printf("\n");
    // print_hand(hands[1]);printf("\n");printf("\n");
    int winner = 0;
    int tie = 0;
    for (int j = 0; j < n_hands; j++) {
      deck_t *a = malloc(sizeof(*a));
      a->n_cards = 0;
      a->cards = NULL;
      for (int i = 0; i < hands[winner]->n_cards; i++) {
        add_card_to(a, *(hands[winner]->cards[i]));
      }
      deck_t *b = malloc(sizeof(*b));
      b->n_cards = 0;
      b->cards = NULL;
      for (int i = 0; i < hands[j]->n_cards; i++) {
        add_card_to(b, *(hands[j]->cards[i]));
      }

      int res = compare_hands(a, b);

      if (res > 0) {
        tie = 0;
      }
      else if (res < 0) {
        winner = j;
        tie = 0;
      }
      else {
        tie = 1;
      }

      free_deck(a);
      free_deck(b);
    }
    if (tie == 1){
      score[n_hands]++;
    }
    else {
      score[winner]++;
    }
  }

  for (size_t i = 0; i < n_hands; i++) {
    printf("Hand %zu won %u / %u times (%.2f%%)\n", i, (unsigned)score[i], num_trials, (float)score[i] / num_trials * 100);
  }
  printf("And there were %u ties\n", (unsigned)score[n_hands]);

  for (int i = 0; i < n_hands; i++) {
    free_deck(hands[i]);
  }
  free(hands);
  free_deck(remain_deck);
  for (int i = 0; i < fc->n_decks; i++) {
    free(fc->decks[i].cards);
  }
  free(fc->decks);
  free(fc);
  fclose(input);
  return EXIT_SUCCESS;
}
