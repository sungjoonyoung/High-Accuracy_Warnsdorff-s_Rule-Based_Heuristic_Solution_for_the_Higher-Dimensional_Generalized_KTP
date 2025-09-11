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

double distance_from_center(int x, int y, int z, int w) {
    double mid = (N - 1) / 2.0;
    double dx = x - mid;
    double dy = y - mid;
    double dz = z - mid;
    double dw = w - mid;
    return dx*dx + dy*dy + dz*dz + dw*dw;
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
    
    string file = "_path_4D.txt";
    ofstream fout(file);
    int step = 1;
    while (true) {
        fout<<"("<<x<<","<<y<<","<<z<<","<<w<<"),\n";
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
                double dist = distance_from_center(nx, ny, nz, nw);

                if (deg < best_deg || (deg == best_deg && dist > best_dist)) {
                    best_deg = deg;
                    best_dist = dist;
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

    N = 5;
    int sx = 0;
    int sy = 0;
    int sz = 0;
    int sw = 0;

    init_knight_moves();
    init_degree();

    bool res = knight_tour(sx, sy,sz,sw);
    
    cout << (res ? "Success" : "Fail");

    return res ? 1 : 0;    
}
