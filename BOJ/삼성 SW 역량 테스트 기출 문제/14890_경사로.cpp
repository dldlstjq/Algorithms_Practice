/*
특별한 알고리즘을 필요로 하진 않았는데 구현이 조금 어려웠다.
행, 열을 한번씩 검사하면서 높이가 같으면 패스, 높이가 1 차이나면 경사로를 만들었다.
경사로가 겹치면 안되고, 범위를 벗어나도 안되고, 경사로가 있는 높이는 모두 높이가 1 차이가 나야한다는 조건 때문에
시간이 제법 걸렸다.

더 간단한 코드가 있는데 연구해 봐야겠다.
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAX = 100 + 1;
int N, L;
int board[MAX][MAX];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> N >> L;
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            cin >> board[i][j];

    int ret = 0;    //다리 개수
    int cnt = 0;    //다리 생성 여부

    for (int i = 0; i < N; ++i) {
        vector<int> v;
        bool road[MAX] = { 0 }; //경사로 여부

        for (int j = 0; j < N - 1; ++j) {
            //높이 같으면 다음 칸
            if (board[i][j] == board[i][j + 1]) {
                v.push_back(j);
                continue;
            }

            //다음 갈 칸이 한 칸 더 큰 경우
            else if (board[i][j] + 1 == board[i][j + 1]) {
                //경사로의 끝이 범위 안, 경사로 끝이 다음 이동할 칸과 1칸 차이, 끝 좌표에 경사로가 없으면 놓을 수 있다.
                if (j + 1 - L >= 0 && (board[i][j + 1 - L] + 1 == board[i][j + 1]) &&
                    !road[j + 1 - L]) {
                    //L 길이만큼 경사로 있다고 표시
                    for (int k = j + 1 - L; k < j + 1; ++k) {
                        road[k] = true;
                    }
                    v.push_back(j);
                    continue;
                }
                else
                    break;
            }

            //다음 갈 칸이 한 칸 더 작은 경우
            else if (board[i][j] - 1 == board[i][j + 1]) {
                //경사로의 끝이 범위 안, 경사로 끝이 다음 이동할 칸과 1칸 차이, 끝 좌표에 경사로가 없으면 놓을 수 있다.
                if (j + L < N && (board[i][j + L] + 1 == board[i][j]) &&
                    !road[j + L]) {
                    //L 길이만큼 경사로 있다고 표시
                    for (int k = j + 1; k <= j + L; ++k) {
                        road[k] = true;
                    }
                    v.push_back(j);
                    continue;
                }
                else
                    break;
            }

            //높이 차이가 1이 아닌 경우 경사로 못 놓는다
            else
                break;
        }
        //v에 N-1만큼 들어있으면 지나갈 수 있다.
        if (v.size() == N - 1) {
            ret++;
        }

    }



    //세로 다리
    for (int i = 0; i < N; ++i) {
        vector<int> v;
        bool road[MAX] = { 0 }; //경사로 여부

        for (int j = 0; j < N - 1; ++j) {
            //높이 같으면 다음 칸
            if (board[j][i] == board[j + 1][i]) {
                v.push_back(j);
                continue;
            }

            //다음 갈 칸이 한 칸 더 큰 경우
            else if (board[j][i] + 1 == board[j + 1][i]) {
                //경사로 검사
                if (j + 1 - L >= 0 && (board[j + 1 - L][i] + 1 == board[j + 1][i]) &&
                    !road[j + 1 - L]) {
                    for (int k = j + 1 - L; k < j + 1; ++k) {
                        road[k] = true;
                    }
                    v.push_back(j);
                    continue;
                }
                else
                    break;
            }

            //다음 갈 칸이 한 칸 더 작은 경우
            else if (board[j][i] - 1 == board[j + 1][i]) {
                if (j + L < N && (board[j + L][i] + 1 == board[j][i]) &&
                    !road[j + L]) {
                    for (int k = j + 1; k <= j + L; ++k) {
                        road[k] = true;
                    }
                    v.push_back(j);
                    continue;
                }
                else
                    break;
            }

            //높이 차이가 1이 아닌 경우 경사로 못 놓는다
            else
                break;
        }
        if (v.size() == N - 1) {
            ret++;
        }

    }
    cout << ret;

    return 0;
}

//////////////////////////////////////////////
//더 간단한 코드
//바로 이렇게 생각하긴 쉽지 않을 것 같다.
#include <stdio.h>

int n, l, a[101][101], dx[] = { 0,0,1,-1 }, dy[] = { 1,-1,0,0 }, ans;

int main() {
    scanf("%d%d", &n, &l);
    int i, j;
    for (i = 0; i < n; i++) for (j = 0; j < n; j++) scanf("%d", &a[i][j]);
    for (i = 0; i < n; i++) {
        int cnt = 1;
        for (j = 0; j < n - 1; j++) {
            if (a[i][j] == a[i][j + 1]) cnt++;
            else if (a[i][j] + 1 == a[i][j + 1] && cnt >= l) cnt = 1;
            else if (a[i][j] - 1 == a[i][j + 1] && cnt >= 0) cnt = -l + 1;
            else break;
        }
        if (j == n - 1 && cnt >= 0) ans++;
        cnt = 1;
        for (j = 0; j < n - 1; j++) {
            if (a[j][i] == a[j + 1][i]) cnt++;
            else if (a[j][i] + 1 == a[j + 1][i] && cnt >= l) cnt = 1;
            else if (a[j][i] - 1 == a[j + 1][i] && cnt >= 0) cnt = -l + 1;
            else break;
        }
        if (j == n - 1 && cnt >= 0) ans++;
    }
    printf("%d\n", ans);
    return 0;
}