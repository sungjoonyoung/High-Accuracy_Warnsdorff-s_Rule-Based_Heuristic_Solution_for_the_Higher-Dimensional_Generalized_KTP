// #include <iostream>
// #include <string>
// #include <vector>
// #include <fstream>
// #include <algorithm>
// #include <tuple>
// #include <cmath>
// using namespace std;

// int N=1000;
// int arr[1000][1000][1000];

// int main(void) {
//     int a;
//     cin>>a;
//     cout<<"A";
//     for(int i=0;i<N;i++)
//         for(int a=0;a<N;a++)
//             for(int b=0;b<N;b++)
//                 arr[i][a][b]=1'000'000'000;
    
//     cout<<"A";
// }

#include <iostream>
#include <vector>
using namespace std;

int main() {
    size_t N = 1000;
    vector<int> arr(N * N * N, 0);

    auto idx = [&](size_t x, size_t y, size_t z) {
        return x * N * N + y * N + z;
    };

    arr[idx(0,0,0)] = 42;
    cout << arr[idx(0,0,0)] << endl;
}
