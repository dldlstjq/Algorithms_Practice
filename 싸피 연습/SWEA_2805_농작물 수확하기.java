/*
마름모 꼴로 배열을 순회하면 된다.
규칙만 잘 찾으면 어렵지 않게 풀 수 있는 것 같다.
*/

package com.ssafy.algo;

import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.InputStreamReader;

public class Main_2805_이인섭 {
	
	
	public static void main(String[] args) throws Exception {
		
//		System.setIn(new FileInputStream("input.txt"));
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		
		int T = Integer.parseInt(br.readLine());
		
		for(int test_case = 1; test_case <= T; test_case++)
		{
			int N = Integer.parseInt(br.readLine());
			int [][]arr= new int[N][N];
			
			for(int i=0; i<N; ++i) {
				String str = br.readLine();
				for(int j=0; j<N; ++j)
					arr[i][j] = str.charAt(j)-'0';
			}
			
			int ret = 0;
			int cnt = 0;
			
			for(int i=0; i<N; ++i) {
				for(int j=N/2-cnt; j<=N/2+cnt; ++j) 
					ret += arr[i][j];
				// 행이 N/2가 아니면 cnt를 1씩 증가하고 N/2에 오면 다시 cnt를 감소
				if(i >= N/2)
					cnt--;
				else 
					cnt++;
			}
			
			StringBuilder sb = new StringBuilder();
			sb.append("#").append(test_case).append(' ').append(ret);
			System.out.println(sb);
		}
	}

}
