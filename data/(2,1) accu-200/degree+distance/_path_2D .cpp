#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <cmath>
#include <chrono>

using namespace std;

int N;
int arr[500][500];
bool visited[500][500];
int dx[8] = {2, 1, -1, -2, -2, -1, 1, 2};
int dy[8] = {1, 2, 2, 1, -1, -2, -2, -1};
int degree[500][500];

struct Pos {
    int x, y;
};

ofstream fout;

bool valid(int x, int y) {
    return 0 <= x && x < N && 0 <= y && y < N;
}

void init_degree() {
    for (int x = 0; x < N; x++)
        for (int y = 0; y < N; y++) {
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

double distance_from_center(int x, int y) {
    double mid = (N - 1) / 2.0;
    double dx = x - mid;
    double dy = y - mid;
    return dx*dx + dy*dy;
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
    string file = "_path_2D.txt";
    ofstream fout(file);
    
    int step = 1;
    while (true) {
        fout<<"("<<x<<","<<y<<"),\n";
        arr[x][y] = step;
        visited[x][y] = true;
        update_degree_around(x, y);

        if (step == N * N)
            return true;

        int best_deg = 1e9;
        double best_dist = -1.0;
        int best_x = -1, best_y = -1;

        for (int i = 0; i < 8; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];

            if (valid(nx, ny) && !visited[nx][ny]) {
                int deg = degree[nx][ny];
                double dist = distance_from_center(nx, ny);

                if (deg < best_deg || (deg == best_deg && dist > best_dist)) {
                    best_deg = deg;
                    best_dist = dist;
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

    N = 10;
    int sx = 4;
    int sy = 5;

    

    init_degree();

    bool res = knight_tour(sx, sy);
    
    cout << (res ? "Success" : "Fail");

    return res ? 1 : 0;
}
