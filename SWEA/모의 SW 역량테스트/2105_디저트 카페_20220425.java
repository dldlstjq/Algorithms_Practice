/*
단순 dfs라고 생각하면 틀리기 쉬운 것 같다.
마름모 방향으로 돌되 한쪽 방향으로 계속 가다가 그 방향이 아니면 다른 방향으로 바꿔야 한다.
그 부분이 잘 생각이 나지 않았고 다시 처음좌표로 돌아왔을 때 무조건 4개 이상은 먹어야 가능하다.
2개만 왔다갔다 하는 것은 문제 조건에 성립하지 않기 때문에 조심해야 한다.

마지막으로 백트래킹을 사용해서 먹었던 부분을 지워줘야 다음에 실행할때 맞는 결과를 가져온다.

 */

import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

public class Solution {

	static int N;
	static int[][] map;
	static boolean[] dessert;

	static int dr[]= {1,1,-1,-1};
	static int dc[]= {1,-1,-1,1};

	static int ret;

	public static void main(String[] args) throws IOException {
		//System.setIn(new FileInputStream("sample_input.txt"));
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		int T = Integer.parseInt(br.readLine());


		for(int test_case = 1; test_case <= T; test_case++)
		{
			StringTokenizer st = new StringTokenizer(br.readLine());

			N = Integer.parseInt(st.nextToken());
			map = new int[N][N];
			dessert = new boolean[101];

			for(int i=0; i<N; ++i) {
				st = new StringTokenizer(br.readLine());
				for(int j=0; j<N; ++j) {
					map[i][j] = Integer.parseInt(st.nextToken());
				}
			}

			ret=-1;

			for(int i=0; i<N; ++i) {
				for(int j=0; j<N; ++j) {
					// 현재 좌표 기준 우측 아래를 함수에 넣어줌
					int nr = i+dr[0];
					int nc = j+dc[0];
					boolean[][] visited= new boolean[N][N];
					visited[i][j] = true;
					dessert[map[i][j]] = true;
					start(i, j, nr, nc, 0, 1, visited);
					dessert[map[i][j]] = false;
				}
			}


			StringBuilder sb = new StringBuilder();
			sb.append("#").append(test_case).append(" ").append(ret);
			System.out.println(sb);
		}
	}

	// sr,sc= 시작 좌표 r,c=현재 좌표 d=방향 cnt=먹은 개수 visited=방문표시
	private static void start(int sr, int sc, int r, int c, int d, int cnt, boolean[][] visited) {
		// 시작 좌표로 돌아왔을 때 2개 이상 먹어야 갱신 가능
		if(sr==r && sc==c) {
			if(cnt <=2) return;
			ret = Math.max(ret, cnt);
			return;
		}
		// 범위를 벗어나거나 같은 디저트 먹었거나 방문한 곳이면 다른 방향 탐색
		if(!isIn(r, c)|| visited[r][c] || dessert[map[r][c]]) {
			return;
		}

		dessert[map[r][c]] = true;
		visited[r][c] = true;

		// 현재 방향으로 계속 이동하다가 아니면 방향을 바꾼다
		for(int i=d; i<4; ++i) {
			start(sr, sc, r+dr[i], c+dc[i], i, cnt+1, visited);
		}

		// 백트래킹
		dessert[map[r][c]] = false;
		visited[r][c] = false;
	}

	private static boolean isIn(int r, int c) {
		return 0<=r&&r<N && 0<=c&&c<N;
	}
}
