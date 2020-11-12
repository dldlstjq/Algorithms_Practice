/*
카드를 입력받아서 정렬.
정렬한 카드에서 현재위치와 다음 위치의 카드가 같으면 카운트 증가.
그 중 제일 최대인 것 출력
*/

#include<iostream>
#include<algorithm>
using namespace std;
long long card[1000000];
int main()
{
	cin.tie(0);
	cin.sync_with_stdio(false);

	int n;
	cin >> n;
	for (int i = 0; i < n; i++)
		cin >> card[i];

	sort(card, card + n);
	//카드세기위한 변수, 갯수를 비교하기위한변수
	int cnt = 1, max = 0, index = 0;
	for (int i = 0; i < n - 1; i++)
	{
		if (card[i] == card[i + 1])
		{
			cnt++;
			if (cnt > max)
			{
				max = cnt;
				index = i;
			}
		}
		else
			//0이아닌 1로초기화!
			cnt = 1;
	}
	cout << card[index] << '\n';

}