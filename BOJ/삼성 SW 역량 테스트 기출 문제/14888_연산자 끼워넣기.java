/*
완전탐색 복습할 때 풀어봤던 문제이다.
이제 이 정도 수준은 잘 풀 수 있지 않나 생각한다.
*/
import java.io.*;
import java.util.StringTokenizer;

public class Main {
	static long max = Long.MIN_VALUE;
	static long min = Long.MAX_VALUE;
	
	static int N;
	static int [] A = new int [13];
	static int [] op = new int [4];
	
	static void solve(int ret, int idx, int plus, int minus, int mult, int divide) {
		if(idx == N) {
			max=Math.max(ret, max);
			min=Math.min(ret, min);
			return;
		}
		
		if(plus>0)
			solve(ret+A[idx], idx+1, plus-1,minus,mult,divide);
		if(minus>0)
			solve(ret-A[idx], idx+1, plus,minus-1,mult,divide);
		if(mult>0)
			solve(ret*A[idx], idx+1, plus,minus,mult-1,divide);
		if(divide>0)
			solve(ret/A[idx], idx+1, plus,minus,mult,divide-1);
		
	}
	
	public static void main(String[] args) throws IOException {
		// TODO Auto-generated method stub

		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine(), " ");
		
		N = Integer.parseInt(st.nextToken());
		
		st = new StringTokenizer(br.readLine(), " ");
		for(int i=0; i<N; ++i) 
			A[i] = Integer.parseInt(st.nextToken());
		
		
		st = new StringTokenizer(br.readLine(), " ");
		for(int i=0; i<4; ++i) 
			op[i] = Integer.parseInt(st.nextToken());
		
		solve(A[0], 1, op[0], op[1], op[2], op[3]);
		
		System.out.println(max);
		System.out.println(min);
		
	}
}