#include <stdio.h>
#include "fibo.h"
#include <string.h>
#include <stdlib.h>

int main(int argc, char **argv){

    if (argc < 1){
        printf("usage: ./main n"); 
    }

    int rang = atoi(argv[1]); 

    // unsigned long long res1 = fibo_rec(rang);  
    // printf("res fibo_rec: %llu\n",res1);

    double res2 = fibo_iter(rang); 
    printf("res fibo_iter: %f\n",res2);

    double res3 = fibo_rec2(rang); 
    printf("res fibo_rec2: %f\n",res3); 

    double gold = fibo_golden(rang); 
    printf("res fibo_golden: %f\n",gold); 

    double res_mat = fibo_matrice(rang); 
    printf("res fibo_matrice: %f\n",res_mat); 

    return 0;
}
