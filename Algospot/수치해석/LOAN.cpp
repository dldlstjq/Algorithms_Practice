/*
이자를 구하는 부분에서 헷갈렸던게 있어 시간이 조금 걸렸다.
이분법 구현 방법은 조금 더 연습해서 익숙해져야 할 필요가 있다고 느꼈다
*/

#include <iostream>

using namespace std;

double N;  //전세금
double P;  //연이율
int M;   //개월 수

//amount원을 연 이율 rates 퍼센트로 month월 간 한달에 monthlyPayment로 
//남았을때 대출 잔금은?
double balance(double amount, int month, double rates, double monthlyPayment) {
    double balance = amount;

    for (int i = 0; i < month; ++i) {
        //이자
        balance *= (1.0 + (rates / 12.0) * 0.01);
        //상환액을 잔금에서 뺀다
        balance -= monthlyPayment;
    }
    return balance;
}

//amount원을 연 이율 rates 퍼센트로 month월 간 갚으려면 한 달에 얼마씩 갚아야 하나? 
double payment(double amount, int month, double rates) {
    //불변조건
    //1. lo원씩 갚으면 month개월 안에 갚을 수 없다.
    //2. hi원씩 갚으면 month개월 안에 갚을 수 있다.
    double lo = 0, hi = amount * (1.0 + (rates / 12.0) * 0.01);
    for (int iter = 0; iter < 100; ++iter) {
        double mid = (lo + hi) / 2.0;
        if (balance(amount, month, rates, mid) <= 0)
            hi = mid;
        else
            lo = mid;
    }
    return hi;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T;
    cin >> T;
    while (T--) {
        cin >> N >> M >> P;

        double C = payment(N, M, P);
        cout << fixed;
        cout.precision(10);
        cout << C << "\n";
    }

    return 0;
}