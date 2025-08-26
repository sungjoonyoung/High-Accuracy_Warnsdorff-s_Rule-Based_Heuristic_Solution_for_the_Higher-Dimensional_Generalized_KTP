#include<iostream>
#include<fstream>
#include<utility>
#include<vector>
using namespace std;
vector<pair<int, double>> v;
int main(void) {
   ios::sync_with_stdio(0);
   cin.tie(0);
   string file = "data.txt";
   ofstream fout(file, ios::trunc);
   ifstream fin("in.txt");
   while (1) {
       int N;
       double acc;
       fin >> N >> acc;
       if (fin.fail())break;
       v.push_back({ N,acc });
   }
   fout << "x=[";
   for (int i = 0; i < v.size(); i++) {
       fout << v[i].first;
       if (i != v.size() - 1)fout << ",";
   }
   fout << "]\n";

   fout << "y=[";
   for (int i = 0; i < v.size(); i++) {
       fout << v[i].second;
       if (i != v.size() - 1)fout << ",";
   }
   fout << "]\n";
}
// #include<iostream>
// using namespace std;
// int arr[25][25][25][25][25];
// int main(void) {
// 	int N = 25;
// 	for (int i = 0; i < N; i++)
// 		for (int ii = 0; ii < N; ii++)
// 			for (int iii = 0; iii < N; iii++)
// 				for (int iiii = 0; iiii < N; iiii++)
// 					for (int iiiii = 0; iiiii < N; iiiii++)
// 						arr[i][ii][iii][iiii][iiiii] = 1;
// }