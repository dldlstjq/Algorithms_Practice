/*
구간 트리를 사용하여 최대, 최소값을 구하면 된다.
언뜻보면 최대, 최소를 구하는 코드가 다 필요할 것 같지만 하나만 코드를 짜서 
수 입력할 때 -1을 붙이고 출력할 때 다시 -1을 곱하면 다른 코드를 짤 필요가 없다.
종만북을 안봤으면 최대, 최소 구하는 코드를 모두 짰을 것이다.

그리고 query 함수에서 범위를 벗어낫을 경우 리턴 값을 잘 설정해야 답이 잘 나온다.
처음 시도할 때 책의 numeric_limits를 이용했는데 값이 잘 안나왔다.
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int N, m;
const int INF = 1000000000 + 1;

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
        return rangeMin[node] = min(leftMin, rightMin);
    }
    //node가 표현하는 범위 array[nodeLeft..nodeRight]가 주어질 때
    //이 범위와 array[left..right]의 교집합의 최소치를 구한다.
    long long query(int left, int right, int node, int nodeLeft, int nodeRight) {
        //두 구간이 겹치지 않으면 아주 큰 값을 반환한다: 무시됨
        if (right < nodeLeft || nodeRight < left)
            return INF;
        //node가 표현하는 범위가 array[left..right]에 완전히 포함되는 경우
        if (left <= nodeLeft && nodeRight <= right)
            return rangeMin[node];
        //양쪽 구간을 나눠서 푼 뒤 결과를 합친다.
        int mid = (nodeLeft + nodeRight) / 2;
        return min(query(left, right, node * 2, nodeLeft, mid),
            query(left, right, node * 2 + 1, mid + 1, nodeRight));
    }
    //query()를 외부에서 호출하기 위한 인터페이스
    long long query(int left, int right) {
        return query(left - 1, right - 1, 1, 0, n - 1);
    }
    //array[index]=newValue로 바뀌었을 때 node를 루트로 하는
    //구간 트리를 갱신하고 노드가 표현하는 구간의 최소치를 반환한다.
    long long update(int index, int newValue, int node, int nodeLeft, int nodeRight) {
        //index가 노드가 표현하는 구간과 상관없는 경우엔 무시한다.
        if (index < nodeLeft || nodeRight < index)
            return rangeMin[node];
        //트리의 리프까지 내려온 경우
        if (nodeLeft == nodeRight)
            return rangeMin[node] = newValue;
        int mid = (nodeLeft + nodeRight) / 2;
        return rangeMin[node] = min(
            update(index, newValue, node * 2, nodeLeft, mid),
            update(index, newValue, node * 2 + 1, mid + 1, nodeRight));
    }
    //update()를 외부에서 호출하기 위한 인터페이스
    long long update(int index, int newValue) {
        return update(index - 1, newValue, 1, 0, n - 1);
    }
};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> N >> m;

    vector<long long> min_v;
    vector<long long> max_v;

    //최대값은 -1을 곱해 부호를 뒤집는다.
    //그러면 마지막에 다시 -1을 곱하면 최대값이 된다.
    for (int i = 0; i < N; ++i) {
        long long num;
        cin >> num;
        min_v.push_back(num);
        max_v.push_back(-num);
    }

    RMQ min_rmq(min_v);
    RMQ max_rmq(max_v);

    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        cout << min_rmq.query(a, b) << " " << -1 * max_rmq.query(a, b) << "\n";
    }
    return 0;
}