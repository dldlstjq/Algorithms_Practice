/*
처음에는 백준온라인에서 풀었던 방식대로 하나씩 삭제해서 
리스트 맨 끝에 넣는 방식으로 구현하니까 시간초과가 났다.
-> 큐를 사용해서 풀면 원소 추가, 삭제가 상수시간에 이루어지기 때문에
시간초과가 안나지만 리스트의 추가, 삭제는 시간이 조금 걸리는 듯 하다.

리스트 포인터를 옮겨주는 식으로 구현해야 정답을 받을 수 있었다.
*/

#include <iostream>
#include <list>

using namespace std;
int N, K;

list <int> josephus(list<int>& li) {

    list<int>::iterator kill = li.begin();

    //사람이 두 명 남을때까지 반복
    while (N > 2) {
        //1부터 삭제. erase()는 지운 원소의 다음 원소를 반환한다.
        kill = li.erase(kill);
        //맨 마지막을 가리키면 다시 처음으로
        if (kill == li.end())
            kill = li.begin();

        --N;

        //K-1번 다음 사람으로 옮긴다.
        for (int i = 0; i < K - 1; ++i) {
            ++kill;
            if (kill == li.end())
                kill = li.begin();
        }

    }
    return li;

}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int c;
    cin >> c;

    while (c--) {
        cin >> N >> K;
        list<int> li;

        for (int i = 1; i <= N; ++i) {
            li.push_back(i);
        }

        list<int> ret = josephus(li);
        cout << ret.front() << " " << ret.back() << "\n";

    }

    return 0;
}