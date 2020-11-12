//stable_sort 처음 사용.
//일반 sort 함수는 순서를 보장하지 않지만 std::stable_sort는 순서를 보장한다.

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <utility>

using namespace std;

bool compare(pair<int, string> a, pair<int, string> b) {
    if (a.first < b.first)
        return true;
    else if (a.first == b.first)
        return false;

    else
        return false;
}


int main() {
    ios_base::sync_with_stdio(0);

    int n;
    cin >> n;
    vector <pair<int, string>> p(n);

    for (int i = 0; i < n; i++)
        cin >> p[i].first >> p[i].second;

    stable_sort(p.begin(), p.end(), compare);

    for (int i = 0; i < n; i++)
        cout << p[i].first << " " << p[i].second << "\n";

    return 0;
}