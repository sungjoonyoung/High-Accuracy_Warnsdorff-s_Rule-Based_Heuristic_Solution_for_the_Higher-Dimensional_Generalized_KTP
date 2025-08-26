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
    int step = 1;
    while (true) {
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
    if (argc < 5) {
        cerr << "Usage: ./a.out N x y z\n";
        return 1;
    }

    N = atoi(argv[1]);
    int sx = atoi(argv[2]);
    int sy = atoi(argv[3]);
    int sz = atoi(argv[4]);

    // 힙 배열 초기화
    size_t total_size = static_cast<size_t>(N) * N * N;
    arr.resize(total_size, 0);
    visited.resize(total_size, false);
    degree.resize(total_size, 0);

    string file = "Dimension=3_N=" + string(argv[1]) + ".txt";

    // 이전 파일 읽기 (누적 통계를 위한)
    ifstream fin(file);
    vector<string> old_lines;
    int success_count = 0, fail_count = 0;
    bool first_line = true;

    if (fin) {
        string line;
        while (getline(fin, line)) {
            if (first_line && line.rfind("Success:", 0) == 0) {
                size_t s_pos = line.find("Success:");
                size_t f_pos = line.find("Fail:");

                if (s_pos != string::npos && f_pos != string::npos) {
                    success_count = stoi(line.substr(s_pos + 8, f_pos - (s_pos + 8)));
                    fail_count = stoi(line.substr(f_pos + 5));
                }
            } else {
                old_lines.push_back(line);
            }
            first_line = false;
        }
        fin.close();
    }

    // 새로운 실행
    init_knight_moves();
    init_degree();

    auto start = chrono::steady_clock::now();
    bool res = knight_tour(sx, sy, sz);
    auto end = chrono::steady_clock::now();

    auto ms = chrono::duration_cast<chrono::milliseconds>(end - start).count();
    auto us = chrono::duration_cast<chrono::microseconds>(end - start).count();

    // 성공/실패 카운트 갱신
    if (res) success_count++;
    else fail_count++;

    // 새로 전체 파일 덮어쓰기
    ofstream fout(file, ios::trunc);
    fout << "Success: " << success_count << " Fail: " << fail_count << "\n";

    for (string& l : old_lines) {
        fout << l << "\n";
    }

    fout << "Start position: " << sx << " " << sy << " " << sz << " - ";
    fout << (res ? "Success" : "Fail");
    fout << " Execution time: " << ms << " ms (" << us << " μs)\n";

    return res ? 1 : 0;
}
