﻿/*
이 문제 역시 bfs를 활용하면 풀리는 문제.
에라토스테네스의 체로 소수를 구한 다음 각 자리수 마다 숫자를 바꿔 소수인지 아닌지 검사하면 된다.
각 자리수를 하나씩 바꾸는 것에서 해결하는데 어려움을 겪었다.
두번째로 풀때는 dist 배열을 안쓰고 큐에 pair를 써서 해결했다.
*/
#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;
#define MAX 10001
bool visited[MAX];
int dist[MAX];

//num이라는 숫자의 index를 digit으로 바꾼다.
int change(int num, int idx, int digit) {
    //맨 앞자리는 0이 안됨
    if (idx == 0 && digit == 0)
        return -1;

    string str = to_string(num);
    str[idx] = digit + '0';
    return stoi(str);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;

    //에라토스테네스의 체로 소수 구함
    bool prime[MAX];
    for (int i = 2; i <= 10000; i++)
        prime[i] = true;

    for (int i = 2; i <= 10000; i++) {
        if (prime[i] == false) continue;
        for (int j = i + i; j <= 10000; j += i) {
            prime[j] = false;
        }
    }


    while (t--) {
        int a, b;
        cin >> a >> b;

        memset(visited, false, sizeof(visited));
        memset(dist, 0, sizeof(dist));

        queue<int> q;
        q.push(a);
        visited[a] = true;
        dist[a] = 0;

        while (!q.empty()) {
            int now = q.front();
            q.pop();

            //i는 4자리수라서 4번, j는 0~9숫자 10번 반복
            //각 자리마다 소수인지 판별하고 횟수랑 같이 큐에 저장
            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 10; j++) {
                    int next = change(now, i, j);
                    if (next != -1) {
                        //next가 소수이면서 방문하지 않았으면 큐에 추가
                        if (prime[next] && !visited[next]) {
                            q.push(next);
                            dist[next] = dist[now] + 1;
                            visited[next] = true;
                        }

                    }
                }
            }
        }

        cout << dist[b] << "\n";

        //두번째로 풀 때 코드
        //while (!q.empty()) {
        //    int now = q.front().first;
        //    int time = q.front().second;
        //    q.pop();

        //    if (now == n2) {
        //        ans = time;
        //        break;
        //    }

        //    //i는 4자리수라서 4번, j는 0~9숫자 10번 반복
        //    //각 자리마다 소수인지 판별하고 횟수랑 같이 큐에 저장
        //    for (int i = 0; i < 4; i++) {
        //        for (int j = 0; j <= 9; j++) {
        //            int next = change(now, i, j);
        //            if (next != -1) {
        //                if (prime[next] != 0 && !visited[next]) {
        //                    q.push({ next,time + 1 });
        //                    visited[next] = true;
        //                }
        //            }
        //        }
        //    }
        //}
        //cout << ans << "\n";
    }

    return 0;
}