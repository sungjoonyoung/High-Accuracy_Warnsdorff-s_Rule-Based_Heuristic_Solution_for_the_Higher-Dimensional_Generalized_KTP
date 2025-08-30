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
// int arr[20][20][20][20];  // 메모리 고려, 20 이하 권장 (백트래킹 매우 느림)
// bool visited[20][20][20][20];
int dx[96], dy[96], dz[96], dw[96];

ofstream fout;

void init_knight_moves() {
    int idx = 0;
    int dims[4] = {0, 1, 2, 3};
    for (int i = 0; i < 4; ++i) {
        for (int j = i+1; j < 4; ++j) {
            for (int sign1 : {-1,1}) {
                for (int sign2 : {-1,1}) {
                    int delta[4] = {};
                    delta[dims[i]] = 2 * sign1;
                    delta[dims[j]] = 1 * sign2;
                    dx[idx] = delta[0];
                    dy[idx] = delta[1];
                    dz[idx] = delta[2];
                    dw[idx] = delta[3];
                    idx++;

                    delta[dims[i]] = 1 * sign1;
                    delta[dims[j]] = 2 * sign2;
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

// 4D 백트래킹
bool backtracking(int x, int y, int z, int w, int step) {
    arr[x][y][z][w] = step;
    visited[x][y][z][w] = true;

    if (step == N * N * N * N) {
        return true;
    }

    for (int i = 0; i < 96; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        int nz = z + dz[i];
        int nw = w + dw[i];

        if (valid(nx, ny, nz, nw) && !visited[nx][ny][nz][nw]) {
            if (backtracking(nx, ny, nz, nw, step + 1)) {
                return true;
            }
        }
    }

    visited[x][y][z][w] = false;
    arr[x][y][z][w] = 0;
    return false;
}

int main(int argc, char* argv[]) {
    if (argc < 6) {
        cerr << "Usage: ./a.out N x y z w\n";
        return 1;
    }

    N = atoi(argv[1]);
    int sx = atoi(argv[2]);
    int sy = atoi(argv[3]);
    int sz = atoi(argv[4]);
    int sw = atoi(argv[5]);

    if (N > 20) {
        cerr << "N too large for naive backtracking (max 20 recommended)\n";
        return 1;
    }

    string file = "4D_Backtracking_N=" + string(argv[1]) + ".txt";
    fout.open(file, ios::app);

    init_knight_moves();

    auto start = chrono::steady_clock::now();

    fout << "Start position: " << sx << " " << sy << " " << sz << " " << sw << " ";
    bool res = backtracking(sx, sy, sz, sw, 1);

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

    fout.close();

    return res ? 1 : 0;
}
