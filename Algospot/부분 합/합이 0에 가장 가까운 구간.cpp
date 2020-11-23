/*
합이 0에 가장 가까운 구간의 값 구하기
부분 합 구해서 오름차순 정렬 한 다음 인접한 값의 차가 가장 적은 것이 답
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MIN = 987654321;

int compare(const void* num1, const void* num2) //ascending
{
    return (*(int*)num1 - *(int*)num2);
}

int rangeValue(vector<int>& v) {
    int psum[50] = { 0 };
    psum[0] = v[0];

    //부분합 구함
    for (int i = 1; i < v.size(); ++i) {
        psum[i] = psum[i - 1] + v[i];
    }

    //부분합 정렬
    qsort(psum, v.size(), sizeof(int), compare);
    //sort(psum, psum+v.size());

    //0에 가깝다는 말은 psum[]의 두 값의 차이가 가장 적다는 뜻
    int ret = MIN;
    for (int i = 1; i < v.size(); ++i) {
        ret = min(psum[i] - psum[i - 1], ret);
    }
    return ret;
}

void initialize(vector<int>& v)
{
    v.push_back(-14);
    v.push_back(7);
    v.push_back(2);
    v.push_back(3);
    v.push_back(-8);
    v.push_back(4);
    v.push_back(-6);
    v.push_back(8);
    v.push_back(9);
    v.push_back(11);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    vector<int> v;
    initialize(v);
    cout << "0에 제일 근접한 부분합: " << rangeValue(v) << "\n";

    return 0;
}