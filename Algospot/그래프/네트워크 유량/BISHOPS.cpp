﻿/*
이런 유형의 문제들은 이분매칭을 통해 풀 수 있다.
이것과 비슷한 유형들을 많이 풀어서 풀이방법을 많이 익혀야 겠다.
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

//대각선의 방향: 왼쪽 아래로 내려가는 대각선, 오른쪽 아래로 내려가는 대각선
const int dx[2] = { -1,1 };
const int dy[2] = { 1,1 };
//체스판의 정보
vector<string> board;
//id[dir][y][x]=dir방향 대각선을 따라 인접한 빈 칸 묶음들 중 (y,x)가 속한 묶음의 번호
int id[2][8][8];
//이분 그래프의 정보
int n, m;
int adj[64][64];
const int MAX_N = 64;

//각 정점에 매칭된 상대 정점의 번호를 저장한다.
vector<int> aMatch, bMatch;
//dfs()의 방문 여부
vector<bool> visited;
//최대 매칭의 크기를 반환한다.
int bipartiteMatch();
int placeBishops() {
    //각 묶음에 번호를 붙인다.
    memset(id, -1, sizeof(id));
    int count[2] = { 0,0 };
    for (int dir = 0; dir < 2; ++dir)
        for (int y = 0; y < board.size(); ++y)
            for (int x = 0; x < board.size(); ++x)
                if (board[y][x] == '.' && id[dir][y][x] == -1) {
                    int cy = y, cx = x;
                    while (0 <= cy && cy < board.size() &&
                        0 <= cx && cx < board.size() &&
                        board[cy][cx] == '.') {
                        id[dir][cy][cx] = count[dir];
                        cy += dy[dir];
                        cx += dx[dir];
                    }
                    count[dir]++;
                }
    //이분 그래프를 만든다.
    n = count[0];
    m = count[1];
    memset(adj, 0, sizeof(adj));
    for (int y = 0; y < board.size(); ++y)
        for (int x = 0; x < board.size(); ++x)
            if (board[y][x] == '.')
                adj[id[0][y][x]][id[1][y][x]] = 1;
    return bipartiteMatch();
}

//A의 정점인 a에서 B의 매칭되지 않은 정점으로 가는 경로를 찾는다.
bool dfs(int a) {
    if (visited[a])
        return false;
    visited[a] = true;
    for (int b = 0; b < m; ++b) {
        if (adj[a][b]) {
            //b가 이미 매칭되어 있다면 bMatch[b]에서부터 시작해 증가 경로를 찾는다.
            if (bMatch[b] == -1 || dfs(bMatch[b])) {
                //증가 경로 발견!! a와 b를 매치시킨다.
                aMatch[a] = b;
                bMatch[b] = a;
                return true;
            }
        }
    }
    return false;
}

//aMatch,bMatch 배열을 계산하고 최대 매칭의 크기를 반환한다.
int bipartiteMatch() {
    //처음에는 어떤 정점도 연결되어 있지 않다.
    aMatch = vector<int>(n, -1);
    bMatch = vector<int>(m, -1);
    int size = 0;
    for (int start = 0; start < n; ++start) {
        visited = vector<bool>(n, false);
        //깊이 우선 탐색을 이용헤 start에서 시작하는 증가 경로를 찾는다.
        if (dfs(start))
            ++size;
    }
    return size;
}


int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;
    while (t--) {
        int N;
        cin >> N;
        board = vector<string>(N, "");
        for (int i = 0; i < N; ++i)
            cin >> board[i];
        cout << placeBishops() << "\n";
    }

    return 0;
}