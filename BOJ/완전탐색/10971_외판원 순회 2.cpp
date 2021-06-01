/*
유명한 TSP문제이다. 알고리즘 시간에 배웠던게 잠깐 생각났다.
아예 처음부터 내가 짜기에는 내용을 몰라 인터넷을 참고해서 풀었는데 틀렸다.
이 역시 순열을 이용하여 모든 정점마다 확인해서 제일 최소 비용을 찾으면 된다.

2021.04.02 
백트래킹을 이용해 다시 풀었다. 40%에서 틀렸는데 다른 사람의 질문을 보고 해결했다.
방문한 도시가 N개 일 때 다시 처음으로 돌아오는 과정에서 해당 경로가 연결되었는지도 확인해야한다.
if문에서 방문 도시가 N개일때만 설정해서 리턴하니 틀렸다.

*/

// 2021.06.01 백트래킹을 이용해서 풀었다. 4.2 풀었던 것보다는 조금 간결하다.
#include <iostream> 
#include <vector> 
#include <algorithm>
using namespace std;

int N;
int W[10][10];
bool visited[10];
int ret = 987654321;

// start는 출발도시, now 현재 도시, cnt 방문한 도시 수, cost는 비용
void TSP(int start, int now, int cnt, int cost) {
    // 모든 도시 방문 후 다시 처음으로 되돌아 온다.
    if (cnt == N) {
        if (W[now][start] == 0)
            return;
        cost += W[now][start];
        ret = min(ret, cost);
        return;
    }

    for (int i = 0; i < N; ++i) {
        // 길이 있고 방문 안한 경우 방문
        if (W[now][i] != 0 && !visited[i]) {
            visited[i] = true;
            TSP(start, i, cnt + 1, cost + W[now][i]);
            visited[i] = false;
        }

    }

}

int main(int argc, char** argv) {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N;
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            cin >> W[i][j];

    // 0~N-1까지 차례대로 시작해서 최소를 구한다.
    for (int i = 0; i < N; ++i) {
        visited[i] = true;
        TSP(i, i, 1, 0);
        visited[i] = false;
    }

    cout << ret;

    return 0;
}

/*
정답코드
*/
#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;
//가중치 저장 위한 배열
int dist[10][10];
int n;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> dist[i][j];

    vector<int> path(n);     //0번부터 3번까지 저장
    vector<bool> visited(n, false);     //방문 여부 저장할 벡터. false로 초기화

    for (int i = 0; i < n; i++)
        path[i] = i;

    int result = 987654321;

    do {
        int sum = 0;
        bool flag = true;

        //돌아오는거 제외하기 때문에 n-1까지
        for (int i = 0; i < n - 1; i++) {
            if (dist[path[i]][path[i + 1]] != 0) {
                sum += dist[path[i]][path[i + 1]];
            }
            else {
                flag = false;
                break;
            }
        }

        //비용이 0이 아니면 비교
        if (flag && dist[path[n - 1]][path[0]] != 0) {
            sum += dist[path[n - 1]][path[0]];
            result = min(result, sum);
        }

    } while (next_permutation(path.begin(), path.end()));

    cout << result;
    return 0;
}



///////////////////////////////////////////////////
/*
백트래킹 이용한 풀이.
*/
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAX = 10 + 1;
int N;
int W[MAX][MAX];
bool visited[MAX];

int ret = 987654321;
void solve(int start, int end, int city_cnt, int cost) {
    //도시 수가 N이고 처음으로 다시 돌아올 수 있으면 진행
    //이 부분에서 N만 확인하면 틀림
    if (city_cnt == N && W[start][end] != 0) {
        cost += W[start][end];
        ret = min(ret, cost);
        return;
    }

    //start부터 시작해서 방문 안한 도시 방문.
    for (int k = 0; k < N; ++k) {
        if (W[start][k] != 0 && !visited[k]) {
            visited[k] = true;
            solve(k, end, city_cnt + 1, cost + W[start][k]);
            visited[k] = false;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> N;
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            cin >> W[i][j];

    //i번째 도시부터 시작해서 하나씩 모두 탐색한다.
    for (int i = 0; i < N; ++i) {
        visited[i] = true;
        for (int j = 0; j < N; ++j) {
            //j번째 도시가 방문 안했고 연결되어 있으면 방문
            if (W[i][j] != 0 && !visited[j]) {
                visited[j] = true;
                //시작은 j번째 도시, 돌아올 도시는 i, 방문한 도시는 2개, 비용은 W[i][j]
                solve(j, i, 2, W[i][j]);
                visited[j] = false;
            }
        }
        visited[i] = false;
    }

    cout << ret;
    return 0;
}