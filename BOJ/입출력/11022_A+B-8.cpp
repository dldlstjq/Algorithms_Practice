#include <stdio.h>

int main() {

	int a1, b, t;
	scanf("%d", &t);
	for (int i = 0; i < t; i++) {
		scanf("%d %d", &a1, &b);
		printf("Case #%d: %d + %d = %d\n", i + 1, a1, b, a1 + b);
	}
	return 0;
}