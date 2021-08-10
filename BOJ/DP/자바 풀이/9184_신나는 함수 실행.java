/*
함수는 함수대로 하고 메모이제이션을 해야 하는데 여기서 잘 몰랐다.
함수 리턴시에 계속해서 배열에 저장하고 그걸 리턴해주면 쉽게 구현할 수 있다.
오랜만에 하다보니 아직까지 메모이제이션 개념이 잘 잡히지 않는데 이번에 dp를 풀면서 감을 익혀나가야겠다.
*/

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.Arrays;
import java.util.StringTokenizer;

public class Main {
	
	static int cache[][][] = new int[21][21][21];
	
	static boolean inRange(int a, int b, int c) {
		return 0 <= a && a <= 20 && 0 <= b && b <= 20 && 0 <= c && c <= 20; 
	}
	
	static int w(int a, int b, int c) {
		if(inRange(a,b,c) && cache[a][b][c] != 0)
			return cache[a][b][c];
		
		if(a<=0 || b<=0 || c<=0)
			return 1;
		
		if(a>20 || b>20 || c>20)
			return cache[20][20][20] = w(20, 20, 20);
		
		if(a<b && b<c)
			return cache[a][b][c] = w(a, b, c-1) + w(a, b-1, c-1) - w(a, b-1, c);
		
		return  cache[a][b][c] = w(a-1, b, c) + w(a-1, b-1, c) + w(a-1, b, c-1) - w(a-1, b-1, c-1);
	}
	
	public static void main(String[] args) throws Exception {
		
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		
		while(true) {
			StringTokenizer st = new StringTokenizer(br.readLine()," ");
			
			int a = Integer.parseInt(st.nextToken());
			int b = Integer.parseInt(st.nextToken());
			int c = Integer.parseInt(st.nextToken());
			
			if(a == -1 && b == -1 && c == -1)
				break;
			
			System.out.printf("w(%d, %d, %d) = %d\n", a, b, c, w(a,b,c));
		}
	}
}