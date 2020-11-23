/*
단순하게 푸는 비율 계산 방법도 잘 생각나지 않았다.
유클리드 알고리즘을 사용하면 더 간단하게 풀 수 있다는데 두 가지 방법 다 이해가 잘 되지 않았다.
다음에 다시 볼 때 이해가 됐으면 좋겠다.
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int N;  //재료의 수

//마법의 약 레시피와 이미 넣은 재료의 양이 주어질 때, 더 넣을 재료의 양을 구한다.
vector<int> potion(const vector<int>& recipe, vector<int> put) {
    vector<int> ans = put;
    int n = recipe.size();
    vector<int> ret(n);

    //각 재료를 최소한 recipe에 적힌 만큼은 넣어야 한다.
    for (int i = 0; i < n; ++i) {
        ret[i] = max(recipe[i] - put[i], 0);
        put[i] += ret[i];
    }

    //비율이 전부 맞을 때까지 재료를 계속 추가하자
    int iter = 0;
    while (true) {
        ++iter;
        //냄비에 재료를 더 넣지 않아도 될 때까지 반복한다.
        bool ok = true;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                //i번째 재료에 의하면 모든 재료는 put[i]/recipe[i]=X배 이상은 넣어야 한다.
                //따라서 put[j]는 recipe[j]*X 이상의 정수가 되어야 한다.
                //(recipe[i]-1)을 더해주는 이유는 올림을 위해
                int required = (put[i] * recipe[j] + recipe[i] - 1) / recipe[i];

                //더 넣어야 하는가?
                if (required > put[j]) {
                    ret[j] += required - put[j];
                    put[j] = required;
                    ok = false;
                }
            }
            if (ok)
                break;
        }
    }
    return ret;
}

int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}

//분수 a/b보다 같거나 큰 최소의 자연수를 반환한다.
int ceil(int a, int b) {
    return (a + b - 1) / b;
}

vector<int> solve(const vector<int>& recipe, const vector<int>& put) {
    int n = recipe.size();
    //모든 recipe[]의 최대공약수를 구한다.
    int b = recipe[0];
    for (int i = 1; i < n; i++)
        b = gcd(b, recipe[i]);

    //최소한 b/b=1배는 만들어야 하므로, a의 초기 값을 b로 둔다.
    int a = b;
    //X를 직접 구하는 대신 ceil(put[i]*b,recipe[i])의 최대값을 구한다.
    for (int i = 0; i < n; i++)
        a = max(a, ceil(put[i] * b, recipe[i]));
    //a/b배 분량을 만들면 된다.
    vector<int> ret(n);
    for (int i = 0; i < n; i++)
        ret[i] = recipe[i] * a / b - put[i];
    return ret;
}



int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int c;
    cin >> c;

    while (c--) {
        vector<int> material;    //재료의 양
        vector<int> pot;   //이미 냄비에 넣은 양

        cin >> N;
        for (int i = 0; i < N; ++i) {
            int tmp;
            cin >> tmp;
            material.push_back(tmp);
        }
        for (int i = 0; i < N; ++i) {
            int tmp;
            cin >> tmp;
            pot.push_back(tmp);
        }

        //vector<int> ret = potion(material, pot);
        vector<int> ret = solve(material, pot);
        for (int i = 0; i < ret.size(); ++i)
            cout << ret[i] << " ";
        cout << "\n";
    }

    return 0;
}