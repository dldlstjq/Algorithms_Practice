/*
union-find 를 이용하여 푸는 문제.
앞서 구간트리부터 시작해 이번 문제까지 개념과 코드의 이해 격차가 많이 나는것 같다.
개념은 알겠는데 코드 이해가 쉽지 않다.

블로그에 이런 글이 있어 공감이 됐다.
답안 풀이를 보면 항상 몇가지 조건을 만들고 그 조건에 따라 프로그래밍하는 깔끔함을 볼 수 있다. 
물론 책이니까 결국 풀어버린 코드를 가지고 깔끔하게 정리할 수 있었겠지만, 실제로 문제를 풀기 시작하면 저런 조건을 만드는게 힘들다.
직관적으로 와닿지 않는다고 할까? 이건 아직 내가 느끼지 못한 영역일지, 원래 그렇게 될 수 없는건지 항상 의문이다.
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n, m;

//트리를 이용해 상호 배제적 집합을 구현한다.
struct BipartiteUnionFind {
    //parent[i]=i의 부모노드, 루트라면 i
    //rank[i]=i가 루트인 경우, i를 루트로 하는 트리의 랭크
    //enemy[i]=i가 루트인 경우, 해당 집합과 적대 관계인 집합의 루트의 번호.(없으면 -1)
    //size[i]=i가 루트인 경우, 해당 집합의 크기 
    vector<int> parent, rank, enemy, size;
    BipartiteUnionFind(int n) :parent(n), rank(n, 0), enemy(n, -1), size(n, 1) {
        for (int i = 0; i < n; ++i)
            parent[i] = i;
    }
    //u가 속한 트리의 루트의 번호를 반환한다.
    int find(int u) {
        if (u == parent[u])
            return u;
        return parent[u] = find(parent[u]);
    }

    int merge(int u, int v) {
        //u나 v가 공집합인 경우 나머지 하나를 반환한다.
        if (u == -1 || v == -1)
            return max(u, v);
        u = find(u); v = find(v);
        //이미 둘이 같은 트리에 속한 경우
        if (u == v)
            return u;
        if (rank[u] > rank[v])
            swap(u, v);
        //이제 항상 rank[v]가 더 크므로 u를 v의 자식으로 넣는다.        
        if (rank[u] == rank[v])
            rank[v]++;
        parent[u] = v;
        size[v] += size[u];
        return v;
    }

    //u와 v가 서로 적이다. 모순이 일어났다면 false, 아니면 true를 반환한다.
    bool dis(int u, int v) {
        //우선 루트를 찾는다.
        u = find(u); v = find(v);
        //같은 집합에 속해 있으면 모순!
        if (u == v)
            return false;
        //적의 적은 나의 동지
        int a = merge(u, enemy[v]), b = merge(v, enemy[u]);
        enemy[a] = b; enemy[b] = a;
        return true;
    }
    //u와 v가 서로 동지다. 모순이 일어났다면 false, 아니면 true를 반환한다.
    bool ack(int u, int v) {
        //우선 루트를 찾는다.
        u = find(u); v = find(v);
        //두 집합이 서로 적대관계라면 모순!
        if (enemy[u] == v)
            return false;
        //동지의 적은 나의 적
        int a = merge(u, v), b = merge(enemy[u], enemy[v]);
        enemy[a] = b;
        //두 집합 다 적대하는 집합이 없으면 b는 -1일 수도 있다.
        if (b != -1)
            enemy[b] = a;
        return true;
    }
};

//BipartiteUnionFind 인스턴스가 주어질 떄,
//한 파티에 올 가능성이 있는 최대 인원을 구한다.
int maxParty(const BipartiteUnionFind& buf) {
    int ret = 0;
    for (int node = 0; node < n; ++node) {
        if (buf.parent[node] == node) {
            int enemy = buf.enemy[node];
            //같은 모임 쌍을 두 번 세지 않기 위해, enemy<node인 경우만 센다.
            //enemy==-1인 경우도 정확히 한 번씩 세게 된다.
            if (enemy > node)
                continue;
            int mySize = buf.size[node];
            int enemySize = (enemy == -1 ? 0 : buf.size[enemy]);
            //두 집합 중 큰 집합을 더한다.
            ret += max(mySize, enemySize);
        }
    }
    return ret;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int c;
    cin >> c;
    while (c--) {
        cin >> n >> m;
        BipartiteUnionFind buf(n);
        bool contradict = false;
        int num = -1;

        for (int i = 0; i < n; ++i) {
            string s;
            int node1, node2;

            cin >> s >> node1 >> node2;
            if (contradict)
                continue;

            if (s == "ACK") {
                //모순 발생할 경우
                if (!buf.ack(node1, node2)) {
                    contradict = true;
                    num = i + 1;
                }
            }
            else {
                //모순 발생할 경우
                if (!buf.dis(node1, node2)) {
                    contradict = true;
                    num = i + 1;
                }
            }
        }

        if (contradict)
            cout << "CONTRADICTION AT " << num << "\n";
        else
            cout << "MAX PARTY SIZE IS " << maxParty(buf) << "\n";

    }
    return 0;
}
