#include <stdio.h>
#include <stdlib.h>

int main()
{
    int i = 0;
    int u = 0;
    i = 10;
    u = -10;
    while(u <= 10)
    {
        printf("\nValores [I:%i] [U:%i]",i,u);
        i--;
        u++;
    }

    return 1;
}
