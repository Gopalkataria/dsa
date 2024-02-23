#include <stdio.h>
#include <stdlib.h>
#include <string.h>



int main() {

    int *chk = ( int * ) calloc( 27 , sizeof(int)) ;

    char inp[10000];
    scanf("%s", inp);
    char c; 
    char res[27];
    
    int k=0;
    for (int i = 0; i < strlen(inp); i++)
    {   
        int p =  inp[i] - 'a';
        // printf("%d\n", p); 
        if (chk[p] == 0 )
        {
            res[k++] = inp[i];
            chk[p] = 1;
        }
        if (k == 26){
            break;
        }
    }
    res[k++] = '\0';
    printf(" %s \n", res);
    return 0; 
}