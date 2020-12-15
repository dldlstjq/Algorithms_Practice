/*
힙을 구현해놓은 priority_queue를 이용하는 문제.
힙정렬을 한 다음 중간 값을 찾는 걸로 처음에 생각했다.
책에서는 수열을 두 묶음으로 나누어 최소, 최대 힙에 저장해
불변식을 통해 문제를 풀었다.

당연히 수를 입력받을 때마다 정렬하면 시간초과.
아무리 생각해도 이런 풀이는 어떻게 생각해 내는지 모르겠다.
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

struct RNG {
    int seed, a, b;
    RNG(int _a, int _b) :a(_a), b(_b), seed(1983) {}
    int next() {
        int ret = seed;
        seed = (seed * (long long)a) + b;
        return ret % 20090711;
    }
};

int median(int n, RNG rng) {
    //힙 생성
    priority_queue<int, vector<int>, less<int>> maxHeap;
    priority_queue<int, vector<int>, greater<int>> minHeap;
    int ret = 0;
    //반복문 불변식
    //1. maxHeap의 크기는 minHeap의 크기와 같거나 1 더 크다.
    //2. maxHeap.top <= minHeap.top()
    for (int cnt = 1; cnt <= n; ++cnt) {
        //우선 1번 불변식부터 만족시킨다.
        if (maxHeap.size() == minHeap.size())
            maxHeap.push(rng.next());
        else
            minHeap.push(rng.next());
        //2번 불변식이 깨졌을 경우 복구하자.
        if (!minHeap.empty() && !maxHeap.empty() &&
            minHeap.top() < maxHeap.top()) {
            int a = maxHeap.top(), b = minHeap.top();
            maxHeap.pop(); minHeap.pop();
            maxHeap.push(b);
            minHeap.push(a);
        }
        ret = (ret + maxHeap.top()) % 20090711;
    }
    return ret;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int c;
    cin >> c;
    while (c--) {
        int N, a, b;
        cin >> N >> a >> b;
        RNG generator(a, b);
        cout << median(N, generator) << "\n";
    }

    return 0;
}