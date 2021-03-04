/*
오일러 회로를 간단한게 구현하는 문제.
오일러 회로 조건을 충분히 알고도 많이 헷갈렸다.
양방향 간선이기 때문에 종만북에서처럼 반대로 뒤집을 필요는 없다.
또 간선 추가시 i만 더해주고 2로 안 나눠줘도 정답이 나온다.

다시 풀 때 차수를 구하는 과정에서 graph[i][j]==1일 때 차수를 증가시키는 형식으로
구현하니 오답을 받았다.

단순히 graph[i][j]를 더하는 것과 1일때만 증가시키는 것의 차이를 잘 모르겠다.
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


//그래프 저장
vector<vector<int>> graph;
//각 정점에서의 차수 저장
vector<int> degree;

//유향 그래프의 인접 행렬 adj가 주어질 때 오일러 서킷 혹은 트레일을 계산한다.
void getEulerCircuit(int here) {
    for (int there = 0; there < graph[here].size(); ++there)
        while (graph[here][there] > 0) {
            graph[here][there]--; //양쪽 간선을 모두 지운다.
            graph[there][here]--;
            getEulerCircuit(there);
        }
    cout << here + 1 << " ";
}


int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;
    graph = vector<vector<int>>(n, vector<int>(n, 0));
    degree.resize(n);
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j) {
            cin >> graph[i][j];
            /*
            이렇게 구현하면 오답을 받는다.
            정확히 왜 그런건지는 모르겠다.
            if (graph[i][j] == 1)
                degree[i]++;
            */
            
            degree[i] += graph[i][j];
            degree[j] += graph[i][j];
        }

    bool cycle = false;
    vector<int> circuit;

    for (int i = 0; i < n; ++i) {
        degree[i] /= 2;    //양방향 간선이므로
        //정점에서의 간선의 개수가 홀수가 있으면 오일러 서킷이 아니다
        if (degree[i] % 2 != 0) {
            cycle = true;
            break;
        }
    }

    if (cycle)
        cout << -1;
    else {
        getEulerCircuit(0);
    }

    return 0;
}

