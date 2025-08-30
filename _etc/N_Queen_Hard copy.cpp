#include<iostream>
#include<stdlib.h>
#include<vector>
#include<random>
#include<algorithm>
#include<time.h>
using namespace std;
int N;
long long plusn,minun,row,col;
int answer[40];
vector<int> row_v;
random_device rd;
mt19937 gen(rd());
bool is_collision(int x1){
    int y1=answer[x1];
    int before=0;
    for(int i=0;i<N;i++){
        if(i==x1)continue;
        if((i+answer[i])==x1+y1)return 1;
        if((i-answer[i])==x1-y1)return 1;
    }
    return 0;
}
int swap_better(int x1,int x2){
    int y1=answer[x1];
    int y2=answer[x2];
    int before=0;
    for(int i=0;i<N;i++){
        if(i==x1 or i==x2)continue;
        before+=((i+answer[i])==(x1+y1));
        before+=((i+answer[i])==(x2+y2));
        before+=((i-answer[i])==(x1-y1));
        before+=((i-answer[i])==(x2-y2));
    }
    int after=0;
    swap(y1,y2);
    for(int i=0;i<N;i++){
        if(i==x1 or i==x2)continue;
        after+=((i+answer[i])==(x1+y1));
        after+=((i+answer[i])==(x2+y2));
        after+=((i-answer[i])==(x1-y1));
        after+=((i-answer[i])==(x2-y2));
    }

    // for(int i=0;i<N;i++)cout<<answer[i]+1<<" ";
    // cout<<"\n"<<before<<" "<<after<<"\n";
    if(before==after)return 1;
    else if(before>after)return 2;
    else return 0;
}
void setting(void){
    shuffle(row_v.begin(), row_v.end(), gen);
    plusn=minun=col=0;
    
    for(int i=0;i<N;i++){
        if(row==(row|((long long)1<<i)))continue;
        for(int j=0;j<N;j++){
            if(row_v[j]==-1)continue;
            if(col==(col|((long long)1<<row_v[j])))continue;
            answer[i]=row_v[j];
            col|=((long long)1<<row_v[j]);
            plusn|=((long long)1<<(i+row_v[j]));
            minun|=((long long)1<<(i-row_v[j]+N));
            break;
        }
    }
}
int main(void){
    ios::sync_with_stdio(0);
    cin.tie(0);
    srand(time(NULL));
    cin>>N;
    for(int i=0;i<N;i++)row_v.push_back(i);
    
    for(int i=0;i<N;i++){
        int in;
        cin>>in;
        if(in==0)continue;
        in--;
        answer[i]=in;
        row_v[in]=-1;
        row|=((long long)1<<i);
        col|=((long long)1<<in);
        plusn|=((long long)1<<(i+in));
        minun|=((long long)1<<(i-in+N));
    }
    //for(int i=0;i<N;i++)cout<<answer[i]+1<<" ";


    int collision=0;
    for(int tryN=0;tryN<300'000;tryN++){
        if(tryN%(N*N*N)==0)setting();
        int swap_n=0;
        collision=0;
        for(int i=0;i<N;i++){
            if(row==(row|((long long)1<<i)))continue;
            for(int j=i+1;j<N;j++){
                if(row==(row|((long long)1<<j)))continue;
                if (is_collision(i) or is_collision(j)) {
                    collision++;
                    int tmp = swap_better(i, j);
                    if (tmp == 2) {
                        swap(answer[i], answer[j]);
                    }
                    else if ((rand()%2==0)) {
                        swap(answer[i], answer[j]);
                    }
                }
            }
        }

        if(collision==0){
            int key=1;
            for(int i=0;i<N;i++){
                if(is_collision(i)){
                    key=0;
                    break;
                }
            }
            if(key){
                for(int i=0;i<N;i++)cout<<answer[i]+1<<" "; 
                return 0;
            }
        }
    }
    cout<<"-1";
}  


#include<iostream>
#include<stdlib.h>
#include<vector>
#include<random>
#include<algorithm>
#include<time.h>
using namespace std;
int N;
long long row,col;
int answer[40];
vector<int> row_v;
random_device rd;
mt19937 gen(rd());
bool is_collision(int x1){
    int y1=answer[x1];
    int before=0;
    for(int i=0;i<N;i++){
        if(i==x1)continue;
        if((i+answer[i])==x1+y1)return 1;
        if((i-answer[i])==x1-y1)return 1;
    }
    return 0;
}
int swap_better(int x1,int x2){
    int y1=answer[x1];
    int y2=answer[x2];
    int before=0;
    for(int i=0;i<N;i++){
        if(i==x1 or i==x2)continue;
        before+=((i+answer[i])==(x1+y1));
        before+=((i+answer[i])==(x2+y2));
        before+=((i-answer[i])==(x1-y1));
        before+=((i-answer[i])==(x2-y2));
    }
    int after=0;
    swap(y1,y2);
    for(int i=0;i<N;i++){
        if(i==x1 or i==x2)continue;
        after+=((i+answer[i])==(x1+y1));
        after+=((i+answer[i])==(x2+y2));
        after+=((i-answer[i])==(x1-y1));
        after+=((i-answer[i])==(x2-y2));
    }

    // for(int i=0;i<N;i++)cout<<answer[i]+1<<" ";
    // cout<<"\n"<<before<<" "<<after<<"\n";
    if(before==after)return 1;
    else if(before>after)return 2;
    else return 0;
}
void setting(void){
    shuffle(row_v.begin(), row_v.end(), gen);
    col=0;
    for(int i=0;i<N;i++){
        if(row==(row|((long long)1<<i)))continue;
        for(int j=0;j<N;j++){
            if(row_v[j]==-1)continue;
            if(col==(col|((long long)1<<row_v[j])))continue;
            answer[i]=row_v[j];
            col|=((long long)1<<row_v[j]);
            break;
        }
    }
}
int main(void){
    ios::sync_with_stdio(0);
    cin.tie(0);
    srand(time(NULL));
    cin>>N;
    for(int i=0;i<N;i++)row_v.push_back(i);
    
    for(int i=0;i<N;i++){
        int in;
        cin>>in;
        if(in==0)continue;
        in--;
        answer[i]=in;
        row_v[in]=-1;
        row|=((long long)1<<i);
        col|=((long long)1<<in);
    }
    //for(int i=0;i<N;i++)cout<<answer[i]+1<<" ";
    setting();
    int collision=0;
    for(int tryN=0;tryN<100'000;tryN++){
        int swap_n=0;
        collision=0;
        for(int i=0;i<N;i++){
            if(row==(row|((long long)1<<i)))continue;
            for(int j=i+1;j<N;j++){
                if(row==(row|((long long)1<<j)))continue;
                if (is_collision(i) or is_collision(j)) {
                    collision++;
                    int tmp = swap_better(i, j);
                    if (tmp == 2) {
                        swap(answer[i], answer[j]);
                        swap_n++;
                    }
                }
            }
        }

        if(swap_n==0){
            int key=1;
            for(int i=0;i<N;i++){
                if(is_collision(i)){
                    key=0;
                    setting();
                    break;
                }
            }
            if(key){
                for(int i=0;i<N;i++)cout<<answer[i]+1<<" "; 
                return 0;
            }
        }
    }
    cout<<"-1";
}  