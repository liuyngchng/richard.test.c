/**
 * 我卖窝窝头我开心
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define M 10000                     // number of mantou
#define N 500                       // number of package

long int sell_mantou();                  // declare the function
    
int p[M];                           // price of mantou   
int c[N];                           // package capacity of mantou
int e[N];                           // price of package

int main()
{
    printf("mantou number is %d\n", M);
    printf("random_max=%d\n", RAND_MAX);
    srand((unsigned)time(NULL));
    int min_r = 1;                  // the minimum of random number
    int max_r = 10000;              // the maximum of random number
    
    for (int i = 0; i < M; i++) {   // init mantou price
        p[i] = rand() % (max_r - min_r + 1);
        printf("p[%d]=%d\n", i, p[i]); // for check mantou price
    }
    
    for (int i = 0; i < N; i++) {   // init package capacity
        c[i] = rand() % (max_r - min_r + 1);
        // printf("c[%d]=%d\n", i, c[i]); // for check package capacity
    }
    
    for (int i = 0; i < N; i++) {   // init package price
        e[i] = rand() % (max_r - min_r +1);
        // printf("e[%d]=%d\n", i, e[i]); // for check package price
    }
    
    // so how to sale mantou with or without package, to get the max profit?
    long int profit = sell_mantou();
    printf("my profit is %ld, I am a smart business guy.\n", profit);
}

/**
 * sale mantou to earn your life, enjoy it.
 * mantou must be put in package and then sell to customer
 */
long int sell_mantou()
{
    long int profit = 0;
    for (int i = 0; i < N; i++) {   // iterate all packages
        printf("package %d capacity c[%d]=%d\n", i, i, c[i]);
        //calculate profit
        int tmp_profit = 0;
        int tmp_c = c[i];      // current capacity
        int pkg_used = 1;
        for (int j = 0; j < M; j++) { // iterate all mantous
            if (p[j] < e[i])    // mantou price < package price, no profit
                continue;
            if (pkg_used) { 
                tmp_profit += p[j] - e[i];// put mantou[j] in packge[i]
                pkg_used = 0;
            } else {
                tmp_profit +=p[j];       // no packge[i] cost   
            }
            //printf("profit:%d, mantou price:%d, pkg price:%d\n", tmp_profit, p[j], e[i]); // dor debug
            tmp_c --;         // capacity count down
        }
        profit += tmp_profit; // calcuate profit of package[i]

    }
   return  profit;
}
