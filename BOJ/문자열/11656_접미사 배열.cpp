/*
문자열 입력받아서 출력할때마다 맨 앞글자 삭제.
*/
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    string str, tmp;
    vector <string> s;

    cin >> str;

    tmp = str;

    for (int i = 0; i < tmp.size(); i++) {
        s.push_back(str);
        str.erase(str.begin());
    }

    sort(s.begin(), s.end());

    for (int i = 0; i < s.size(); i++) {
        cout << s[i] << '\n';
    }

    return 0;
}