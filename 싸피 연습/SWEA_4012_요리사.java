/*
백준에서 스타트와 링크라는 거의 똑같은 문제를 풀어봐서 쉽게 해결할 수 있었다.
N이 최대 16이라서 그 절반인 16C8은 시간내에 해결될거라고 생각했다.
조합을 이용해 절반을 뽑은 뒤 재료 시너지를 구해 차이가 최소를 구하면 된다.
조합은 재귀를 이용해도 되지만 nextPermutation으로 풀어봤다.
*/

import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.StringTokenizer;

public class Solution {
	
	static int N;
	static int ingredient[][];
	
	public static void main(String[] args) throws Exception{
		//System.setIn(new FileInputStream("sample_input.txt"));
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		
		int T = Integer.parseInt(br.readLine());
		
		
		for(int test_case = 1; test_case <= T; test_case++)
		{
			N = Integer.parseInt(br.readLine());
			
			ingredient = new int[N][N];
			
			for(int i=0; i<N; ++i) {
				StringTokenizer st = new StringTokenizer(br.readLine(), " ");
				for(int j=0; j<N; ++j) {
					ingredient[i][j] = Integer.parseInt(st.nextToken());
				}
			}
			
			// 조합을 통해 가능한 모든 N/2개를 뽑고 남은 것들과 재료조합을 비교해 최소값을 구한다.
			int comb[] = new int[N];
			for(int i=N-1; i>=N-N/2; --i)
				comb[i] = 1;
			
			int diff = Integer.MAX_VALUE;
			do {
				ArrayList<Integer> A = new ArrayList<>();
				ArrayList<Integer> B = new ArrayList<>();
				// 재료를 반반 나눔
				for(int i=0; i<N; ++i) {
					if(comb[i] == 1) 
						A.add(i);
					else
						B.add(i);
				}
				
				// A, B의 모든 재료 시너지 합
				int sumA = synergy(A);
				int sumB = synergy(B);
				
				diff = Math.min(diff, Math.abs(sumA-sumB));
				
			}while(np(comb));
			
			System.out.printf("#%d %d%n", test_case, diff);
		}
	}
	
	private static int synergy(ArrayList<Integer> arr){
		int sum = 0;
		// 모든 재료조합의 시너지를 구한다.
		for(int i=0; i<arr.size(); ++i) {
			for(int j=0; j<arr.size(); ++j) {
				sum += ingredient[arr.get(i)][arr.get(j)];
			}
		}
		return sum;
	}

	private static boolean np(int[] comb) {
		int N = comb.length;
		int i = N-1;
		while(i>0 && comb[i-1] >= comb[i]) --i;
		if(i==0)
			return false;
		
		int j= N-1;
		while(comb[i-1] >= comb[j]) --j;
		swap(comb, i-1, j);
		
		int k=N-1;
		while(i<k)
			swap(comb, i++, k--);
		return true;
	}

	private static void swap(int[] comb, int i, int j) {
		int tmp = comb[i];
		comb[i] = comb[j];
		comb[j] = tmp;
	}
}