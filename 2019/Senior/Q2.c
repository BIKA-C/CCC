#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

bool isPrime(int num)
{
    for (int i = 2; i <= (int)sqrt((float)num); i++)
        if (num % i == 0)
            return false;
    return true;
}

int* readIn(int size)
{
    int* input = calloc(size, sizeof(int));
    while (size--)
        scanf("%d", input++);
    return input;
}

void calculate(int num, int* ansA, int* ansB)
{
    // if it is a prime, then itself is the only answer
    if (isPrime(num))
    {
        *ansA = *ansB = num;
        return;
    }

    // brutal search
    for (int i = 3; i < num; i++)
    {
        if (! isPrime(i)) // pass if it is not a prime
            continue;

        // notice: a valid answer must satisfy 2N = A + B, -> B = 2N - A
        // where B must be a prime as well
        else if (! isPrime(2 * num - i))
            continue;
        else
        {
            *ansA = i;
            *ansB = 2 * num - i;
            return;
        }
    }
}

int* answer(int* input, int size)
{
    int* result      = calloc(size * 2, sizeof(int));
    int  resultIndex = 0;

    for (int i = 0; i < size; i++, resultIndex += 2)
        calculate(input[i], &result[resultIndex], &result[resultIndex + 1]);

    return result;
}

void present(int* result, int length)
{
    for (int i = 0; i < length; i += 2)
        printf("%d %d\n", result[i], result[i + 1]);
}

int main()
{
    int size;
    scanf("%d", &size);

    int* input  = readIn(size) - size;
    int* result = answer(input, size);

    present(result, size * 2);

    free(input);
    free(result);
}