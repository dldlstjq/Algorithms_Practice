/*
처음 접근할때 나온 알파벳을 숫자로 맵핑시켜 순열을 돌리면서 제일 큰 값을 계산하면 된다고 생각했다.
map을 이용하여 알파벳과 숫자를 저장했고 순열을 돌렸는데 에러가 났다.
아마 next_permutation에서 map은 돌아가지 않는 것 같다.

그래서 알파벳이랑 숫자를 매칭시키는 방법을 생각해봤는데 너무 복잡하게 되거나 생각이 잘 안났다.
결국 다른 사람 풀이를 봤는데 수학적으로 접근해서 ABC=100A+10B+C 이런식으로 접근했다.
100 10 1
 A  B  C

100 10 1
C   B  A

101A+20B+101C 로 만들어 정수부분을 정렬한 뒤 9부터 내려가면서 곱해주면 되었다.
순열이라 적혀있어 순열로만 풀이를 생각한게 못푼 원인이지 않나 싶다.
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n;
vector<string> v;

long long alphabet[26];

//10의 거듭제곱 계산
long long ten(int N) {
    int tmp = 1;
    for (int i = 0; i < N; ++i)
        tmp *= 10;
    return tmp;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n;

    for (int i = 0; i < n; ++i) {
        string str;
        cin >> str;
        v.push_back(str);
    }

    //수학적으로 계산한다.
    //GCF= 100G+10C+F 로 생각해서 alpha[G]+=100, alpha[C]+=10 이렇게 저장해둔다.
    //-1을 곱해서 정렬할 때 자릿수가 큰게 앞으로 오도록 한다.
    for (int i = 0; i < v.size(); ++i) {
        string str = v[i];
        int len = str.length() - 1;
        for (int j = 0; j < str.length(); ++j) {
            alphabet[str[j] - 'A'] += (long long)(-1 * ten(len--));
        }
    }

    sort(alphabet, alphabet + 26);

    //가장 자릿수가 큰 수부터 9를 곱해가며 수를 구한다.
    long long ret = 0;
    int num = 9;
    for (int i = 0; i < 26; ++i) {
        if (alphabet[i] != 0) {
            ret += -1 * (alphabet[i] * num--);
        }
    }

    cout << ret;
    return 0;
}