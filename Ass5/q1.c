#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define lint long long int

lint *links;
lint *sizes;
lint *heads;

lint find(lint a)
{
    while (a != links[a])
    {
        a = links[a];
    }
    return a;
}

bool same(lint a, lint b)
{
    if (find(a) == find(b))
    {
        return true;
    }
    return false;
}

void unite(lint a, lint b)
{
    a = find(a);
    b = find(b);
    if (sizes[a] < sizes[b])
    {
        a = a ^ b;
        b = a ^ b;
        a = a ^ b;
    }
    sizes[a] += sizes[b];
    links[b] = a;
    heads[b] = 0;
}

int main()
{

    lint n, m;

    scanf("%lld %lld", &n, &m);

    links = (lint *)malloc((n + 1) * sizeof(lint));
    sizes = (lint *)malloc((n + 1) * sizeof(lint));
    heads = (lint *)malloc((n + 1) * sizeof(lint));

    for (lint i = 0; i <= n; i++)
    {
        links[i] = i;
        sizes[i] = 1;
        heads[i] = 1;
    }

    lint count = n - 1;
    lint a, b;
    while (m--)
    {
        scanf("%d %d", &a, &b);
        if (!(same(a, b)))
        {
            unite(a, b);
            count--;
        }
    }
    printf("%d\n", count);
    if (count == 0)
    {
        return 0;
    }
    lint i;
    for (i = 1; i <= n; i++)
    {
        if (heads[i] == 1)
        {
            printf("%d ", i);
            i++;
            break;
        }
    }
    if (count > 1)
    {
        for (; i <= n; i++)
        {
            if (heads[i] == 1)
            {
                printf("%d\n%d ", i, i);
                count--;
                if (count == 1)
                {
                    i++;
                    break;
                }
            }
        }
    }

    for (; i <= n; i++)
    {
        if (heads[i] == 1)
        {
            printf("%d", i);
            i++;
            break;
        }
    }

    return 0;
}