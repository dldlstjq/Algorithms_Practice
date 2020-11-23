/*
개념이 쉬운 것 같아 쉽게 풀릴 것 같았는데 어려웠다.
부분 합 구하는 방법을 수학적으로 접근했다는 것에서 하나 배우는 것 같다.
그리고 주문이 겹치지 않게 주문하는 방법을 이해하는 데는 다소 시간이 필요할 것 같다.
더 자세한 설명은 블로그 참고
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


int N, K;

//box[]의 부분 합 배열 psum[]과 k가 주어질 때, 몇 가지 방법으로 살 수 있는지 반환한다.
//psum[]의 첫 번째 원소 전에 0을 삽입했다고 가정한다.
int waysToBuy(const vector<int>& psum, int k) {
    const int MOD = 20091101;
    int ret = 0;

    //psum[]의 각 값을 몇 번이나 본 적 있는지 기록한다.
    vector<long long> count(k, 0);
    for (int i = 0; i < psum.size(); ++i)
        count[psum[i]]++;

    //두 번 이상 본 적 있다면 이 값 중 두 개를 선택하는 방법의 수를 더한다.
    //즉, count[i]개 중 2개를 고를 경우의 수 (조합 공식 이용)
    for (int i = 0; i < k; ++i)
        if (count[i] >= 2)
            ret = (ret + ((count[i] * (count[i] - 1)) / 2)) % MOD;
    return ret;
}

//box[]의 부분 합 배열 psum[]과 k가 주어질 때, 겹치지 않게 몇 번이나 살 수 있는지 반환한다.
//psum[]의 첫 번째 원소 전에 0을 삽입했다고 가정한다.
int maxBuys(const vector<int>& psum, int k) {
    //ret[i]=첫 번째 상자부터 i번째 상자까지 고려했을 때 살 수 있는 최대 횟수
    vector<int> ret(psum.size(), 0);
    //prev[s]=psum[]이 s였던 마지막 위치
    vector<int>prev(k, -1);
    for (int i = 0; i < psum.size(); ++i) {
        //i번째 상자를 아예 고려하지 않는 경우
        if (i > 0)
            ret[i] = ret[i - 1];
        else
            ret[i] = 0;
        //psum[i]를 전에도 본 적이 있으면, prev[psum[i]]+1부터 여기까지 쭉 사본다.
        int loc = prev[psum[i]];
        if (loc != -1)
            ret[i] = max(ret[i], ret[loc] + 1);
        //prev[]에 현재 위치를 기록한다.
        prev[psum[i]] = i;
    }
    return ret.back();
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int c;
    cin >> c;

    while (c--) {
        cin >> N >> K;
        vector<int> box(N);
        for (int i = 0; i < N; ++i)
            cin >> box[i];

        vector<int> psum(N + 1);
        //psum[]의 첫번째 원소 이전에 0을 추가.
        //사실상 psum[-1]=0이라는 가정이 성립해서 psum[i]=psum[j-1]인지 확인할때
        //j=0인 예외 신경 안써도 된다.
        psum[0] = 0;

        //어린이들에게 인형을 모두 나눠주려면 인형의 총 수가 K의 배수여야하므로
        //부분합 구하기(K로 나눈 나머지로 값 저장)
        for (int i = 1; i < box.size(); ++i)
            psum[i] = (psum[i - 1] + box[i - 1]) % K;

        cout << waysToBuy(psum, K) << " " << maxBuys(psum, K) << "\n";
    }


    return 0;
}