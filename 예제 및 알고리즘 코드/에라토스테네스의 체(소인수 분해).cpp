/*
합성수 n을 p*q로 표현될 때 한 수는 항상 √n이상이라는 점을 이용하면
n-1까지 순회하지 않고 √n까지만 순회하도록 최적화할 수 있다.

p*q로 표현 안될 때는 n까지 순회해야 할 것 같다.
*/

//에라토스테네스의 체
int n;
bool isPrime[MAX_N + 1];
//가장 단순한 형태의 에라토스테네스의 체 구현
//종료한 뒤 isPrime[i]=i가 소수인가?
void eratosthenes() {
	memset(isPrime, 1, sizeof(isPrime));
	//1은 항상 예외 처리!
	isPrime[0] = isPrime[1] = false;
	int sqrtn = int(sqrt(n));
	for (int i = 2; i <= sqrtn; ++i)
		//이 수가 아직 지워지지 않았다면
		if (isPrime[i])
			//i의 배수 j들에 대해 isPriem[j]=false로 둔다.
			//i*i미만의 배수는 이미 지워졌으므로 신경 쓰지 않는다.
			for (int j = i * i; j <= n; j += i)
				isPirme[j] = false;
}


//에라토스테네스의 체를 이용한 빠른 소인수 분해
const int MAX = 1000000;

int N; //소인수분해하고자 하는 수
//minFactor[i]=i의 가장 작은 소인수(i가 소수인 경우 자기 자신)
int minFactor[MAX];

//에라토스테네스의 체를 수행하면서 소인수분해를 위한 정보도 저장한다.
void eratosthenes2() {
    //1은 항상 예외 처리
    minFactor[0] = minFactor[1] = -1;
    //모든 숫자를 처음에는 소수로 표시해 둔다.
    for (int i = 2; i <= N; ++i)
        minFactor[i] = i;

    //에라토스테네스의 체 수행
    for (int i = 2; i <= sqrt(N); ++i) {
        if (minFactor[i] == i) {
            for (int j = i * i; j <= N; j += i) {
                //아직 약수를 본 적 없는 숫자인 경우 i를 써 둔다.
                if (minFactor[j] == j)
                    minFactor[j] = i;
            }
        }
    }
}

//2이상의 자연수 n을 소인수분해한 결과를 반환한다.
vector<int> factor(int n) {
    vector<int> ret;
    //n이 1이 될때까지 가장 작은 소인수로 나누기를 반복한다.
    while (n > 1) {
        ret.push_back(minFactor[n]);
        n /= minFactor[n];
    }
    return ret;
}
