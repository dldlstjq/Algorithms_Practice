/*
0과 1일 경우는 따로 처리해주면 탑다운 방식으로 해결할 수 있다.
다시 dp를 보기 시작했는데 점화식이 잘 생각났으면 좋겠다.
*/

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.Arrays;

public class Main {
	
	static int cache[] = new int[41];
	
	static int solve(int cnt) {
		if(cnt == 0)
			return 0;
		
		if(cnt == 1)
			return 1;
		
		if(cache[cnt] != -1)
			return cache[cnt];
		
		cache[cnt] = solve(cnt-1) + solve(cnt-2);
		return cache[cnt];
	}
	
	public static void main(String[] args) throws Exception {
		
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		
		int T = Integer.parseInt(br.readLine());
		
		for(int i=0; i<T; ++i) {
			int n = Integer.parseInt(br.readLine());
			
			Arrays.fill(cache, -1);
			
			if(n == 0)
				System.out.println(1+" "+0);
			else if(n == 1)
				System.out.println(0+" "+1);
			else
				System.out.println(solve(n-1) + " "+ solve(n));
		}
	}
}