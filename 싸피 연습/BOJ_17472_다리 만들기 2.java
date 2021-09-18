// 내 블로그 참조 https://sincerity96.tistory.com/100

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.LinkedList;
import java.util.PriorityQueue;
import java.util.Queue;
import java.util.StringTokenizer;

public class Main {
	// 다리를 연결할 때 쓸 좌표와 방향, 길이
	static class Pos{
		int r,c;
		int dir, len;
		
		Pos(int r, int c, int dir, int len){
			this.r=r;
			this.c=c;
			this.dir=dir;
			this.len=len;
		}
	}
	// 연결된 다리의 섬 번호와 길이
	static class Bridge implements Comparable<Bridge>{
		int num, dist;
		Bridge(int num, int dist){
			this.num=num;
			this.dist=dist;
		}
		@Override
		public int compareTo(Bridge o) {
			return Integer.compare(this.dist, o.dist);
		}
	}
	
	static int N,M;
	static int[][] map;
	static boolean[][] visited;
	
	static boolean[] isConnected;	// 다리를 만들고 나서 모든 섬이 연결되었는지 확인
	
	static int dr[]= {-1,0,1,0};
	static int dc[]= {0,1,0,-1};
	
	static int cnt = 1;	// 섬 번호
	static ArrayList<Bridge>[] list;	// 섬과 연결된 다리 정보 저장.
	
	static int answer;	// 최종 답
	
	public static void main(String[] args) throws Exception{
		
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine());
		
		N = Integer.parseInt(st.nextToken());
		M = Integer.parseInt(st.nextToken());
		
		map = new int[N][M];
		visited = new boolean[N][M];
		
		for(int i=0; i<N; ++i) {
			st = new StringTokenizer(br.readLine());
			for(int j=0; j<M; ++j)
				map[i][j] = Integer.parseInt(st.nextToken());
		}
		
		
		for(int i=0; i<N; ++i) {
			for(int j=0; j<M; ++j)
				if(map[i][j] == 1 && !visited[i][j]) {
					checkIsland(i, j, cnt++);	// 각 섬마다 번호 붙임
				}
		}
		
		list= new ArrayList[cnt];
		isConnected= new boolean[cnt];
		for(int i=1; i<cnt; ++i)
			list[i] = new ArrayList<>();
		
		int idx = 1;
		int result = -1;
		
		// 1번 섬부터 cnt-1번 섬까지 연결할 수 있는 모든 다리를 구한다.
		// bfs로 구했기 때문에 각 섬까지 갈 수 있는 최단거리의 다리가 순서대로 저장된다.
		// 따라서 1번섬부터 다리를 따라가면 최단거리로 섬으로 가는 다리를 구할 수 있다고 생각
		// 하지만 dfs로 연결된 섬을 따라가다보면 안되는 반례 존재.
		// 결국 모든 섬에서 연결할 수 있는 다리를 구한 뒤 크루스칼이나 프림을 사용해 최소 간선만을 구해야 한다.
	
		// 모든 섬에서 연결할 수 있는 다리 건설
		for(int i=1; i<cnt; ++i)
			makeBridge(i);
		
		// 프림 알고리즘으로 MST를 구한다.
		Prim();
		
		// 모든 섬이 true면 연결 되었다.
		int tmp = 0;
		for(int i=1; i<cnt; ++i) {
			if(isConnected[i]) {
				tmp++;
			}
		}
		
		result = tmp==cnt-1 ? answer : -1;
		System.out.println(result);
	}
	
	private static void Prim() {
		// 다리를 통해 섬 방문
		PriorityQueue<Bridge> pq = new PriorityQueue<>();

		pq.offer(new Bridge(1, 0));
		
		while(!pq.isEmpty()) {
			Bridge curr = pq.poll();
			// 이미 연결되었으면 다른 섬 조사
			if(isConnected[curr.num])
				continue;
			// 연결되지 않았으면 길이 저장후 연결 표시
			answer += curr.dist;
			isConnected[curr.num] = true;
			
			for(int i=0; i<list[curr.num].size(); ++i) {
				int n = list[curr.num].get(i).num;
				int dist = list[curr.num].get(i).dist;
				if(!isConnected[n])
					pq.offer(new Bridge(n, dist));
			}
		}
	}

	// 맵 범위 체크
		private static boolean inRange(int r, int c) {
			return 0<=r&&r<N && 0<=c&&c<M;
		}
		// 섬마다 번호 할당
		private static void checkIsland(int r, int c, int cnt) {
			visited[r][c] = true;
			map[r][c] = cnt;
			for(int i=0; i<4; ++i) {
				int nr = r+dr[i];
				int nc = c+dc[i];
				if(!inRange(nr, nc) || visited[nr][nc] || map[nr][nc] == 0)
					continue;
				checkIsland(nr, nc, cnt);
			}
		}
		
		private static void makeBridge(int num) {
			Queue<Pos> q = new LinkedList<>();
			// num에 해당하는 섬을 모두 큐에 저장
			for(int i=0; i<N; ++i) {
				for(int j=0; j<M; ++j)
					if(map[i][j] == num)
						q.offer(new Pos(i, j, -1, 0));
			}
			
			boolean connected[] = new boolean[cnt];	
			
			int ret = 0;
			
			boolean start = true;
			while(!q.isEmpty()) {
				int size = q.size();
				
				while(size-- > 0) {
					// 다리는 가로 또는 세로가 될 수밖에 없다.
					Pos curr = q.poll();
					
					if(curr.dir == -1) {
						for(int i=0; i<4; ++i) {
							int nr = curr.r+dr[i];
							int nc = curr.c+dc[i];
							
							if(!inRange(nr, nc) || map[nr][nc] != 0)
								continue;
							
							// 방문하지 않은 곳이고 바다이면 큐에 저장
							if(map[nr][nc] == 0) {
								q.offer(new Pos(nr, nc, i, curr.len+1));

							}
						}
					}
					
					
					else {
						int nr = curr.r+dr[curr.dir];
						int nc = curr.c+dc[curr.dir];
						
						if(!inRange(nr, nc))
							continue;
						

						// 방문하지 않은 곳이고 바다이면 큐에 저장
						if(map[nr][nc] == 0) {
							q.offer(new Pos(nr, nc, curr.dir, curr.len+1));
						}

						// 바다가 아니면서 다른 섬에 도착하면 다리 완성
						else if(map[nr][nc] !=0 && map[nr][nc] !=num) {
							// num 번호의 섬과 연결되지 않았으면 연결해주고 리스트에 추가
							int island = map[nr][nc];
							if(!connected[island] && curr.len >= 2) {
								connected[island] = true;
								list[num].add(new Bridge(island, curr.len));
							}
						}
					}
					
				}
				
			}
		}
}
