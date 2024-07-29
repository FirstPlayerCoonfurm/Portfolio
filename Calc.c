#include <stdio.h>

int main(){
    char oper;
    double num_a;
    double num_b;
    double res;

    printf("\nEnter an operator (+; -: *; /;)");\
    scanf("%c", &oper);
    
    printf("Enter num 1: ");
    scanf("%lf", &num_a);

    printf("Enter num 2: ");
    scanf("%lf", &num_b);

    switch(oper){
        default:
        printf("%c is not valid", oper);

        case '+':
        res = num_a + num_b;
        printf("\nresult: %lf", res);
        break;

        case '-':
        res = num_a - num_b;
        printf("\nresult: %lf", res);
        break;

        case '*':
        res = num_a * num_b;
        printf("\nresult: %lf", res);
        break;

        case '/':
        res = num_a / num_b;
        printf("\nresult: %lf", res);
        break;
    }
}
