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
int dx[6], dy[6], dz[6];
int degree[500][500][500];

struct Pos {
    int x, y, z;
};

ofstream fout;

void init_knight_moves() {
    int idx = 0;
    // x축 이동
    dx[idx] = 1; dy[idx] = 0; dz[idx] = 0; idx++;
    dx[idx] = -1; dy[idx] = 0; dz[idx] = 0; idx++;
    // y축 이동
    dx[idx] = 0; dy[idx] = 1; dz[idx] = 0; idx++;
    dx[idx] = 0; dy[idx] = -1; dz[idx] = 0; idx++;
    // z축 이동
    dx[idx] = 0; dy[idx] = 0; dz[idx] = 1; idx++;
    dx[idx] = 0; dy[idx] = 0; dz[idx] = -1; idx++;
}


bool valid(int x, int y, int z) {
    return 0 <= x && x < N && 0 <= y && y < N && 0 <= z && z < N;
}

void init_degree() {
    for (int x = 0; x < N; x++)
        for (int y = 0; y < N; y++)
            for (int z = 0; z < N; z++) {
                int cnt = 0;
                for (int i = 0; i < 6; i++) {
                    int nx = x + dx[i];
                    int ny = y + dy[i];
                    int nz = z + dz[i];
                    if (valid(nx, ny, nz))
                        cnt++;
                }
                degree[x][y][z] = cnt;
            }
}

void update_degree_around(int x, int y, int z) {
    for (int i = 0; i < 6; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        int nz = z + dz[i];
        if (valid(nx, ny, nz) && !visited[nx][ny][nz]) {
            degree[nx][ny][nz]--;
        }
    }
}

bool knight_tour(int x, int y, int z) {
    
    string file = "_path_3D.txt";
    ofstream fout(file);

    int step = 1;
    while (true) {

        fout<<"("<<x<<","<<y<<","<<z<<"),\n";
        arr[x][y][z] = step;
        visited[x][y][z] = true;
        update_degree_around(x, y, z);

        if (step == N * N * N)
            return true;

        int best_deg = 1e9;
        double best_dist = -1.0;
        int best_x = -1, best_y = -1, best_z = -1;

        for (int i = 0; i < 6; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            int nz = z + dz[i];

            if (valid(nx, ny, nz) && !visited[nx][ny][nz]) {
                int deg = degree[nx][ny][nz];

                if (deg < best_deg ) {
                    best_deg = deg;
                    best_x = nx;
                    best_y = ny;
                    best_z = nz;
                }
            }
        }

        if (best_x == -1) return false;

        x = best_x;
        y = best_y;
        z = best_z;
        step++;
    }
    return true;
}


int main(int argc, char* argv[]) {

    N = 5;
    int sx = 3;
    int sy = 1;
    int sz = 4;


    // 새로운 실행
    init_knight_moves();
    init_degree();
    bool res = knight_tour(sx, sy, sz);
    
    cout << (res ? "Success" : "Fail");

    return res ? 1 : 0;
}