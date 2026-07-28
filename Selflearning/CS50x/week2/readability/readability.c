#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

float compute_index(string sentences);

int main(void)
{
    string sentences = get_string("Text: ");
    float index = compute_index(sentences);
    if (index < 1.5)
        printf("Before Grade 1\n");
    else if (index >= 15.5)
        printf("Grade 16+\n");
    else
        printf("Grade %0.f\n", index);
    return 0;
}

float compute_index(string sentences)
{
    float index = 0;
    int words_num = 1;
    int sentences_num = 0;
    int letters_num = 0;
    for (int i = 0; sentences[i] != '\0'; i++)
    {
        if (isalpha(sentences[i]))
            letters_num++;
        else if (sentences[i] == ' ')
            words_num++;
        else if ((sentences[i] == '.' || sentences[i] == '?') || sentences[i] == '!')
            sentences_num++;
    }
    index = 0.0588 * letters_num / words_num * 100 - 0.296 * sentences_num / words_num * 100 - 15.8;
    return index;
}
