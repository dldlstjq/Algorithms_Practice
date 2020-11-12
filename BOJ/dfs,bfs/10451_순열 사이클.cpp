﻿/*
dfs 이용해서 정점이 연결되었는지 확인하면 쉽게 풀이 가능
*/

#include <iostream>
#include <cstring>

using namespace std;

const int MAX = 1000 + 1;

int N;
int arr[MAX];
bool visited[MAX];

void DFS(int node)
{
    visited[node] = true;
    if (!visited[arr[node]])
        DFS(arr[node]);
}


int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int T;
    cin >> T;

    for (int t = 0; t < T; t++)
    {
        memset(visited, false, sizeof(visited));
        cin >> N;
        for (int i = 1; i <= N; i++)
            cin >> arr[i];

        int cnt = 0;
        for (int i = 1; i <= N; i++)
            //컴포넌트 개수
            if (!visited[i])
            {
                DFS(i);
                cnt++;
            }
        cout << cnt << "\n";
    }
    return 0;
}