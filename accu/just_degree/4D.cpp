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
int dx[96], dy[96], dz[96], dw[96];
int degree[100][100][100][100];

ofstream fout;

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
                    for (int i = 0; i < 96; i++) {
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
    for (int i = 0; i < 96; i++) {
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

        for (int i = 0; i < 96; i++) {
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
    if (argc < 6) {
        cerr << "Usage: ./4D.exe N x y z w\n";
        return 1;
    }

    N = atoi(argv[1]);
    int sx = atoi(argv[2]);
    int sy = atoi(argv[3]);
    int sz = atoi(argv[4]);
    int sw = atoi(argv[5]);

    

    string file = "Dimension=4_N=" + string(argv[1]) + ".txt";

    // 이전 파일 읽기 (누적 통계를 위한)
    ifstream fin(file);
    vector<string> old_lines;
    int success_count = 0, fail_count = 0;
    bool first_line = true;

    if(fin) {
        string line;
        while (getline(fin, line)) {
            if (first_line && line.rfind("Success:", 0) == 0) {
                // 첫 줄에서 Success/Fail 카운트 추출
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
    bool res = knight_tour(sx, sy, sz, sw);
    auto end = chrono::steady_clock::now();
    
    auto ms = chrono::duration_cast<chrono::milliseconds>(end - start).count();
    auto us = chrono::duration_cast<chrono::microseconds>(end - start).count();

    if (res)  success_count++;
    else fail_count++;
    // 새로 전체 파일 덮어쓰기
    ofstream fout(file, ios::trunc);
    fout << "Success: " << success_count << " Fail: " << fail_count << "\n";

    for (string& l : old_lines) {
        fout << l << "\n";
    }

    fout << "Start position: " << sx << " " << sy << " " << sz << " "<<sw<<" - ";
    fout << (res ? "Success" : "Fail");
    fout << " Execution time: " << ms << " ms (" << us << " μs)\n";



    
    return res ? 1 : 0;
    
}
