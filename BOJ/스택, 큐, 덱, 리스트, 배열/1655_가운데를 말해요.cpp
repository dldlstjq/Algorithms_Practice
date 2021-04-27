/*
2696_중앙값 구하기랑 같은 문제이다.
단순히 생각하면 숫자를 입력받을때마다 정렬해서 가운데 값을 뽑아내면 된다.
하지만 n이 최대 100,000이고 정렬 자체가 nlogn이기 때문에 전체 시간복잡도가 O(n^2logn)이 되어 시간초과가 난다.

중간값은 우선순위 큐를 쓰면 되는데 로직이 생각나지 않아 종만북을 보고 다시 원리를 파악했다.

1.최대 힙의 크기는 최소 힙의 크기와 같거나, 하나 더 크다.
2.최대 힙의 최대 원소는 최소 힙의 최소 원소보다 작거나 같다.
이때 이 수열의 중간값은 항상 최대 힙의 루트에 있게 된다.
*/

#include <iostream> 
#include <vector>
#include <queue>
using namespace std;


int main(int argc, char** argv) {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    priority_queue<int, vector<int>, greater<int>> min_heap; //오름차순
    priority_queue<int, vector<int>, less<int>> max_heap;    //내림차순

    //1.maxheap의 크기는 minheap의 크기와 같거나 1 더 크다.
    //2. maxheap.top()<=minheap.top()
    cin >> n;
    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;
        //1번 불변식
        if (max_heap.size() == min_heap.size())
            max_heap.push(x);
        else
            min_heap.push(x);
        //2번 불변식이 깨질 경우 복구
        if (!min_heap.empty() && !max_heap.empty() &&
            min_heap.top() < max_heap.top()) {
            int a = max_heap.top(), b = min_heap.top();
            max_heap.pop(); min_heap.pop();
            max_heap.push(b);
            min_heap.push(a);
        }
        cout << max_heap.top() << "\n";


    }
    return 0;
}