#include <cstring>
#include <chrono>
#include <iostream>

using namespace std;
using namespace std::chrono;

#define MAX 10000

double A [MAX][MAX] = {1}, x[MAX] = {}, y[MAX] = {};


int main(){

    auto start = high_resolution_clock::now();
    for (int i = 0; i < MAX ; i++)
        for (int j = 0 ; j < MAX ; j++)
            y[i] += A[i][j]*x[j];
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout<<duration.count()<<" ms"<<endl;

    memset(y, 0, sizeof(y));

    auto start1 = high_resolution_clock::now();
    for (int j = 0; j < MAX ; j++)
        for (int i = 0 ; i < MAX ; i++)
            y[i] += A[i][j]*x[j];
    auto stop1 = high_resolution_clock::now();
    auto duration1 = duration_cast<microseconds>(stop1 - start1);
    cout<<duration1.count()<<" ms"<<endl;
    
    return 0;
}

