/*
2021.07.24
너무 오랜만에 푸는 dp라 공식이 잘 생각나지 않았다.
더구나 자바로 하니 c++과 다른 문법에 에러도 많이 났다.
우선 점화식 자체를 제대로 세우지 못했고 인덱스 설정도 잘못해서 에러가 많이 났다.
간단한 dp이지만 dp도 어느정도 풀어서 감을 계속 가져가야겠다.
*/
import java.io.*;
import java.util.Arrays;
import java.util.StringTokenizer;

public class Main {

	final static int MAX = 15+1;
	static int N;
	static int [] T = new int[MAX];
	static int [] P = new int[MAX];
	static int [] cache = new int[MAX];
	
	static int solve(int day) {
		if(day > N+1) 
			return -987654321;
		 
		if(day == N+1)
			return 0;
		
		if(cache[day] != -1)return cache[day];
		cache[day] = Math.max(solve(day+1), solve(day+T[day])+P[day]);
		return cache[day];
	}
	
	public static void main(String[] args) throws IOException {
		// TODO Auto-generated method stub

		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine(), " ");
		
		Arrays.fill(cache, -1);
		
		N = Integer.parseInt(st.nextToken());
		
		for(int i=1; i<=N; ++i) {
			st = new StringTokenizer(br.readLine(), " ");
			T[i] = Integer.parseInt(st.nextToken());
			P[i] = Integer.parseInt(st.nextToken());
		}
		System.out.println(solve(1));
		
	}
}
