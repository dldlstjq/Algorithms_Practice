//유클리드 알고리즘. 최대공약수
//p<q인 입력이 들어올 경우 p%q=p이므로 다음 재귀호출은 자동으로 gcd(q,p)가 된다.
int gcd(int p, int q) {
	if (q == 0)return p;
	return gcd(q, p % q);
}
//최소 공배수
int lcm(int p, int q) {
	return p * q / gcd(p, q);
}