#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include<algorithm>
#include<tuple>
#include<cmath>
using namespace std;

int N;
int arr[500][500][500];
bool visited[500][500][500];
int dx[24], dy[24], dz[24];

struct Pos {
    int x, y, z;
};

ofstream fout;

void init_knight_moves() {
    int idx = 0;
    int dirs[3] = {0, 1, 2};
    for (int i = 0; i < 3; ++i) {
        int a = dirs[i];
        int b = dirs[(i + 1) % 3];
        int c = dirs[(i + 2) % 3];
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

int get_degree(int x, int y, int z) {
    int cnt = 0;
    for (int i = 0; i < 24; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        int nz = z + dz[i];
        if (valid(nx, ny, nz) && !visited[nx][ny][nz]) cnt++;
    }
    return cnt;
}

double distance_from_center(int x, int y, int z, int N) {
    double mid = (N - 1) / 2.0;
    double dx = x - mid;
    double dy = y - mid;
    double dz = z - mid;
    return sqrt(dx*dx + dy*dy + dz*dz);
}


bool knight_tour(int x, int y, int z) {
    int step=1;
    while(1){
        arr[x][y][z] = step;
        visited[x][y][z] = true;
        if (step == N * N * N) return true;

        //디그리 거리 x y z
        vector<tuple<int, double, int, int, int>> next;
        for (int i = 0; i < 24; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            int nz = z + dz[i];
            if (valid(nx, ny, nz) && !visited[nx][ny][nz]) {
                int deg = get_degree(nx, ny, nz);
                double length_deg = distance_from_center(nx, ny, nz, N);
                next.push_back({deg, length_deg, nx, ny, nz});
            }
        }
        if(next.empty())return false;

        sort(next.begin(), next.end(),[&](tuple<int, double, int, int, int> a, tuple<int, double, int, int, int> b){
            if(get<0>(a)==get<0>(b))
                return get<1>(a)>get<1>(b);
            else
                return get<0>(a)<get<0>(b);
        });
        x = get<2>(next[0]);
        y = get<3>(next[0]);
        z = get<4>(next[0]);

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
    ofstream fout(file, ios::app);

    init_knight_moves();
    fout << "Start position: " << sx << " " << sy << " " << sz << " ";
    if (!knight_tour(sx, sy, sz)) {
        // cout << "No solution found\n";
        fout << "No solution found\n";
    }
    else {
        fout<<"Yes solution found\n";
    }
}
