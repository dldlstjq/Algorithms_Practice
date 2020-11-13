/*
10815번이랑 비슷한 문제지만 이번엔 카드가 몇 개 있는지 찾는 문제이다.
똑같이 이분탐색을 통해서 풀었는데 문제는 시간초과가 났다.
해결을 못해서 찾아보니 lower_bound, upper_bound라는 것을 사용했다.

lower_bound는 찾고자 하는 값 이상이 처음 나타나는 위치,
upper_bound는 찾고자 하는 값보다 큰 값이 처음으로 나타나는 위치를 반환한다.
따라서 upper_bound에서 lower_bound를 빼주면 쉽게 풀 수 있었다.
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int N;
    cin >> N;
    vector<int> v(N);

    for (int i = 0; i < N; i++)
        cin >> v[i]; \
        sort(v.begin(), v.end());

    int M;
    cin >> M;
    for (int i = 0; i < M; i++)
    {
        int num;
        cin >> num;
        cout << upper_bound(v.begin(), v.end(), num) - lower_bound(v.begin(), v.end(), num) << " ";
    }
    cout << "\n";
    return 0;
}