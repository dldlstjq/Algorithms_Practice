#include <iostream>
#include <string>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    string str;

    getline(cin, str);

    for (int i = 0; i < str.size(); i++) {
        if (str[i] >= 'A' && str[i] <= 'Z') {
            if (str[i] + 13 > 'Z')
                str[i] -= 13;

            else
                str[i] += 13;
        }

        else if (str[i] >= 'a' && str[i] <= 'z') {
            if (str[i] + 13 > 'z')
                str[i] -= 13;

            else
                str[i] += 13;
        }
    }

    cout << str;

    return 0;
}