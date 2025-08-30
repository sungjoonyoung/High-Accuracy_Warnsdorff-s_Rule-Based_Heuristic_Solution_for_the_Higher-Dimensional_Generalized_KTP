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
int arr[50][50][50][50][50];
bool visited[50][50][50][50][50];
// int arr[12][12][12][12][12];  // 5D 배열, N 최대 10 권장 (메모리, 속도 문제)
// bool visited[12][12][12][12][12];
int dx[240], dy[240], dz[240], dw[240], dv[240];

ofstream fout;

void init_knight_moves() {
    int idx = 0;
    int dims[5] = {0,1,2,3,4};
    // 5D 나이트는 2칸, 1칸을 임의 두 축에 두고 나머지는 0
    for (int i = 0; i < 5; ++i) {
        for (int j = i+1; j < 5; ++j) {
            for (int sign1 : {-1,1}) {
                for (int sign2 : {-1,1}) {
                    int delta[5] = {};
                    delta[dims[i]] = 2 * sign1;
                    delta[dims[j]] = 1 * sign2;
                    dx[idx] = delta[0];
                    dy[idx] = delta[1];
                    dz[idx] = delta[2];
                    dw[idx] = delta[3];
                    dv[idx] = delta[4];
                    idx++;

                    delta[dims[i]] = 1 * sign1;
                    delta[dims[j]] = 2 * sign2;
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

bool backtracking(int x, int y, int z, int w, int v, int step) {
    arr[x][y][z][w][v] = step;
    visited[x][y][z][w][v] = true;

    if (step == N * N * N * N * N) {
        return true;
    }

    for (int i = 0; i < 240; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        int nz = z + dz[i];
        int nw = w + dw[i];
        int nv = v + dv[i];

        if (valid(nx, ny, nz, nw, nv) && !visited[nx][ny][nz][nw][nv]) {
            if (backtracking(nx, ny, nz, nw, nv, step + 1)) {
                return true;
            }
        }
    }

    visited[x][y][z][w][v] = false;
    arr[x][y][z][w][v] = 0;
    return false;
}

int main(int argc, char* argv[]) {
    if (argc < 7) {
        cerr << "Usage: ./a.out N x y z w v\n";
        return 1;
    }

    N = atoi(argv[1]);
    int sx = atoi(argv[2]);
    int sy = atoi(argv[3]);
    int sz = atoi(argv[4]);
    int sw = atoi(argv[5]);
    int sv = atoi(argv[6]);

    if (N > 10) {
        cerr << "N too large for naive backtracking (max 10 recommended)\n";
        return 1;
    }

    string file = "5D_Backtracking_N=" + string(argv[1]) + ".txt";
    fout.open(file, ios::app);

    init_knight_moves();

    auto start = chrono::steady_clock::now();

    fout << "Start position: " << sx << " " << sy << " " << sz << " " << sw << " " << sv << " ";
    bool res = backtracking(sx, sy, sz, sw, sv, 1);

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
