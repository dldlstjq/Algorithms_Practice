//pair로 데이터 저장.

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>


using namespace std;
const int MAX = 100000;
pair <pair<string, int>, pair<int, int>> student[MAX];

bool compare(pair <pair<string, int>, pair<int, int>>a, pair <pair<string, int>, pair<int, int>>b) {
    if (a.first.second > b.first.second)
        return true;
    else if (a.first.second == b.first.second) {
        if (a.second.first < b.second.first)
            return true;
        else if (a.second.first == b.second.first) {
            if (a.second.second > b.second.second)
                return true;

            else if (a.second.second == b.second.second) {
                if (a.first.first < b.first.first)
                    return true;
            }
        }
    }
    return false;
}

int main() {
    ios_base::sync_with_stdio(0);
    int n;
    cin >> n;

    for (int i = 0; i < n; i++)
        cin >> student[i].first.first >> student[i].first.second >> student[i].second.first >> student[i].second.second;

    sort(student, student + n, compare);

    for (int i = 0; i < n; i++)
        cout << student[i].first.first << "\n";

    return 0;
}


/////////////////////////////////////////
//구조체 선언해서 저장
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>


using namespace std;
const int MAX = 100000;

struct student {
    string name;
    int kor, eng, math;
};

bool compare(student a, student b) {
    if (a.kor > b.kor)
        return true;
    else if (a.kor == b.kor) {
        if (a.eng < b.eng)
            return true;
        else if (a.eng == b.eng) {
            if (a.math > b.math)
                return true;

            else if (a.math == b.math) {
                if (a.name < b.name)
                    return true;
            }
        }
    }
    return false;
}

int main() {
    ios_base::sync_with_stdio(0);
    int n;
    cin >> n;
    vector<student> v(n);

    for (int i = 0; i < n; i++)
        cin >> v[i].name >> v[i].kor >> v[i].eng >> v[i].math;

    sort(v.begin(), v.end(), compare);

    for (int i = 0; i < n; i++)
        cout << v[i].name << "\n";

    return 0;
}