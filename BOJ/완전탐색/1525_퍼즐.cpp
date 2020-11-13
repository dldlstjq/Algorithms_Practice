/*
처음에 2차원 배열로 다 해결해야 하는 줄 알아서 시도해보다가 못 풀었다.
0인 부분을 9로 바꿔서 하나의 숫자로 만들어 주는 것이 포인트였다.
BFS를 활용해서 9의 위치를 찾아 좌표를 저장하고 값을 바꿔서 원래 목표 값과 일치하는지 확인하면 된다.
*/

#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>

using namespace std;
#define TARGET 123456789
int graph[3][3];
int dy[] = { -1,0,1,0 };
int dx[] = { 0,1,0,-1 };

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    string str = "";
    //0인 부분을 9로 바꿔서 숫자로 만들어 주는게 핵심.
    for (int i = 0; i < 9; i++) {
        int num;
        cin >> num;
        if (num == 0)
            num = 9;
        str += to_string(num);
    }

    int start = stoi(str);
    queue<int> q;
    map<int, int> visited;
    q.push(start);
    visited[start] = 0;

    while (!q.empty()) {
        int now = q.front();
        string s = to_string(now);
        q.pop();

        //원하는 목표
        if (now == TARGET)
            break;

        int z = s.find("9"); //9의 위치가 비어있는 칸
        //9좌표 저장
        int y = z / 3;
        int x = z % 3;

        //상화좌우 확인해서 모든 경우의 수 확인
        for (int i = 0; i < 4; i++) {
            int ny = y + dy[i];
            int nx = x + dx[i];
            if (0 <= ny && ny < 3 && 0 <= nx && nx < 3) {
                string temp = s;
                swap(temp[y * 3 + x], temp[ny * 3 + nx]);

                int next = stoi(temp);
                if (!visited[next]) {
                    visited[next] = visited[now] + 1;
                    q.push(next);
                }
            }
        }

    }
    //타겟 값이 없으면 -1 출력
    if (!visited.count(TARGET))
        cout << -1 << "\n";
    else
        cout << visited[TARGET] << "\n";

    return 0;
}