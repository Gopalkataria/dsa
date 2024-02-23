#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct stNode
{
    int freq;
    char *word;
    struct stNode *next;
};
typedef struct stNode *Node;

struct sthashtable
{
    int mask;
    Node *table;
};

typedef struct sthashtable *Hash;

int getHash(char *word, int mask)
{
    char c;
    int hash = 0;
    while (c = *word++)
        hash = hash + c - 'a';

    return hash & mask;
}

Hash createHash(int mask)
{
    Hash h = (Hash)malloc(sizeof(struct sthashtable));
    h->mask = mask;
    h->table = (Node *)calloc(mask + 1, sizeof(Node));
    return h;
}

void addWord(Hash h, char *word)
{
    int index = getHash(word, h->mask);
    Node t = h->table[index];
    Node new = (Node)malloc(sizeof(struct stNode));
    new->word = (char *)malloc(strlen(word) + 1);
    strcpy(new->word, word);
    new->freq = 1;
    new->next = NULL;
    if (t == NULL)
    {
        h->table[index] = new;
    }
    else
    {
        h->table[index] = new;
        new->next = t;
    }
}

Node getWord(Hash h, char *word)
{
    int index = getHash(word, h->mask);
    Node t = h->table[index];
    while (t != NULL)
    {
        if (strcmp(t->word, word) == 0)
        {
            return t;
        }
        t = t->next;
    }
    return NULL;
}

int main()
{
    int n;
    scanf("%d", &n);
    Hash h = createHash((1 << 15) - 1);
    int k = 0;
    Node useful[10000];
    for (int i = 0; i < n; i++)
    {
        char word[100];
        scanf("%s", word);
        printf("%s %d\n", word, getHash(word, h->mask));
        Node t = getWord(h, word);
        if (t == NULL)
        {
            addWord(h, word);
        }
        else
        {
            if (t->freq == 1)
                useful[k++] = t;
            t->freq++;
        }
    }

    for (int i = 0; i < k; i++)
    {
        printf("%s %d\n", useful[i]->word, useful[i]->freq);
    }
}