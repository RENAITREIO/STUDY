#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int compute_score(string word);
const int POINTS[] = {1, 3, 3, 2,  1, 4, 2, 4, 1, 8, 5, 1, 3,
                      1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int main(void)
{
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    if (score1 > score2)
        printf("Player 1 wins!\n");
    else if (score1 < score2)
        printf("Player 2 wins!\n");
    else
        printf("Tie!\n");
    return 0;
}

int compute_score(string word)
{
    int score = 0;
    for (int i = 0; word[i] != '\0'; i++)
    {
        if (islower(word[i]))
        {
            score += POINTS[word[i] - 'a'];
        }
        else if (isupper(word[i]))
        {
            score += POINTS[word[i] - 'A'];
        }
    }
    return score;
}
