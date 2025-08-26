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
vector<int> arr;          // 1차원 힙 배열
vector<bool> visited;     // 1차원 힙 배열
vector<int> degree;

int dx[24], dy[24], dz[24];

struct Pos {
    int x, y, z;
};

ofstream fout;

void init_knight_moves() {
    int idx = 0;
    int base_moves[3][3] = {
        {2, 2, 1},
        {2, 1, 2},
        {1, 2, 2}
    };

    idx = 0;
    for (int p = 0; p < 3; p++) {
        int a = base_moves[p][0];
        int b = base_moves[p][1];
        int c = base_moves[p][2];
        for (int sign_a : {-1, 1}) {
            for (int sign_b : {-1, 1}) {
                for (int sign_c : {-1, 1}) {
                    dx[idx] = sign_a * a;
                    dy[idx] = sign_b * b;
                    dz[idx] = sign_c * c;
                    idx++;
                }
            }
        }
    }
}

inline bool valid(int x, int y, int z) {
    return 0 <= x && x < N && 0 <= y && y < N && 0 <= z && z < N;
}

inline size_t idx3(int x, int y, int z) {
    return static_cast<size_t>(x) * N * N + y * N + z;
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
                    if (valid(nx, ny, nz))
                        cnt++;
                }
                degree[idx3(x, y, z)] = cnt;
            }
}

void update_degree_around(int x, int y, int z) {
    for (int i = 0; i < 24; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        int nz = z + dz[i];
        if (valid(nx, ny, nz) && !visited[idx3(nx, ny, nz)]) {
            degree[idx3(nx, ny, nz)]--;
        }
    }
}

bool knight_tour(int x, int y, int z) {
    string file = "_path_3D.txt";
    ofstream fout(file, ios::trunc);
    
    int step = 1;
    while (true) {
        fout<<"("<<x<<","<<y<<","<<z<<"),\n";
        arr[idx3(x, y, z)] = step;
        visited[idx3(x, y, z)] = true;
        update_degree_around(x, y, z);

        if (step == N * N * N)
            return true;

        int best_deg = 1e9;
        int best_x = -1, best_y = -1, best_z = -1;

        for (int i = 0; i < 24; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            int nz = z + dz[i];

            if (valid(nx, ny, nz) && !visited[idx3(nx, ny, nz)]) {
                int deg = degree[idx3(nx, ny, nz)];

                if (deg < best_deg) {
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
    N = 8;
    int sx = 2;
    int sy = 3;
    int sz = 1;

    // 힙 배열 초기화
    size_t total_size = static_cast<size_t>(N) * N * N;
    arr.resize(total_size, 0);
    visited.resize(total_size, false);
    degree.resize(total_size, 0);


    

    // 새로운 실행
    init_knight_moves();
    init_degree();

    
    bool res = knight_tour(sx, sy, sz);

    
    cout << (res ? "Success" : "Fail");

    return res ? 1 : 0;
}
