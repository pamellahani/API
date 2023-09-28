#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "fibo.h"

#define NMAX 1000000
/*
Nom: fibo_rec
Parametres: entier n 
Valeur de retour: F(n)
aucun effet de bord, 
Post-condition: F(n) est un entier appartenant a la serie de Fibonnacci
*/
unsigned long long fibo_rec(int n){ //complexite : O(exp(n))
    if (n<=1){
        return n; 
    }
    else{
        return fibo_rec(n-2)+fibo_rec(n-1); 
    }
}

/*
Nom: fibo_iter
Parametres: entier n 
valeur de retour: F(n)
aucun effet de bord, 
Post-condition: F(n) est un entier appartenant a la serie de Fibonnacci
*/
double fibo_iter(int n){        //complexite O(N)
    double *tab = malloc(sizeof(double)*NMAX); 
    tab[0]=0; 
    tab[1]=1;
    for (int i =2;i<=n;i++){
        tab[i]=tab[i-1]+tab[i-2]; 
    }
    double res = tab[n]; 
    free(tab);
    return res; 
}

//fonction auxiliaire de fibo_rec2
double fibo_aux_rec2(double n, double a, double b){     //complexite O(log(n))
    if (n==0){
        return a; 
    }
   return fibo_aux_rec2(n-1,a+b,a); 
}

/*
Nom: fibo_rec2
Parametres: entier n 
valeur de retour: F(n)
aucun effet de bord, 
Post-condition: F(n) est un entier appartenant a la serie de Fibonnacci
*/
//fonction recursive dont le temps d'execution est considerablement reduit. 

double fibo_rec2(int n){   //complexite O(N)
    if (n==1){
        return 1; 
    }
    return fibo_aux_rec2(n,0,1);   
}

/*
Nom: puissance
Parametres: reel x, entier n (exposant) 
valeur de retour: x^n
aucun effet de bord, 
Post-condition: x^n est un nombre reel
*/
double puissance(double x, int n){ //complexite O(log(n))
    if(n==1){
        return x; 
    }
    if (n%2==0){
        return puissance(x*x,n/2); 
    }
    else{
        return x*puissance(x*x,((n-1)/2)); 
    }
}

/*
Nom: fibo_golden
Parametres: entier n 
valeur de retour: F(n)
effet de bord: calcul de F(n) en utilisant le nombre d'or 
Post-condition: F(n) est un entier appartenant a la serie de Fibonnacci
*/
double fibo_golden(int n){      //complexite O(log(n))
    double psi = (1+sqrt(5))/2; 
    double delta = (1-sqrt(5))/2;
    double res = (1/sqrt(5))*(puissance(psi,n)-puissance(delta,n)); 
    return res; 
}


/*
Nom: multiplier_mat
Parametres: matrice d'entiers de taille 2x2 mat1, matrice d'entiers de taille 2x2 mat2
valeur de retour: produit mat1 x mat2
effet de bord: aucun
Post-condition: le resultat est une matrice de taille 2x2
*/ 
Matrice multiplier_mat(Matrice mat1 ,Matrice mat2){     //complexite O(1)
    Matrice result; 
    result.a=mat1.a*mat2.a + mat1.b*mat2.c; 
    result.b=mat1.a*mat2.b + mat1.b*mat2.d; 
    result.c=mat1.c*mat2.a + mat1.d*mat2.c; 
    result.d=mat1.c*mat2.b + mat1.d*mat2.d; 
    return result; 
}

/*
Nom: puissance_mat
Parametres: matrice d'entiers de taille 2x2 mat, entier n (exposant)
valeur de retour: mat^n
effet de bord: aucun
Post-condition: le resultat est une matrice de taille 2x2
*/ 
//implementation d'exponentiation rapide matricielle. 
Matrice puissance_mat(Matrice m, int n){    //complexite O(log(n))
    if (n==1){
        return m; 
    }
    if (n%2==0){
        return puissance_mat(multiplier_mat(m,m),n/2); 
    }
    else{
        return multiplier_mat(m, puissance_mat(multiplier_mat(m,m),(n-1)/2)) ;  
    }
}

/*
Nom: calcul_Mat2
Parametres: matrice d'entiers de taille 2x2 mat1, matrice d'entiers de taille 2x1 mat2
valeur de retour: produit mat1 x mat2
effet de bord: aucun
Post-condition: le resultat est une matrice d'entiers de taille 2x1
*/ 
//calcul le produit des matrices (0,1,1,1)  et (0,1)
Mat2 calcul_Mat2(Matrice mat1, Mat2 mat2){      //complexite O(1)
    Mat2 result; 
    result.x= mat1.a*mat2.x + mat1.b*mat2.y; 
    result.y= mat1.c*mat2.x + mat1.d*mat2.y; 
    return result;  
}

/*
Nom: fibo_matrice
Parametres: entier n 
valeur de retour: F(n)
effet de bord: aucun
Post-condition: le resultat est un nombre reel.
*/ 
//renvoi F(n) calcule avec matrices. 
double fibo_matrice(int n){     //complexite O(log(n))
    Mat2 result = {0,1};
    Matrice matrice = {0,1,1,1}; 
    result = calcul_Mat2(puissance_mat(matrice,n),result); 
    return result.x; 
}




