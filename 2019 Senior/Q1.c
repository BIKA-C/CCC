#include <stdio.h>

int main()
{
    char input[1000001];
    scanf("%s", input);

    int H_count = 0, V_count = 0;

    // count inputs
    for (int i = 0; input[i] != '\0'; i++)
    {
        if (input[i] == 'V')
            V_count++;
        else if (input[i] == 'H')
            H_count++;
    }

    // notice: VV cancel each other, so do HH
    // and VHVH or VVVHHHVH 
    // 4 possible situations:
    // 0V 0H
    // 1V 1H
    // 0V 0H
    // 1V 1H

    if (H_count % 2 == 0 && V_count % 2 == 0)
        printf("1 2\n3 4");
    else if (H_count % 2 == 1 && V_count % 2 == 0)
        printf("3 4\n1 2");
    else if (H_count % 2 == 0 && V_count % 2 == 1)
        printf("2 1\n4 3");
    else if (H_count % 2 == 1 && V_count % 2 == 1)
        printf("4 3\n2 1");
}