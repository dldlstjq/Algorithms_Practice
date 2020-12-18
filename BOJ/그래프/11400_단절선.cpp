/*
단절점이 아니라 단절선을 찾는 문제.
단절점 구하는 코드 이해가 완벽하게 되지 않아
단절선 구하는 방식이 왜 저렇게 되는지 이해가 되진 않는다.
나중에 다시 한번 더 자세히 봐야겠다.
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


//그래프의 인접 리스트 표현
vector<vector<int>> adj;
//각 정점의 발견 순서. -1로 초기화한다.
vector<int> discovered;
//각 정점이 절단점인지 여부를 저장한다. false로 초기화한다.
vector<bool> isCutVertex;
int counter = 0;

//절단선 저장
vector<pair<long long, long long>> cutEdges;

//here를 루트로 하는 서브트리에서 절단점들을 찾는다.
//반환 값은 해당 서브트리에서 역방향 간선으로 갈 수 있는 정점 중
//가장 일찍 발견된 정점의 발견 시점. 처음 호출할 때는 isRoot=true로 둔다.
int findCutVertex(int here, int prev = -1) {
    //발견 순서를 기록한다.
    discovered[here] = counter++;
    int ret = discovered[here];
    for (int i = 0; i < adj[here].size(); ++i) {

        int there = adj[here][i];
        if (there == prev)continue;
        if (discovered[there] == -1) {
            //이 서브트리에서 갈 수 있는 가장 높은 정점의 번호
            int subtree = findCutVertex(there, here);
            //절단선
            if (subtree > discovered[here])
                cutEdges.push_back({ min(here,there),max(here,there) });

            ret = min(ret, subtree);
        }
        else
            ret = min(ret, discovered[there]);
    }
    return ret;
}


int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int v, e;
    cin >> v >> e;

    adj = vector <vector<int>>(v);
    for (int i = 0; i < e; ++i) {
        int a, b;
        cin >> a >> b;
        adj[a - 1].push_back(b - 1);
        adj[b - 1].push_back(a - 1);
    }

    //배열들을 전부 초기화
    discovered = vector<int>(adj.size(), -1);
    isCutVertex = vector<bool>(adj.size(), false);

    findCutVertex(0);
    sort(cutEdges.begin(), cutEdges.end());
    cout << cutEdges.size() << "\n";

    for (int i = 0; i < cutEdges.size(); ++i)
        cout << cutEdges[i].first + 1 << " " << cutEdges[i].second + 1 << "\n";

    return 0;
}

