/*
11969번: Breed Counting 이랑 비슷한 문제였다.
여기서는 알파벳 갯수대로 배열을 생성해 구간합을 구하면 된다.
*/

#include <iostream>
#include <string>
using namespace std;

string s;
int psum[26][200001];

int partialSum(char ch, int a, int b) {
	if (a == 0)return psum[ch - 'a'][b];
	return psum[ch - 'a'][b] - psum[ch - 'a'][a - 1];
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin >> s;

	//부분 합 계산
	for (int i = 0; i < s.length(); ++i) {
		psum[s[i] - 'a'][i]++;
		if (i >= 1) {
			for (int j = 0; j < 26; ++j) {
				psum[j][i] += psum[j][i - 1];
			}
		}

	}

	int q;
	cin >> q;
	for (int i = 0; i < q; ++i) {
		char alpa;
		int l, r;
		cin >> alpa >> l >> r;
		cout << partialSum(alpa, l, r) << "\n";
	}
	return 0;
}