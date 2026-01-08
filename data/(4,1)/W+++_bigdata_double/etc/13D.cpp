#include<iostream>
#include<string>
#include<vector>
#include<fstream>
using namespace std;
int N;
int arr[500][500][500];
int dx[24], dy[24], dz[24];

void init_knight_moves(void) {
    int idx = 0;
    int dirs[3] = {0, 1, 2}; // 축 인덱스 x=0, y=1, z=2
    for (int i = 0; i < 3; ++i) {
        int a = dirs[i];
        int b = dirs[(i + 1) % 3];
        int c = dirs[(i + 2) % 3];
        for (int sign1 : {-1, 1}) {
            for (int sign2 : {-1, 1}) {
                int delta[3] = {};
                delta[a] = 2 * sign1;
                delta[b] = 1 * sign2;
                dx[idx] = delta[0];
                dy[idx] = delta[1];
                dz[idx] = delta[2];
                idx++;
                
                // 반대 조합: 1칸 vs 2칸
                delta[a] = 1 * sign1;
                delta[b] = 2 * sign2;
                dx[idx] = delta[0];
                dy[idx] = delta[1];
                dz[idx] = delta[2];
                idx++;
            }
        }
    }
}
int main(int argc, char* argv[]){
    //파일 이름
    N=atoi(argv[1]);
    string file;
    file+="Dimension=3_";
    file+="N=";
    file+=argv[1];
    file+=".txt";
    ofstream fout(file, ios::app);
    //현재 위치 업데이트
    vector<int> cur;
    for(int i=0;i<3;i++)cur.push_back(atoi(argv[i+2]));
    for(auto a:cur)fout<<a<<" ";
    cout<<": ";
    //나이트 이동경로 업데이트
    init_knight_moves();
    
}