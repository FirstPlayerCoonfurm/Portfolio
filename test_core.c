#include <iostream>

int f(int x) { return 16*(9-x)*(9-x)+127; }
int main(){
    int a = -10, b = 10, p = 130, n = 0, t;
    for(t = a; t <= b; t++){
        if(f(t)>p)
        n++;
        printf("%d\n", n);
    }
    return 0;
}