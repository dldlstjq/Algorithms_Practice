/*
원래 분할정복으로 풀었던 문제를 스택을 사용해 O(N)에 해결하는 방법
다시 볼 문제
*/

#include <iostream>
#include <vector>
#include <stack>

using namespace std;

int N;
//각 판자의 높이를 저장하는 배열
vector<int> h;

//스택을 사용한 O(n) 해법
int solveStack() {
    //남아 있는 판자들의 위치들을 저장한다.
    stack<int> remaining;
    h.push_back(0); //제일 끝 울타리 높이가 i번째 울타리 높이보다 작아야 범위가 설정되므로

    int ret = 0;
    for (int i = 0; i < h.size(); ++i) {
        //남아 있는 판자들 중 오른쪽 끝 판자가 h[i]보다 높다면
        //이 판자의 최대 사각형은 i에서 끝난다.
        while (!remaining.empty() && h[remaining.top()] >= h[i]) {
            int j = remaining.top();
            remaining.pop();
            int width = -1;
            //j번쨰 판자 왼쪽에 판자가 하나도 안 남아있는 경우 left[i]=-1,
            //아닌 경우 left[j]=남아 있는 판자 중 가장 오른쪽에 있는 판자의 번호가 된다.
            if (remaining.empty())
                width = i;
            else
                width = (i - remaining.top() - 1);
            ret = max(ret, h[j] * width);
        }
        remaining.push(i);
    }
    return ret;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int c;
    cin >> c;
    while (c--) {
        h.clear();
        cin >> N;
        for (int i = 0; i < N; ++i) {
            int tmp;
            cin >> tmp;
            h.push_back(tmp);
        }

        cout << solveStack() << "\n";
    }

    return 0;
}