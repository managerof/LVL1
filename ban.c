#include <stdio.h>

void old_function(x, y)
    int x;
    double y;
{
    printf("x: %d, y: %f\n", x, y);
}

int main()
{
    old_function(1, 2.0f);
    
    return 0;
}