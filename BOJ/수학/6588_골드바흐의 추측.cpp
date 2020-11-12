/*
에라토스테네스의 체 활용한 문제.
*/

#include <iostream>
#include <cmath>

using namespace std;

int arr[1000001];
int n;


int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int a = 0, b = 0;
	bool flag = false;	//합 여부 체크

	//에라토스테네스의 체
	for (int i = 2; i <= 1000000; i++) {
		arr[i] = i;
	}

	for (int i = 2; i <= sqrt(1000000); i++) {
		if (arr[i] == 0)continue;
		for (int j = i + i; j <= 1000000; j += i) {
			arr[j] = 0;
		}
	}

	cin >> n;
	while (n != 0) {
		//3부터 돌면서 계산. 홀수이므로 2씩 증가. 
		//0이 아니고 합이 n이면 flag로 합 여부 체크
		for (int i = 3; i < n; i += 2) {
			if (arr[i] != 0 && arr[n - i] != 0 && arr[i] + arr[n - i] == n) {
				flag = true;
				a = arr[i];
				b = arr[n - i];
				break;
			}

		}
		if (flag == true)
			cout << n << " = " << a << " + " << b << '\n';
		else
			cout << "Goldbach's conjecture is wrong." << '\n';

		flag = false;
		a = b = 0;


		cin >> n;
	}

	/* 더 간단한 풀이
	while(1) {
    scanf("%d", &n);
    if (n == 0) break;
    i = 3;
    while(1) {
      if (n - i < 0) {
        printf("Goldbach's conjecture is wrong.\n");
        break;
      }
      if (check[i] == true && check[n-i] == true) {
        printf("%d = %d + %d\n", n, i, n-i);
        break;
      }
      i++;
    }
  }
	*/
	return 0;
}