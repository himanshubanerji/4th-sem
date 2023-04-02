// Program: Brute Force String Matching

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Strings
{
    char *text;
    char *pattern;
} String;

int stringMatch(int n, int m, char *text, char *pattern)
{
    int i, j;
    for (i = 0; i < n; i++)
    {
        j = 0;
        while ((j < m) && (pattern[j] == text[i + j]))
        {
            j += 1;
        }
        if (j == m)
        {
            return i;
        }
    }

    return -1;
}

int main()
{

    String *tp = malloc(sizeof(String));
    char ch;
    int n, m;
    printf("Enter size of text: ");
    scanf("%d", &n);
    printf("Enter size of pattern: ");
    scanf("%d", &m);

    tp->text = calloc(n, sizeof(char));
    tp->pattern = calloc(m, sizeof(char));

    scanf("%c", &ch);
    printf("Enter text: ");
    scanf("%s", tp->text);
    printf("Enter pattern: ");
    scanf("%s", tp->pattern);

    int index = stringMatch(n, m, tp->text, tp->pattern);

    if (index != -1)
    {
        printf("Pattern matched at index %d", index);
    }
    else
    {
        printf("Pattern not matched");
    }

    return 0;
}