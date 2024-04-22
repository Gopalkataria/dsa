#include <bits/stdc++.h>
using namespace std;

int isans( int a , int b , int c  , int * xors , int * inp){

    int k = xors[c] ^ xors[a - 1];
    return k < (k ^ inp[b]) ? 1 : 0; 
}

int main()
{
    int t, n, k;
    cin >> t;
    while (t--)
    {
        cin >> n;
        int xors[n + 1];
        int inp[n + 1]; 
        for (int i = 1; i <= n; i++)
        {
            cin >> k;
            inp[i] = k;
            xors[i] = xors[i - 1] ^ k; 
        }
        int count = 0 ; 
        for (int i = 1; i <= n; i++)
        {
            for (int j = i; j <= n; j++ ){
                for (int k = j; k <= n; k++)
                {
                    count += isans(i, j, k, xors, inp);
                    if( isans( i,j,k,xors,inp)){
                        cout << i << j << k << " " << (xors[k] ^ xors[i - 1]) << " " << inp[j] << endl;
                    }
                }
            }
        }

        cout << count << endl ; 
    }
}