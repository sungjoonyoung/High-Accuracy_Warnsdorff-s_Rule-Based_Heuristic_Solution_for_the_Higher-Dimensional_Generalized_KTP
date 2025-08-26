#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <tuple>
#include <cmath>
#include <chrono>
using namespace std;

int N;
int arr[100][100][100][100];
bool visited[100][100][100][100];
int dx[48], dy[48], dz[48], dw[48];
int degree[100][100][100][100];

ofstream fout;
string file="_path_4D.txt";
void pr(int x,int y,int z,int w,int xx,int yy,int zz,int ww){
    fout<<"(";
    fout<<"(";

    fout<<x<<",";
    fout<<y<<",";
    fout<<z<<",";
    fout<<w<<",";
    
    fout<<"),(";

    fout<<xx<<",";
    fout<<yy<<",";
    fout<<zz<<",";
    fout<<ww<<",";

    fout<<")),\n";
}
void init_knight_moves() {
    int idx = 0;
    int dirs[4] = {0, 1, 2, 3};
    for (int i = 0; i < 4; ++i) {
        for (int j = i + 1; j < 4; ++j) {
            int a = dirs[i], b = dirs[j];
            for (int sign1 : {-1, 1}) {
                for (int sign2 : {-1, 1}) {
                    int delta[4] = {};
                    delta[a] = 2 * sign1;
                    delta[b] = 1 * sign2;
                    dx[idx] = delta[0];
                    dy[idx] = delta[1];
                    dz[idx] = delta[2];
                    dw[idx] = delta[3];
                    idx++;

                    delta[a] = 1 * sign1;
                    delta[b] = 2 * sign2;
                    dx[idx] = delta[0];
                    dy[idx] = delta[1];
                    dz[idx] = delta[2];
                    dw[idx] = delta[3];
                    idx++;
                }
            }
        }
    }
}

bool valid(int x, int y, int z, int w) {
    return 0 <= x && x < N && 0 <= y && y < N && 0 <= z && z < N && 0 <= w && w < N;
}

void init_degree() {
    for (int x = 0; x < N; x++)
        for (int y = 0; y < N; y++)
            for (int z = 0; z < N; z++)
                for (int w = 0; w < N; w++) {
                    int cnt = 0;
                    for (int i = 0; i < 48; i++) {
                        int nx = x + dx[i];
                        int ny = y + dy[i];
                        int nz = z + dz[i];
                        int nw = w + dw[i];
                        if (valid(nx, ny, nz, nw)){
                            pr(x,y,z,w,nx,ny,nz,nw);
                            cnt++;
                        }
                    }
                    degree[x][y][z][w] = cnt;
                }
}

void update_degree_around(int x, int y, int z, int w) {
    for (int i = 0; i < 48; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        int nz = z + dz[i];
        int nw = w + dw[i];
        if (valid(nx, ny, nz, nw) && !visited[nx][ny][nz][nw]) {
            degree[nx][ny][nz][nw]--;
        }
    }
}


int main(int argc, char* argv[]) {
    N = 4;
    fout.open(file);   // 전역 fout을 열기
    
    init_knight_moves();
    // for(int i=0;i<24;i++){
    //     cout<<dx[i]<<" "<<dy[i]<<" "<<dz[i]<<" "<<dw[i]<<"\n";
    // }
    init_degree();
    // for(int i=0;i<48;i++){
    //     cout<<dx[i]<<" "<<dy[i]<<" "<<dz[i]<<" "<<dw[i]<<"\n";
    // }
}
