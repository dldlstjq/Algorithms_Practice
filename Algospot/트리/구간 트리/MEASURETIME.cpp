/*
수열 크기가 최대 10만이라 삽입정렬 직접 수행으로는 시간초과가 난다.
펜윅트리를 이용하면 쉽게 풀린다는데 코드 이해가 잘 안간다...
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

//펜윅트리의 구현. 가상의 배열 A[]의 부분 하을
//빠르게 구현할 수 있도록 한다. 초기화시에는 A[]의
//원소가 전부 0이라고 생각한다.
struct FenwickTree {
    vector<int> tree;
    FenwickTree(int n) :tree(n + 1) {}
    //A[0..pos]의 부분 합을 구한다.
    int sum(int pos) {
        //인덱스가 1부터 시작한다고 생각하자.
        ++pos;
        int ret = 0;
        while (pos > 0) {
            ret += tree[pos];
            //다음 구간을 찾기 위해 최종 비트를 지운다.
            pos &= (pos - 1);
        }
        return ret;
    }
    //A[pos]에 val을 더한다.
    void add(int pos, int val) {
        ++pos;
        while (pos < tree.size()) {
            tree[pos] += val;
            //마지막 비트를 추출하기 위해
            pos += (pos & -pos);
        }
    }

};

//펜윅 트리를 이용해 문제를 해결한다.
long long countMoves(const vector<int>& A) {
    FenwickTree tree(1000000);
    long long ret = 0;
    for (int i = 0; i < A.size(); ++i) {
        ret += tree.sum(999999) - tree.sum(A[i]);
        tree.add(A[i], 1);
    }
    return ret;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int c;
    cin >> c;
    while (c--) {
        int n;
        cin >> n;
        vector<int> a;
        for (int i = 0; i < n; ++i) {
            int tmp;
            cin >> tmp;
             a.push_back(tmp);

        }
        cout << countMoves(a) << "\n";
    }
    return 0;
}
