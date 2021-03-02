/*
종만북에 있는 구간 트리 코드를 거의 그대로 사용했다.
수정한 것은 구간 합을 구해야 하기 때문에 return값으로 더한 것을 반환하도록 수정했다.
범위가 long long 형까지 가기 때문에 long long으로 수정해 줘야한다.
또한 문제에서 인덱스는 1부터 시작인데 코드내에서는 0부터 시작하므로 1을 빼줘서
인덱스를 맞춰줘야 하고 바꾸는 수 c 역시 범위가 long long 이므로 이것도 고려해 줘야 한다.
코드는 복잡해 보이지만 조금만 생각해보면 재귀함수이기 때문에 비교적(?)
간단하지 않나 생각한다.
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int n, m, k;

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
        return rangeMin[node] = leftMin + rightMin;
    }
    //node가 표현하는 범위 array[nodeLeft..nodeRight]가 주어질 때
    //이 범위와 array[left..right]의 교집합의 최소치를 구한다.
    long long query(long long left, long long right, int node, int nodeLeft, int nodeRight) {
        //두 구간이 겹치지 않으면 아주 큰 값으 반환한다: 무시됨
        if (right < nodeLeft || nodeRight < left)
            return 0;
        //node가 표현하는 범위가 array[left..right]에 완전히 포함되는 경우
        if (left <= nodeLeft && nodeRight <= right)
            return rangeMin[node];
        //양쪽 구간을 나눠서 푼 뒤 결과를 합친다.
        int mid = (nodeLeft + nodeRight) / 2;
        return query(left, right, node * 2, nodeLeft, mid) +
            query(left, right, node * 2 + 1, mid + 1, nodeRight);
    }
    //query()를 외부에서 호출하기 위한 인터페이스
    //1씩 빼줘서 인덱스를 맞춰준다.
    long long query(long long left, long long right) {
        return query(left - 1, right - 1, 1, 0, n - 1);
    }
    //array[index]=newValue로 바뀌었을 때 node를 루트로 하는
    //구간 트리를 갱신하고 노드가 표현하는 구간의 최소치를 반환한다.
    long long update(int index, long long newValue, int node, int nodeLeft, int nodeRight) {
        //index가 노드가 표현하는 구간과 상관없는 경우엔 무시한다.
        if (index < nodeLeft || nodeRight < index)
            return rangeMin[node];
        //트리의 리프까지 내려온 경우
        if (nodeLeft == nodeRight)
            return rangeMin[node] = newValue;
        int mid = (nodeLeft + nodeRight) / 2;
        return rangeMin[node] =
            update(index, newValue, node * 2, nodeLeft, mid) +
            update(index, newValue, node * 2 + 1, mid + 1, nodeRight);
    }
    //update()를 외부에서 호출하기 위한 인터페이스
    //newValue가 long long인 경우도 고려해야 한다.
    long long update(int index, long long newValue) {
        return update(index - 1, newValue, 1, 0, n - 1);
    }
};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> m >> k;

    vector<long long> v;

    for (int i = 0; i < n; ++i) {
        int tmp;
        cin >> tmp;
        v.push_back(tmp);
    }

    RMQ rmq(v);

    for (int i = 0; i < m + k; ++i) {
        int a;
        long long b, c;
        cin >> a >> b >> c;
        if (a == 1)
            rmq.update(b, c);
        else
            cout << rmq.query(b, c) << "\n";
    }
    return 0;
}