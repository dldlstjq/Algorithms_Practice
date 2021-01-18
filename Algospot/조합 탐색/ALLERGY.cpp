/*
slowSearch와 search의 코드 구성은 크게 다르지 않습니다.
하지만 탐색순서가 다르기 때문에 다음과 같은 차이가 생겼습니다.

1. search()는 항상 모든 친구가 먹을 음식이 있는 조합만을 찾아냅니다.
   하지만 slowSearch()는 마지막 조각까지 결정한 뒤에도 배고픈 친구가 남는 경우들도 모두 탐색하게됩니다.

2. search()는 한 번 호출될 때마다 항상 음식을 하나 하게 됩니다.
   (즉, 음식을 한다는 말은 음식이 필요한 친구가 반드시 있다는 의미)
   반면 slowSearch()는 음식을 하지 않고도 재귀호출을 할 수 있습니다.(반드시 필요하지 않은 음식을 만드는 경우도 있다)
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <map>

using namespace std;

int n, m;
//canEat[i]: i번 친구가 먹을 수 있는 음식의 집합
//eaters[i]: i번 음식을 먹을 수 있는 친구들의 집합
vector<int> canEat[50], eaters[50];
int best;

/*
//food:이번에 고려해야 할 음식의 번호
//edible: 지금까지 고른 음식 중 i번 친구가 먹을 수 있는 음식의 수
//chosen:지금까지 고른 음식의 수
void slowSearch(int food, vector<int> &edible, int chosen)
{
		//간단한 가지치기
		if (chosen >= best)
			   return;
		//기저 사례:모든 음식에 대해 만들지 여부를 결정했으면
		//모든 친구가 음식을 먹을 수 있는지 확인하고 그렇다면 최적해 갱신
		if (food == foodNum)
		{
			   if (find(edible.begin(), edible.end(), 0) == edible.end())
					best = chosen;
			   return;
		}
		//food를 만들지 않는 경우
		slowSearch(food + 1, edible, chosen);
		//food를 만드는 경우
		for (int j = 0; j < eaters[food].size(); j++)
			   edible[eaters[food][j]]++;
		slowSearch(food, edible, chosen + 1);
		for (int j = 0; j < eaters[food].size(); j++)
			   edible[eaters[food][j]]--;
}
*/


//chosen: 지금까지 선택한 음식의 수
//edible[i]: 지금까지 고른 음식 중 i번 친구가 먹을 수 있는 음식의 수
void search(vector<int>& edible, int chosen) {
	//간단한 가지치기
	if (chosen >= best)return;
	//아직 먹을 음식이 없는 첫 번째 친구를 찾는다.
	int first = 0;
	while (first < n && edible[first]>0)
		++first;
	//모든 친구가 먹을 음식이 있는 경우 종료한다.
	if (first == n) {
		best = chosen;
		return;
	}
	//이 친구가 먹을 수 있는 음식을 하나 만든다.
	for (int i = 0; i < canEat[first].size(); ++i) {
		int food = canEat[first][i];
		for (int j = 0; j < eaters[food].size(); ++j)
			edible[eaters[food][j]]++;
		search(edible, chosen + 1);
		for (int j = 0; j < eaters[food].size(); ++j)
			edible[eaters[food][j]]--;
	}
}

void clear() {
	for (int i = 0; i < m; ++i)
		eaters[i].clear();
	for (int i = 0; i < n; ++i)
		canEat[i].clear();
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int c;
	cin >> c;
	while (c--) {
		cin >> n >> m;
		best = m;

		map<string, int> index;	//canEat과 eaters 벡터에 추가할 때 필요
		for (int i = 0; i < n; ++i) {
			string name;
			cin >> name;
			index[name] = i;	//해당 이름을 가진 사람은 i번째 인덱스이다.
		}

		for (int i = 0; i < m; ++i) {
			int people;
			cin >> people;
			for (int j = 0; j < people; ++j) {
				string name;
				cin >> name;
				//i번 음식을 먹을 수 있는 사람들
				eaters[i].push_back(index[name]);
				//현재 이 사람이 먹을 수 있는 음식 목록에 i번 음식 추가
				canEat[index[name]].push_back(i);
			}
		}
		vector<int> edible(n, 0);	//아직 음식을 고르지 않았으므로 모두 0
		search(edible, 0);
		cout << best << "\n";
		clear();
	}

	return 0;
}