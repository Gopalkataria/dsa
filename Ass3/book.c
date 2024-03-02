#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define max(a, b) ((a) > (b) ? (a) : (b))

const int SMASK = 8;
const int MASK = (1 << SMASK) - 1;

const int cacheS = 0;
const int cachemask = (1 << cacheS) - 1;

typedef struct stNode
{
  int data;
  struct stNode *next;
} stNode;

typedef stNode *Node;
typedef struct stTree *Tree;

typedef struct stSubsequence
{
  int wants;
  int currsize;
  Node listindices;
  Node listindicesend;
  Tree parent;
} stSubsequence;

typedef stSubsequence *Subsequence;

struct stTree
{
  int key;
  struct stTree *left;
  struct stTree *right;
  int height;
  Subsequence *table;
  short size;
};

Tree createTree(int key)
{
  Tree t = (Tree)malloc(sizeof(struct stTree));
  assert(t != NULL);
  t->key = key;
  t->table = NULL;
  t->left = NULL;
  t->right = NULL;
  t->height = 1;
  t->size = 0;
  return t;
}

int height(Tree t)
{
  if (t == NULL)
    return 0;
  return t->height;
}

int balance(Tree t)
{
  if (t == NULL)
    return 0;
  return height(t->left) - height(t->right);
}

Tree leftRotate(Tree t)
{
  if (t == NULL || t->right == NULL)
    return t;

  Tree RC = t->right;
  Tree t2 = RC->left;

  RC->left = t;
  t->right = t2;

  t->height = 1 + max(height(t->left), height(t->right));
  RC->height = 1 + max(height(RC->left), height(RC->right));

  return RC;
}

Tree rightRotate(Tree t)
{
  if (t == NULL || t->left == NULL)
    return t;

  Tree LC = t->left;
  Tree t2 = LC->right;

  LC->right = t;
  t->left = t2;

  t->height = 1 + max(height(t->left), height(t->right));
  LC->height = 1 + max(height(LC->left), height(LC->right));

  return LC;
}

Tree addSubtoT(Tree t, Subsequence s)
{
  int k = s->wants >> SMASK;
  int i = s->wants & MASK;
  if (t == NULL)
  {
    t = createTree(k);

    if (t->table == NULL)
      t->table = (Subsequence *)calloc(MASK + 1, sizeof(Subsequence));

    t->table[i] = s;
    s->parent = t;
    t->size++;
    return t;
  }

  if (t->key == k)
  {

    if (t->table == NULL)
      t->table = (Subsequence *)calloc(MASK + 1, sizeof(Subsequence));

    t->table[i] = s;
    s->parent = t;
    t->size++;
    return t;
  }

  if (t->key > k)
  {
    t->left = addSubtoT(t->left, s);
  }
  else
  {
    t->right = addSubtoT(t->right, s);
  }

  int b = balance(t);

  if (t->key & ((1 << 3) - 1))
  {
    if (b > 1 && k < t->left->key)
    {
      return rightRotate(t);
    }

    if (b < -1 && k > t->right->key)
    {
      return leftRotate(t);
    }

    if (b > 1 && k > t->left->key)
    {
      t->left = leftRotate(t->left);
      return rightRotate(t);
    }

    if (b < -1 && k < t->right->key)
    {
      t->right = rightRotate(t->right);
      return leftRotate(t);
    }
  }

  return t;
}

Subsequence getSubfromT(Tree t, Subsequence S )
{

  if (t == NULL)
    return NULL;

  int k = S->wants >> SMASK;
  int i = S->wants & MASK;

  if (t->key == k)
  {
    if (t->table == NULL)
    {
      return NULL;
    }

    Subsequence s = t->table[i];
    t->table[i] = NULL;
    if (s != NULL)
      t->size--;
    if (t->size == 0)
    {
      free(t->table);
      t->table = NULL;
    }
    return s;
  }

  if (t->key > k)
  {
    return getSubfromT(t->left, S);
  }
  else if (t->key < k)
  {
    return getSubfromT(t->right, S);
  }
  else
  {
    return NULL;
  }
}
Subsequence findSubfromT(Tree t, int query)
{

  if (t == NULL)
    return NULL;

  int k = query >> SMASK;
  int i = query & MASK;

  if (t->key == k)
  {
    if (t->table == NULL)
    {
      return NULL;
    }
    return t->table[i];
  }

  if (t->key > k)
  {
    return getSubfromT(t->left, query);
  }
  else if (t->key < k)
  {
    return getSubfromT(t->right, query);
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
  s->parent = NULL;
  return s;
}

void addtoSubsequence(Subsequence s, int index)
{
  Node newnode = (Node)malloc(sizeof(stNode));
  assert(newnode != NULL);
  newnode->data = index;
  newnode->next = NULL;
  if (s->listindices == NULL)
  {
    s->listindices = newnode;
    s->listindicesend = newnode;
  }
  else
    s->listindicesend->next = newnode;
  s->listindicesend = newnode;
  s->wants++;
  s->currsize++;
}

void addtoCache(Tree *cache, int *index, Tree t)
{
  *index = (*index + 1) & cachemask;
  cache[*index] = t;
}

Tree getfromCache(Tree *Cache, int query, Tree t)
{
  int k = query >> SMASK;
  Tree temp = t;
  for (int i = 0; i < cachemask + 1; i++)
  {
    if (Cache[i] != NULL && (Cache[i])->key == k)
    {
      temp = Cache[i];
      // printf("*");
      return temp;
    }
  }
  return temp;
}

int main()
{
  int n;
  scanf("%d", &n);

  Subsequence maxsubsequence = NULL;
  int maxsize = 0;

  Tree t = NULL, ct = NULL;

  Tree *Cache = (Tree *)calloc(cachemask + 1, sizeof(Tree));
  int index = 0;

  Subsequence s2,
      s1;

  for (int i = 0; i < n; i++)
  {
    int x;
    scanf("%d", &x);
    ct = t;
    s1 = findSubfromT(ct, x);
    int h1 = s1->wants & MASK;
    if (s1 == NULL)
    {
      s1 = createSubsequence(x);
    }
    addtoSubsequence(s1, i);

    s2 = findSubfromT(ct, x + 1);
    if (s2 != NULL)
    {
      if (s2->currsize < s1->currsize)
      {
        s2 = getSubfromT(t, x + 1);
        addSubtoT(t, s1);
      }
    } else {
      if( (s1->wants & MASK )  != h1) {
        
      }
    }

    if (s1->currsize > maxsize)
    {
      maxsize = s1->currsize;
      maxsubsequence = s1;
    }

    // addtoCache(Cache, &index, s1->parent);
  }

  Node temp = maxsubsequence->listindices;
  printf("%d\n", maxsubsequence->currsize);
  while (temp != NULL)
  {
    printf("%d ", temp->data);
    temp = temp->next;
  }

  return 0;
}
