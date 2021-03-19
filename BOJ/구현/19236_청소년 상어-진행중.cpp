#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <queue>

using namespace std;

typedef struct {
    int x;
    int y;
}direction[8];

direction Dir[8] = { {-1,0},{-1,-1},{0,-1},{1,-1},
{1,0} ,{1,1} ,{0,1} ,{-1,1} };

typedef struct {
    int idx, dir;
    int y, x;
}Fish;
Fish shark;
Fish fishes[17];


//vector<pair<int, int>> fish[4][4];  //물고기 좌표
//vector<pair<int, int>> order;   //물고기 순서

int board[4][4];    //상어가 있으면 1, 아니면 0
bool visited[4][4]; //상어 방문 여부

int ret;

//(x,y)칸에 있을 떄 물고기 최댓값
int solve(Fish fishes, int tank[4][4], Fish shark, int total) {

    ret = max(ret, total);

    //물고기 이동
    for (int i = 0; i < 17; ++i) {

    }

    //상어 이동

    return ret;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            int idx, dir;
            cin >> idx >> dir;

            if (i == 0 && j == 0) {
                shark = { idx,dir - 1,i,j };
                continue;
            }
            //물고기는 1~ 16, 방향은 0~7로 설정
            fishes[idx] = { idx,dir - 1,i,j };
            board[i][j] = idx;
        }
    }


    solve(0, 0);

    return 0;
}