//아직 c밖에 모를때 c로 푼것
//2019년 1월 10일에 푼것

#include <stdio.h>

int main()
{
	int n = 0, i, j;

	scanf("%d", &n);
	for (i = 0; i < n; i++) {
		for (j = 0; j <= i; j++) {
			printf("*");
		}
		printf("\n");
	}

	return 0;
}