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

void init_knight_moves() {
    int idx = 0;
    // a: ±3이 들어갈 축, b: ±2가 들어갈 축 (서로 달라야 함)
    for (int a = 0; a < 4; ++a) {
        for (int b = 0; b < 4; ++b) {
            if (a == b) continue;
            for (int s3 : {3, -3}) {
                for (int s2 : {2, -2}) {
                    int v[4] = {0, 0, 0, 0};
                    v[a] = s3;
                    v[b] = s2;
                    dx[idx] = v[0];
                    dy[idx] = v[1];
                    dz[idx] = v[2];
                    dw[idx] = v[3];
                    ++idx;
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
                    arr[x][y][z][w]=degree[x][y][z][w]=visited[x][y][z][w]=0;
                    int cnt = 0;
                    for (int i = 0; i < 48; i++) {
                        int nx = x + dx[i];
                        int ny = y + dy[i];
                        int nz = z + dz[i];
                        int nw = w + dw[i];
                        if (valid(nx, ny, nz, nw))
                            cnt++;
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

bool knight_tour(int x, int y, int z, int w) {
    int step = 1;
    while (true) {
        arr[x][y][z][w] = step;
        visited[x][y][z][w] = true;
        update_degree_around(x, y, z, w);

        if (step == N * N * N * N)
            return true;

        int best_deg = 1e9;
        double best_dist = -1.0;
        int best_x = -1, best_y = -1, best_z = -1, best_w = -1;

        for (int i = 0; i < 48; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            int nz = z + dz[i];
            int nw = w + dw[i];

            if (valid(nx, ny, nz, nw) && !visited[nx][ny][nz][nw]) {
                int deg = degree[nx][ny][nz][nw];

                if (deg < best_deg ) {
                    best_deg = deg;
                    best_x = nx;
                    best_y = ny;
                    best_z = nz;
                    best_w = nw;
                }
            }
        }

        if (best_x == -1) return false;

        x = best_x;
        y = best_y;
        z = best_z;
        w = best_w;
        step++;
    }
    return true;
}

int main(int argc, char* argv[]) {
    init_knight_moves();
    for(int i=0;i<48;i++){
        cout<<dx[i]<<" "<<dy[i]<<" "<<dz[i]<<" "<<dw[i]<<"\n";
    }
}
