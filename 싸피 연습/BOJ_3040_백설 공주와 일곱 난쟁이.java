/*
비트 마스킹을 사용해서 7명을 뽑아 합이 100이 되면 출력하고 종료했다.
되는 경우가 하나밖에 없기 때문에 바로 종료해도 무방하다.
9명중 7명을 뽑아야 하기 때문에 for문을 이용하면 idx로 체크가 가능하지만
그냥 부분집합을 이용하려니까 7명이 아닐때를 고려해야해서 cnt를 선언해 뽑았을 때는 +1, 아니면 카운트 하지 않았다.
*/

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

public class Solution {
	static int arr[] = new int[9];
	/*
	static void subset(int idx, int flag, int sum) {
		if(idx == 7) {
			// 7번째 까지 뽑았을 때 합이 100이 아니면 다시 시도, 아니면 출력 후 종료
			if(sum != 100)
				return;
			
			StringBuilder sb = new StringBuilder();
			for(int i=0; i<9; ++i) {
				 // & 연산 값이 0이 아니면 i번째 수 선택
				if((flag & 1<<i) !=0) {
					sb.append(arr[i]).append('\n');
				}
			}
			System.out.println(sb);
			System.exit(0);
		}
		
		
		for(int i=0; i<9; ++i) {
			if((flag & 1<<i) !=0 ) continue;
			subset(idx+1, flag|1<<i, sum+arr[i]);
		}
	}
	*/
	
	
	static void subset1(int idx, int flag, int sum, int cnt) {
		// 모든 난쟁이를 픽했는데 7명이 아니면 리턴
		if(idx == 9 && cnt != 7)
			return;
		
		// 7명 뽑았을 떄 합이 100이 아니면 리턴, 맞으면 출력 후 종료
		if(cnt == 7) {
			if(sum != 100)
				return;
			
			StringBuilder sb = new StringBuilder();
			for(int i=0; i<9; ++i) {
				 // & 연산 값이 0이 아니면 i번째 수 선택
				if((flag & 1<<i) !=0) {
					sb.append(arr[i]).append('\n');
				}
			}
			System.out.println(sb);
			System.exit(0);
		}
		
		// idx번째 비트를 1. idx번째 난쟁이 선택
        // 선택했기 때문에 합 증가, cnt+1
		flag |= 1<<idx;
		subset1(idx+1, flag, sum+arr[idx], cnt+1);
		 // 선택 안했기 때문에 idx만 1 증가
		flag ^= 1<<idx;
		subset1(idx+1, flag, sum, cnt);
	}
	

	public static void main(String[] args) throws Exception{
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		
		for(int i=0; i<9; ++i) 
			arr[i] = Integer.parseInt(br.readLine());
		
		subset1(0, 0, 0, 0);
	}
}