#include <stdio.h>
#include <stdlib.h>

typedef struct chambar
{
    int req;
    int delta;
} Chambar;

int cmpreq(const void *a, const void *b)
{
    return ((Chambar *)a)->req - ((Chambar *)b)->req;
}

int cmpreqrev(const void *a, const void *b)
{
    return ((Chambar *)b)->req - ((Chambar *)a)->req;
}

int main()
{

    int ni, ini;
    scanf("%d %d", &ni, &ini);

    Chambar positives[ni];
    Chambar negatives[ni];

    int requirements[ni];

    for (int i = 0; i < ni; i++)
    {
        scanf("%d", &requirements[i]);
    }

    int n = 0, p = 0;

    for (int i = 0; i < ni; i++)
    {
        int delta;
        scanf("%d", &delta);

        if (delta <= 0)
        {
            negatives[n].req = requirements[i];
            negatives[n].delta = delta;
            n++;
        }
        else
        {
            positives[p].req = requirements[i];
            positives[p].delta = delta;
            p++;
        }
    }

    // print positives
    qsort(positives, p, sizeof(Chambar), cmpreq);
    qsort(negatives, n, sizeof(Chambar), cmpreqrev);


    // print positives
    for (int i = 0; i < p; i++)
    {
        if( ini >= positives[i].req){
            ini += positives[i].delta; 
        } else {
            printf("NO\n");
            return 0; 
        }
        // printf("%d %d\n", (positives[i]).req, (positives[i]).delta);
    }

    // print negatives
    for (int i = 0; i < n; i++)
    {
        if (ini >= negatives[i].req)
        {
            ini += negatives[i].delta;
        }
        else
        {
            printf("NO\n");
            return 0;
        }
        // printf("%d %d\n", (negatives[i]).req, (negatives[i]).delta);
    }

    if( ini >= 0 ){
        printf("YES\n");
    } else {
        printf("NO\n");

    }

    return 0;
}