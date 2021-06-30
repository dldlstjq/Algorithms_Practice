/*
처음엔 순열을 이용해서 풀려고 했었다.
하지만 사전 순으로 출력해야한다는 점에서 순열이 아닌것 같았다.
걸국 재귀함수를 이용해야 할 것 같았는데 재귀함수는 잘 몰라서 못 풀었다.
모음인 경우에는 모음을 증가하고 자음인 경우에는 자음만 증가시켜 조건에 맞을때 출력하면 되었다.
*/

/*
2021.06.30 백트래킹으로 거의 다 왔는데 헤맸다. 
다시 풀 때 모음과 자음을 나눠서 저장했는데 그렇게 되면 예제 출력과 순서가 다르게 나온다.
따로 저장할 필요 없이 하나의 벡터나 배열에 문자를 저장하고 정렬한 다음 하나씩 문자를 더한다.
자음이면 자음을 카운트하고 모음이면 모음을 카운트 해서 길이가 L이 될때 조건 만족 여부에 따라 암호를 출력하면 된다.
백트래킹을 오래 안하다 하려니 생각이 잘 안난다.
*/

#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <algorithm>
#include <utility>

using namespace std;
int L, C;
char arr[16];

void dfs(int pos, int mo, int ja, string s) {
    //길이가 L과 맞고 자음, 모음 만족하면 출력
    if (s.length() == L) {
        if (mo >= 1 && ja >= 2)
            cout << s << "\n";
        return;
    }

    //현재 위치부터 C까지 모음이면 모음 증가, 자음이면 자음증가
    for (int i = pos; i < C; i++) {
        if (arr[i] == 'a' || arr[i] == 'e' || arr[i] == 'i' || arr[i] == 'o' || arr[i] == 'u')
            dfs(i + 1, mo + 1, ja, s + arr[i]);
        else
            dfs(i + 1, mo, ja + 1, s + arr[i]);
    }

}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> L >> C;

    for (int i = 0; i < C; i++) {
        cin >> arr[i];
    }
    sort(arr, arr + C);
    dfs(0, 0, 0, "");

    return 0;
}