/*
2차원이 아닌 1차원 배열을 이용한 냅색문제이다.
뒤에서부터 물건을 채워나가면 앞에 값들이 최적화되지 않았기 때문에 이용 가능하다.
하지만 물건을 직접 구해야 하는 경우에는 2차원 배열을 이용해야 한다.
*/

import java.util.Scanner;

public class DP1_KnapsackTest_1Arr {

	public static void main(String[] args) {
		Scanner sc=  new Scanner(System.in);
		int N = sc.nextInt();
		int W = sc.nextInt();
		
		int[] weights = new int[N+1];
		int[] profits = new int[N+1];
		
		for(int i=1; i<=N; ++i) {
			weights[i] = sc.nextInt();
			profits[i] = sc.nextInt();
		}
		
		int[] D = new int[W+1];
		
		for(int i=1; i<=N; ++i) {
			for(int w=W; w>=weights[i]; --w) {
				D[w] = Math.max(D[w], profits[i]+D[w-weights[i]]);
			}
		}
		System.out.println(D[W]);
		
	}

}
