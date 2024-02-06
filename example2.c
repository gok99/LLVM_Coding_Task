#include <stdio.h>
#include <stdlib.h>

int main() {
    int num,a,b,c;
    scanf("%d", &num);

    a=10;
    b=num*10;
    c=1;
    while (b>c){
        if (c%5 == 0){
            c=num*2;
        } else {
            c=num*3;
        }
    }
    printf("%d\n",c);
    return 0;
}