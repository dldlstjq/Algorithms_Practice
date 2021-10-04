/*
소수를 구한 뒤에 투포인터를 적용하면 된다.
소수 구하는 게 에라토스테네스인데 2중 for문에서 범위설정하는게 쉽지 않다.
c++에서는 벡터를 이용해서 했는데 여기선 cnt 변수를 써서 딱 cnt만큼만 배열을 할당했다.
*/

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.Arrays;

public class Main {
	
	static boolean[] isPrime;
	static final int MAX = 4000000+1;
	static int[] arr;
	static int N, cnt;
	
	static void eratosthenes() {
		isPrime = new boolean[MAX];
		
		Arrays.fill(isPrime, true);
		isPrime[0] = isPrime[1] = false;
		int sqrtn = (int)Math.sqrt(MAX);
		for(int i=2; i<=sqrtn; ++i) {
			if(isPrime[i])
				for(int j= i*i; j<=N; j+=i)
					isPrime[j] = false;
		}
		
		for(int i=2; i<=N; ++i)
			if(isPrime[i])
				cnt++;
	}
	
	public static void main(String[] args) throws Exception {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

		N = Integer.parseInt(br.readLine());
		eratosthenes();
		
		arr = new int[cnt];
		int idx = 0;
		for(int i=2; i<=N; ++i)
			if(isPrime[i])
				arr[idx++] = i;
		
				
		int s=0, e=0;
		int sum = 0, ans = 0;
		
		while(e <= arr.length) {
			if(sum>=N)
				sum -= arr[s++];
			else if(e == arr.length) break;
			else sum += arr[e++];
			
			if(sum == N) ans++;
		}
		
		System.out.println(ans);
	}
}