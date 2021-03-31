/*
처음엔 테트리스를 다 구현해서 직접 비교해야 하는 줄 알았다.
그러기엔 시간도 많이 들고 구현도 힘들어서 다시 생각했다.
블록이 칸에 닿는 부분과 각 칸의 높이가 일치하는지만 확인하면 됐다.
*/

#include <iostream>
using namespace std;

const int MAX = 100 + 1;

int C, P;
int board[MAX];
int ret;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> C >> P;
    for (int i = 0; i < C; ++i)
        cin >> board[i];

    //블록 번호에 따라 계산한다.
    if (P == 1) {
        //세로는 모든 칸에 성립한다.
        ret += C;
        //가로는 4칸을 차지하므로 계산해준다.
        //현재 위치부터 3칸까지 각 칸의 높이가 같은 경우만 성립
        for (int i = 0; i + 3 < C; ++i) {
            if (board[i] == board[i + 1] && board[i + 1] == board[i + 2] && board[i + 2] == board[i + 3])
                ret++;
        }
    }

    else if (P == 2) {
        //인접한 두 칸만 높이가 같으면 된다. 0 0
        for (int i = 0; i + 1 < C; ++i) {
            if (board[i] == board[i + 1])
                ret++;
        }
    }

    else if (P == 3) {
        //원래 모양 0 0 1
        for (int i = 0; i + 2 < C; ++i) {
            if (board[i] == board[i + 1] && board[i + 1] + 1 == board[i + 2])
                ret++;
        }
        //회전 1 0
        for (int i = 0; i + 1 < C; ++i) {
            if (board[i] == board[i + 1] + 1)
                ret++;
        }
    }

    else if (P == 4) {
        //원래 모양 1 0 0
        for (int i = 0; i + 2 < C; ++i) {
            if (board[i] == board[i + 1] + 1 && board[i + 1] == board[i + 2])
                ret++;
        }
        //회전 0 1
        for (int i = 0; i + 1 < C; ++i) {
            if (board[i] + 1 == board[i + 1])
                ret++;
        }
    }

    else if (P == 5) {
        //원래 모양 0 0 0
        for (int i = 0; i + 2 < C; ++i) {
            if (board[i] == board[i + 1] && board[i + 1] == board[i + 2])
                ret++;
        }
        //90도 회전 0 1
        for (int i = 0; i + 1 < C; ++i) {
            if (board[i] + 1 == board[i + 1])
                ret++;
        }
        //180도 회전 1 0 1
        for (int i = 0; i + 2 < C; ++i) {
            if (board[i] == board[i + 1] + 1 && board[i + 1] + 1 == board[i + 2])
                ret++;
        }
        //270도 회전 1 0
        for (int i = 0; i + 1 < C; ++i) {
            if (board[i] == board[i + 1] + 1)
                ret++;
        }
    }

    else if (P == 6) {
        //원래 모양 0 0 0
        for (int i = 0; i + 2 < C; ++i) {
            if (board[i] == board[i + 1] && board[i + 1] == board[i + 2])
                ret++;
        }
        //90도 회전 0 0
        for (int i = 0; i + 1 < C; ++i) {
            if (board[i] == board[i + 1])
                ret++;
        }
        //180도 회전 0 1 1
        for (int i = 0; i + 2 < C; ++i) {
            if (board[i] + 1 == board[i + 1] && board[i + 1] == board[i + 2])
                ret++;
        }
        //270도 회전 2 0
        for (int i = 0; i + 1 < C; ++i) {
            if (board[i] == board[i + 1] + 2)
                ret++;
        }
    }

    else if (P == 7) {
        //원래 모양 0 0 0
        for (int i = 0; i + 2 < C; ++i) {
            if (board[i] == board[i + 1] && board[i + 1] == board[i + 2])
                ret++;
        }
        //90도 회전 0 2
        for (int i = 0; i + 1 < C; ++i) {
            if (board[i] + 2 == board[i + 1])
                ret++;
        }
        //180도 회전 1 1 0
        for (int i = 0; i + 2 < C; ++i) {
            if (board[i] == board[i + 1] && board[i + 1] == board[i + 2] + 1)
                ret++;
        }
        //270도 회전 0 0
        for (int i = 0; i + 1 < C; ++i) {
            if (board[i] == board[i + 1])
                ret++;
        }
    }

    cout << ret;

    return 0;
}