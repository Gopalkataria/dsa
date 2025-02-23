#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

const int MASK = (1 << 17) - 1;

typedef struct stNode
{
  int data;
  struct stNode *next;
} stNode;

typedef stNode *Node;

typedef struct stSubsequence
{
  int wants;
  int currsize;
  Node listindices;
  Node listindicesend;
  struct stSubsequence *next;
} stSubsequence;

typedef stSubsequence *Subsequence;

struct stHash
{
  int key;
  Subsequence *table;
};

typedef struct stHash *Hash;

Hash createHash(int size)
{
  Hash h = (Hash)malloc(sizeof(struct stHash));
  assert(h != NULL);
  h->key = size;
  h->table = (Subsequence *)calloc(size, sizeof(Subsequence));
  assert(h->table != NULL);
  return h;
}

void addSubtoHS(Hash h, int k, Subsequence s)
{
  int index = k & MASK;
  Subsequence t = h->table[index];
  if (t == NULL)
  {
    h->table[index] = s;
  }
  else
  {
    h->table[index] = s;
    s->next = t;
  }
}

Subsequence removeSubsequence(Subsequence *head, int data)
{
  Subsequence current = *head;
  Subsequence t = NULL;

  while (current->next != NULL)
  {
    if (current->next->wants == data)
    {
      t = current->next;
      current->next = t->next;
      return t;
    }
    current = current->next;
  }

  return NULL;
}

Subsequence getSubfromHS(Hash h, int k)
{
  int index = k & MASK;
  Subsequence t = NULL;

  if (h->table[index] != NULL)
  {
    if (h->table[index]->wants == k)
    {
      t = h->table[index];
      h->table[index] = t->next;
      return t;
    }
    else
    {
      t = removeSubsequence(&h->table[index], k);
      return t;
    }
  }
  else
  {
    return NULL;
  }
}

Subsequence createSubsequence(int wants)
{
  Subsequence s = (Subsequence)malloc(sizeof(stSubsequence));
  assert(s != NULL);
  s->wants = wants;
  s->currsize = 0;
  s->listindices = NULL;
  return s;
}

void addtoSubsequence(Subsequence s, int index)
{
  Node newnode = (Node)malloc(sizeof(stNode));
  assert(newnode != NULL);
  newnode->data = index;
  newnode->next = NULL;
  if (s->listindices == NULL)
    s->listindices = newnode;
  else
    s->listindicesend->next = newnode;
  s->listindicesend = newnode;
  s->wants++;
  s->currsize++;
}

int main()
{
  int n;
  scanf("%d", &n);

  Subsequence maxsubsequence = NULL;
  int maxsize = 0;

  Hash H = createHash(MASK + 1);
  assert(H != NULL);

  Subsequence s2, s1;

  for (int i = 0; i < n; i++)
  {
    int x;
    scanf("%d", &x);
    s1 = getSubfromHS(H, x);

    if (s1 == NULL)
    {
      s1 = createSubsequence(x);
    }
    addtoSubsequence(s1, i);

    s2 = getSubfromHS(H, x + 1);
    if (s2 != NULL)
    {
      if (s2->currsize > s1->currsize)
        s1 = s2;
    }

    if (s1->currsize > maxsize)
    {
      maxsize = s1->currsize;
      maxsubsequence = s1;
    }

    addSubtoHS(H, x + 1, s1);
  }

  // print indices in max Subsequence
  Node temp = maxsubsequence->listindices;
  printf("%d\n", maxsubsequence->currsize);
  while (temp != NULL)
  {
    printf("%d ", temp->data);
    temp = temp->next;
  }

  return 0;
}