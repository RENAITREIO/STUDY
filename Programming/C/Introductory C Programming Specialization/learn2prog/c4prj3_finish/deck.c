#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "deck.h"

void free_deck(deck_t *deck);

void print_hand(deck_t * hand){
  for (int i = 0; i < hand->n_cards; i++) {
    print_card(*(hand->cards[i]));
    printf(" ");
  }
}

int deck_contains(deck_t * d, card_t c) {
  for (int i = 0; i < d->n_cards; i++) {
    if (d->cards[i]->value == c.value && d->cards[i]->suit == c.suit) {
      return 1;
    }
  }
  return 0;
}

void shuffle(deck_t * d){
  for (int i = 0; i < d->n_cards; i++) {
    int randNum = random() % d->n_cards;
    card_t *tmp = d->cards[i];
    d->cards[i] = d->cards[randNum];
    d->cards[randNum] = tmp;
  }
}

void assert_full_deck(deck_t * d) {
  for (unsigned i = 0; i < 52; i++) {
    assert(deck_contains(d, card_from_num(i)) == 1);
  }
}

void add_card_to(deck_t *deck, card_t c) {
  deck->cards = realloc(deck->cards, (deck->n_cards + 1) * sizeof(card_t *));
  deck->cards[deck->n_cards] = malloc(sizeof(card_t));
  deck->cards[deck->n_cards]->value = c.value;
  deck->cards[deck->n_cards]->suit = c.suit;
  deck->n_cards++;
}

card_t * add_empty_card(deck_t *deck) {
  card_t c = {.value = 0, .suit = 0};
  add_card_to(deck, c);
  return deck->cards[deck->n_cards - 1];
}

deck_t * make_deck_exclude(deck_t *excluded_cards) {
  deck_t *cards = malloc(sizeof(*cards));
  cards->n_cards = 0;
  cards->cards = NULL;
  for (int i = 0; i < 52; i++) {
    card_t c = card_from_num(i);
    if (!deck_contains(excluded_cards, c))
      add_card_to(cards, c);
  }
  return cards;
}

deck_t * build_remaining_deck(deck_t **hands, size_t n_hands) {
  deck_t *excluded_cards = malloc(sizeof(deck_t));
  excluded_cards->n_cards = 0;
  excluded_cards->cards = NULL;
  for (int i = 0; i < n_hands; i++) {
    for (int j = 0; j < hands[i]->n_cards; j++) {
      if (hands[i]->cards[j]->value != 0) {
	      add_card_to(excluded_cards, *(hands[i]->cards[j]));
      }
    }
  }
  deck_t *res = make_deck_exclude(excluded_cards);
  free_deck(excluded_cards);
  return res;
}

void free_deck(deck_t * deck) {
  for (int i = 0; i < deck->n_cards; i++) {
    free(deck->cards[i]);
  }
  free(deck->cards);
  free(deck);
}
