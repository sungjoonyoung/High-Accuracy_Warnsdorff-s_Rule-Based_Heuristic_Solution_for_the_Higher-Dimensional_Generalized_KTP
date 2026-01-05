#include<iostream>
#include<string>
#include<vector>
#include<fstream>
using namespace std;
int arr[10'000][10'000][10'000];
int main(void){
    for (int i = 0; i < 10000; ++i)
    for (int j = 0; j < 10000; ++j)
        for (int k = 0; k < 10; ++k)  // ← 10만 해도...
            arr[i][j][k] = 1;
}