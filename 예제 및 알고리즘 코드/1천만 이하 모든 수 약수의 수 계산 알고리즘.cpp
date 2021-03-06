//에라토스테네스의 체로 소인수분해 정보 저장
void erathosthenes() {
    //1은 항상 예외 처리
    minFactor[0] = minFactor[1] = -1;

    //모든 숫자를 처음에는 소수로 표시
    for (int i = 2; i <= TM; ++i)
        minFactor[i] = i;

    //에라토스테네스의 체를 수행
    int sqrtn = int(sqrt(TM));
    for (int i = 2; i <= sqrtn; ++i) {
        if (minFactor[i] == i) {
            for (int j = i * i; j <= TM; j += i)
                //아직 약수를 본적 없는 숫자인 경우 i를 써 둔다
                if (minFactor[j] == j)
                    minFactor[j] = i;
        }
    }
}

//Ten Million
const int TM = 1000 * 1000 * 10;
//minFactor[i]=i의 가장 작은 소인수(i가 소수인 경우 자기 자신)
int minFactor[TM + 1];
//minFactorPower[i]=i의 소인수 분해에는 minFactor[i]가 몇 승이 포함되어 있는가?
int minFactorPower[TM + 1];
//factors[i]=i가 가진 약수의 수
int factors[TM + 1];
void getFactorsSmart() {
    factors[1] = 1;
    for (int n = 2; n <= TM; ++n) {
        //소수인 경우 약수가 두 개 밖에 없다.
        if (minFactor[n] == n) {
            minFactorPower[n] = 1;
            factors[n] = 2;
        }
        //소수가 아닌 경우, 가장 작은 소인수로 나눈 수(m)의
        //약수의 수를 응용해 n의 약수의 수를 찾는다.
        else {
            int p = minFactor[n];
            int m = n / p;
            //m이 p로 더이상 나누어 지지 않는 경우
            if (p != minFactor[m])
                minFactorPower[n] = 1;
            else
                minFactorPower[n] = minFactorPower[m] + 1;
            int a = minFactorPower[n];
            factors[n] = (factors[m] / a) * (a + 1);
        }
    }
}


//완전탐색. 1부터 TM까지 약수의 개수를 일일이 구한다.
void getFactors() {
    memset(factors, 0, sizeof(factors));
    for (int i = 1; i <= TM; ++i) {
        for (int j = i; j <= TM; j += i) {
            factors[j]++;
        }
    }
}