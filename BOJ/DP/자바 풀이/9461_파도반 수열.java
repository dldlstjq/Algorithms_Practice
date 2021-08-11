/*
규칙성을 찾아서 점화식을 세우면 된다.
long 타입으로 선언해야 정답이 나온다.
*/

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.StringTokenizer;


public class Main {
	
	static long cache[] = new long[101];
	static long solve(int num) {
		if(cache[num] != 0)
			return cache[num];
		
		return cache[num] = solve(num-3) + solve(num-2);
	}
	
	public static void main(String[] args) throws Exception {
		
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		
		int T = Integer.parseInt(br.readLine());
		
		cache[1] = cache[2] = cache[3] = 1;
		
		for(int i=0; i<T; ++i) {
			int N = Integer.parseInt(br.readLine());
			System.out.println(solve(N));
		}
		
	}
}