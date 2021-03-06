// Tourism
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

struct Info
{
    int  N;
    int  K;
    int  fewestDay;
    int  minimum;
    int* scores;
    int* orderedIndex;
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

// return the biggest value in a given set
int localMax(int array[], int length)
{
    // find the max in a given set
    int max = array[0];
    for (int i = 1; i < length; i++)
        if (array[i] > max)
            max = array[i];
    return max;
}

// radix: an interesting sorting algorithem (FAST)
void orderedIndex(Info data)
{
#define BASE 10

    data->orderedIndex = calloc(data->N, sizeof(int));
    int max            = localMax(data->scores, data->N);
    int exp            = 1;

    while (max / exp > 0)
    {
        int bucket[BASE] = {0};

        for (int i = 0; i < data->N; i++)
            bucket[BASE - (data->scores[i] / exp) % BASE]++;

        for (int i = 1; i < BASE; i++)
            bucket[i] += bucket[i - 1];

        for (int i = 0; i < data->N; i++)
            data->orderedIndex[--bucket[BASE - (data->scores[i] / exp) % BASE]] = i;

        exp *= BASE;
    }
#undef BASE
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

    return data;
}

void preparation(Info data)
{
    // calculate the fewest days
    fewestDays(data);
    // descending sort by index
    orderedIndex(data);
    data->minimum = (data->N % data->K) == 0 ? (data->K) : (data->N % data->K);
}

int sum(Info data)
{
    int ans = 0;
    for (int i = 0; i < data->N; i++)
        ans += data->scores[i];
    return ans;
}

int result(Info data, int* breakPoints)
{
    int ans = localMax(data->scores, breakPoints[0]);
    for (int i = 1; i < data->fewestDay; i++)
        ans += localMax(&data->scores[breakPoints[i]], breakPoints[i - 1] - breakPoints[i]);
    
    return ans;
}

int calculate(Info data)
{
    int ans = 0;
    preparation(data);
    if (data->K == 1)
        return sum(data);
    /* some simple trials
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
    */

    /* more complicated situations
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
    compare the first 500 and the last 500

    N = 1000, K = 499, days 3 ?
    (2 499 499)
    (3 498 499) ...

    N = 1000, K = 333, days 4 ?
    */

    ///////////////////

    /* discovery
    the minmum visit each day can be expressed as:
    m = N % K
    if m = 0, then m = K

    if the distance d (d = indexF - indexI) between the largest and the second largest satisfies
    d >= m
    then these two numbers definitely can be seperated into 2 groups
    N = 5, K = 3, m = 2
    1, 9, 1, 8, 1

    if d < m, but the largest number belongs to a PREVIOUS group
    then these two numbers definitely can be seperated into 2 groups
    N = 5, K = 3, m = 2
    1, 9, 8, 1, 1

    if d < m, and the largest is at the begaining of a NEW group
    then these two numbers can NOT be seperated into 2 groups
    N = 7, K = 4, m = 3
    1, 1, 1, 1, 9, 8, 1
    */
    for (int i = 0; i < data->fewestDay; i++)
    {
        int distance = abs(data->orderedIndex[i] - ((i - 1) < 0 ? 0 : data->orderedIndex[i - 1]));
        int group    = (data->orderedIndex[i] + 1) / data->K;
        int remain   = (data->orderedIndex[i] + 1) - data->K * group;
        if (remain <= data->minimum)
        // if(localMax(int *array, int length))
    }
    return 0;
}

int main()
{
    Info data = readIn();
    int  ans  = calculate(data);

    printf("%d", data->fewestDay);

    free(data->orderedIndex);
    free(data->scores);
    free(data);
}