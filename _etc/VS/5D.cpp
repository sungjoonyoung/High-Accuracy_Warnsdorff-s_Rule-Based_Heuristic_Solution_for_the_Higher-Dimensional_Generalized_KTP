#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <tuple>
#include <cmath>
using namespace std;

int N;
int arr[50][50][50][50][50];         // 5D 배열, 메모리 고려해 50 정도로 설정
bool visited[50][50][50][50][50];

int dx[240], dy[240], dz[240], dw[240], dv[240];  // 5D 나이트 이동 (240가지)

// 5D 나이트 이동 초기화
void init_knight_moves() {
    int idx = 0;
    int dirs[5] = {0,1,2,3,4};
    // 5D에서 나이트는 임의의 두 축을 선택해 2칸과 1칸 이동, 나머지는 0
    // 가능한 모든 축쌍 조합 (i < j)
    for (int i=0; i<5; i++) {
        for (int j=i+1; j<5; j++) {
            for (int sign1 : {-1,1}) {
                for (int sign2 : {-1,1}) {
                    int delta[5] = {};
                    delta[dirs[i]] = 2 * sign1;
                    delta[dirs[j]] = 1 * sign2;
                    dx[idx] = delta[0];
                    dy[idx] = delta[1];
                    dz[idx] = delta[2];
                    dw[idx] = delta[3];
                    dv[idx] = delta[4];
                    idx++;

                    delta[dirs[i]] = 1 * sign1;
                    delta[dirs[j]] = 2 * sign2;
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

int get_degree(int x, int y, int z, int w, int v) {
    int cnt = 0;
    for (int i=0; i<240; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        int nz = z + dz[i];
        int nw = w + dw[i];
        int nv = v + dv[i];
        if (valid(nx, ny, nz, nw, nv) && !visited[nx][ny][nz][nw][nv]) cnt++;
    }
    return cnt;
}

double distance_from_center(int x, int y, int z, int w, int v) {
    double mid = (N - 1) / 2.0;
    double dx = x - mid;
    double dy = y - mid;
    double dz = z - mid;
    double dw = w - mid;
    double dv = v - mid;
    return sqrt(dx*dx + dy*dy + dz*dz + dw*dw + dv*dv);
}

bool knight_tour(int x, int y, int z, int w, int v) {
    int step = 1;
    while (true) {
        arr[x][y][z][w][v] = step;
        visited[x][y][z][w][v] = true;
        if (step == N*N*N*N*N) return true;

        vector<tuple<int, double, int, int, int, int, int>> next;
        for (int i=0; i<240; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            int nz = z + dz[i];
            int nw = w + dw[i];
            int nv = v + dv[i];
            if (valid(nx, ny, nz, nw, nv) && !visited[nx][ny][nz][nw][nv]) {
                int deg = get_degree(nx, ny, nz, nw, nv);
                double dist = distance_from_center(nx, ny, nz, nw, nv);
                next.emplace_back(deg, dist, nx, ny, nz, nw, nv);
            }
        }
        if (next.empty()) return false;

        sort(next.begin(), next.end(), [](auto& a, auto& b) {
            return (get<0>(a) != get<0>(b)) ? get<0>(a) < get<0>(b)
                                           : get<1>(a) > get<1>(b);
        });

        tie(ignore, ignore, x, y, z, w, v) = next[0];
        step++;
    }
    return true;
}

int main(int argc, char* argv[]) {
    if (argc < 7) {
        cerr << "Usage: ./5D.exe N x y z w v\n";
        return 1;
    }

    N = atoi(argv[1]);
    int sx = atoi(argv[2]);
    int sy = atoi(argv[3]);
    int sz = atoi(argv[4]);
    int sw = atoi(argv[5]);
    int sv = atoi(argv[6]);

    string file = "Dimension=5_N=" + string(argv[1]) + ".txt";
    ofstream fout(file, ios::app);

    init_knight_moves();
    fout << "Start position: " << sx << " " << sy << " " << sz << " " << sw << " " << sv << " ";
    if (!knight_tour(sx, sy, sz, sw, sv)) {
        fout << "No solution found\n";
    } else {
        fout << "Yes solution found\n";
    }
}
