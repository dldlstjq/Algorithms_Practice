/*
문제 자체는 이해하기 어렵지 않다.
구현만 제대로 되면 문제없는데 만약에 조금이라도 답이 다르게 나오면 디버깅하기 너무 힘들것 같다.
비율이랑 비율 위치를 미리 선언해서 쓰면 편하게 쓸 수 있다.
 */

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.StringTokenizer;

public class Main {

	static int N;
	static int[][] map;
	static int[][] tmp;

	static int dr[]= {0,1,0,-1};
	static int dc[]= {-1,0,1,0};

	static double[] rate= {0.05,0.1,0.1,0.02,0.07,0.07,0.02,0.01,0.01};
	static int sr[][]= {
			{0,1,-1,2,1,-1,-2,1,-1},
			{2,1,1,0,0,0,0,-1,-1},
			{0,1,-1,2,1,-1,-2,1,-1},
			{-2,-1,-1,0,0,0,0,1,1}
	};
	static int sc[][]= {
			{-2,-1,-1,0,0,0,0,1,1},
			{0,1,-1,2,1,-1,-2,1,-1},
			{2,1,1,0,0,0,0,-1,-1},
			{0,1,-1,2,1,-1,-2,1,-1}
	};

	static int len;	// 토네이도 크기
	static int turn;	// 토네이도 방향

	static int r;
	static int c;
	static int ret;
	static boolean fin;

	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

		N = Integer.parseInt(br.readLine());

		map = new int[N][N];
		tmp = new int[N][N];

		for(int i=0; i<N; ++i) {
			StringTokenizer st = new StringTokenizer(br.readLine());
			for(int j=0; j<N; ++j) {
				map[i][j] = Integer.parseInt(st.nextToken());
			}
		}

		turn = 0;    // 이동 방향
		len = 1;    // 이동 길이
		r= N/2;    // 시작점
		c= N/2;

		while(!fin) {
			startTornado();

		}
		System.out.println(ret);
	}

	private static void startTornado() {

		for(int k=0; k<2; ++k) {
			for(int i=0; i<len; ++i) {
				int nr = r+dr[turn];
				int nc = c+dc[turn];

				if(nr < 0 || nc<0) {
					fin = true;
					return;
				}

				// y부분에 모래가 없으면 다음 좌표 진행
				if(map[nr][nc] == 0) {
					r=nr;
					c=nc;
					continue;
				}

				moveSand(nr, nc);    // 모래 이동
				map[nr][nc] = 0;	// y에는 모래가 없다
				r=nr;
				c=nc;
			}
			turn = (turn+1)%4;	// 방향 전환
		}
		len++;	// 토네이도 이동 길이 1씩 증가
	}

	private static void moveSand(int row, int col) {
		int y = map[row][col];

		int sum = 0;
		for(int i=0; i<9; ++i) {
			int nr = row+sr[turn][i];
			int nc = col+sc[turn][i];

			int sand = (int)(y*rate[i]);
			sum += sand;

			// 범위 밖으로 나간 모래 양
			if(!(0<=nr && nr<N && 0<=nc && nc<N)) {
				ret += sand;
				continue;
			}

			map[nr][nc] += sand;
		}

		// 알파 계산
		int ar = row+dr[turn];
		int ac = col+dc[turn];

		if(0<=ar && ar<N && 0<=ac && ac<N)
			map[ar][ac] += y-sum;
		else ret += y-sum;
	}

}
