#include <bits/stdc++.h>
using namespace std;

int countposs( int * board , int n ){




    return 0; 
}

int main()
{
    int t, n, k , moves;
    cin >> t;
    int a, b; 
    while (t--)
    {
        cin >> n;
        cin >> moves;
        int * board = ( int * ) calloc( n , sizeof(int)); 
        while (moves--)
        {
            cin >> a, b;
            board[a - 1] = 1;
            board[b - 1] = 1; 

        }


        cout << countposs( board , n ) << endl;
    }
}