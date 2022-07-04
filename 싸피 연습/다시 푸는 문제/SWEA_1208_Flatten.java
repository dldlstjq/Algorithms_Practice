/*
문제 이해를 잘못해서 시간이 걸렸다.
1. 최고, 최저점 높이를 구한 후 평탄화 작업
2. 평탄화 작업 후 최고, 최저점 높이 차이 구함
평탄화를 위한 최고, 최저점 + 높이 차이를 구하기 위한 최고, 최저점 두번 구해야 한다.
이걸 몰라서 답이 제대로 안나왔다.
*/

import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.InputStreamReader;
import java.util.StringTokenizer;


public class Solution {
	
	static class Box{
		int height; int idx;
		Box(int height, int idx){
			this.height= height;
			this.idx = idx;
		}
	}
	
	public static void main(String[] args) throws Exception {
		//System.setIn(new FileInputStream("input.txt"));
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

		for(int test_case = 1; test_case <= 10; test_case++)
		{
		
			int dump = Integer.parseInt(br.readLine());
			int box[] = new int[100];
			
			
			StringTokenizer st= new StringTokenizer(br.readLine());
			for(int i=0; i<100; ++i) {
				box[i] = Integer.parseInt(st.nextToken());
			}
			
			int diff = 0;
			Box max = new Box(0, 0);
			Box min = new Box(0, 0);
			
			for(int i=0; i<dump; ++i) {
				// 최대, 최소 높이를 구함
				max = getMax(box);
				min = getMin(box);
				
				// 평탄화 작업 수행
				box[max.idx]--;
				box[min.idx]++;
				
				// 평탄화 진행 후 다시 높이 차이 구함
				max = getMax(box);
				min = getMin(box);
				
				diff = max.height-min.height;
				if(diff <= 1) break;
			}
			
			StringBuilder sb = new StringBuilder();
			sb.append("#").append(test_case).append(" ").append(diff);
			System.out.println(sb.toString());
		}
	}

	private static Box getMax(int[] arr) {
		int max = Integer.MIN_VALUE;
		int idx = 0;
		for(int i=0; i<100; ++i) {
			if(max < arr[i]) {
				max = arr[i];
				idx = i;
			}
		}
			
		return new Box(max, idx);
	}

	private static Box getMin(int[] arr) {
		int min = Integer.MAX_VALUE;
		int idx = 0;
		for(int i=0; i<100; ++i) {
			if(min > arr[i]) {
				min = arr[i];
				idx = i;
			}
		}
		return new Box(min, idx);
	}
}
