/*
버블 소트라고 해서 진짜 버블 소트를 쓰면 시간초과가 난다.
머지소트를 이용하여 정렬 도중 위치가 바뀌는 경우 swap 되는 수 사이의 거리를 카운트 하면 된다.
정렬 함수의 종류와 구현을 동빈나 유튜브를 통해 공부했는데 다시 한번 정리할 필요성을 느꼈다.
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
#define MAX 500001
int arr[MAX];
int arr2[MAX];
int N;
long long cnt;
void merge(int left, int right)
{
	int mid = (left + right) / 2;

	int i = left;
	int j = mid + 1;
	int k = left;
	while (i <= mid && j <= right)
	{
		if (arr[i] <= arr[j]) {
			arr2[k++] = arr[i++];
		}

		else {
			//왼쪽 배열에 남아있는 원소들의 개수
			arr2[k++] = arr[j++];
			cnt += mid - i + 1;
		}

	}

	int tmp = i > mid ? j : i;

	while (k <= right) {
		arr2[k++] = arr[tmp++];
	}

	for (int i = left; i <= right; i++) arr[i] = arr2[i];
}

void partition(int left, int right)
{
	int mid;
	if (left < right)
	{
		mid = (left + right) / 2;
		partition(left, mid);
		partition(mid + 1, right);
		merge(left, right);
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int N;
	cin >> N;

	for (int i = 0; i < N; i++)
		cin >> arr[i];

	partition(0, N - 1);
	cout << cnt;

	return 0;
}