/*
백트래킹의 대명사인 n-queen 문제였다.
무식하게 NxN 배열을 선언해놓고 거기서 퀸을 하나씩 놓으며 해결하려했는데 바로 위의 행과 
비교가 됐을 뿐 같은 열에 있는지 확인을 할 수 없었다.

인터넷에서 찾은 코드가 알고리즘 수업 때 들은 코드와 똑같아 이걸 보고 해결할 수 있었다.
2차원 배열 선언할 것도 없이 1차원 배열만 하나 있으면 인덱스가 행, 해당하는 원소를 열로 잡으면 된다.
이후 1~N까지 같은 열이거나 대각선인지 확인해서 맞으면 넣고 아니면 다시 돌아가면 된다.

알고리즘은 아래와 같습니다.
1. promising 함수를 통해 해당 칸에 퀸을 배치할 수 있는지 여부를 판단합니다.
2. promising 함수가 true를 반환할 경우
    i) N 번째 열까지 도달했을 경우 완성된 체스판이므로 개수를 셉니다
    ii) 해당 열 모든 칸에 퀸을 배치하면서 가능성을 판단합니다다
3. 총 완성된 체스판의 수를 출력합니다.

*/

#include <iostream>
using namespace std;

int n, cnt;

// col[1]의 의미는 1행 *열이다.
// col[1] = 1 => 1행 1열, col[2] = 3 => 2행 3열
int col[15 + 1];

bool promising(int i) {
    int k = 1;
    bool flag = true;
    //k=1~i-1까지 
    while (k < i && flag) {
        //같은 열이거나 대각선이라면 배치 못함
        if (col[i] == col[k] || abs(col[i] - col[k]) == abs(i - k))
            flag = false;
        k++;
    }
    return flag;
}

void n_queen(int i) {
    if (promising(i)) {
        //판이 완성
        if (i == n)
            cnt++;
        else {
            //해당 열에 배치
            for (int j = 1; j <= n; ++j) {
                col[i + 1] = j;
                n_queen(i + 1);
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n;

    //0을 넣어주지만 사실 인덱스 1부터 시작해서 n행까지이다.
    n_queen(0);
    cout << cnt;

    return 0;
}