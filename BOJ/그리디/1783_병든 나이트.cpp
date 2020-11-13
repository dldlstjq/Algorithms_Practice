/*
그리디 알고리즘은 매 순간 최선을 선택한다라는 말 때문에 매우 쉽게 들리지만, 
매 순간의 선택이 최선이 되도록 방법을 정하는 것 자체가 매우 어렵기 때문에 알고리즘중에 사람들이 가장 어려워 한다.

처음엔 이 말이 뭔가 싶었는데 문제를 풀다보니 이해할 수 있었다.
이 문제 역시 접근 방법을 몰라 여러번 시도하다 구글링을 통해 해결할 수 있었다.
체스판의 높이에 따라 갈 수 있는 경우가 정해져 있어 그 부분만 고려하면 문제를 풀 수 있다.
*/

/*
두 번째로 풀 때 이해하며 푼 코드. 밑에 더 간단하게 줄인 코드가 있지만 이해는 이게 더 잘되는 것 같다.
*/
#include <iostream>
#include <algorithm>

using namespace std;
int n, m;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> m;

    //높이가 1이면 현재 위치만 가능
    if (n == 1)
        cout << 1;

    //높이 2이면 1칸위, 1칸 아래 두가지 밖에 못감. 가로 길이에 따라 경로 결정
    else if (n == 2) {
        if (m <= 2)
            cout << 1;
        else if (2 < m && m <= 4)
            cout << 2;
        else if (4 < m && m <= 6)
            cout << 3;
        else if (m >= 7)
            cout << 4;
    }

    //높이 3이상이면 모든 경우의 수 이용하고 가로 당 한칸씩 이동 가능
    else if (n >= 3) {
        if (m <= 4)
            cout << m;
        else if (m == 5 || m == 6)
            cout << 4;
        else if (m == 7)
            cout << 5;
        else if (m >= 8)
            cout << 5 + m - 7;
    }

    return 0;
}



///////////////////////////////////
/*
다른 사람이 푼 더 깔끔한 코드. 하지만 처음보면 이해 못할 것 같다.
*/
#include <iostream> 
using namespace std;
int min(int a, int b) {
    return a < b ? a : b;
}

int main() {
    int N, M;
    cin >> N >> M;
    if (N == 1)
        cout << 1 << endl;
    else if (N == 2)
        cout << min(4, (M + 1) / 2) << endl;
    else if (M < 7) cout << min(4, M) << endl;

    else cout << M - 7 + 5 << endl;

    return 0;
}

