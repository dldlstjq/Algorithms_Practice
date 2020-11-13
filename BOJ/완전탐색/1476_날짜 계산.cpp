/*
Year-E는 15의 배수이고, Year-S는 28의 배수이고, Year-M은 19의 배수이므로 이 모든 조건을 만족하는 년도가 답
*/

#include <iostream>

using namespace std;
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int e, s, m;

    cin >> e >> s >> m;

    int year = 1;
    while (1) {
        if ((year - e) % 15 == 0 && (year - s) % 28 == 0 && (year - m) % 19 == 0) {
            break;
        }
        year++;
    }

    cout << year;
    return 0;
}