/*
이분 탐색을 이용하면 쉽게 푸는 문제.
1. 카드를 입력받아서 정렬
2. 찾고 싶은 카드를 이분 탐색을 통해 찾아서 있으면 1, 없으면 0 출력
*/
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int n, m;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n;
    vector<long long> card(n);

    long long int max = 0;
    for (int i = 0; i < n; i++) {
        cin >> card[i];

    }
    sort(card.begin(), card.end());

    cin >> m;
    for (int i = 0; i < m; i++) {
        int num;
        cin >> num;

        int left = 0;
        int right = n - 1;
        bool searched = false;
        while (left <= right) {
            int mid = (left + right) / 2;

            if (card[mid] > num) {
                right = mid - 1;
            }
            else if (card[mid] < num)
                left = mid + 1;
            else if (card[mid] == num) {
                searched = true;
                break;
            }


        }
        if (searched)
            cout << 1 << " ";
        else
            cout << 0 << " ";
    }


    return 0;
}