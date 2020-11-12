//DP[a] = b 의 의미는 "a번째 숫자까지 읽을 수 있는 단어의 갯수는 b개입니다"
//자세한 풀이는 https://yabmoons.tistory.com/163 참고

#include <iostream>
#include <string>

using namespace std;
#define MAX 5001
#define MOD 1000000
string password;
int arr[MAX];
int DP[MAX];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> password;

    //int형 변환
    for (int i = 1; i <= password.length(); ++i) {
        arr[i] = password[i - 1] - '0';
    }

    //0 하나만 들어온 경우 변환 안됨
    if (password.length() == 1 && password[0] - '0' == 0)
        cout << 0;

    else {
        DP[0] = 1;

        //1~9사이 숫자면 변환 가능
        for (int i = 1; i <= password.length(); ++i) {
            if (arr[i] >= 1 && arr[i] <= 9) {
                DP[i] = (DP[i - 1] + DP[i]) % MOD;
            }
            if (i == 1)
                continue;

            //10이상 26이하면 추가로 알파벳 변환 가능
            int Temp = arr[i] + arr[i - 1] * 10;
            if (Temp >= 10 && Temp <= 26)
            {
                DP[i] = (DP[i - 2] + DP[i]) % MOD;
            }

        }

        cout << DP[password.length()];

    }


    return 0;
}