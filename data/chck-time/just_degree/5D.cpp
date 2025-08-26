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

int arr[25][25][25][25][25];
bool visited[25][25][25][25][25];
int degree[25][25][25][25][25];

int dx[240], dy[240], dz[240], dw[240], dv[240];

void init_knight_moves() {
    int idx = 0;
    int dirs[5] = {0,1,2,3,4};
    for (int i=0; i<5; i++) {
        for (int j=i+1; j<5; j++) {
            for (int sign1 : {-1,1}) {
                for (int sign2 : {-1,1}) {
                    int delta[5] = {};
                    delta[dirs[i]] = 2 * sign1;
                    delta[dirs[j]] = 1 * sign2;
                    dx[idx] = delta[0];
                    dy[idx] = delta[1];
                    dz[idx] = delta[2];
                    dw[idx] = delta[3];
                    dv[idx] = delta[4];
                    idx++;

                    delta[dirs[i]] = 1 * sign1;
                    delta[dirs[j]] = 2 * sign2;
                    dx[idx] = delta[0];
                    dy[idx] = delta[1];
                    dz[idx] = delta[2];
                    dw[idx] = delta[3];
                    dv[idx] = delta[4];
                    idx++;
                }
            }
        }
    }
}

bool valid(int x, int y, int z, int w, int v) {
    return 0 <= x && x < N &&
           0 <= y && y < N &&
           0 <= z && z < N &&
           0 <= w && w < N &&
           0 <= v && v < N;
}

void init_degree() {
    for (int x=0; x<N; x++)
        for (int y=0; y<N; y++)
            for (int z=0; z<N; z++)
                for (int w=0; w<N; w++)
                    for (int v=0; v<N; v++) {
                        int cnt = 0;
                        for (int i=0; i<240; i++) {
                            int nx = x + dx[i];
                            int ny = y + dy[i];
                            int nz = z + dz[i];
                            int nw = w + dw[i];
                            int nv = v + dv[i];
                            if (valid(nx, ny, nz, nw, nv)) cnt++;
                        }
                        degree[x][y][z][w][v] = cnt;
                    }
}

void update_degree_around(int x, int y, int z, int w, int v) {
    for (int i=0; i<240; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        int nz = z + dz[i];
        int nw = w + dw[i];
        int nv = v + dv[i];
        if (valid(nx, ny, nz, nw, nv) && !visited[nx][ny][nz][nw][nv]) {
            degree[nx][ny][nz][nw][nv]--;
        }
    }
}

bool knight_tour(int x, int y, int z, int w, int v) {
    int step = 1;
    while (true) {
        arr[x][y][z][w][v] = step;
        visited[x][y][z][w][v] = true;
        update_degree_around(x, y, z, w, v);

        if (step == N*N*N*N*N) return true;

        int best_deg = 1e9;
        double best_dist = -1.0;
        int best_x = -1, best_y = -1, best_z = -1, best_w = -1, best_v = -1;

        for (int i=0; i<240; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            int nz = z + dz[i];
            int nw = w + dw[i];
            int nv = v + dv[i];

            if (valid(nx, ny, nz, nw, nv) && !visited[nx][ny][nz][nw][nv]) {
                int deg = degree[nx][ny][nz][nw][nv];
                if (deg < best_deg) {
                    best_deg = deg;
                    best_x = nx;
                    best_y = ny;
                    best_z = nz;
                    best_w = nw;
                    best_v = nv;
                }
            }
        }
        if (best_x == -1) return false;

        x = best_x;
        y = best_y;
        z = best_z;
        w = best_w;
        v = best_v;
        step++;
    }
    return true;
}

int main(int argc, char* argv[]) {
    if (argc < 7) {
        cerr << "Usage: ./5D.exe N x y z w v\n";
        return 1;
    }

    N = atoi(argv[1]);
    int sx = atoi(argv[2]);
    int sy = atoi(argv[3]);
    int sz = atoi(argv[4]);
    int sw = atoi(argv[5]);
    int sv = atoi(argv[6]);

    // 배열 초기화
    fill(&visited[0][0][0][0][0], &visited[0][0][0][0][0] + sizeof(visited)/sizeof(bool), false);
    fill(&arr[0][0][0][0][0], &arr[0][0][0][0][0] + sizeof(arr)/sizeof(int), 0);

    string file = "Dimension=5_N=" + string(argv[1]) + ".txt";
    ofstream fout(file, ios::app);

    init_knight_moves();
    init_degree();

    auto start = chrono::steady_clock::now();

    fout << "Start position: " << sx << " " << sy << " " << sz << " " << sw << " " << sv << " ";
    bool res = knight_tour(sx, sy, sz, sw, sv);

    auto end = chrono::steady_clock::now();
    auto diff = end - start;
    auto ms = chrono::duration_cast<chrono::milliseconds>(diff).count();
    auto us = chrono::duration_cast<chrono::microseconds>(diff).count();

    if (!res) {
        fout << "No solution found\n";
    } else {
        fout << "Yes solution found\n";
    }
    fout << "Execution time: " << ms << " ms (" << us << " μs)\n";

    return res ? 1 : 0;
}
