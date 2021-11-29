/*
2021 하반기 오전 삼성 기출을 풀어봤다.
주사위를 굴리고 해당 좌표에 있는 숫자가 동서남북 연속으로 있으면 점수를 계산한다.
주사위 숫자를 2차원 배열에 저장해서 굴릴때마다 번호를 바꿔줬고
이동 방향 역시 조건에 맞게 맞춰줬다.

주사위 이동방향을 바로 갱신하지 않아서 처음에 정확한 값이 안나왔고 같은 숫자일때만 점수 계산이 들어가는 것도 고려해야 했다.
그래도 답이 제대로 안나왔을때 어디서 안되는지를 빨리 찾아서 1시간내에 해결할 수 있었던 것 같다.

또 바로 답을 출력하는 것이 아니라 중간에 주사위 이동 방향과 밑면의 숫자가 제대로 나오는지 체크했던 게 더 빨리 풀 수 있는 방법이 되었던 것 같다.

싸피에서 웹 공부한다고 대략 3~4주 정도 코테 문제를 안풀었는데 그래도 감각이 살아있는 것 같다.
*/

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.Arrays;
import java.util.StringTokenizer;

public class Main {
	
	static int N,M,K;
	static int [][] map;
	static int [][] dice = 
			{{0,2,0},
			{4,1,3},
			{0,5,0},
			{0,6,0}};
	
	static int dr[] = {-1,0,1,0};
	static int dc[] = {0,1,0,-1};
	
	static int score;	// 전체 점수
	static int cnt;	// 점수 계산 시 같은 칸이 몇 칸인지
//	static int dir;	// 현재 방향
	
	public static void main(String[] args) throws Exception {
		//System.setIn(new FileInputStream("input.txt"));
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine());

		// 아랫면 = A, 주사위가 있는 칸 = B
		// A > B인 경우 이동 방향을 90도 시계 방향으로 회전시킨다.
		// A < B인 경우 이동 방향을 90도 반시계 방향으로 회전시킨다.
		// A = B인 경우 이동 방향에 변화는 없다.
		
		
		// 가장 처음에 주사위의 이동 방향은 동쪽이다. 
		
		N = Integer.parseInt(st.nextToken());
		M = Integer.parseInt(st.nextToken());
		K = Integer.parseInt(st.nextToken());
		
		map = new int[N][M];
		
		for(int i=0; i<N; ++i) {
			st = new StringTokenizer(br.readLine());
			for(int j=0; j<M; ++j) {
				map[i][j] = Integer.parseInt(st.nextToken());
			}
		}
		
		int dir=1;	// 동쪽에서 시작
		int r=0, c=0;	// 현재 좌표
		int A = dice[3][1];	// 주사위 밑면
		int B = map[r][c];	// 주사위가 있는 칸
		
		for(int i=0; i<K; ++i) {
//			System.out.println((i+1)+"번째");
			// 이동할 수 있으면 방향 그대로 이동
			if(isIn(r+dr[dir], c+dc[dir])) 
				moveDice(dir);	// 주사위 이동
			
				
			else {
				dir = (dir+2)%4;	// 방향을 바꾸고 주사위 정리
				moveDice(dir);	// 방향 반대로
			}
				
			// 좌표 이동
			r += dr[dir];
			c += dc[dir];
			
			A = dice[3][1];	// 주사위 밑면
			B = map[r][c];	// 주사위가 있는 칸
			
			// 밑면은 dice[3][1]
//			System.out.println("주사위 밑면: " + dice[3][1]);

			cnt = 0;
			checkScore(B, r, c, new boolean[N][M]);	// 점수 체크
			score += cnt*B;	// 점수 계산
//			System.out.println("점수: "+score);
//			System.out.println();
			
			if(A > B) 
				dir = (dir+1)%4;	// 90도 시계방향
			else if(A < B)
				dir = (dir+3)%4;	// 90도 반시계방향
		}
		
		System.out.println(score);
	}

	private static boolean isIn(int r, int c) {
		return 0<=r && r<N && 0<=c && c<M;
	}

	private static void checkScore(int num, int r, int c, boolean[][] visited) {
		// dfs로 같은 칸 체크
		visited[r][c] = true;
		cnt++;
		for(int i=0; i<4; ++i) {
			int nr = r+dr[i];
			int nc = c+dc[i];
			// 범위 벗어나거나 방문했거나 숫자 다르면 다른 방향 탐색
			if(!isIn(nr,nc) || visited[nr][nc] || num!=map[nr][nc]) continue;
			checkScore(num, nr, nc, visited);
		}
	}


	// 주사위 좌표 정리
	private static void moveDice(int dir) {
//		System.out.println("주사위 방향: "+dir);
		
		// 북쪽 이동
		if(dir == 0) {
			int tmp = dice[0][1];
			for(int i=0; i<=2; ++i) 
				dice[i][1] = dice[i+1][1];
			dice[3][1] = tmp;
		}
		
		// 동쪽 이동
		else if(dir == 1) {
			int tmp = dice[1][2];
			for(int i=2; i>=1; --i) 
				dice[1][i] = dice[1][i-1];
			dice[1][0] = dice[3][1];
			dice[3][1] = tmp;
		}
		
		// 남쪽 이동
		else if(dir == 2) {
			int tmp = dice[3][1];
			for(int i=3; i>=1; --i) 
				dice[i][1] = dice[i-1][1];
			dice[0][1] = tmp;
		}
		
		// 서쪽 이동
		else if(dir == 3) {
			int tmp = dice[1][0];
			for(int i=0; i<=1; ++i) 
				dice[1][i] = dice[1][i+1];
			dice[1][2] = dice[3][1];
			dice[3][1] = tmp;
		}
	}
}