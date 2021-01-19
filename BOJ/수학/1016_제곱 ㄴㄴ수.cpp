/*
문제는 이해가 갔는데 풀이가 어렵다.

백만짜리 배열을 선언하고
#
"i"는 2~max까지 순회하며 다음을 반복

##
(i*i) * j 는 제곱 YES수이므로
배열[(i*i) * j]를 true로 바꾼다.
다만 (i*i) * j의 값을 min~max 사이로 해싱한다 민다
j+=1.
##
#
마지막에 배열에서 false가 몇개인지 샌다

대충 풀이가 이렇다는데 코드에서 start 계산이 왜 하는지,
true를 만들어주는 인덱스 계산이 왜 저렇게 되는지 이해가 잘 안된다.

min~max 사이의 범위로 들어오게 만들게 하기 위해 그런거 같다.
*/

#include <iostream> 
using namespace std;

bool isSqr[1000001];

int main() {
	long long min, max;
	cin >> min >> max;

	for (long long i = 2; i * i <= max; i++) {
		long long start = min / (i * i);
		if (start * i * i != min) start++;
		for (long long j = start; i * i * j <= max; j++) {
			isSqr[i * i * j - min] = true;
		}
	}
	int count = 0;
	for (int i = 0; i < max - min + 1; i++) {
		if (!isSqr[i]) count++;
	}
	cout << count << endl;

	return 0;
}


/*다른풀이
우선. max와 min 사이 숫자의 갯수는 최대 1,000,000개 입니다.

bool 타입으로 result[1000001] 의 배열을 선언합니다.
그다음 제곱 들을 저장할 수의 배열을 선언합니다.
long long 타입으로 num[1000002]

<cmath> 헤더의 sqrt 함수를 통해서 min과 max 사이의 가장큰 제곱근(sq_max)을 구해줍니다.

구한 제곱근 보다 작고 2보다 큰 숫자들의
제곱을 num 배열에 넣고 그것의 개수를 셉니다(cntNum)
제곱들의 갯수만큼 for문을 돌립니다.

for문 내부에서
min과 max사이에 제곱(num[i])으로 나누어 떨어지는 가장 작은 수를 div_min에 넣고
div_min + num[i] 의 갯수를 구해줍니다.

중복 체크는 result 배열을 이용합니다.
중복 되지 않은 true의 개수를 count 변수로 구합니다.

마지막 출력은 max-min + 1 갯수에서 result 배열에서의 true의 개수를 빼줍니다.
*/

#include<iostream>
#include<cmath>

using namespace std;

bool result[1000001] = { false };  //max - min 사이의 최대 갯수
long long num[1000001] = { 0 };    //제곱들 저장

int main(void) {
    long long min;
    long long max;

    cin >> min >> max;

    long long sq_max = (long long)sqrt(max);    //범위 내 제곱값이 될 수 있는 가장 큰수
    long long cntNum = 0;                        //제곱들의 개수
    for (long long i = 2; i <= sq_max; i++) {        //제곱들 저장
        num[i] = i * i;
        cntNum++;
    }

    int count = 0; // max와  min 사이에 제곱의 수로 나누어 떨어지는 수.

    for (int i = 2; i < cntNum + 2; i++) {

        long long div_min = min;                 //div_min을 범위의 최소값 min으로 둔 후 
        if (div_min % num[i] != 0) {               //div_min이 제곱수로 나누어 지지 않으면 
            div_min = (min / num[i] + 1) * num[i]; //최소값을 제곱근으로 나눈 몫에 +1 후 다시 곱해서 범위 안의 값으로 바꾼다.
        }

        for (long long tmp = div_min; tmp <= max; tmp += num[i]) { //num[i]로 나누어지는 div_min을 count 한다.
            if (!result[tmp - min]) {
                result[tmp - min] = true;
                count++;
            }
        }

    }
    cout << max - min - count + 1;
    return 0;
}