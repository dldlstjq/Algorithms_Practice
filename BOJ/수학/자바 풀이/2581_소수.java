/*
에라토스테네스의 체로 소수를 구한 다음 최솟값과 합을 구하면 된다.
에라토스테네스도 잠깐 관련 문제를 안 풀면 잊어먹어서 조금씩 계속 봐야할 필요성이 있는 것 같다.
*/

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.Arrays;

public class Main {
	
	final static int MAX= 10000+1;
	static boolean isPrime[] = new boolean[MAX];
	static int M, N;
    
	static void eratosthenes() {
		Arrays.fill(isPrime, true);
		isPrime[0] = isPrime[1] = false;
		int sqrtn = (int) Math.sqrt(MAX);
		for(int i=2; i<=sqrtn; ++i)
			if(isPrime[i])
				for(int j= i*i; j<=N; j+=i)
					isPrime[j] = false;
	}

	public static void main(String[] args) throws Exception {
		
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		
		M = Integer.parseInt(br.readLine());
		N = Integer.parseInt(br.readLine());
		
		eratosthenes();
		
		int sum = 0;
		int min_value = Integer.MAX_VALUE;
		
		for(int i=M; i<=N; ++i) {
			if(!isPrime[i])
				continue;
			sum += i;
			min_value = Math.min(min_value, i);
		}
		
		if(sum ==0)
			System.out.println(-1);
		else
			System.out.printf("%d%n%d", sum, min_value);
	}
}