//내 풀이. DP를 잘 모르는 상태에서 막무가내 식으로 품
#include <stdio.h>

int d[1000001];

int main() {
	int n = 0;

	d[0] = 0;
	d[1] = 0;
	d[2] = 1;
	d[3] = 1;
	scanf("%d", &n);

	for (int i = 4; i <= n; i++) {
		//2나 3으로 나누어 지는 경우 
		//나눴을 때랑 1 뺐을 때의 해당 인덱스의 값이 작은 쪽 +1
		//ex)10의 경우 2로 나누면 
		//10->5->4->2->1 4번이지만 
		//1을 빼고 계산하면 10->9->3->1 3번이면 됨.
		if (i % 3 == 0) {
			if (d[i - 1] > d[i / 3])
				d[i] = d[i / 3] + 1;
			else
				d[i] = d[i - 1] + 1;

			continue;
		}
		else if (i % 2 == 0) {
			if (d[i - 1] > d[i / 2])
				d[i] = d[i / 2] + 1;
			else
				d[i] = d[i - 1] + 1;
			continue;
		}
		//2나 3으로 나누어 지지 않으면 1을 뻬야 하므로 그 전의 계산에 1이 더해짐
		else
			d[i] = d[i - 1] + 1;
	}

	printf("%d\n", d[n]);

	return 0;
}



/////////////다른 사람 풀이. 더 작은 값이 있는 쪽으로 계산해서 풀어나감. 더 간단
#include <stdio.h>

int d[1000001];

int min(int a, int b) {
	return a < b ? a : b;
}

int main() {
	int n = 0;

	d[0] = 0;
	d[1] = 0;
	scanf("%d", &n);

	for (int i = 2; i <= n; i++) {
		if (i % 3 == 0) {
			d[i] = min(d[i / 3], d[i - 1]) + 1;
			continue;
		}
		else if (i % 2 == 0) {
			d[i] = min(d[i / 2], d[i - 1]) + 1;
			continue;
		}
		//2나 3으로 나누어 지지 않으면 1을 뻬야 하므로 그 전의 계산에 1이 더해짐
		else
			d[i] = d[i - 1] + 1;
	}
	printf("%d\n", d[n]);

	return 0;
}