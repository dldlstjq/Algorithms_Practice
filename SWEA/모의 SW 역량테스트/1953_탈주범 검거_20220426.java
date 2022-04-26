/*
그렇게 썩 어렵진 않은 문제인 것 같다.
터널 별 갈 수 있는 방향을 tunnel이란 2차원 배열에 미리 선언해 뒀고
방향별로 갈 수 있는지 없는지 결정하는 부분을 설정하는데 시간이 걸렸다.

단순 상하좌우 4개의 방향에 대해서 연결될 수 없는 터널을 넣어서 가지 못한다고 확인했다.

 */

import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.LinkedList;
import java.util.Queue;
import java.util.StringTokenizer;

public class Solution {
	static class Pos{
		int r; int c; int t;
		Pos(int r, int c, int t){
			this.r=r;
			this.c=c;
			this.t=t;
		}
	}

	static int N,M;
	static int R,C,L;
	static int[][] map;
	static boolean[][] visited;

	static int ret;

	static int[] dr= {-1,0,1,0};
	static int[] dc= {0,1,0,-1};

	static int[][] tunnel= {
			{0,0,0,0},
			{0,1,2,3},
			{0,2,-1,-1},
			{1,3,-1,-1},
			{0,1,-1,-1},
			{1,2,-1,-1},
			{2,3,-1,-1},
			{0,3,-1,-1}
	};

	static int[][] notGo= {
			{3,4,7},
			{2,4,5},
			{3,5,6},
			{2,6,7}
	};

	public static void main(String[] args) throws IOException {
		//System.setIn(new FileInputStream("sample_input.txt"));

		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

		int T = Integer.parseInt(br.readLine());

		for(int test_case = 1; test_case <= T; test_case++)
		{
			StringTokenizer st = new StringTokenizer(br.readLine());
			N = Integer.parseInt(st.nextToken());
			M = Integer.parseInt(st.nextToken());
			R = Integer.parseInt(st.nextToken());
			C = Integer.parseInt(st.nextToken());
			L = Integer.parseInt(st.nextToken());

			map = new int[N][M];
			visited = new boolean[N][M];

			for(int i=0; i<N; ++i) {
				st = new StringTokenizer(br.readLine());
				for(int j=0; j<M; ++j) {
					map[i][j] = Integer.parseInt(st.nextToken());
				}
			}

			ret = 0;
			start();
			StringBuilder sb = new StringBuilder();
			sb.append("#").append(test_case).append(" ").append(ret);
			System.out.println(sb);
		}
	}

	private static void start() {
		Queue<Pos> q = new LinkedList<>();
		q.offer(new Pos(R, C, 1));
		visited[R][C] = true;

		ret = 1;	// R,C 위치는 갈 수 있음

		while(!q.isEmpty()) {
			Pos now = q.poll();

			// L시간이 되면 이동 불가
			if(now.t==L) continue;

			// 터널 통과
			testTunnel(now.r, now.c, now.t, map[now.r][now.c], q);
		}
	}

	private static void testTunnel(int r, int c, int t, int n, Queue<Pos> q) {

		for(int i=0; i<tunnel[n].length; ++i) {
			if(tunnel[n][i]==-1) break;
			int d = tunnel[n][i];
			int nr = r+dr[d];
			int nc = c+dc[d];

			// 범위 아웃, 방문한 곳, 터널이 없는 곳
			if(!isIn(nr, nc) || visited[nr][nc] || map[nr][nc]==0) continue;

			// 다음 위치에 있는 구조물에 따라 갈수있는지 여부가 결정
			boolean no = false;
			for(int j=0; j<notGo[d].length; ++j) {
				if(map[nr][nc] == notGo[d][j]) {
					no = true;
					break;
				}
			}

			if(no) continue;

			q.offer(new Pos(nr, nc, t+1));
			visited[nr][nc] = true;
			ret++;
		}
	}

	private static boolean isIn(int r, int c) {
		return 0<=r&&r<N && 0<=c&&c<M;
	}
}
