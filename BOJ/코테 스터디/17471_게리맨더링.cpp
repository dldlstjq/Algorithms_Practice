/*
처음엔 접근조차 하지 못했다.
선거구를 어떻게 나눠야 할지 전혀 몰랐다.
피드백을 통해 조합으로 모든 경우를 검사해야한다는 걸 알았다.
구역을 나눈 후 전부 연결되었는지 확인하고 인구 수 차이를 구하면 된다.

1. 선거구는 구역을 적어도 하나 포함해야한다는것
2. 다른 선거구끼리 인접한 구역은 0개 이상, 즉 서로 연결되어있지 않아도 된다는 것
이 두가지를 고려하지 않아 예제가 제대로 돌아가지 않았다.
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

const int MAX = 10 + 1;
const int INF = 987654321;
int N;
int people[MAX];
bool visited[MAX];

vector<int> v;
vector<int> graph[MAX];
int ret;

bool is_connected(const vector<int>& area) {
    bool visited[MAX] = { false };

    //선거구가 적어도 하나는 있어야 한다.
    int size = area.size();
    if (size == 0)
        return false;

    queue<int> q;
    q.push(area[0]);
    visited[area[0]] = true;
    int cnt = 0;

    while (!q.empty()) {
        int cur = q.front();
        q.pop();

        cnt++;
        for (int i = 0; i < graph[cur].size(); ++i) {
            int next = graph[cur][i];
            //같은 선거구
            if (v[cur - 1] == v[next - 1]) {
                if (!visited[next]) {
                    q.push(next);
                    visited[next] = true;
                }
            }

            //다른 선거구 연결
            else {
                visited[next] = true;
            }
        }

    }

    //같은 선거구끼리 연결된 경우 true
    if (cnt == size)
        return true;
    else
        return false;
}

void solve() {
    vector<int> red, blue;

    for (int i = 0; i < v.size(); ++i) {
        if (v[i] == 0)
            red.push_back(i + 1);
        else
            blue.push_back(i + 1);
    }

    //서로 연결되었는지 확인한다.
    if (!is_connected(red) || !is_connected(blue))
        return;

    //인구수 확인
    int sum_red = 0;
    int sum_blue = 0;

    for (int i = 0; i < red.size(); ++i)
        sum_red += people[red[i]];


    for (int i = 0; i < blue.size(); ++i)
        sum_blue += people[blue[i]];

    ret = min(ret, abs(sum_red - sum_blue));
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> N;
    for (int i = 1; i <= N; ++i)
        cin >> people[i];

    for (int i = 1; i <= N; ++i) {
        int num;
        cin >> num;
        for (int j = 0; j < num; ++j) {
            int tmp;
            cin >> tmp;
            graph[i].push_back(tmp);
        }
    }

    ret = INF;
    for (int i = 1; i <= N; ++i) {
        for (int j = 0; j < i; ++j)
            v.push_back(0);

        for (int j = 0; j < N - i; ++j)
            v.push_back(1);

        do {
            solve();
        } while (next_permutation(v.begin(), v.end()));

        v.clear();
    }


    if (ret == INF)
        cout << -1;
    else
        cout << ret;
    return 0;
}