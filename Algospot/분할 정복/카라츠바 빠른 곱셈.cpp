/*
O(n^2) 걸리는 알고리즘과 카라츠바 알고리즘의 시간을 직접 비교해 본다.
입력이 클수록 카라츠바가 빠르지만 입력이 작다면 O(n^2) 알고리즘을 사용하는 것이
편하다.
*/
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <chrono>
using namespace std;

//num[]의 자릿수 올림을 처리한다.
void normalize(vector<int>& num) {
	num.push_back(0);
	//자릿수 올림을 처리한다.
	for (int i = 0; i + 1 < num.size(); ++i) {
		if (num[i] < 0) {
			int borrow = (abs(num[i]) + 9) / 10;
			num[i + 1] -= borrow;
			num[i] += borrow * 10;
		}
		else {
			num[i + 1] += num[i] / 10;
			num[i] %= 10;
		}
	}
	while (num.size() > 1 && num.back() == 0)
		num.pop_back();
}

//두 긴 자연수의 곱을 반환한다.
//각 배열에는 각 수의 자릿수가 1의 자리에서부터 시작해 저장되어 있다.
//예: multiply({3,2,1}, {6,5,4}) = 123*456 = 56088 = {8,8,0,6,5}
vector<int>multiply(const vector<int>& a, const vector<int>& b) {
	vector<int> c(a.size() + b.size() + 1, 0);
	for (int i = 0; i < a.size(); ++i)
		for (int j = 0; j < b.size(); ++j)
			c[i + j] += a[i] * b[j];
	normalize(c);
	return c;
}

//a += b * (10^k);를 구현한다.
void addTo(vector<int>& a, const vector<int>& b, int k) {
	int length = b.size();
	a.resize(max(a.size() + 1, b.size() + k));

	//이렇게 함으로써 굳이 다른 vector를 선언하지 않아도 되고 간편해졌다
	for (int i = 0; i < length; ++i)
		a[i + k] += b[i];

	//정규화
	for (int i = 0; i < a.size(); ++i) {
		if (a[i] >= 10) {
			a[i + 1] += a[i] / 10;
			a[i] %= 10;
		}
	}
}

//a -= b;를 구현한다. a>=b를 가정한다.
void subFrom(vector<int>& a, const vector<int>& b) {
	int length = b.size();
	a.resize(max(a.size() + 1, b.size() + 1));

	for (int i = 0; i < length; ++i)
		a[i] -= b[i];

	//정규화
	for (int i = 0; i < a.size(); ++i) {
		if (a[i] < 0) {
			a[i] += 10;
			a[i + 1] -= 1;
		}
	}
}

//두 긴 정수의 곱을 반환한다.
vector<int> karatsuba(const vector<int>& a, const vector<int>& b) {
	int an = a.size(), bn = b.size();
	//a가 b보다 짧을 경우 둘을 바꾼다.
	if (an < bn)
		return karatsuba(b, a);
	//기저 사례: a나 b가 비어 있는 경우
	if (an == 0 || bn == 0)
		return vector<int>();
	//기저 사례: a가 비교적 짧은 경우 O(n^2) 곱셈으로 변경한다.
	if (an <= 5)
		return multiply(a, b);

	int half = an / 2;
	//a와 b를 밑에서 half자리와 나머지로 분리한다.
	vector<int> a0(a.begin(), a.begin() + half);
	vector<int> a1(a.begin() + half, a.end());
	vector<int> b0(b.begin(), b.begin() + min<int>(b.size(), half));
	vector<int> b1(b.begin() + min<int>(b.size(), half), b.end());
	//z2 = a1 * b1
	vector<int> z2 = karatsuba(a1, b1);
	//z0 = a0 * b0
	vector<int> z0 = karatsuba(a0, b0);
	//a0 = a0 + a1; b0 = b0 + b1
	addTo(a0, a1, 0);
	addTo(b0, b1, 0);
	//z1 = (a0 * b0) - z0 - z2;
	vector<int> z1 = karatsuba(a0, b0);
	subFrom(z1, z0);
	subFrom(z1, z2);
	//ret = z0 + z1 * 10^half + z2 * 10^(half * 2)
	vector<int> ret;
	addTo(ret, z0, 0);
	addTo(ret, z1, half);
	addTo(ret, z2, half + half);
	return ret;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	using namespace std::chrono;

	vector<int> a, b, result;
	string number;
	high_resolution_clock::time_point t1, t2;
	duration<double> time_span;	//시간 재기 위해

	cout << "첫번째 정수 입력: ";
	cin >> number;
	for (int i = number.size() - 1; i >= 0; i--)
		a.push_back(number[i] - '0');
	cout << "두번째 정수 입력: ";
	cin >> number;
	for (int i = number.size() - 1; i >= 0; i--)
		b.push_back(number[i] - '0');

	t1 = high_resolution_clock::now();
	result = multiply(a, b);
	for (int i = result.size() - 1; i >= 0; i--)
		cout << result[i];
	cout << "\n";
	t2 = high_resolution_clock::now();
	time_span = duration_cast<duration<double>>(t2 - t1);
	cout << "기본 곱하기 경과시간: " << time_span.count() << "초" << "\n";

	t1 = high_resolution_clock::now();
	result = karatsuba(a, b);
	t2 = high_resolution_clock::now();
	for (int i = result.size() - 1; i >= 0; i--)
		cout << result[i];
	cout << "\n";
	time_span = duration_cast<duration<double>>(t2 - t1);
	cout << "카라츠바 곱하기 경과시간: " << time_span.count() << "초" << "\n";

	return 0;
}