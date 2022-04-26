/*
쉽게 해결가능한 줄 알았는데 조건을 잘못 알아서 한번에 풀지 못했다.

최대 높이인 좌표를 모두 구한 후 하나씩 살펴봤다.
자기보다 높은 높이가 나오면 이미 깎았는지 아닌지 판단 후 깎았을 때 높이가 낮아지면 깎은 후 탐색을 계속 했다.
높이를 깎고 나서 재귀를 빠져나올 때는 다시 원래 상태로 만들어야하고 visited 상태도 원래대로 돌려줘야한다.

어떻게 해서 테스트케이스가 다 잘 나왔는데 오답을 맞았다.
어디서 틀렸는지 몰라 이전 풀이를 봤고 최대 K 깊이만큼 깎을 수 있기 때문에 1~K 높이를 다 시도해봐야한다.
단순히 K만큼만 깎을수 있다 해서 진행했는데 그게 아니었다.

실제 시험장에서 이렇게 실수한다면 풀었는줄 알고 방심했다가 코테에서 떨어지는 불상사가 발생할 수 있을 것 같다.
무조건 문제를 잘 읽어서 조건을 하나씩 이해하자.

 */

import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.LinkedList;
import java.util.Queue;
import java.util.StringTokenizer;

public class Solution {

	static int N, K;
	static int[][] map;
	static boolean[][] visited;

	static int[] dr= {-1,0,1,0};
	static int[] dc= {0,1,0,-1};
	static int maxLen;
	static Queue<int[]> q;
	static int ret;

	public static void main(String[] args) throws IOException {
		//System.setIn(new FileInputStream("sample_input.txt"));

		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		int T = Integer.parseInt(br.readLine());

		for(int test_case = 1; test_case <= T; test_case++)
		{
			StringTokenizer st = new StringTokenizer(br.readLine());
			N = Integer.parseInt(st.nextToken());
			K = Integer.parseInt(st.nextToken());

			map = new int[N][N];
			visited = new boolean[N][N];
			maxLen = 0;
			for(int i=0; i<N; ++i) {
				st = new StringTokenizer(br.readLine());
				for(int j=0; j<N; ++j) {
					map[i][j] = Integer.parseInt(st.nextToken());
					maxLen = Math.max(maxLen, map[i][j]);
				}
			}

			q = new LinkedList<>();

			// 가장 높은 봉우리 위치 찾기
			for(int i=0; i<N; ++i) {
				for(int j=0; j<N; ++j) {
					if(map[i][j] == maxLen) {
						q.offer(new int[]{i, j});
					}
				}
			}

			ret = 0;
			while(!q.isEmpty()) {
				int[] now = q.poll();
				findPath(now[0], now[1], 1, false);
			}

			StringBuilder sb = new StringBuilder();
			sb.append("#").append(test_case).append(" ").append(ret);
			System.out.println(sb);
		}
	}

	private static void findPath(int r, int c, int cnt, boolean destroy) {
		visited[r][c] = true;

		for(int i=0; i<4; ++i) {
			int nr=r+dr[i];
			int nc=c+dc[i];

			// 범위 아웃 혹은 방문한 곳
			if(!isIn(nr, nc) || visited[nr][nc]) continue;

				// 높이가 낮은 경우 K이하만큼 높이를 깎을 수 있음
				// 무조건 K 만큼 깎는 것이 아님!!
			else if(map[nr][nc] >= map[r][c]) {
				if(!destroy) {
					for(int j=1; j<=K; ++j) {
						if(map[nr][nc]-j <map[r][c]) {
							map[nr][nc] -= j;
							findPath(nr, nc, cnt+1, true);
							map[nr][nc] += j;
						}
					}
				}

				else continue;
			}
			else {
				findPath(nr, nc, cnt+1, destroy);
			}

		}

		ret = Math.max(ret, cnt);
		visited[r][c] = false;

	}

	private static boolean isIn(int r, int c) {
		return 0<=r&&r<N && 0<=c&&c<N;
	}
}
