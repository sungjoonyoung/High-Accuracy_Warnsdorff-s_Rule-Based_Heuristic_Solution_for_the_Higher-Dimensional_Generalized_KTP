#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <chrono>

using namespace std;

int N;
int arr[500][500];
bool visited[500][500];

// (3,2) 이동 규칙 (총 8방향)
int dx[8] = {3, 3, -3, -3, 2, 2, -2, -2};
int dy[8] = {2, -2, 2, -2, 3, -3, 3, -3};

int degree[500][500];

bool valid(int x, int y) {
    return 0 <= x && x < N && 0 <= y && y < N;
}

void init_degree() {
    for (int x = 0; x < N; x++)
        for (int y = 0; y < N; y++) {
            arr[x][y]=degree[x][y]=visited[x][y]=0;
            int cnt = 0;
            for (int i = 0; i < 8; i++) {
                int nx = x + dx[i];
                int ny = y + dy[i];
                if (valid(nx, ny))
                    cnt++;
            }
            degree[x][y] = cnt;
        }
}

void update_degree_around(int x, int y) {
    for (int i = 0; i < 8; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if (valid(nx, ny) && !visited[nx][ny]) {
            degree[nx][ny]--;
        }
    }
}

bool knight_tour(int x, int y) {
    int step = 1;
    while (true) {
        arr[x][y] = step;
        visited[x][y] = true;
        update_degree_around(x, y);

        if (step == N * N)
            return true;

        int best_deg = 1e9;
        int best_x = -1, best_y = -1;

        for (int i = 0; i < 8; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];

            if (valid(nx, ny) && !visited[nx][ny]) {
                int deg = degree[nx][ny];

                if (deg < best_deg) {
                    best_deg = deg;
                    best_x = nx;
                    best_y = ny;
                }
            }
        }

        if (best_x == -1) return false;

        x = best_x;
        y = best_y;
        step++;
    }
    return true;
}

int main(int argc, char* argv[]) {
    if (argc < 4) {
        cerr << "Usage: ./a.out N x y\n";
        return 1;
    }

    N = atoi(argv[1]);
    int sx = atoi(argv[2]);
    int sy = atoi(argv[3]);

    string file = "Dimension=2_N=" + string(argv[1]) + ".txt";

    // 이전 파일 읽기 (누적 통계용)
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

    init_degree();

    auto start = chrono::steady_clock::now();
    bool res = knight_tour(sx, sy);
    for(int i=0;i<8 and !res;i++){
        for(int j=0;j<8-1;j++)swap(dx[j],dx[j+1]);
        for(int j=0;j<8-1;j++)swap(dy[j],dy[j+1]);
        init_degree();
        res = knight_tour(sx, sy);
    }
    auto end = chrono::steady_clock::now();

    auto ms = chrono::duration_cast<chrono::milliseconds>(end - start).count();
    auto us = chrono::duration_cast<chrono::microseconds>(end - start).count();

    if (res) success_count++;
    else fail_count++;

    ofstream fout(file, ios::trunc);
    fout << "Success: " << success_count << " Fail: " << fail_count << "\n";

    for (string& l : old_lines) {
        fout << l << "\n";
    }

    fout << "Start position: " << sx << " " << sy << " - ";
    fout << (res ? "Success" : "Fail");
    fout << " Execution time: " << ms << " ms (" << us << " μs)\n";

    return res ? 1 : 0;
}
