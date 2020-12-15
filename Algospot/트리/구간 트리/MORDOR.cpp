/*
구간트리를 이용해 최대, 최소값을 구하는 문제이다.
최소값은 책에 있는 코드를 쓰면 되지만 최대값은 따로 만들어야 되는줄 알았다.
하지만 -1을 곱하면 최솟값이 곧 최대값이 되므로 쉽게 구할 수 있었다.
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAX = numeric_limits<int>::max();

//배열의 구간 최소 쿼리를 해결하기 위한 구간 트리의 구현
struct RMQ {
    //배열의 길이
    int n;
    //각 구간의 최소치
    vector<int> rangeMin;
    RMQ(const vector<int>& array) {
        n = array.size();
        rangeMin.resize(n * 4);
        init(array, 0, n - 1, 1);
    }
    //node 노드가 array[left..right]배열을 표현할 때
    //node를 루트로 하는 서브트리를 초기화하고, 이 구간의 최소치를 반환한다.
    int init(const vector<int>& array, int left, int right, int node) {
        if (left == right)
            return rangeMin[node] = array[left];
        int mid = (left + right) / 2;
        int leftMin = init(array, left, mid, node * 2);
        int rightMin = init(array, mid + 1, right, node * 2 + 1);
        return rangeMin[node] = min(leftMin, rightMin);
    }
    //node가 표현하는 범위 array[nodeLeft..nodeRight]가 주어질 때
    //이 범위와 array[left..right]의 교집합의 최소치를 구한다.
    int query(int left, int right, int node, int nodeLeft, int nodeRight) {
        //두 구간이 겹치지 않으면 아주 큰 값으 반환한다: 무시됨
        if (right < nodeLeft || nodeRight < left)
            return MAX;
        //node가 표현하는 범위가 array[left..right]에 완전히 포함되는 경우
        if (left <= nodeLeft && nodeRight <= right)
            return rangeMin[node];
        //양쪽 구간을 나눠서 푼 뒤 결과를 합친다.
        int mid = (nodeLeft + nodeRight) / 2;
        return min(query(left, right, node * 2, nodeLeft, mid),
            query(left, right, node * 2 + 1, mid + 1, nodeRight));
    }
    //query()를 외부에서 호출하기 위한 인터페이스
    int query(int left, int right) {
        return query(left, right, 1, 0, n - 1);
    }
    //array[index]=newValue로 바뀌었을 때 node를 루트로 하는
    //구간 트리를 갱신하고 노드가 표현하는 구간의 최소치를 반환한다.
    int update(int index, int newValue, int node, int nodeLeft, int nodeRight) {
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
    int update(int index, int newValue) {
        return update(index, newValue, 1, 0, n - 1);
    }
};



int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int c;
    cin >> c;
    while (c--) {
        int n, q;
        cin >> n >> q;
        vector<int> height;
        vector<int> minus_h;
        for (int i = 0; i < n; ++i) {
            int tmp;
            cin >> tmp;
            height.push_back(tmp);
            minus_h.push_back(-tmp);
        }

        RMQ rmq(height);
        RMQ minus_rmq(minus_h);

        for (int i = 0; i < q; ++i) {
            int a, b;
            cin >> a >> b;

            int high = -1 * (minus_rmq.query(a, b));
            int low = rmq.query(a, b);

            cout << high - low << "\n";
        }

    }

    return 0;
}