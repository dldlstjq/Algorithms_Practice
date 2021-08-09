/*
소수인 두 수의 합으로 나타낼 수 있고 그 차가 최소인 것을 출력한다.
원래 n을 전역으로 선언해서 한번만 소수를 구하는데 여기서는 n이 입력할 때 마다 바뀌어서 MAX까지 다 구하는 것으로 바꿨다.
*/
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.Arrays;

public class Main {
	
	final static int MAX= 10000+1;
	static boolean isPrime[] = new boolean[MAX];

	static void eratosthenes() {
		Arrays.fill(isPrime, true);
		isPrime[0] = isPrime[1] = false;
		int sqrtn = (int) Math.sqrt(MAX);
		for(int i=2; i<=sqrtn; ++i)
			if(isPrime[i])
				for(int j= i*i; j<MAX; j+=i)	//MAX전까지 소수를 판별
					isPrime[j] = false;
	}
    
	public static void main(String[] args) throws Exception {
		
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		
		int T = Integer.parseInt(br.readLine());
		StringBuilder sb = new StringBuilder();
		eratosthenes();
        
		for(int i=0; i<T; ++i) {
			int n = Integer.parseInt(br.readLine());
			
            // 차이가 최소인 것을 출력
			int diff = Integer.MAX_VALUE;
			int a=0, b=0;
			for(int j=2; j<=n; ++j) {
				
				if(isPrime[j] && isPrime[n-j]) {
					if((int)Math.abs(j-(n-j)) < diff) {
						diff = (int)Math.abs(j-(n-j));
						a=j; b=n-j;
					}
				}
			}
			sb.append(a + " ").append(b).append("\n");
		}
		System.out.println(sb);
	}

}