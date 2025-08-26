#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include<algorithm>
#include<tuple>
#include<cmath>
#include <chrono>

using namespace std;

int N;
int arr[500][500][500];
bool visited[500][500][500];
int dx[24], dy[24], dz[24];
int degree[500][500][500];

struct Pos {
    int x, y, z;
};

ofstream fout;
string file="_path_3D.txt";
void pr(int x,int y,int z,int xx,int yy,int zz){
    fout<<"(";
    fout<<"(";

    fout<<x<<",";
    fout<<y<<",";
    fout<<z<<",";

    fout<<"),(";

    fout<<xx<<",";
    fout<<yy<<",";
    fout<<zz<<",";

    fout<<")),\n";
}
void init_knight_moves() {
    int idx = 0;
    int dirs[3] = {0, 1, 2};
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

bool valid(int x, int y, int z) {
    return 0 <= x && x < N && 0 <= y && y < N && 0 <= z && z < N;
}

void init_degree() {
    for (int x = 0; x < N; x++)
        for (int y = 0; y < N; y++)
            for (int z = 0; z < N; z++) {
                int cnt = 0;
                for (int i = 0; i < 24; i++) {
                    int nx = x + dx[i];
                    int ny = y + dy[i];
                    int nz = z + dz[i];
                    if (valid(nx, ny, nz)){
                        cnt++;
                        pr(x,y,z,nx,ny,nz);
                    }
                }
                degree[x][y][z] = cnt;
            }
}


int main(int argc, char* argv[]) {
    N = 5;
    fout.open(file);   // 전역 fout을 열기
    
    init_knight_moves();
    init_degree();
}