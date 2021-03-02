/*
구간 트리를 사용하면 되긴 하지만 주의해야 할 건 업데이트의 경우
배열 값을 업데이트 하는 것이 아니라 배열 값에 추가를 해줘야 한다.
또한 어느 범위에도 속하지 않을 때 리턴 값을 매우 크게 했는데 이 또한
0으로 설정해야 맞는 값이 나왔다. 
범위 안에 들어오지 않을 때 리턴 값을 어떻게 설정해야 하는지 헷갈린다.
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int N, Q;

//배열의 구간 최소 쿼리를 해결하기 위한 구간 트리의 구현
struct RMQ {
    //배열의 길이
    int n;
    //각 구간의 최소치
    vector<long long> rangeMin;
    RMQ(const vector<long long>& array) {
        n = array.size();
        rangeMin.resize(n * 4);
        init(array, 0, n - 1, 1);
    }
    //node 노드가 array[left..right]배열을 표현할 때
    //node를 루트로 하는 서브트리를 초기화하고, 이 구간의 최소치를 반환한다.
    long long init(const vector<long long>& array, int left, int right, int node) {
        if (left == right)
            return rangeMin[node] = array[left];
        int mid = (left + right) / 2;
        long long leftMin = init(array, left, mid, node * 2);
        long long rightMin = init(array, mid + 1, right, node * 2 + 1);
        return rangeMin[node] = (leftMin + rightMin);
    }
    //node가 표현하는 범위 array[nodeLeft..nodeRight]가 주어질 때
    //이 범위와 array[left..right]의 교집합의 최소치를 구한다.
    long long query(int left, int right, int node, int nodeLeft, int nodeRight) {
        //두 구간이 겹치지 않으면 아주 큰 값을 반환한다: 무시됨
        if (right < nodeLeft || nodeRight < left)
            return 0;
        //node가 표현하는 범위가 array[left..right]에 완전히 포함되는 경우
        if (left <= nodeLeft && nodeRight <= right)
            return rangeMin[node];
        //양쪽 구간을 나눠서 푼 뒤 결과를 합친다.
        int mid = (nodeLeft + nodeRight) / 2;
        return (query(left, right, node * 2, nodeLeft, mid) +
            query(left, right, node * 2 + 1, mid + 1, nodeRight));
    }
    //query()를 외부에서 호출하기 위한 인터페이스
    long long query(int left, int right) {
        return query(left - 1, right - 1, 1, 0, n - 1);
    }
    //array[index]=newValue로 바뀌었을 때 node를 루트로 하는
    //구간 트리를 갱신하고 노드가 표현하는 구간의 최소치를 반환한다.
    long long update(int index, long long newValue, int node, int nodeLeft, int nodeRight) {
        //index가 노드가 표현하는 구간과 상관없는 경우엔 무시한다.
        if (index < nodeLeft || nodeRight < index)
            return rangeMin[node];
        //트리의 리프까지 내려온 경우
        //배열에 값에 추가한다.
        if (nodeLeft == nodeRight)
            return rangeMin[node] += newValue;
        int mid = (nodeLeft + nodeRight) / 2;
        return rangeMin[node] =
            update(index, newValue, node * 2, nodeLeft, mid) +
            update(index, newValue, node * 2 + 1, mid + 1, nodeRight);
    }
    //update()를 외부에서 호출하기 위한 인터페이스
    long long update(int index, long long newValue) {
        return update(index - 1, newValue, 1, 0, n - 1);
    }
};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> N >> Q;

    vector<long long> v(N, 0);

    RMQ rmq(v);

    for (int i = 0; i < Q; ++i) {
        int p, x, q;
        int a;
        cin >> a;

        if (a == 1) {
            cin >> p >> x;
            v[p - 1] = x;
            rmq.update(p, x);
        }
        else {
            cin >> p >> q;
            cout << rmq.query(p, q) << "\n";
        }
    }
    return 0;
}