from math import log2

t = int(input())

while( t != 0 ) :
    t -= 1
    inp = [ int(x) for x in input().split() ]
    n = inp[0] 
    k = inp[1]

    d = int(log2(k))
    if( n == 1 ):
        print( k )
        continue 
    n -=1 

    print((1<<d) - 1 , end=" ")
    if( n > 0 ):
        print( k - ((1<<d) - 1) , end=" ")
        n -= 1
    if( n > 0 ) :
        for _ in range(n) :
            print("0", end=" ")
    print("\n" , end="")