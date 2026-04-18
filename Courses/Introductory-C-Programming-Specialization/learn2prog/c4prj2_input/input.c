#include "input.h"
#include <string.h>


deck_t * hand_from_string(const char * str, future_cards_t * fc) {
    deck_t *res = malloc(sizeof(deck_t));
    res->cards = NULL;
    res->n_cards = 0;

	// Bad designed code 😭
    // for (size_t i = 0; i < strlen(str); i+=3){
    //     char value_let = str[i];
    //     char suit_let = str[i + 1];
    //     if (value_let != '?' && value_let != '\n') {
    //         card_t tmp = card_from_letters(value_let, suit_let);
    //         add_card_to(res, tmp);
    //     }
    //     else {
    //         size_t index = atoi(&str[i + 1]);
    //         card_t *ptr = add_empty_card(res);
    //         add_future_card(fc,index,ptr);
	// 		while (i + 2 < strlen(str) && str[i + 2] != ' ')
	// 		{
	// 			i++;
	// 		}
    //     }
    // }

	for (size_t i = 0; i < strlen(str); i++) {
		if (str[i] == '\n' || str[i] == ' ') { 
			continue;
		}
		else if (str[i] == '?') {
			card_t *ptr = add_empty_card(res);
			int index = atoi(&str[i+1]);
			add_future_card(fc, index, ptr);
			while (i < strlen(str) && str[i] != ' ')
				i++;
		}
		else {
			card_t card = card_from_letters(str[i], str[i+1]);
			add_card_to(res, card);
			i++;
		}
	}
    return res;
}

deck_t ** read_input(FILE * f, size_t * n_hands, future_cards_t * fc) {
    deck_t **res = NULL;
    char *line = NULL;
    size_t sz = 0;
    size_t i = 0;
    while(getline(&line, &sz, f) != -1) {
        res = realloc(res, (i + 1) * sizeof(deck_t *));
        res[i] = hand_from_string(line, fc);
        i++;
        free(line);
        line = NULL;
        (*n_hands)++;
    }
    free(line);
    return res;
}