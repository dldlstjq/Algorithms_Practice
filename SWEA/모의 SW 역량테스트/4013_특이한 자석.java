/*
자석도 4개로 정해져있고 자석의 극도 8개로 정해져있어 그리 어렵지 않았다.
연쇄적으로 회전한다는 부분, 시계, 반시계 회전만 잘 설정하면 빨리 풀 수 있는 문제인것 같다.

 */

import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

public class Solution {

	static int K;
	static int[][] magnet;
	static int score;

	public static void main(String[] args) throws IOException {
		//System.setIn(new FileInputStream("sample_input.txt"));

		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

		int T = Integer.parseInt(br.readLine());


		for(int test_case = 1; test_case <= T; test_case++)
		{
			K = Integer.parseInt(br.readLine());

			magnet = new int[4][8];

			StringTokenizer st= null;
			for(int i=0; i<4; ++i) {
				st = new StringTokenizer(br.readLine());
				for(int j=0; j<8; ++j) {
					magnet[i][j] = Integer.parseInt(st.nextToken());
				}
			}

			for(int i=0; i<K; ++i) {
				st = new StringTokenizer(br.readLine());
				int n = Integer.parseInt(st.nextToken());
				int d = Integer.parseInt(st.nextToken());

				rotate(n-1, d);
			}

			score = 0;
			score += magnet[0][0]==0? 0 : 1;
			score += magnet[1][0]==0? 0 : 2;
			score += magnet[2][0]==0? 0 : 4;
			score += magnet[3][0]==0? 0 : 8;

			StringBuilder sb = new StringBuilder();
			sb.append("#").append(test_case).append(" ").append(score);
			System.out.println(sb);
		}
	}

	private static void rotate(int n, int d) {
		int left = magnet[n][6];
		int right = magnet[n][2];
		int origin = d;
		if(d==1)
			clock(n);
		else
			clockwise(n);

		// 오른쪽 검사
		//2, 6번이 맞닿아 있음
		for(int i=n+1; i<4; ++i) {
			if(right == magnet[i][6]) break;

			right = magnet[i][2];	// 오른쪽과 맞닿은 극 저장
			if(d==1) {	// 시계방향이면 반시계 회전
				clockwise(i);
				d=-1;
			}
			else {	// 반시계방향이면 시계회전
				clock(i);
				d=1;
			}
		}

		d = origin;
		// 왼쪽
		for(int i=n-1; i>=0; --i) {
			if(left == magnet[i][2]) break;

			left = magnet[i][6];	// 오른쪽과 맞닿은 극 저장
			if(d==1) {	// 시계방향이면 반시계 회전
				clockwise(i);
				d=-1;
			}
			else {	// 반시계방향이면 시계회전
				clock(i);
				d=1;
			}
		}

	}

	private static void clockwise(int n) {
		int tmp = magnet[n][0];
		for(int i=0; i<7; ++i)
			magnet[n][i] = magnet[n][i+1];
		magnet[n][7] = tmp;
	}

	private static void clock(int n) {
		int tmp = magnet[n][7];
		for(int i=7; i>=1; --i)
			magnet[n][i] = magnet[n][i-1];
		magnet[n][0] = tmp;
	}
}
