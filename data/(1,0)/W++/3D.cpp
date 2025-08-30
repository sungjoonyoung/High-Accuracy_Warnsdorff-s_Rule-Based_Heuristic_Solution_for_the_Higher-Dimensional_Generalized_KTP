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
                arr[x][y][z]=degree[x][y][z]=visited[x][y][z]=0;
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
    int step = 1;
    while (true) {
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
    if (argc < 5) {
        cerr << "Usage: ./a.out N x y z\n";
        return 1;
    }

    N = atoi(argv[1]);
    int sx = atoi(argv[2]);
    int sy = atoi(argv[3]);
    int sz = atoi(argv[4]);

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

    auto start = chrono::steady_clock::now();
    bool res = knight_tour(sx, sy, sz);
    for(int i=0;i<6 and !res;i++){
        for(int j=0;j<6-1;j++)swap(dx[j],dx[j+1]);
        for(int j=0;j<6-1;j++)swap(dy[j],dy[j+1]);
        for(int j=0;j<6-1;j++)swap(dz[j],dz[j+1]);
        init_degree();
        res = res = knight_tour(sx, sy, sz);
    }
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