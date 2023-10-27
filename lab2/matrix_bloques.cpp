#include <iostream>
#include <chrono>

using namespace std;
using namespace std::chrono;

int sizes[] = {100, 200, 300, 400, 500, 600, 700, 800, 900, 1000, 2000};

void init(float**& matrizA, float**& matrizB, int size, float**& Res){
    matrizA = new float *[size];
    matrizB = new float *[size];
    Res = new float *[size];

    for(int i=0;i<size;i++){
        matrizA[i] = new float[size];
        matrizB[i] = new float[size];
        Res[i] = new float[size];
    }

    for(int i=0 ; i<size ; i++){
        for(int j=0; j<size; j++){
            matrizA[i][j]=1+rand()%100;
            matrizB[i][j]=1+rand()%100;
            Res[i][j]=0;
        }
    }
}

void multiplicar(float** matrizA, float** matrizB, int size, float** Res ){
    int i, j, k, ii, jj, kk;
    int blockSize=100;  //80kb cache L1, float 4bytes, 80000/4 = 20000 = 141 aprox 

    for (i = 0; i < size; i += blockSize) 
        for (j = 0; j < size; j += blockSize) 
            for (k = 0; k < size; k += blockSize)
                for (ii = i; ii < std::min(i + blockSize, size); ii++) 
                    for (jj = j; jj < std::min(j + blockSize, size); jj++) 
                        for (kk = k; kk < std::min(k + blockSize, size); kk++) 
                            Res[ii][jj] += matrizA[ii][kk] * matrizB[kk][jj];
}

int main() {
    // Definir las dimensiones de las matrices
    float** matrizA;
    float** matrizB;
    float** Res;

    for (int i = 0; i <  sizeof(sizes)/sizeof(sizes[0]); i++)
    {
        init(matrizA, matrizB, sizes[i], Res);

        auto start = high_resolution_clock::now() ;
        multiplicar(matrizA, matrizB, sizes[i], Res);
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        cout<<duration.count()<<" mic_s"<<endl;
    }

    return 0;
}