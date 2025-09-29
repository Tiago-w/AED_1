#include <stdio.h>
#include <stdlib.h>

int main(){

    int num, *p;
    float num2, *p1;
    char c, *p2;
    num=2;
    num2=5;
    c ='a';


    p=&num;
    p1=&num2;
    p2=&c;

    printf("%d\n", num);
    printf("%.2f\n", num2);
    printf("%c\n\n", c);
    
    *p=4;
    *p1=10;
    *p2='t';

    printf("%d\n",num);
    printf("%.2f\n", num2);
    printf("%c\n", c);

    return 0;
}