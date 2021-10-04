/*
네이버 코테를 대비해 투포인터를 다시 풀어봤다.
개념자체는 쉬운데 막상 코드로 구현하라고 하면 헷갈린다.
start, end를 두어서 조건순서를 어떻게 맞춰야 모든 경우를 카운트할 수 있는지를 잘 따져봐야 할 것 같다.
일단은 합이 일치하는지를 가장 마지막에 두고 생각하면 그나마 떠올리기 쉬울 것 같다.
*/

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.StringTokenizer;


public class Main {
    
	public static void main(String[] args) throws Exception {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine());
		
		int N = Integer.parseInt(st.nextToken());
		int M = Integer.parseInt(st.nextToken());
		
		int[] arr = new int[N];
		
		st = new StringTokenizer(br.readLine());
		for(int i=0; i<N; ++i) 
			arr[i] = Integer.parseInt(st.nextToken());
		
		int s=0, e= 0;
		int ans = 0, sum = 0;
		while(s < N) {
			// 합이 M보다 크거나 같으면 s 증가
			if(sum >= M)
				sum -= arr[s++];
			
			else if(e == N) break;
			else sum += arr[e++];
			
			if(sum == M) {
				ans++;
			}
		}
		
		System.out.println(ans);
	}
}