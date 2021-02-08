# CCC 2019 Senior Solutions

By William Chen

:white_check_mark: Language used: C  
:white_check_mark: Documented with explanantions

<!-- @import "[TOC]" {cmd="toc" depthFrom=1 depthTo=6 orderedList=false} -->

<!-- code_chunk_output -->

- [CCC 2019 Senior Solutions](#ccc-2019-senior-solutions)
  - [Problem S1: Flipper](#problem-s1-flipper)
  - [Problem S2: Pretty Average Primes](#problem-s2-pretty-average-primes)
  - [Problem S3: Arithmetic Square](#problem-s3-arithmetic-square)
  - [Problem S4: Tourism](#problem-s4-tourism)
  - [Problem S5: Triangle: The Data Structure](#problem-s5-triangle-the-data-structure)

<!-- /code_chunk_output -->

## Overview

| Problem                                                                             |           Mark            |
| :---------------------------------------------------------------------------------- | :-----------------------: |
| [Problem S1: Flipper](#problem-s1-flipper)                                          | 15/15 :heavy_check_mark:  |
| [Problem S2: Pretty Average Primes](#problem-s2-pretty-average-primes)              | 15/15 :heavy_check_mark:  |
| [Problem S3:  Arithmetic Square](#problem-s3-arithmetic-square)                     | 15/15 :heavy_check_mark:  |
| [Problem S4: Tourism](#problem-s4-tourism)                                          | 0/15  :hammer_and_wrench: |
| [Problem S5: Triangle: The Data Structure](#problem-s5-triangle-the-data-structure) | 0/15  :hammer_and_wrench: |
| **Total:**                                                                          |         **45/75**         |

## Problem S1: Flipper

```C
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
    // 1V 0H
    // 0V 1H
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
```

## Problem S2: Pretty Average Primes

```C
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
```

## Problem S3: Arithmetic Square

``` C
// Arithmetic Square
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define UNKNOWN 1000001

void read(int grid[][3])
{
    char input[3][3][10];

    // take 3 strings to each 'input' row. Each string will not be longer than 9 characters
    for (int row = 0; row < 3; row++)
        scanf("%s %s %s", input[row][0], input[row][1], input[row][2]);

    // put strings back to numbers and mark any unknowns
    for (int row = 0; row < 3; row++)
        for (int column = 0; column < 3; column++)
            if (input[row][column][0] == 'X')
            {
                grid[row][column] = UNKNOWN;
                continue;
            }
            else
                grid[row][column] = atoi(input[row][column]);
}

void present(int grid[][3])
{
    for (int row = 0; row < 3; row++)
    {
        for (int column = 0; column < 3; column++)
        {
            if (grid[row][column] == UNKNOWN)
                printf("%c", 'X');
            else
                printf("%d", grid[row][column]);
            if (column != 2)
                printf(" ");
        }
        printf("\n");
    }
}

// calculate the last unknown in an array
void determinLast(int array[3])
{
    if (array[0] == UNKNOWN)
        array[0] = array[1] - (array[2] - array[1]);
    else if (array[1] == UNKNOWN) // Alert! potential issue: 8 X 3, where X = (8 - 3) / 2 + 8 = 5.5 which is NOT an integer
        array[1] = ((array[2] - array[0]) / 2) + array[0];
    else if (array[2] == UNKNOWN)
        array[2] = array[1] + (array[1] - array[0]);
}

// extract a vertical array out of a 2D array
void map(int grid[][3], int column, int dest[], bool fromGrid)
{
    if (fromGrid)
        for (int i = 0; i < 3; i++)
            dest[i] = grid[i][column];
    else
    {
        for (int i = 0; i < 3; i++)
            grid[i][column] = dest[i];
        memset(dest, 0x0, sizeof(int) * 3);
    }
}

// fullfill any spot that can be determined
void fullfill(int grid[][3])
{
    //scan horizontally
    int horizontal_known = 0;
    for (int row = 0; row < 3; row++)
    {
        for (int column = 0; column < 3; column++)
        {
            if (grid[row][column] != UNKNOWN)
                horizontal_known++;
        }
        if (horizontal_known == 2)
        {
            determinLast(grid[row]);
            horizontal_known = 0;
        }
        horizontal_known = 0;
    }

    //scan vertically
    int vertical_known = 0;
    int temp[3]        = {0, 0, 0};
    for (int column = 0; column < 3; column++)
    {
        for (int row = 0; row < 3; row++)
        {
            if (grid[row][column] != UNKNOWN)
                vertical_known++;
        }
        if (vertical_known == 2)
        {
            map(grid, column, temp, true);
            determinLast(temp);
            map(grid, column, temp, false);
            vertical_known = 0;
        }
        vertical_known = 0;
    }
}

int howManyGiven(int grid[][3])
{
    int ans = 0;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (grid[i][j] != UNKNOWN)
                ans++;
    return ans;
}

bool isSolved(int grid[][3])
{
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (grid[i][j] == UNKNOWN)
                return false;
    return true;
}

void iterate(int grid[][3])
{
    // make a nice copy
    int copy[3][3];
    memcpy(copy, grid, sizeof(int) * 9);

    // fill out the last spot in any row or column
    // e.g. 1 X 3, where X can be determined: -> 1 2 3
    fullfill(grid);

    /// ! Iteration ! ///
    while (memcmp(grid, copy, sizeof(int) * 9) != 0)
    {
        fullfill(grid);
        memcpy(copy, grid, sizeof(int) * 9);
    }
}

void reallyFunnyQuestion(int grid[][3])
{
    // memset(grid, input, sizeof(int) * 9); Only for Byte

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            grid[i][j] = 1;
}

void funnyQuestion(int grid[][3])
{
    int input = UNKNOWN;
    for (int i = 0; i < 3 && input == UNKNOWN; i++)
        for (int j = 0; j < 3 && input == UNKNOWN; j++)
            if (grid[i][j] != UNKNOWN)
                input = grid[i][j];

    // memset(grid, input, sizeof(int) * 9); Only for Byte

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            grid[i][j] = input;
}

void unknown_6_h(int grid[][3], int row)
{
    if (row == 0)
    {
        memcpy(grid[1], grid[0], sizeof(int) * 3);
        memcpy(grid[2], grid[0], sizeof(int) * 3);
    }
    else if (row == 1)
    {
        memcpy(grid[0], grid[1], sizeof(int) * 3);
        memcpy(grid[2], grid[1], sizeof(int) * 3);
    }
    else if (row == 2)
    {
        memcpy(grid[0], grid[2], sizeof(int) * 3);
        memcpy(grid[1], grid[2], sizeof(int) * 3);
    }
}

void unknown_6_v(int grid[][3], int column)
{
    if (column == 0)
    {
        for (int row = 0; row < 3; row++)
            grid[row][1] = grid[row][2] = grid[row][0];
    }
    else if (column == 1)
    {
        for (int row = 0; row < 3; row++)
            grid[row][0] = grid[row][2] = grid[row][1];
    }
    else if (column == 2)
    {
        for (int row = 0; row < 3; row++)
            grid[row][0] = grid[row][1] = grid[row][2];
    }
}

int unknown_4_x(int grid[][3], int row)
{
    return grid[row][2] - grid[row][1];
}

int unknown_4_y(int grid[][3], int column)
{
    return grid[2][column] - grid[1][column];
}

void unknown_4_solve(int grid[][3], int a, int x, int y)
{
    /*
        a       a+x     a+2x
        a+y     a+y+x   a+y+2x
        a+2y    a+2y+x  a+2y+2x
    */

    for (int row = 0; row < 3; row++)
        for (int column = 0; column < 3; column++)
            grid[row][column] = a + column * x + row * y;
}

void unknown_4(int grid[][3])
{
    /*
        a    a+x    a+2x
        b    b+x    b+2x
        c    c+x    c+2x
    */

    /*
        a       a+x     a+2x
        a+y     a+y+x   a+y+2x
        a+2y    a+2y+x  a+2y+2x
    */

    /*
        1a+0x+0y    1a+1x+0y    1a+2x+0y
        1a+0x+1y    1a+1x+1y    1a+2x+1y
        1a+0x+2y    1a+1x+2y    1a+2x+2y
    */

    // Conclusion: solving system of equations with 3 unknowns

    // Jesus freaking hard
    // requires matrix knowledge

    // new way to approach:
    // there must be a row and column given
    // use the row to isolate x
    // use the column to isolate y
    // calculate a

    int a = UNKNOWN, x = UNKNOWN, y = UNKNOWN;

    // horizontal scan
    int h = 0;
    for (int row = 0; row < 3; row++)
    {
        h = 0;
        for (int column = 0; column < 3; column++)
            if (grid[row][column] != UNKNOWN)
                h++;
        if (h == 3)
            x = unknown_4_x(grid, row);
    }
    // vertical scan
    int v = 0;
    for (int column = 0; column < 3; column++)
    {
        v = 0;
        for (int row = 0; row < 3; row++)
            if (grid[row][column] != UNKNOWN)
                v++;
        if (v == 3)
            y = unknown_4_y(grid, column);
    }

    if (grid[1][1] != UNKNOWN)
        a = grid[1][1] - x - y;
    else if (grid[0][0] != UNKNOWN)
        a = grid[0][0];
    else if (grid[0][2] != UNKNOWN)
        a = grid[0][2] - 2 * x;
    else if (grid[2][0] != UNKNOWN)
        a = grid[0][2] - 2 * y;
    else if (grid[2][2] != UNKNOWN)
        a = grid[0][2] - 2 * y - 2 * x;

    unknown_4_solve(grid, a, x, y);
}

void unknown_6(int grid[][3])
{
    // check if it is situation 1

    // horizontal scan
    int h = 0;
    for (int row = 0; row < 3; row++)
    {
        h = 0;
        for (int column = 0; column < 3; column++)
            if (grid[row][column] != UNKNOWN)
                h++;
        if (h == 3)
        {
            unknown_6_h(grid, row);
            return;
        }
    }
    // vertical scan
    int v = 0;
    for (int column = 0; column < 3; column++)
    {
        v = 0;
        for (int row = 0; row < 3; row++)
            if (grid[row][column] != UNKNOWN)
                v++;
        if (v == 3)
        {
            unknown_6_v(grid, column);
            return;
        }
    }

    // situation 3
    if (grid[1][1] != UNKNOWN)
    {
        grid[0][1] = grid[1][1];
        iterate(grid);
        return;
    }
    // situation 4
    else if (grid[1][1] == UNKNOWN)
    {
        if (grid[0][1] != UNKNOWN)
            grid[1][1] = grid[0][1];
        else if (grid[2][1] != UNKNOWN)
            grid[1][1] = grid[2][1];
        else if (grid[1][0] != UNKNOWN)
            grid[1][1] = grid[1][0];
        else if (grid[1][2] != UNKNOWN)
            grid[1][1] = grid[1][2];
        iterate(grid);
        return;
    }
}

void unknown_7_clear_h(int grid[][3], int exceptRow)
{
    for (int row = 0; row < 3; row++)
    {
        if (row == exceptRow) continue;
        for (int column = 0; column < 3; column++)
            grid[row][column] = UNKNOWN;
    }
}

void unknown_7_clear_v(int grid[][3], int exceptColumn)
{
    for (int column = 0; column < 3; column++)
    {
        if (column == exceptColumn) continue;
        for (int row = 0; row < 3; row++)
            grid[row][column] = UNKNOWN;
    }
}

void unknown_7_solve(int grid[][3], int row, int column)
{
    // consider do not let the middle row being empty because: 8 X 3, where X = (8 - 3) / 2 + 8 = 5.5 which is not an integer.
    if (grid[1][0] == UNKNOWN && grid[1][1] == UNKNOWN && grid[1][2] == UNKNOWN)
    {
        for (int r = 0; r < 3; r++)
        {
            grid[r][column] = grid[row][column];
        }
        iterate(grid);
        // after iteration, it becomes the normal T shaped quesion, which has 4 unknowns.
        unknown_4(grid);
        return;
    }
    else // if it is not empty, safe to run
    {
        for (int c = 0; c < 3; c++)
            grid[row][c] = grid[row][column];
        iterate(grid);
    }

    /* Goal:
    5. 7 unknowns, one of the corners must have a value
    a X X          a        a       a
    X X b    ->    b        b       b
    X X X          2b-a     2b-a    2b-a
    */

    // horizontal scan
    for (int row = 0; row < 3; row++)
    {
        // the row with all the same numbers is not the row we wanted
        if (grid[row][0] == grid[row][1])
            continue;
        else if (grid[row][0] == UNKNOWN || grid[row][1] == UNKNOWN || grid[row][2] == UNKNOWN)
            continue;
        else
        {
            unknown_7_clear_h(grid, row);
            unknown_6_h(grid, row);
            return;
        }
    }
    // vertical scan
    for (int column = 0; column < 3; column++)
    {
        // the column with all the same numbers is not the column we wanted
        if (grid[0][column] == grid[1][column])
            continue;
        else if (grid[0][column] == UNKNOWN || grid[1][column] == UNKNOWN || grid[2][column] == UNKNOWN)
            continue;
        else
        {
            unknown_7_clear_v(grid, column);
            unknown_6_v(grid, column);
            return;
        }
    }
}

void unknown_7(int grid[][3])
{
    // first step: locate the corner value
    // X 23391 X
    // X X X
    // X X -362252
    if (grid[0][0] != UNKNOWN)
        unknown_7_solve(grid, 0, 0);
    else if (grid[0][2] != UNKNOWN)
        unknown_7_solve(grid, 0, 2);
    else if (grid[2][0] != UNKNOWN)
        unknown_7_solve(grid, 2, 0);
    else if (grid[2][2] != UNKNOWN)
        unknown_7_solve(grid, 2, 2);
}

void calculate(int grid[][3])
{
    // fill out the last spot in any row or column
    // e.g. 1 X 3, where X can be determined: -> 1 2 3
    // and after one spot is being filled, do it again to check if it could continue
    // e.g. consider the following:
    // X X X          X X X          X X 4
    // 2 3 X    ->    2 3 4    ->    2 3 4
    // X X 4   1st    X X 4   2nd    X X 4
    iterate(grid);

    // check if finished
    if (isSolved(grid)) return;

    /*deal with the remaining spots

    possible situations
    1. 6 unknowns
    a X X          a a a
    b X X    ->    b b b
    c X X          c c c

    2. 4 unknowns
    a   a+d   a+2d        a   a+d   a+2d
    b   X     X     ->    b   b+d   b+2d
    c   X     X           c   c+d   c+2d
    
    3. 6 unknowns
    a X X          a X X
    X b X    ->    b b X    ->    iterate again
    X X c          X X c

    4. 6 unknowns
    a X X          a X X
    X X b    ->    X c b    ->    iterate again
    X c X          x c X

    5. 7 unknowns, unbelievable. note: one of the corners must have a value
    a X X          a        a       a
    X X b    ->    b        b       b
    X X X          2b-a     2b-a    2b-a

    some easy situations:
    1. 8 unknowns
    a X X
    X X X
    X X X

    2. 9 unknowns
    X X X
    X X X
    X X X
    */

    int unknown = 9 - howManyGiven(grid);
    if (unknown == 9)
        reallyFunnyQuestion(grid);
    else if (unknown == 8)
        funnyQuestion(grid);
    else if (unknown == 4)
        unknown_4(grid);
    else if (unknown == 6)
        unknown_6(grid);
    else if (unknown == 7)
        unknown_7(grid);
}

int main()
{
    // 14 X X
    // X X 18
    // X 16 X

    // 14 X X
    // 16 16 X
    // 18 18 18

    // 8 9 10
    // 16 18 20
    // 24 27 30

    // 8 27 46
    // 34 27 20
    // 60 27 -6

    // 8 7 6
    // 18 18 18
    // 28 29 30

    int grid[3][3];

    memset(grid, 0x0, sizeof(int) * 9);

    // int known = 9;
    read(grid);
    calculate(grid);
    present(grid);
}
```

## Problem S4: Tourism

:no_entry:Unfinished

### Some Simple Trials

Let's say `N = 7` and `K = 3`, then `days = 3`  
scores are: `2 5 7 1 4 9 3`

Possible Combinations:
| #   |      Combination      | Total |
| --- | :-------------------: | :---: |
| 1.  | (2 5 7), (1 4 9), (3) |  19   |
| 2.  | (2), (5 7 1), (4 9 3) |  19   |
| 3.  | (2 5), (7 1), (4 9 3) |  21   |
| 4.  | (2 5), (7 1 4), (9 3) |  21   |

>*Notice*: What we want to do is that **TRY** to group the top 3 biggest numbers into their groups. There might be situations that the top numbers could not be in their groups  
>>e.g. `N = 5`, `K = 3`, `days = 2` and scores are: `9 8 1 1 1`  
Notice: there is no way to seprate 9 and 8 into different groups. There is not enough days

### More Complicated Situations

Consider the following:

```txt
1.  N = 1000, K = 999, days 2
    (1 999) or (999 1)
    compare the first and the last number
```

```txt
2.  N = 1000, K = 998, days 2
    (2 998) or (998 2)
    compare the first 2 and the last 2
```

```txt
3.  N = 1000, K = 800, days2
    (200 800) or (800 200)
    compare the first 200 and the last 200
```

```txt
4.  N = 1000, K = 500, days 2
    (500 500)
    compare the first 500 and the last 500
```

```txt
5.  N = 1000, K = 499, days 3 ?
    (2 499 499)
    (3 498 499) ...
```

```txt
6.  N = 1000, K = 333, days 4 ?
```

### Some Discoveries

:warning: These might be wrong or fragmentary

1. The Minmum visit per day&emsp;`Minmum = (N % K) == 0 ? (K) : (N % K)`
   > The *Minmum* by definition means that if there is a day visited a number that is less than `m` then the trip can not be finished with in the 'fewest days'
   >> Notice: The *Minmum* `m` can be ranged `Minmum <= m <= K`
2. If the distance d (`d = indexF - indexI`) between the largest and the second largest satisfies `d >= m`, then these two numbers can be seperated into 2 groups

    ```txt
    N = 5, K = 3, m = 2
    1, 9, 1, 8, 1
    ```

3. If `d < m`, but the largest number belongs to a **PREVIOUS** group then these two numbers can be seperated into 2 groups

    ```txt
    N = 5, K = 3, m = 2
    1, 9, 8, 1, 1
    ```

4. If `d < m`, and the largest is at the **begaining** of a **NEW** group, then these two numbers can **NOT** be seperated into 2 groups

    ```txt
    N = 7, K = 4, m = 3
    1, 1, 1, 1, 9, 8, 1
    ```

Since the Minmum visit is only allowed once, therefor the quesion is really asking:

1. Which day will have the Minmum visit?
2. What number the Minmum will be? (Minmum Visit `x` is ranged: `Minmum <= x <= K`)
3. Which the other day will compensate if `x` is bigger than Minmum?

### Brave Attempts

~~First Idea (recursive function)~~:x:Failed

  1. locate the biggest score
  2. split the array into two parts
  3. check forwards if groups can be formed
  4. check backwards if groups can be formed
  5. if did not success, try the 2nd largest
  6. if did work out, repeat the process for the 2nd largest

     >A desending ordered index list :heavy_check_mark:

Second Idea

### Source Code

```C
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
```

## Problem S5: Triangle: The Data Structure
