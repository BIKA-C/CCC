// Tourism
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

struct Info
{
    int  N;
    int  K;
    int  fewestDay;
    int* scores;
};
typedef struct Info* Info;

void fewestDays(Info data)
{
    // calculate the fewest days
    double days     = (float)data->N / (float)data->K;
    data->fewestDay = days;

    if (modf(days, &days) > 0)
        data->fewestDay++;
}

Info readIn()
{
    // create data
    Info data = (Info)calloc(1, sizeof(struct Info));

    // take N and K
    scanf("%d", &data->N);
    scanf("%d", &data->K);

    // take scores for attractions
    data->scores = calloc(data->N, sizeof(int));
    int* ptr     = data->scores;
    for (int i = 0; i < data->N; i++)
        scanf("%d", ptr++);

    // calculate the fewest days
    fewestDays(data);

    return data;
}

int localMax(int array[], int length)
{
    // find the max in a given set
    int max = array[0];
    for (int i = 1; i < length; i++)
        if (array[i] > max)
            max = array[i];
    return max;
}

int calculate(Info data)
{
    /*
    let's say N = 7, K = 3, fewest day = 3
    
    scores: 2 5 7 1 4 9 3

    possible combinations:
    1. (2 5 7), (1 4 9), (3) total 19
    2. (2), (5 7 1), (4 9 3) total 19
    3. (2 5), (7 1), (4 9 3) total 21
    4. (2 5), (7 1 4), (9 3) total 21

    notice: what we want to do is that 
    TRY to group the top 3 biggest numbers into their groups

    there might be situations that the top numbers could not be in their groups
    e.g. N = 5, K = 3, days = 2
    scores: 9 8 1 1 1
    notice: there is no way to seprate 9 and 8 into different groups 
    there is not enough days

    consider the following:

    N = 1000, K = 999, days 2
    (1 999) or (999 1)
    compare the first and the last number

    N = 1000, K = 998, days 2
    (2 998) or (998 2)
    compare the first 2 and the last 2

    N = 1000, K = 800, days2
    (200 800) or (800 200)
    compare the first 200 and the last 200

    N = 1000, K = 500, days 2
    (500 500)
    comare the first 500 and the last 500

    N = 1000, K = 499, days 3 ?

    N = 1000, K = 333, days 4 ?

    the minmum visit each day can be expressed as:
    y = N % K

    */
    return 0;
}

int main()
{
    Info data = readIn();
    int  ans  = calculate(data);

    printf("%d", data->fewestDay);

    free(data->scores);
    free(data);
}