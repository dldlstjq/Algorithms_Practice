/*
너무 어렵게 생각해서 오히려 시간이 많이 걸린 문제였다.
비트가 바뀔때 카운트만 해주면 쉽게 풀리는데 일일이 비트를 바꿔주려다 시간도 많이 걸렸고
코드도 더 길어지면서 효율도 안좋아졌다.

조금은 단순하게 생각해서 접근하는 것도 좋은 방법인 것 같다.
*/

package com.ssafy.algo;

import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStreamReader;

public class Main {

	public static void main(String[] args) throws IOException {
		
		//System.setIn(new FileInputStream("input.txt"));
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		int T;
		T= Integer.parseInt(br.readLine());
	
		for(int test_case = 1; test_case <= T; test_case++)
		{
			int ret = 0;	
			String str = br.readLine();	// 입력으로 받아온 비트
			
			char ch = '0';
			
			for(int i=0; i<str.length(); ++i) {
				if(str.charAt(i) != ch) {
					ch = str.charAt(i);
					ret++;
				}
			}
			
			StringBuilder sb = new StringBuilder();	// 정답 출력
			sb.append("#").append(test_case).append(" "+ret);
			System.out.println(sb.toString());
		}
	}

}
