#include <iostream>
#include <string>
#include <fstream>
#include <chrono>

using namespace std;

int N;
int arr[500][500][500];
bool visited[500][500][500];
int dx[24], dy[24], dz[24];

ofstream fout;

void init_knight_moves() {
    int idx = 0;
    int dirs[3] = {0, 1, 2};
    for (int i = 0; i < 3; ++i) {
        int a = dirs[i];
        int b = dirs[(i + 1) % 3];
        // int c = dirs[(i + 2) % 3]; // 사용하지 않으므로 제거 가능
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

bool backtracking(int x, int y, int z, int step) {
    // 디버깅용 진행 출력, 필요 없으면 주석 처리하세요.
    cout << "\rStep " << step << ": (" << x << ", " << y << ", " << z << ")" << flush;

    arr[x][y][z] = step;
    visited[x][y][z] = true;

    if (step == N * N * N) return true;

    for (int i = 0; i < 24; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        int nz = z + dz[i];

        if (valid(nx, ny, nz) && !visited[nx][ny][nz]) {
            if (backtracking(nx, ny, nz, step + 1)) return true;
        }
    }

    visited[x][y][z] = false;
    arr[x][y][z] = 0;
    return false;
}

int main(int argc, char* argv[]) {
    if (argc < 5) {
        cerr << "Usage: ./a.out N x y z\n";
        return 1;
    }

    N = atoi(argv[1]);
    int sx = atoi(argv[2]);
    int sy = atoi(argv[3]);
    int sz = atoi(argv[4]);

    if (N > 30) {
        cerr << "N is too large for naive backtracking (max 30 recommended)\n";
        return 1;
    }

    // 배열 초기화
    for (int x = 0; x < N; ++x)
        for (int y = 0; y < N; ++y)
            for (int z = 0; z < N; ++z) {
                visited[x][y][z] = false;
                arr[x][y][z] = 0;
            }

    string file = "3D_Backtracking_N=" + string(argv[1]) + ".txt";
    fout.open(file, ios::app);

    init_knight_moves();

    auto start = chrono::steady_clock::now();

    fout << "Start position: " << sx << " " << sy << " " << sz << " ";
    bool res = backtracking(sx, sy, sz, 1);

    auto end = chrono::steady_clock::now();
    auto diff = end - start;

    auto ms = chrono::duration_cast<chrono::milliseconds>(diff).count();
    auto us = chrono::duration_cast<chrono::microseconds>(diff).count();

    if (!res) {
        fout << "No solution found\n";
        cerr << "No solution found\n";
    } else {
        fout << "Yes solution found\n";
        cerr << "Yes solution found\n";
    }

    fout << "Execution time: " << ms << " ms (" << us << " μs)\n";

    fout.close();

    return res ? 1 : 0;
}
