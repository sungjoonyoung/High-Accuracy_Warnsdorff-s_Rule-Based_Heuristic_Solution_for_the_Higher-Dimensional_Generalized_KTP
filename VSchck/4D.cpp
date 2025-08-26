#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <tuple>
#include <cmath>
using namespace std;

int N;
int arr[100][100][100][100];
bool visited[100][100][100][100];
int dx[96], dy[96], dz[96], dw[96];

ofstream fout;

void init_knight_moves() {
    int idx = 0;
    int dirs[4] = {0, 1, 2, 3};
    for (int i = 0; i < 4; ++i) {
        for (int j = i+1; j < 4; ++j) {
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

int get_degree(int x, int y, int z, int w) {
    int cnt = 0;
    for (int i = 0; i < 96; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        int nz = z + dz[i];
        int nw = w + dw[i];
        if (valid(nx, ny, nz, nw) && !visited[nx][ny][nz][nw]) cnt++;
    }
    return cnt;
}

double distance_from_center(int x, int y, int z, int w) {
    double mid = (N - 1) / 2.0;
    double dx = x - mid;
    double dy = y - mid;
    double dz = z - mid;
    double dw = w - mid;
    return sqrt(dx*dx + dy*dy + dz*dz + dw*dw);
}

bool knight_tour(int x, int y, int z, int w) {
    int step = 1;
    while (true) {
        arr[x][y][z][w] = step;
        visited[x][y][z][w] = true;
        if (step == N * N * N * N) return true;

        vector<tuple<int, double, int, int, int, int>> next;
        for (int i = 0; i < 96; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            int nz = z + dz[i];
            int nw = w + dw[i];
            if (valid(nx, ny, nz, nw) && !visited[nx][ny][nz][nw]) {
                int deg = get_degree(nx, ny, nz, nw);
                double dist = distance_from_center(nx, ny, nz, nw);
                next.emplace_back(deg, dist, nx, ny, nz, nw);
            }
        }
        if (next.empty()) return false;

        sort(next.begin(), next.end(), [](auto& a, auto& b) {
            return (get<0>(a) != get<0>(b)) ? get<0>(a) < get<0>(b)
                                           : get<1>(a) > get<1>(b);
        });

        tie(ignore, ignore, x, y, z, w) = next[0];
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
    ofstream fout(file, ios::app);

    init_knight_moves();
    fout << "Start position: " << sx << " " << sy << " " << sz << " " << sw << " ";
    if (!knight_tour(sx, sy, sz, sw)) {
        fout << "No solution found\n";
    } else {
        fout << "Yes solution found\n";
        return 1;
    }
}
