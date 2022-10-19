/**
 * 我卖窝窝头我开心
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define M 10000             // number of mantou
#define N 500               // number of package

int sell_mantou();          // declare the function
    
int p[M];                   // price of mantou   
int c[N];                   // package capacity of mantou
int e[N];                   // price of package

int main()
{
    printf("mantou number is %d\n", M);
    printf("random_max=%d\n", RAND_MAX);
    srand((unsigned)time(NULL));
    int min_r = 1;          // the minimum of random number
    int max_r = 10000;      // the maximum of random number
    
    // init mantou price
    for (int i = 0; i < M; i++) {
        p[i] = rand() % (max_r - min_r + 1);
        // printf("p[%d]=%d\n", i, p[i]); // for check mantou price
    }
    
    // init package capacity
    for (int i = 0; i < N; i++) {
        c[i] = rand() % (max_r - min_r + 1);
        // printf("c[%d]=%d\n", i, c[i]); // for check package capacity
    }
    
    // init package price
    for (int i = 0; i < N; i++) {
        e[i] = rand() % (max_r - min_r +1);
        // printf("e[%d]=%d\n", i, e[i]); // for check package price
    }
    
    // so how to sell mantou with or without package, to get the max profit?
    int profit = sell_mantou();
    printf("my profit is %d, I am a smart business guy.\n", profit);
}

/**
 * sell mantou to earn your life, enjoy it.
 */
int sell_mantou()
{
    int profit = 0;
    for (int i = 0; i < N; i++) {
        printf("e[%d]=%d\n", i, e[i]); // use glocal variables
    }
   return  profit;
}
