/*
분할정복 중 하나이다.
반복문을 이용한 재귀가 익숙해져 반복문으로 해결을 많이 했는데 4개의 재귀를 따로 호출해도 된다.

*/

import java.io.BufferedReader;
import java.io.InputStreamReader;

public class Main {
	
	static char arr[][];
	
	// 다 같은 숫자로 되어있는지 확인
	static boolean check(int r, int c, int n) {
		for(int i=r; i<r+n; ++i) {
			for(int j=c; j<c+n; ++j) {
				if( arr[i][j] != arr[r][c])
					return false;
			}
		}
		return true;
	}
	
	// 쿼드트리 분할 정복
	private static void quadtree(int r, int c, int n) {
		// 기저조건: 다 같은 숫자이면 숫자 출력후 종료
		if(check(r, c, n)) {
			System.out.print(arr[r][c]);
			return;
		}
		
		System.out.print('(');
		// 절반씩 줄어든다.
		int half = n/2;
		quadtree(r, c, half);
		quadtree(r, c+half, half);
		quadtree(r+half, c, half);
		quadtree(r+half, c+half, half);
		System.out.print(')');
	}
	
	public static void main(String[] args) throws Exception{
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
//		StringTokenizer st = new StringTokenizer(br.readLine(), " ");

		int N = Integer.parseInt(br.readLine());
		arr = new char[N][N];
		
		for(int i=0; i<N; ++i)
			arr[i] = br.readLine().toCharArray();
		
		quadtree(0, 0, N);
	}
}