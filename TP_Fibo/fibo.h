//structure matrice de tallle 2 (0,1,1,1)
struct matrice{
    double a;
    double b; 
    double c; 
    double d;  
};

typedef struct matrice Matrice; 

//matrice de taille 2x1 (0,1)
struct mat2{
    double x; 
    double y; 
};

typedef struct mat2 Mat2; 


unsigned long long fibo_rec(int n); 

double fibo_iter(int n); 

double fibo_rec2(int n); 

double puissance(double x, int n);

double fibo_golden(int n);

Matrice multiplier_mat(Matrice mat1 ,Matrice mat2); 

Matrice puissance_mat(Matrice m, int n); 

Mat2 calcul_vect(Matrice m, Mat2 u);

double fibo_matrice(int n); 



