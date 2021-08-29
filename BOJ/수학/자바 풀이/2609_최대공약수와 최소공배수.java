/*
처음 코테 공부를 할 때는 못 푸는 문제 중 하나였는데 이제 로직을 알고나니 쉽게 해결할 수 있는 것 같다.
*/

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

public class Main {
	
	private static int lcd(int a, int b) {
		return a*b/gcd(a, b);
	}

	private static int gcd(int a, int b) {
		if(a%b == 0)return b;
		return gcd(b, a%b);
	}
	
	public static void main(String[] args) throws Exception {
		
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine(), " ");
		
		int a=0, b=0;
		
		a= Integer.parseInt(st.nextToken());
		b= Integer.parseInt(st.nextToken());
		
		System.out.println(gcd(a, b));
		System.out.println(lcd(a, b));
	}
}