/*
문제 이해는 쉬운 편이었다.
L 시간동안 몇 개의 터널을 지날 수 있는지를 구하는 것으로 이해하고 시작했다.
터널 구조물이 7개이기 때문에 7가지 모두에 대해 함수를 만들려고 하다가 구조물 타입을 매개 변수로 받고 모양에 따른 방향을 static으로 선언하면
좀 더 간단하게 코드를 구현할 수 있다고 생각했다.

구조물 타입별로 모양을 미리 저장하고 타입에 따른 방향을 계산하면서 갈 수 있는 곳을 구했다.
생각보다 쉽네 하고 돌려보니 답이 안맞았다.
분명 코드상 틀린건 없는것 같은데 디버깅을 해보니 터널 모양에 따라 갈 수 있는지, 없는지를 고려해야 했다.
인접한 좌표에 터널이 있다고 해서 무조건 가는 것이 아니라 모양에 따라 연결되어있어야만 갈수 있었다.
즉, 윗방향으로 이동했는데 그때 터널 모양이 좌우로 되어있으면 갈 수가 없다.
따라서 타입에 따라 예외 설정을 다 해주고 난 다음에야 정답을 받을 수 있었다.
*/

import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.InputStreamReader;
import java.util.LinkedList;
import java.util.Queue;
import java.util.StringTokenizer;


public class Solution {
	
	static class Pos{
		int r, c;
		Pos(int r, int c){
			this.r=r;
			this.c=c;
		}
	}
	
	static int N, M, R, C, L;
	static int[][] map;
	static int[][] dist;
	
	static int dr[] = {-1,1,0,0};	// 상하좌우 순서
	static int dc[] = {0,0,-1,1};
	
	// 터널 타입별 모양
	static int[][] tunnelType = {{}, {0,1,2,3}, {0,1}, {2,3},
			{0,3}, {1,3}, {1,2}, {0,2}};

	static Queue<Pos> q;
	
	public static void main(String[] args) throws Exception {
		//System.setIn(new FileInputStream("sample_input.txt"));
		
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
			
			StringBuilder sb = new StringBuilder();
			sb.append("#").append(test_case).append(" "+findLocation());
			System.out.println(sb);
		}
	}

	private static int findLocation() {
		q = new LinkedList<Pos>();
		boolean[][] visited = new boolean[N][M];
		
		q.offer(new Pos(R, C));
		visited[R][C] = true;
		
		int cnt = 0;
		while(!q.isEmpty()) {
			cnt += q.size();	// 장소 개수 카운트
			L--;	// 1시간 감소
			// 시간이 0일때 cnt 리턴
			if(L == 0) {
				break;
			}
			
			int size = q.size();
			while(size-- > 0) {
				Pos curr = q.poll();
				
				int type = map[curr.r][curr.c];
				searchTunnel(curr.r, curr.c, type, visited);
			}
		}
		
		return cnt;
	}

	private static void searchTunnel(int r, int c, int type, boolean[][] visited) {
		
		int[] tunnel = tunnelType[type];
		for(int i=0; i<tunnel.length; ++i) {
			int nr = r+dr[tunnel[i]];
			int nc = c+dc[tunnel[i]];
			
			// 경계체크, 터널 구조물 체크, 방문 체크
			if(!inRange(nr, nc) || map[nr][nc] == 0 || visited[nr][nc]) 
				continue;
			
			// 상
			if(tunnel[i] == 0) {
				// 1번은 모두 연결 가능
				// 상 방향일 때 1,2,5,6 번만 연결 가능
				if(map[nr][nc] != 1 && map[nr][nc] != 2 && map[nr][nc] != 5 && map[nr][nc] != 6)
					continue;
			}
			
			// 하
			else if(tunnel[i] == 1) {
				// 하 방향일 때 1,2,4,7 번만 연결 가능
				if(map[nr][nc] != 1 && map[nr][nc] != 2 && map[nr][nc] != 4 && map[nr][nc] != 7)
					continue;
			}
			
			// 좌
			else if(tunnel[i] == 2) {
				// 좌 방향일 때 1,3,4,5 번만 연결 가능
				if(map[nr][nc] != 1 && map[nr][nc] != 3 && map[nr][nc] != 4 && map[nr][nc] != 5)
					continue;
			}
			
			// 우
			else if(tunnel[i] == 3) {
				// 우 방향일 때 1,3,6,7 번만 연결 가능
				if(map[nr][nc] != 1 && map[nr][nc] != 3 && map[nr][nc] != 6 && map[nr][nc] != 7)
					continue;
			}
			
			q.offer(new Pos(nr, nc));
			visited[nr][nc] = true;
		}
	}
    
	private static boolean inRange(int r, int c) {
		return 0<=r && r<N && 0<=c && c<M;
	}
}