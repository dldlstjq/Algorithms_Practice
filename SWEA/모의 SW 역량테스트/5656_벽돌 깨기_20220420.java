/*
2022.04.20
오랜만에 다시 풀어봤다.
원본 배열을 복사해놓고 하나의 과정이 끝나면 다시 복사해서 쓰는 과정을 반복하는 전형적인 방식이다.
처음에는 프로세스를 잘 몰라 헤맸는데 어느정도 하다보니 기억이 났다.
문제는 벽돌을 부수는 과정이 완전히 끝나고 나서 남은 벽돌을 내려줘야 하는데 중간중간에 벽돌을 내려주는 과정을 넣다보니 제대로 된 답이 안나왔다.
그것만 주의하면 될 것 같다.
 */

import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.List;
import java.util.StringTokenizer;

public class Solution {

	static int N,W,H;
	static int[][] board;
	static int dr[]= {-1,0,1,0};
	static int dc[]= {0,1,0,-1};

	static int ret;

	public static void main(String[] args) throws IOException {
		//System.setIn(new FileInputStream("sample_input.txt"));

		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

		int T;
		T=Integer.parseInt(br.readLine());

		for(int test_case = 1; test_case <= T; test_case++)
		{
			StringTokenizer st = new StringTokenizer(br.readLine());
			N = Integer.parseInt(st.nextToken());
			W = Integer.parseInt(st.nextToken());
			H = Integer.parseInt(st.nextToken());

			board = new int[H][W];
			for(int i=0; i<H; ++i) {
				st = new StringTokenizer(br.readLine());
				for(int j=0; j<W; ++j) {
					board[i][j] = Integer.parseInt(st.nextToken());
				}
			}

			ret = Integer.MAX_VALUE;
			solve(0);

			StringBuilder sb = new StringBuilder();
			sb.append("#").append(test_case).append(" ").append(ret);
			System.out.println(sb);
		}

	}

	private static void solve(int n) {
		if(n == N) {
			ret = Math.min(ret, getNum());
			return;
		}

		int[][] tmp = new int[H][W];
		copy(tmp, board);

		for(int i=0; i<W; ++i) {
			for(int j=0; j<H; ++j) {
				if(board[j][i]==0) continue;
				breakGusul(j, i);
				break;
			}
			downBlock();	// 블록을 다 부수고 내려야한다.
			solve(n+1);
			copy(board, tmp);
		}
	}

	private static void breakGusul(int r, int c) {
		int n = board[r][c];
		board[r][c] = 0;
		// 4방탐색
		for(int i=0; i<4; ++i) {
			int nr = r;
			int nc = c;
			for(int j=0; j<n-1; ++j) {	// n-1번만 진행
				nr += dr[i];
				nc += dc[i];
				if(!isIn(nr, nc)) {
					break;
				}
				else if(board[nr][nc] == 0) {
					continue;
				}
				breakGusul(nr, nc);
			}
		}
	}

	private static int getNum() {
		int cnt = 0;
		for(int i=0; i<H; ++i) {
			for(int j=0; j<W; ++j)
				if(board[i][j] != 0) cnt++;
		}
		return cnt;
	}

	private static void downBlock() {
		for(int i=0; i<W; ++i) {
			List<Integer> list=  new ArrayList<>();
			for(int j=H-1; j>=0; --j) {
				if(board[j][i]==0) continue;
				list.add(board[j][i]);
				board[j][i] = 0;
			}

			int k=0;
			if(list.isEmpty()) continue;
			for(int j=H-1; j>=0; --j) {
				board[j][i] = list.get(k++);
				if(k==list.size()) break;
			}
		}
	}

	private static void copy(int[][] tmp, int[][] arr) {
		for(int i=0; i<H; ++i)
			tmp[i] = arr[i].clone();
	}

	private static boolean isIn(int r, int c) {
		return 0<=r&&r<H && 0<=c&&c<W;
	}


}
