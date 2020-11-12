/*
문제에 맞게 진법을 변형해주면 됨
*/

#include <iostream>
#include <cmath>
#include <string>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    string n;
    int b;
    long long result = 0;
    cin >> n >> b;

    int j = 0;
    int len = n.size();

    //오른쪽부터 거꾸로 내려오면서 계산
    for (int i = len - 1; i >= 0; i--) {
        if (n[i] >= 'A' && n[i] <= 'Z') {
            n[i] = n[i] - 65 + 10;
            result = result + n[i] * pow(b, j);
            j++;
        }
        else {
            n[i] = n[i] - 48;
            result = result + n[i] * pow(b, j);
            j++;
        }
    }
    cout << result;

    return 0;
}