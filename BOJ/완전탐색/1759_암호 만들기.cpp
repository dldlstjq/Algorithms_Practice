/*
처음엔 순열을 이용해서 풀려고 했었다.
하지만 사전 순으로 출력해야한다는 점에서 순열이 아닌것 같았다.
걸국 재귀함수를 이용해야 할 것 같았는데 재귀함수는 잘 몰라서 못 풀었다.
모음인 경우에는 모음을 증가하고 자음인 경우에는 자음만 증가시켜 조건에 맞을때 출력하면 되었다.
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