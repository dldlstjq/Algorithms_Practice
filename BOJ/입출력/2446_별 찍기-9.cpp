#include <iostream>
#include <math.h>

using namespace std;

//내 풀이
int main() {
	std::ios_base::sync_with_stdio(false);
	int n;

	cin >> n;

	for (int i = -1 * (n - 1); i <= n - 1; i++) {
		for (int j = -1 * (n - 1); j <= n - 1; j++) {
			if (abs(i) >= abs(j))
				cout << "*";
			else if (j > abs(i))
				break;
			else
				cout << " ";
		}

		cout << '\n';
	}
	return 0;
}


///////다른 사람풀이
int main() {

	int i, j, k;
	int n;
	scanf("%d", &n);

	for (i = 0; i < n; i++) {
		for (j = 0; j < i; j++)
			printf(" ");

		for (k = 2 * (n - i - 1); k >= 0; k--)
			printf("*");

		printf("\n");
	}

	for (i = 2; i <= n; i++) {

		for (j = 1; j <= n - i; j++)
			printf(" ");

		for (k = 0; k <= 2 * (i - 1); k++)
			printf("*");

		printf("\n");
	}


	return 0;
}