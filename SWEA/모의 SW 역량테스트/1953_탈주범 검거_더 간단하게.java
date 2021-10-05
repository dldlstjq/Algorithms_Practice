/*
갈 수 있는 파이프를 if문으로 전부 계산했는데 여기서는 string으로 저장하여 한번에 관리했다.
0123(상좌우하) 순으로 관리하면 3-d 가 바로 반대방향이 되어 갈 수 있는 여부를 쉽게 확인할 수 있다.
그러면 if문을 여러개 쓰지 않고 한번에 계산이 가능한데 우선 문제를 풀고나서 좀 더 간단하게 바꾸는 연습을 하는게 맞는 것 같다.
*/

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.LinkedList;
import java.util.Queue;
import java.util.StringTokenizer;

public class Solution_1953_탈주범검거 {
	
	// dfs는 시간으로 방문 관리
	
	private static String[] type = {
		null,
		"0312", // 1: 상하좌우
		"03", // 2: 상하
		"12", // 3: 좌우
		"02", // 4: 상우
		"32", // 5: 하우
		"31", // 6: 하좌
		"01", // 7: 상좌
	};
	
	static int[] dr = {-1,0,0,1};
	static int[] dc = {0,-1,1,0};
	static int N, M, R, C, L;
	static int[][] map;
	
	public static void main(String[] args) throws Exception{
		// 그래프 한 정점 출발해서 인접한 정점 계속 따라서 탐색 => 그래프의 연결성 확인
		// DFS, BFS
		
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		
		int T;
		T= Integer.parseInt(br.readLine());	

		StringTokenizer st = null;
		for(int test_case = 1; test_case <= T; test_case++)
		{
			st=  new StringTokenizer(br.readLine());
			
			N = Integer.parseInt(st.nextToken());
			M = Integer.parseInt(st.nextToken());
			R = Integer.parseInt(st.nextToken());
			C = Integer.parseInt(st.nextToken());
			L = Integer.parseInt(st.nextToken());
			
			map = new int[N][M];
			
			for(int i=0; i<N; ++i) {
				st=  new StringTokenizer(br.readLine());
				for(int j=0; j<M; ++j) {
					map[i][j] = Integer.parseInt(st.nextToken());
				}
			}
			
			System.out.println("#"+test_case+" "+bfs());
			
		}
	}

	private static int bfs() {
		Queue<int[]> queue = new LinkedList<int[]>();
		boolean[][] visited = new boolean[N][M];
		int result = 0, time =1;
		
		queue.offer(new int[] {R,C});
		visited[R][C] = true;
		result++;
		
		int r,c,nr,nc,size,current[], dir;
		String info  =null;
		while(time++<L) {
			size =  queue.size();
			while(size-- > 0) {
				current = queue.poll();
				r = current[0];
				c = current[1];
				
				info = type[map[r][c]];
				
				for(int d= 0, length = info.length(); d<length; d++) {
					dir = info.charAt(d)-'0';
					nr = r+dr[dir];
					nc = c+dc[dir];
					
					// 이어지는 구조물인지 체크
					if(nr>=0 && nr< N && nc>=0 && nc< M && map[nr][nc] != 0
							&& type[map[nr][nc]].contains(Integer.toString(3-dir))
							&& !visited[nr][nc]){
						queue.offer(new int[] {nr, nc});
						visited[nr][nc] = true;
						result++;
					}
				}
			}
		}
		return result;
	}
	
	
}
