/*
처음에 dp+dfs 문제로 접근했다가 도저히 아이디어가 생각이 안나서 해결하지 못했다.
알곱보니 길찾기라서 bfs로 접근하면 되는데 문제는 말의 이동 횟수를 고려해야하기 때문에
방문 배열을 3차원으로 만들어야 한다.
레벨 별 탐색을 하거나 이동거리를 확인하는 변수를 배열에 추가해서 하는 방법 두가지가 있다.
*/

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.LinkedList;
import java.util.Queue;
import java.util.StringTokenizer;

public class Main {
	
	static class Pos{
		int r, c, horseCnt, dist;
		Pos(int r, int c, int horseCnt, int dist){
			this.r=r;
			this.c=c;
			this.horseCnt = horseCnt;
			this.dist = dist;
		}
	}
	
	static int K;	// 말 이동횟수
	static int W, H;	// 가로, 세로
	static int map[][];	// 맵
	static boolean visited[][][];	// 방문여부, 말 이동 횟수
	
	// 말, 원숭이 이동. 시계방향
	static int dr[] = {-1,0,1,0,-2,-1,1,2,1,2,-1,-2};
	static int dc[] = {0,1,0,-1,1,2,2,1,-1,-2,-2,-1};
	
	private static void bfs() {
		Queue<Pos> q = new LinkedList<>();
		q.offer(new Pos(0, 0, 0, 0));
		visited[0][0][0] = true;
		
		int depth = 0;	// 이동 횟수
		
		while(!q.isEmpty()) {
			// depth별 탐색
			int size = q.size();
			while(size-- > 0) {
				Pos curr = q.poll();
				
				// 도착지점에 도착하면 그 때 거리 리턴
				if(curr.r == H-1 && curr.c == W-1) {
					System.out.println(depth);
					return;
//					return curr.dist;
				}
				
				// 원숭이 이동 탐색
				int length = curr.horseCnt == K?4:12;
				for(int i=0; i<length; ++i) {
					int nr = curr.r+dr[i];
					int nc = curr.c+dc[i];
					
					int horseCnt = i>=4 ? curr.horseCnt+1 : curr.horseCnt;
					
					// 경계를 벗어나거나, 장애물이 있거나 방문했으면 패스
					if(nr<0 || nr>=H ||nc<0 || nc>=W || visited[nr][nc][horseCnt] || map[nr][nc] == 1)
						continue;
					
					// 방문체크 및 큐에 넣어주기
					visited[nr][nc][horseCnt] = true;
					q.offer(new Pos(nr, nc, horseCnt, curr.dist+1));
				}
			}
			
			depth++;
			
		}
		System.out.println(-1);
//		return -1;
	}
	
	public static void main(String[] args) throws Exception{
		BufferedReader br= new BufferedReader(new InputStreamReader(System.in));
		
		
		// bfs 사용하는데 말 이동이 추가됐다.
		// 방문을 함과 동시에 말 이동횟수나 사용횟수를 체크해야 한다.
		// 말처럼 이동하고 한칸씩 이동하면 갈 수 없으나
		// 한 칸씩 이동한 후 말처럼 이동하면 갈 수 있는 경우도 있다.
		// 특정지점으로 이동할 때 말 이동 사용횟수 체크
		
		K = Integer.parseInt(br.readLine());
		StringTokenizer st = new StringTokenizer(br.readLine());
		W = Integer.parseInt(st.nextToken());
		H = Integer.parseInt(st.nextToken());
		
		map = new int[H][W];
		for(int i=0; i<H; ++i) {
			st = new StringTokenizer(br.readLine());
			for(int j=0; j<W; ++j)
				map[i][j] = Integer.parseInt(st.nextToken());
		}
		visited = new boolean[H][W][K+1];
		bfs();
	}
}
