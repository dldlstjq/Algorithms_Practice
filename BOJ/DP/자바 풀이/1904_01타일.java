/*
00인 타일 1개, 1인 타일 1개로 모든게 조합 가능하다.
그래서 길이 2를 뺀 것과 1개 뺀 것을 계속 더해가면 된다.
배열 갯수를 백만개를 선언해도 되지만 크기를 3개만 선언해서 모듈연산을 통해 이용해도 된다.
*/

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.Arrays;

public class Main {
	
	static final int MOD = 15746;
	static final int MAX = 1000000+1;
	static int cache[] = new int[MAX];
	
	static int solve(int num) {
		if(num <= 1)
			return 1;
		
		if(cache[num] != -1)
			return cache[num]%MOD;
		// 00 2개인것 하나, 1 있는 것 하나로 조합 가능
		cache[num] = solve(num-2)%MOD + solve(num-1)%MOD;
		return cache[num]%MOD;
	}
	
	public static void main(String[] args) throws Exception {
		
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		
		int n = Integer.parseInt(br.readLine());
		Arrays.fill(cache, -1);
		System.out.println(solve(n));
	}
}