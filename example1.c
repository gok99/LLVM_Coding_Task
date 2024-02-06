#include <stdio.h>
#include <stdlib.h>

int main() {
    int num,a,b,c;
    scanf("%d", &num);

    a=10;
    b=num*2;
    c=0;
    if (b>10){
        c=num*2;
    }
    
    printf("%d\n",c);
    return 0;
}