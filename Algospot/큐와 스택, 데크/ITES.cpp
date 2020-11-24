/*
난수 생성방법에서 막혔다.
알고리즘 자체는 쉽게 이해가 갔는데 오프라인 알고리즘의 경우 조금만 생각하면
시간이 적게 걸릴 수 있었다.

생각하는 방법을 많이 길러야겠다.
*/

#include <iostream>
#include <queue>

using namespace std;

struct RNG {
    unsigned seed;
    RNG() :seed(1983) {}
    unsigned next() {
        unsigned ret = seed;
        seed = ((seed * 214013u) + 2531011u);
        return ret % 10000 + 1;
    }
};

//온라인 알고리즘.
//모든 데이터를 미리 생성하는 대신, 구간에 새 숫자를 포함시켜야 할 때마다
//해당 숫자 하나씩 생성.
int countRange(int k, int n) {
    RNG rng;    //신호값을 생성하는 난수 생성기
    queue<int> q;   //현재 구간에 들어있는 숫자들을 저장하는 큐
    int ret = 0, rangeSum = 0;

    for (int i = 0; i < n; ++i) {
        //구간에 숫자를 추가한다.
        int tmp = rng.next();
        rangeSum += tmp;
        q.push(tmp);

        //구간 합이 k를 초과하는 동안 구간에서 숫자를 뺀다
        while (rangeSum > k) {
            rangeSum -= q.front();
            q.pop();
        }

        if (rangeSum == k)
            ret++;

    }
    return ret;
}

//오프라인 알고리즘.
//tail이 head 부터 다시 시작하는게 아니라 마지막 위치에서 부터 시작.
//while에서 tail이 N만큼만 반복하기 때문에 O(N) 밖에 안걸림
int optimized(const vector<int>& signals, int k) {
    int ret = 0, tail = 0, rangeSum = signals[0];
    for (int head = 0; head < signals.size(); ++head) {
        //rangeSum이 k이상인 최초의 구간을 만날 때까지 tail을 옮긴다.
        while (rangeSum < k && tail + 1 < signals.size())
            rangeSum += signals[++tail];

        if (rangeSum == k)
            ret++;

        //signals[head]는 이제 구간에서 빠진다.
        rangeSum -= signals[head];
    }
    return ret;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int c;
    cin >> c;

    while (c--) {
        int n, k;
        cin >> k >> n;
        cout << countRange(k, n) << "\n";
    }


    return 0;
}