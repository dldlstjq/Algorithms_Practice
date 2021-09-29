/*
한 번 시도해본 문제인데 혼자서 풀지 못한 기억이 있었다.
이번에는 꼭 풀어보고 싶다는 마음으로 도전했다.

우선 열쇠 획득 정보를 비트로 표현해야 한다는 것은 바로 생각 났다.
그리고 bfs를 사용해 조건에 따라 움직이도록 설정했다.
문제는 방문 표시였는데 처음엔 방문 설정을 하지 않았다.
방문처리를 해버리면 열쇠를 얻은 경우에 다시 돌아갈 수 없을 수도 있기 때문에 하지 않았다.
하지만 방문처리를 안하니 무한루프를 돌아서 종료되지 않았다.

그때 생각난 것이 열쇠를 얻었을때, 얻지 않았을 때를 방문 조건에 추가하면
같은 좌표라도 열쇠 획득 여부에 따라 방문할 수도, 안할 수도 있었다.
그래서 visited 배열을 3차원으로 만들어 열쇠획득 여부까지 설정했고 그것에 따라 구현하니 정답을 받을 수 있었다.

정답 받고는 믿기지가 않았다. 내가 이렇게 성장했다니....
확실히 많은 문제를 풀어본 것이 도움이 된 것 같고 이때까지의 노력이 헛되이 되지 않았다는 것을 느낄 수 있었다.

핵심은 열쇠획득을 비트로 표시하는 것, visited로 열쇠획득 여부를 판별해야 하는 것이다.
만약 비트가 아닌 배열로 표시하면 메모리도 많이 잡아먹을 것이고 구현하는 것도 쉽지 않았을 것이다.
또, 처음에 했던 실수는 열쇠를 전역으로 선언한 것인데 전역으로 선언하면 열쇠를 획득한 적이 없는데 획득했다고 표시되기 때문에 좌표값에 따라 열쇠를 설정해줘야 한다.

골드1의 난이도이지만 혼자 힘으로 해결해내서 정말 뿌듯했다.
*/


import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.LinkedList;
import java.util.Queue;
import java.util.StringTokenizer;

public class Main {
	
	static class Pos{
		int r, c, key, dist;	// x-y 좌표, 키 획득여부, 이동거리
		Pos(int r, int c, int key, int dist){
			this.r=r;
			this.c=c;
			this.key=key;
			this.dist=dist;
		}
	}
	
	static int N, M;
	static char[][] maze;
	static boolean[][][] visited;	// x-y좌표, 열쇠 획득여부
	
	static int dr[] = {-1,0,1,0};
	static int dc[] = {0,1,0,-1};
	
	static Queue<Pos> q;
	
	public static void main(String[] args) throws Exception{
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine());
		
		N = Integer.parseInt(st.nextToken());
		M = Integer.parseInt(st.nextToken());
		
		maze = new char[N][M];
		visited = new boolean[N][M][127];	// 열쇠는 a~f 6개이므로 2^7-1로 표시
		q = new LinkedList<>();
		
		for(int i=0; i<N; ++i) {
			maze[i] = br.readLine().toCharArray();
			for(int j=0; j<M; ++j) {
				// 현재위치를 큐에 추가
				if(maze[i][j] == '0') {
					q.offer(new Pos(i, j,0, 0));
					visited[i][j][0] = true;
					maze[i][j] = '.';
				}
					
			}
		}
		
		findExit();
	}

	private static void findExit() {
		
		while(!q.isEmpty()) {
			Pos curr = q.poll();
			
			// 출구이면 최소 비용 출력
			if(maze[curr.r][curr.c] == '1') {
				System.out.println(curr.dist);
				return;
			}
			
			for(int i=0; i<4; ++i) {
				int nr = curr.r+dr[i];
				int nc = curr.c+dc[i];
				
				// 경계를 벗어나고, 이미 방문했거나 벽이면 갈 수 없다.
				if(nr<0 || nr>=N || nc<0 || nc>=M || maze[nr][nc] == '#' || visited[nr][nc][curr.key])
					continue;
				
				// 문 : 대응하는 열쇠가 있을 때만 이동할 수 있다. (A - F)
				else if('A'<=maze[nr][nc] && maze[nr][nc]<='F') {
					int door = maze[nr][nc] -'A';
					
					// 대응하는 열쇠가 있으면 해당 칸을 갈 수 있다.
					if((curr.key & (1<<door)) != 0) {
						q.offer(new Pos(nr, nc, curr.key, curr.dist+1));
						visited[nr][nc][curr.key] = true;
					}
				}
				
				// 열쇠 : 언제나 이동할 수 있다. 이 곳에 처음 들어가면 열쇠를 집는다. (a - f)
				else if('a'<=maze[nr][nc] && maze[nr][nc]<='f') {
					int key = maze[nr][nc] -'a';
					// 주의! curr.key에 바로 표시해버리면 아직 탐색하지 않은 다른 방향에서 열쇠를 찾았다고 생각한다.
					// 새로운 변수에다가 열쇠 획득 표시. 이것때문에 바로 정답이 안나옴.
					int newKey = curr.key | 1<<key;	// key에 해당하는 열쇠를 찾았다고 표시
					q.offer(new Pos(nr, nc, newKey, curr.dist+1));	// 새로 획득한 열쇠와 함께 큐에 추가
					visited[nr][nc][key] = true;
				}
				
				// 빈 곳('.'), 출구(1) : 언제나 이동할 수 있다.
				else if(maze[nr][nc] == '.' || maze[nr][nc] == '1') {
					q.offer(new Pos(nr, nc, curr.key, curr.dist+1));
					visited[nr][nc][curr.key] = true;
				}
			}
		}
		
		// 큐를 빠져나오면 출구를 찾지 못하거나 갈 수 없다.
		System.out.println(-1);
	}
}
