#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "cards.h"


void assert_card_valid(card_t c) {
  // assert value from 2 to VALUE_ACE
  assert(c.value > 1 && c.value < 15);
  // assert suit from SPADES to CLUBS
  assert(c.suit >= SPADES && c.suit <= CLUBS);
}

const char * ranking_to_string(hand_ranking_t r) {
  // assert the range ?
  // assert(r >=STRAIGHT_FLUSH && r <=NOTHING);
  // switch r to string type
  switch (r)
  {
  case STRAIGHT_FLUSH:
    return "STRAIGHT_FLUSH";
    break;
  case FOUR_OF_A_KIND:
    return "FOUR_OF_A_KIND";
    break;
  case FULL_HOUSE:
    return "FULL_HOUSE";
    break;
  case FLUSH:
    return "FLUSH";
    break;
  case STRAIGHT:
    return "STRAIGHT";
    break;
  case THREE_OF_A_KIND:
    return "THREE_OF_A_KIND";
    break;
  case TWO_PAIR:
    return "TWO_PAIR";
    break;
  case PAIR:
    return "PAIR";
    break;
  case NOTHING:
    return "NOTHING";
    break;
  }
  return "";
}

char value_letter(card_t c) {
  // if range from 2~10
  if (c.value > 1 && c.value < 11)
  {
    // x % 10
    int x = c.value % 10;
    // return x+'0'
    return (x + '0');
  }
  // else consider J Q K A
  else
  {
    // switch from VALUE_JACK to VALUE_ACE
    // return the value
    switch (c.value)
    {
    case VALUE_JACK:
      return 'J';
      break;
    case VALUE_QUEEN:
      return 'Q';
      break;
    case VALUE_KING:
      return 'K';
      break;
    case VALUE_ACE:
      return 'A';
      break;
    }
  }
  return ' ';
}


char suit_letter(card_t c) {
  // switch from SPADES to CLUBS
  // return the suit
  switch (c.suit)
  {
  case SPADES:
    return 's';
    break;
  case HEARTS:
    return 'h';
    break;
  case DIAMONDS:
    return 'd';
    break;
  case CLUBS:
    return 'c';
    break;
  default:
    assert(0);
  }
}

void print_card(card_t c) {
  // get the value
  char val = value_letter(c);
  // get the suit
  char suit = suit_letter(c);
  // print the value and suit without any ' ' and '\n'
  printf("%c%c", val, suit);
}

card_t card_from_letters(char value_let, char suit_let) {
  card_t temp;
  // assert the range of value
  assert((value_let >= '2' && value_let <= '9') || value_let == 'J' || value_let == 'Q' || value_let == 'K' || value_let == 'A' || value_let == '0');
  // assert the suit
  assert(suit_let == 's' || suit_let == 'h' || suit_let == 'd' || suit_let == 'c');
  // shift the value to unsigned
  if (value_let >= '0' && value_let <= '9')
  {
    temp.value = value_let - '0';
    if (temp.value == 0)
      temp.value = 10;
  }
  else
  {
    switch (value_let)
    {
    case 'J':
      temp.value = VALUE_JACK;
      break;
    case 'Q':
      temp.value = VALUE_QUEEN;
      break;
    case 'K':
      temp.value = VALUE_KING;
      break;
    case 'A':
      temp.value = VALUE_ACE;
      break;
    }
  }
  // shift the suit to suit_t
  switch (suit_let)
  {
  case 's':
    temp.suit = SPADES;
    break;
  case 'h':
    temp.suit = HEARTS;
    break;
  case 'd':
    temp.suit = DIAMONDS;
    break;
  case 'c':
    temp.suit = CLUBS;
    break;
  }
  return temp;
}

card_t card_from_num(unsigned c) {
  card_t temp;
  // assert 0<=c<52 ?
  // assert(c >= 0 && c < 52);
  // c / 13 decide suit
  temp.suit = (suit_t) (c / 13);
  // c % 13 + 1decide value
  temp.value = c % 13 + 2;
  return temp;
}
