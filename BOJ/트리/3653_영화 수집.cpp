/*
문제를 처음 보고 세그먼트 트리를 생각하기가 쉽지 않았다.
또한 적용시키기도 어려워 보였다.

다른 사람 풀이를 봤는데도 이해하기가 쉽지 않다.

알고리즘
1. 배열을 M + N 크기로 설정하고 (M ~ N - 1)까지 1로 표시하고 (0 ~ M - 1)까지는 0으로 표시합니다. 
즉, (0 ~ M - 1)은 현재 빈 공간이고 M 부터 1번 DVD의 위치를 표시한 것입니다.(자세한 그림은 lyzqm 블로그에 포스팅 되어있습니다.)

2. 현재 배열이 (0 ~ M - 1)까지는 빈 공간이고 M번부터 DVD의 위치가 차례대로 배치되어있기 때문에 
DVD 번호가 주어졌을 때 (0 ~ 배열[해당 DVD 번호] - 1)까지의 구간 합을 구해줍니다.

3. 확인한 DVD를 맨 위로 배치하는 과정을 현재 빈 공간 중 끝인  M - 1번 인덱스에 배치하는 방식으로 진행합니다.
(물론 기존에 DVD가 배치되어 있던 곳은 비워지고 현재 DVD가 배치되어 있던 곳은 채워진다.) 
이렇게 되면 (0 ~ 배열[해당 DVD 번호] - 1)까지의 구간 합은 0이 되므로 맨 위에 배치된 것으로 판단해도 됩니다.

4, 2 ~ 3번 과정을 반복하는데 3번의 빈 공간은 한 칸씩 줄어들므로 M - 1 -> M - 2 -> M -3 -> ... 이런식으로 업데이트 해줘야합니다.

*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int N, M;

//배열의 구간 최소 쿼리를 해결하기 위한 구간 트리의 구현
struct segment {
    //배열의 길이
    int size;
    //각 구간의 최소치
    vector<int> tree, idx;
    segment(int n, int m) {
        size = n + m;
        idx.resize(n);
        tree.resize(size * 4, 0);
    }
    //세그먼트 트리 초기화
    int init(int node, int m, int left, int right) {
        if (left == right) {
            if (left >= m) {
                idx[left - m] = left;
                tree[node] = 1;
            }
            return tree[node];
        }
        int mid = (left + right) / 2;
        return tree[node] = init(node * 2, m, left, mid) + init(node * 2 + 1, m, mid + 1, right);
    }

    void init(int M) {
        init(1, M, 0, size - 1);
    }

    //구간 합 구하기
    int query(int left, int right, int node, int nodeLeft, int nodeRight) {
        //두 구간이 겹치지 않으면 아주 큰 값으 반환한다: 무시됨
        if (right < nodeLeft || nodeRight < left)
            return 0;
        //node가 표현하는 범위가 array[left..right]에 완전히 포함되는 경우
        if (left <= nodeLeft && nodeRight <= right)
            return tree[node];
        //양쪽 구간을 나눠서 푼 뒤 결과를 합친다.
        int mid = (nodeLeft + nodeRight) / 2;
        return query(left, right, node * 2, nodeLeft, mid) +
            query(left, right, node * 2 + 1, mid + 1, nodeRight);
    }
    //query()를 외부에서 호출하기 위한 인터페이스
    int query(int left, int right) {
        return query(left, idx[right] - 1, 1, 0, size - 1);
    }
    //세그먼트 트리 업데이트
    int update(int index, int newValue, int node, int nodeLeft, int nodeRight) {
        //index가 노드가 표현하는 구간과 상관없는 경우엔 무시한다.
        if (index < nodeLeft || nodeRight < index)
            return tree[node];
        //트리의 리프까지 내려온 경우
        if (nodeLeft == nodeRight)
            return tree[node] = newValue;
        int mid = (nodeLeft + nodeRight) / 2;
        return tree[node] =
            update(index, newValue, node * 2, nodeLeft, mid) +
            update(index, newValue, node * 2 + 1, mid + 1, nodeRight);
    }
    //update()를 외부에서 호출하기 위한 인터페이스
    int update(int index, int newValue) {
        return update(idx[index], newValue, 1, 0, size - 1);
    }
    //해당 dvd 인덱스 업데이트
    void change(int index, int val) {
        idx[index] = val;
    }
};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;
    while (t--) {
        cin >> N >> M;
        segment seg(N, M);
        seg.init(M);

        //idx은 빈 공간 인덱스 표시
        int idx = M - 1;
        while (M--) {
            int num;
            cin >> num;

            cout << seg.query(0, num - 1) << " ";
            seg.update(num - 1, 0); //해당 dvd를 꺼내고
            seg.change(num - 1, idx);   //디비디의 위치를 바꾼다.
            seg.update(num - 1, 1); //누적합 업데이트
            idx--;  //빈 공간

        }
        cout << "\n";
    }
    return 0;
}