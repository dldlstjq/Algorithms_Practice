/*
풀이는 금방 떠올랐는데 실수때문에 시간이 조금 걸렸다.
화살표를 제외한 도형은 dfs로 구하고 화살표는 따로 구해서 최댓값을 선정하면 된다.
dfs 함수 내에서 방문한 곳은 방문하지 않아야하는데 그 조건을 빼먹었고 메인 함수에서도
visited[i][j]=true인 곳을 다시 false로 바꿔줘야 다른 도형도 찾을 수 있는데 이 두가지에서 실수가 나왔다.
메인에서 dfs 함수 호출할 때도 자기자신을 포함하고 함수를 호출해야 한다.
*/

import java.io.*;
import java.util.StringTokenizer;

public class Main {

	final static int MAX = 500+4;
	static int N,M;
	static int [][]board = new int[MAX][MAX];
	static boolean [][] visited = new boolean[MAX][MAX];
	
	static int[] dy= {-1,0,1,0};
	static int[] dx= {0,1,0,-1};
	
	static int ret=0;
	
	static boolean is_in(int y, int x) {
		return 0<=y&&y<N && 0<=x&&x<M;
	}
	
	static void dfs(int y, int x, int cnt, int sum) {
		if(cnt == 4) {
			ret = Math.max(ret, sum);
			return;
		}
		
		for(int d=0; d<4; ++d) {
			int ny = y+dy[d];
			int nx = x+dx[d];
			
			// 범위 아웃
			if(!(0<=ny&&ny<N && 0<=nx&&nx<M))
				continue;
			// 이미 방문한 곳 패스
			if(visited[ny][nx])
				continue;
			// 백트래킹
			visited[ny][nx] = true;
			dfs(ny, nx, cnt+1, sum+board[ny][nx]);
			visited[ny][nx] = false;
		}
		
	}
	
	// y,x 는 화살표 모양 가운데
	static void arrow_shape(int y, int x) {
		// 위로 볼록
		if(is_in(y-1,x) && is_in(y,x+1) && is_in(y,x-1)) {
			ret = Math.max(ret, board[y][x]+board[y-1][x]+board[y][x+1]+board[y][x-1]);
		}
		// 오른 볼록
		if(is_in(y-1,x) && is_in(y,x+1) && is_in(y+1,x)) {
			ret = Math.max(ret, board[y][x]+board[y-1][x]+board[y][x+1]+board[y+1][x]);
		}
		// 아래 볼록
		if(is_in(y+1,x) && is_in(y,x+1) && is_in(y,x-1)) {
			ret = Math.max(ret, board[y][x]+board[y+1][x]+board[y][x+1]+board[y][x-1]);
		}
		// 왼 볼록
		if(is_in(y-1,x) && is_in(y+1,x) && is_in(y,x-1)) {
			ret = Math.max(ret, board[y][x]+board[y-1][x]+board[y+1][x]+board[y][x-1]);
		}
		
	}
	
	public static void main(String[] args) throws IOException {
		// TODO Auto-generated method stub

		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine(), " ");
		
		N = Integer.parseInt(st.nextToken());
		M = Integer.parseInt(st.nextToken());
		
		
		for(int i=0; i<N; ++i) {
			st = new StringTokenizer(br.readLine(), " ");
			for(int j=0;j<M;++j) {
				board[i][j] = Integer.parseInt(st.nextToken());
			}
		}
		
		
		for(int i=0; i<N; ++i) {
			for(int j=0;j<M;++j) {
				visited[i][j]=true;
				// 인자로 넘겨줄 떄 (i,j)를 포함하고 넘겨야한다.
				dfs(i, j, 1, board[i][j]);
                visited[i][j]=false;
				arrow_shape(i, j);
			}
		}
		System.out.println(ret);	
		
	}
}