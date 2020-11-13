/*
유명한 TSP문제이다. 알고리즘 시간에 배웠던게 잠깐 생각났다.
아예 처음부터 내가 짜기에는 내용을 몰라 인터넷을 참고해서 풀었는데 틀렸다.
이 역시 순열을 이용하여 모든 정점마다 확인해서 제일 최소 비용을 찾으면 된다.
*/

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
처음 인터넷으로 찾은 코드. 정점 0부터 시작하기 때문에 오답이었다. 
다른 정점도 하게 하려했으나 아직까지는 구현 못함
*/
#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;
//가중치 저장 위한 배열
int dist[10][10];
int n;
int TSP(vector<int> path, vector<bool> visited, int len) {
    //모든 도시 다 방문했을 경우
    if (path.size() == n)
        return len + dist[path.back()][0];
    int ret = 987654321;

    for (int next = 0; next < n; next++) {
        //방문했다면 패스
        if (visited[next] == true)
            continue;

        int cur = path.back();
        path.push_back(next);
        visited[next] = true;
        ret = min(ret, TSP(path, visited, len + dist[cur][next]));
        visited[next] = false;
        path.pop_back();
    }
    return ret;
}


int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> dist[i][j];

    vector<int> path(1, 0);     //경로를 저장할 벡터, 시작 도시 0번도시 선택
    vector<bool> visited(n, false);     //방문 여부 저장할 벡터. false로 초기화
    visited[0] = true;      //출발 도시 방문 여부 체크
    double ret = TSP(path, visited, 0);
    cout << ret;

    return 0;
}