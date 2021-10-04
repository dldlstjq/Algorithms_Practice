/*
이 문제는 합이 딱 맞는 것이 아니라 S 이상이면 최소길이를 찾는 것이다.
while 종료조건을 e<N 으로 설정했는데 가장 마지막 인덱스에 S 이상인 경우를 세줘야 하기 때문에 e<=N으로 설정해야 하는것 같다.
*/

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.StringTokenizer;


public class Main {
	
	public static void main(String[] args) throws Exception {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine());
		
		int N = Integer.parseInt(st.nextToken());
		int S = Integer.parseInt(st.nextToken());
		
		int[] arr= new int[N];
		st = new StringTokenizer(br.readLine());
		for(int i=0; i<N; ++i)
			arr[i] = Integer.parseInt(st.nextToken());
		
		int sum=0, len=Integer.MAX_VALUE;
		int s=0,e=0;
		while(e <= N) {
			if(sum >= S)
				sum -= arr[s++];
			else if(e==N) break;
			else sum += arr[e++];
			
			if(sum >= S) {
				if(len > e-s)
					len = e-s;
			}
		}
		
		if(len == Integer.MAX_VALUE)
			System.out.println(0);
		else
			System.out.println(len);
	}

}
