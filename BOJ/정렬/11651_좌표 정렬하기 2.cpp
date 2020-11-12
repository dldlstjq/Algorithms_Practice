/*
C 풀이. 퀵소트 직접 구현.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	int x;
	int y;
}point;
point array[100001];
#define SWAP(x, y, temp) { temp = x; x = y; y = temp; }
void quick_sort(int left, int right, point* array);
int main(void) {

	int N;
	scanf("%d", &N);


	int i;
	for (i = 0; i < N; i++) {
		scanf("%d %d", &array[i].x, &array[i].y);
	}

	quick_sort(0, N - 1, array);

	for (i = 0; i < N; i++) {
		printf("%d %d\n", array[i].x, array[i].y);
	}

	return 0;
}

void quick_sort(int left, int right, point* array) {
	int pivot = left;
	int i, j = left;
	point temp;

	if (left < right) {
		for (i = left + 1; i <= right; i++) {
			if (array[i].y < array[pivot].y) {
				j++;
				SWAP(array[i], array[j], temp);
			}
			else if (array[i].y == array[pivot].y) {
				if (array[i].x < array[pivot].x) {
					j++;
					SWAP(array[i], array[j], temp);
				}
			}
		}
		SWAP(array[pivot], array[j], temp);
		pivot = j;

		quick_sort(left, pivot - 1, array);
		quick_sort(pivot + 1, right, array);
	}
}


//////////////////////////////////////
/*
C++ 풀이. 페어, sort 함수 사용. 더 간단
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>

using namespace std;

bool compare(pair<int, int>& a, pair<int, int>& b) {
	if (b.second > a.second)
		return true;
	else if (a.second == b.second) {
		if (b.first > a.first)
			return true;
		else
			return false;
	}
	else
		return false;
}

int main() {
	int n;
	int b;
	cin >> n;
	vector <pair<int, int>> p(n);

	for (int i = 0; i < n; i++)
		cin >> p[i].first >> p[i].second;

	sort(p.begin(), p.end(), compare);

	for (int i = 0; i < n; i++)
		cout << p[i].first << " " << p[i].second << "\n";

	return 0;
}
