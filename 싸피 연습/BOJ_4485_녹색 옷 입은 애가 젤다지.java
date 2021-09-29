/*
이전에 비슷한 문제를 풀어봐서 비교적 쉽게 접근할 수 있었다.
가중치가 있기 때문에 일반적인 bfs로는 해결할 수 없고 다익스트라를 이용해야 한다.
현재 위치까지의 가중치와 그 다음 위치로 이동할 때 가중치의 합이 현재 저장된 값보다 작으면 값을 갱신한다.

정석은 다익스트라를 활용하는 것 같은데 우선순위 큐를 이용해 값이 가장 작은 것 부터 먼저 처리하면서 끝에 다다르면 종료하는 것으로 했다.
*/

// 첫 풀이
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.PriorityQueue;
import java.util.StringTokenizer;

public class Main {
	
	static class Ruppe implements Comparable<Ruppe>{
		int r, c, ruppe;
		Ruppe(int r, int c, int ruppe){
			this.r =r;
			this.c=c;
			this.ruppe= ruppe;
		}
		
		@Override
		public int compareTo(Ruppe o) {
			return Integer.compare(this.ruppe, o.ruppe);
		}
	}

	static int[][] map;
	
	public static void main(String[] args) throws Exception{
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		
		int t= 1;
		while(true) {
			int N = Integer.parseInt(br.readLine());
			if(N == 0) break;
			
			map = new int[N][N];
			
			for(int i=0; i<N; ++i) {
				StringTokenizer st = new StringTokenizer(br.readLine());
				for(int j=0; j<N; ++j)
					map[i][j] = Integer.parseInt(st.nextToken());
			}
			
			System.out.printf("Problem %d: %d%n", t++, getMinruppe(N));
		}
		
		
	}

	private static int getMinruppe(int n) {
		// 가장 최소값을 가진 좌표를 먼저 탐색하도록 우선순위 큐 사용
		PriorityQueue<Ruppe> pq = new PriorityQueue<>();
		boolean[][] visited = new boolean[n][n];
		
		pq.offer(new Ruppe(0 ,0, map[0][0]));	// 0,0에서 시작
		visited[0][0] = true;
		
		int dr[] = {-1,0,1,0};
		int dc[] = {0,1,0,-1};
		
		int sum = 0;
		while(!pq.isEmpty()) {
			Ruppe curr = pq.poll();
			// N-1, N-1까지 이동하면 그때 루피가 최소금액
			if(curr.r == n-1 && curr.c == n-1) {
				sum = curr.ruppe;
				break;
			}
			
			for(int i=0; i<4; ++i) {
				int nr = curr.r+dr[i];
				int nc = curr.c+dc[i];
				
				if(nr<0 || nr>=n || nc<0 || nc>=n || visited[nr][nc])
					continue;
				
				pq.offer(new Ruppe(nr, nc, map[nr][nc]+curr.ruppe));
				visited[nr][nc] = true;
			}
		}
		return sum;
	}
}



// 다익스트라 풀이
// 최소비용 갱신에서 방문처리까지 같이 되므로 visited를 따로 설정할 필요는 없다.
private static void dijkstra() {
		PriorityQueue<Node> pq = new PriorityQueue<>();
		
		//초기 탐색
		pq.offer(new Node(0, 0, map[0][0]));
		distance[0][0] = map[0][0];	//초기 위치 최소비용 저장
		
		while(!pq.isEmpty()) {
			
			Node n = pq.poll();
			int r = n.r;
			int c = n.c;
			
			visited[r][c] = true;	//최소비용이 구해졌으므로 더이상 갱신 X
			
			//사방 탐색
			for(int d=0; d<4; d++) {
				
				int nr = r + dr[d];
				int nc = c + dc[d];
				
				//경계를 벗어나거나 방문한(최단거리가 구해진) 정점이라면? 
				if(nr<0 || nr>=N || nc<0 || nc>=N || visited[nr][nc]) continue;	//다음방향 탐색
				
				//현 저장되어있는 다음 좌표(nr,nc)까지의 최소비용보다 r,c좌표를 경유해서 nr,nc로 이동한 최소비용이 작으면? 
				if(distance[nr][nc]  >  distance[r][c]+map[nr][nc]) {
					distance[nr][nc] = distance[r][c]+map[nr][nc];	//갱신
					pq.offer(new Node(nr, nc, distance[nr][nc]));
				}
			}
		}
	}