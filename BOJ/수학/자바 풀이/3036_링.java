/*
최소 공배수를 구해서 각 반지름과 나눠주면 된다.
*/

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

public class Main {
	
	static int gcd(int a, int b) {
		if(a%b ==0) return b;
		return gcd(b, a%b);
	}
	
	static int lcd(int a, int b) {
		return a*b/gcd(a, b);
	}
	
	public static void main(String[] args) throws Exception {
		
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		int N = Integer.parseInt(br.readLine());
		
		int ring[] = new int[N];
		
		StringTokenizer st = new StringTokenizer(br.readLine(), " ");
		for(int i=0; i<N; ++i) 
			ring[i] = Integer.parseInt(st.nextToken());
		
		int first= ring[0];
		
		for(int i=1; i<N; ++i) {
			System.out.println(lcd(first, ring[i])/ring[i] +"/"+ lcd(first, ring[i])/first);
		}
	}
}