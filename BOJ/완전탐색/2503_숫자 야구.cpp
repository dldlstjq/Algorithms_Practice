/*
문제 조건이 세자리 숫자이기 때문에 111~999까지 숫자 중 안되는 숫자를 제외한
나머지 숫자의 개수를 카운팅 하는 방식을 해결했다.

스트라이크, 볼 여부를 판단은 string형으로 변환해서 인덱스끼리 비교하는 것이
편한 방법이어서 사용했다.

각 자릿수에 중복되는 숫자가 있으면 안되기 때문에 그 부분은 고려했는데
0이 들어가면 안되는건 생각하지 못해 처음에 오답을 받았다.
*/

// 2021.07.02 세 개 숫자가 모두 달라야하는것, 0은 포함되지 않는다는것만 잘 확인하면 쉽게 풀 수 있다.
#include <iostream> 
#include <string>
using namespace std;

const int MAX = 1000 + 1;
int N;
bool arr[MAX];

bool match(int s, int b, int n, int goal) {
    int strike = 0, ball = 0;

    string s1 = to_string(n);
    string s2 = to_string(goal);

    for (int i = 0; i < s1.length(); ++i) {
        for (int j = 0; j < s2.length(); ++j) {
            if (s1[i] == s2[j] && i == j)
                strike++;
            else if (s1[i] == s2[j] && i != j)
                ball++;
        }
    }

    if (strike == s && ball == b)
        return true;
    else
        return false;
}

int main(int argc, char** argv) {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N;
    for (int i = 0; i < N; ++i) {
        int num, s, b;
        cin >> num >> s >> b;

        for (int j = 100; j <= 999; ++j) {
            // 세 개 숫자가 같은 경우랑 0이 있는 경우는 제외
            string tmp = to_string(j);
            if (tmp[0] == tmp[1] || tmp[1] == tmp[2] || tmp[0] == tmp[2]
                || tmp[0] == '0' || tmp[1] == '0' || tmp[2] == '0')
                continue;

            // 첫번째 조건과 일치하는건 true
            if (i == 0) {
                if (match(s, b, j, num))
                    arr[j] = true;
            }
            // 두번째 부터는 이전 조건을 만족하면서 일치하는지 확인. 일치 안하면 다시 false
            else {
                if (arr[j] && !match(s, b, j, num))
                    arr[j] = false;
            }
        }
    }

    int ret = 0;
    for (int i = 100; i <= 999; ++i) {
        if (arr[i])
            ret++;
    }

    cout << ret;

    return 0;
}


//////////////////////////////////

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

bool baseball[1000];

//해당 숫자의 스트라이크, 볼 여부를 반환
//ans는 질문한 숫자, num은 후보 숫자
//스트라이크, 볼 순으로 반환
pair<int, int> isStrike(int ans, int num) {
    pair<int, int> ret;
    //비교를 쉽게 하기 위해 string으로 변환
    string s1 = to_string(ans);
    string s2 = to_string(num);
    int s = 0, b = 0;
    for (int i = 0; i < s1.size(); ++i) {
        for (int j = 0; j < s2.size(); ++j) {
            //자릿수와 숫자가 같으면 스트라이크
            if (i == j && s1[i] == s2[j])
                s++;
            //자릿수는 다른데 숫자가 같으면 볼
            else if (i != j && s1[i] == s2[j])
                b++;
        }
    }
    ret = make_pair(s, b);
    return ret;
}


int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;

    for (int i = 0; i < 1000; ++i)
        baseball[i] = false;

    for (int i = 0; i < t; ++i) {
        int num, s, b;
        cin >> num >> s >> b;

        pair<int, int> player;
        for (int j = 111; j <= 999; ++j) {
            //각 자리가 중복되는 숫자는 고려하지 않는다.
            //0이 있는 경우도 제외해야한다.
            string tmp = to_string(j);
            if (tmp[0] == tmp[1] || tmp[1] == tmp[2] || tmp[0] == tmp[2]
                || tmp[0] == '0' || tmp[1] == '0' || tmp[2] == '0')
                continue;

            player = isStrike(num, j);

            //맨 처음엔 전부 false이기 때문에 스트라이크, 볼 일치하면 true
            if (i == 0) {
                if (player.first == s && player.second == b)
                    baseball[j] = true;
            }
            //두번째 부터는 모든 경우를 만족해야 하기 때문에 
            //true인 수 중에서 스트라이크, 볼이 일치하지 않으면 false로 변경
            else {
                if (baseball[j])
                    if (player.first != s || player.second != b)
                        baseball[j] = false;
            }

        }
    }

    //true인 부분만 카운트
    int cnt = 0;
    for (int i = 111; i < 1000; ++i)
        if (baseball[i])
            cnt++;
    cout << cnt;

    return 0;
}