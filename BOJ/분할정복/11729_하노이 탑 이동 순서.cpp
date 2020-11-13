/*
대표적인 재귀함수 문제지만 역시 오랜만에 보니 풀이방법을 다 잊어버렸다.
vector pair로 저장하여 크기만큼 출력하면 된다.

-풀이 방법
가장 왼쪽부터 A, B, C봉이라고 하겠다. 
먼저 N-1개 원판을 A에서 B로 옮긴다. 
그리고 A의 가장 밑에 있는 원판을 A에서 C로 옮긴다. 
마지막으로 B에있는 N-1개의 원판을 C로 옮긴다.
원판을 여러개를 한번에 옮길 수 없어서 N-1개를 옮기는 것을 하나씩 재귀적으로 푼다.
N-1개를 B로 옮기는 것은 또 그 속에서 가장 밑의 원판과 N-1-1개의 문제가 되는 것이다.
*/
#include <iostream>
#include <vector>
#include <utility>
  
using namespace std;
vector<pair<int, int> > v;    //이동 횟수에 사용되는 전역변수

//from에서 temp를 거쳐 to로 이동
void hanoi(int from, int temp, int to, int n) {
    if (n == 1) {
        v.push_back(make_pair(from, to));

    }
    else {
        hanoi(from, to, temp, n - 1);
        v.push_back(make_pair(from, to));
        hanoi(temp, from, to, n - 1);

    }

}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;

    hanoi(1, 2, 3, n);  //하노이탑 재귀호출
    cout << v.size() << "\n";

    for (int i = 0; i < v.size(); i++)
        cout << v[i].first << " " << v[i].second << "\n";

    return 0;
}