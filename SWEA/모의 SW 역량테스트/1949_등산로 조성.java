/*
디저트 카페와 비슷하게 백트래킹을 사용했다.
가장 높은 값에서 낮은 값으로 최대 얼마나 갈 수 있는지 구해야 하는데 한 곳의 길이를 최대 K만큼 감소시킬 수가 있다.

가장 높은 곳에서 시작해야 하므로 길이가 가장 높은 곳이 최대 5개,
지도 크기 최대 8X8, K의 최대가 5이므로 충분히 4중 for문을 돌려도 시간안에 될 것 같았다.
가장 먼저 봉우리 개수만큼 for문을 돌리고 지도 크기 하나 당 최대 K만큼 하나씩 감소시키면서 등산로의 최대 길이를 구하면 된다.
*/

import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.List;
import java.util.StringTokenizer;

public class Solution {
	
	static class Pos{
		int x; int y;
		Pos(int x, int y){
			this.x=x;
			this.y=y;
		}
	}
	
	static int N, K;
	static int[][] map;
	static boolean[][] visited;
	
	static List<Pos> list;
	static int dr[]= {-1,0,1,0};
	static int dc[]= {0,1,0,-1};
	
	static int ret;
	
	public static void main(String[] args) throws Exception {
		//System.setIn(new FileInputStream("sample_input.txt"));

		BufferedReader br= new BufferedReader(new InputStreamReader(System.in));
		
		int T = Integer.parseInt(br.readLine());

		for(int test_case = 1; test_case <= T; test_case++)
		{
		
			StringTokenizer st = new StringTokenizer(br.readLine());
			N = Integer.parseInt(st.nextToken());
			K = Integer.parseInt(st.nextToken());
			
			map = new int[N][N];
			list = new ArrayList<>();
			ret = 0;
			int top = 0;
			for(int i=0; i<N; ++i) {
				st = new StringTokenizer(br.readLine());
				for(int j=0; j<N; ++j) {
					map[i][j] = Integer.parseInt(st.nextToken());
					top = Math.max(top, map[i][j]);
				}
			}
			// 제일 높은 값 리스트에 저장
			for(int i=0; i<N; ++i) {
				for(int j=0; j<N; ++j) {
					if(map[i][j] == top) list.add(new Pos(i, j));
				}
			}
			
			visited = new boolean[N][N];
			// N*N 모든 좌표마다 K만큼 감소시켜 최대 등산로 길이를 확인한다.
			for(int l=0; l<list.size(); ++l) {
				int r = list.get(l).x;
				int c = list.get(l).y;
				
				
				for(int i=0; i<N; ++i) {
					for(int j=0; j<N; ++j) {
						// 현재 정상과 같은 위치면 통과
						if(i == r && j == c) continue;
						// 1부터 K만큼 감소시키면서 최대 길이 확인
						for(int k=1; k<=K; ++k) {
							map[i][j] -= k;
							findPath(r, c, 1);
							map[i][j] += k;
						}
					}
				}
			}
			
			StringBuilder sb = new StringBuilder();
			sb.append("#"+test_case+" ").append(ret);
			System.out.println(sb.toString());
		}
	}

	private static void findPath(int r, int c, int dist) {
		for(int i=0; i<4; ++i) {
			int nr = r+dr[i];
			int nc = c+dc[i];
			
			// 범위 벗어나거나 방문했거나 길이가 크거나 같으면 갈 수 없음
			if(!isIn(nr, nc) || visited[nr][nc] || map[nr][nc] >= map[r][c])
				continue;
			
			visited[nr][nc] = true;
			findPath(nr, nc, dist+1);
			visited[nr][nc] = false;
		}
		// 최대값 갱신
		ret = Math.max(ret,  dist);
	}

	private static boolean isIn(int r, int c) {
		return 0<=r && r<N && 0<=c && c<N;
	}
}
