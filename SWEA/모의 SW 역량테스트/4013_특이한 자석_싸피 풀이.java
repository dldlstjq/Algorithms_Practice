/*
백준 기출 문제랑 똑같은 문제인 것 같은데 여기서 나온 문제가 실제 시험에서 나온 것 같다.
그래서 모의 SW 역량테스트를 풀어보라고 하는 것 같다.
백준 톱니바퀴랑 같은 문제여서 그렇게 어렵진 않았고 회전하기 전에 회전할 자석을 모두 알고 있어야 한다.
점수가 1,2,4,8 이어서 비트 연산으로 하면 더 깔끔하게 점수 계산이 가능하다.
*/

import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.InputStreamReader;
import java.util.StringTokenizer;


public class Solution {
	
	static int N, K;
	static int[][] magnet;	// 자석 저장
	static int[] info;	// 회전 정보 저장

	public static void main(String[] args) throws Exception {
		//System.setIn(new FileInputStream("sample_input.txt"));
		
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		
		int T;
		T= Integer.parseInt(br.readLine());	

		for(int test_case = 1; test_case <= T; test_case++)
		{
			K = Integer.parseInt(br.readLine());
			
			magnet = new int[4][8];	// 1번행부터 1번자석
			
			StringTokenizer st = null;
			for(int i=0; i<4; ++i) {
				st = new StringTokenizer(br.readLine());
				for(int j=0; j<8; ++j)
					magnet[i][j] = Integer.parseInt(st.nextToken());
			}
			
			for(int i=0; i<K; ++i) {
				st = new StringTokenizer(br.readLine());
				int num = Integer.parseInt(st.nextToken())-1;	// 인덱스 맞춰줌
				int dir = Integer.parseInt(st.nextToken());
				
				searchMagnet(num, dir);	// 회전할 자석 조사
				rotate();	// 회전
			}
			
			StringBuilder sb = new StringBuilder();
			sb.append("#").append(test_case).append(" "+getScore());
			System.out.println(sb);
		}
	}

	private static int getScore() {
		int sum = 0;
		for(int i=0; i<4; ++i)
			if(magnet[i][0] == 1)
				sum+= 1<<i;
		return sum;
	}
	
	private static void rotate() {
		for(int i=0; i<4; ++i) {
			if(info[i] == 0) continue;	// 회전하지 않음
			
			// 시계방향이 1
			if(info[i] == 1) {
				int tmp = magnet[i][7];
				for(int k=7; k>=1; --k)
					magnet[i][k] = magnet[i][k-1];
				magnet[i][0] = tmp;
			}
			// 반시계 방향이 -1
			else {
				int tmp = magnet[i][0];
				for(int k=0; k<=6; ++k)
					magnet[i][k] = magnet[i][k+1];
				magnet[i][7] = tmp;
			}
		}
	}

	private static void searchMagnet(int num, int dir) {
		// N 극이 0 으로, S 극이 1
		// 2번과 그 다음 6번이 맞물려 있다.
		
		info = new int[4];
		info[num] = dir;	// num번째 자석의 회전정보 저장
		// 오른쪽 자석의 극 조사
		for(int i=num+1; i<4; ++i) {
			// 이전 자석의 회전 정보가 있고, 이전자석의 2번과 현재 자석의 6번이 다른 극이면 회전
			if(info[i-1] !=0 && magnet[i-1][2] != magnet[i][6])
				info[i] = info[i-1]*-1;
		}
		
		// 왼쪽 자석 조사
		for(int i=num-1; i>=0; --i) {
			// 이전 자석의 회전 정보가 있고, 현재자석의 2번과 다음 자석의 6번이 다른 극이면 회전
			if(info[i+1] !=0 && magnet[i][2] != magnet[i+1][6])
				info[i] = info[i+1]*-1;
		}
	}
}