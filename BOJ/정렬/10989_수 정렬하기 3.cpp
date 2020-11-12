/*
처음에 못풀어서 C 풀이참고함.
범위가 10,000,000이라서 배열 선언하면 메모리 초과 발생.
이 수는 10,000보다 작거나 같은 자연수이기 때문에 10001 배열을 만들어
입력받은 수의 인덱스에 해당하는 부분을 증가 시켜 그 수만큼 인덱스 출력시키면 정답
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int arr[10001] = { 0 };

int main()
{
	int n = 0;
	int temp;

	scanf("%d", &n);

	for (int i = 1; i <= n; i++) {
		scanf("%d", &temp);
		arr[temp]++;
	}

	for (int i = 1; i <= 10000; i++) {
		for (int j = 0; j < arr[i]; j++)
			printf("%d\n", i);
	}



	return 0;
}