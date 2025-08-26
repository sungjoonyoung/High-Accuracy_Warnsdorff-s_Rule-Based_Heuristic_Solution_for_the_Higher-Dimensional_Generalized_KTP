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
string file="_path_2D.txt";

bool valid(int x, int y) {
    return 0 <= x && x < N && 0 <= y && y < N;
}
void pr(int x,int y,int xx,int yy){
    fout<<"(";
    fout<<"(";

    fout<<x<<",";
    fout<<y<<",";

    fout<<"),(";

    fout<<xx<<",";
    fout<<yy<<",";

    fout<<")),\n";
}
void init_degree() {
    for (int x = 0; x < N; x++)
        for (int y = 0; y < N; y++) {
            int cnt = 0;
            for (int i = 0; i < 8; i++) {
                int nx = x + dx[i];
                int ny = y + dy[i];
                if (valid(nx, ny)){
                    pr(x,y,nx,ny);
                    cnt++;
                }
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


int main(int argc, char* argv[]) {
    N = 10;
    fout.open(file);   // 전역 fout을 열기
    init_degree();
    fout.close();      // 다 쓰고 닫기
}
