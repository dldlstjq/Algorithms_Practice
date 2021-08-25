/*
큐를 이용한 풀이이다.
다른 배열을 선언하는 것보다 메모리를 덜 잡아먹을 줄 알았는데 더 잡아먹었다.
골드2인 이유가 시간초과 때문인것 같은데 운 좋게(?) 시간초과가 나지 않아 쉽게 해결한 것 같다.
이동 속도가 행, 열 크기를 한참 넘어가는 100 이라고 했을 때 반복문으로 일일이 한칸씩 진행하면 100번을 진행해야 한다.
대신 (R-1)*2, (C-1)*2 번을 돌면 같은 방향을 보고 있으면서 제자리로 돌아오기 때문에 이것을 모듈려 연산하여 이동을 대폭 줄일 수 있다.

이러게 푸니 한칸씩 이동하는 것보다 반이상 시간을 줄였다.

760ms
*/


import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.LinkedList;
import java.util.Queue;
import java.util.StringTokenizer;


public class Main {
	
	static class Fish{
		int r,c;
		int velocity, dir, size;
		public Fish(int r, int c, int velocity, int dir, int size) {
			super();
			this.r = r;
			this.c = c;
			this.velocity = velocity;
			this.dir = dir;
			this.size = size;
		}
	}
	
	static int R,C,M;
	static Fish[][] sea;
	static Fish[][] tmp;
	
	static int dr[] = {0,-1,1,0,0};
	static int dc[] = {0,0,0,1,-1};
	
	static int fisherman;	// 낚시꾼 위치
	
	static int ret;	// 상어 크기 합
	
	static void arrayCopy() {
		for(int i=0; i<=R; ++i)
			tmp[i] = sea[i].clone();
		
		// sea 초기화
		for(int i=1; i<=R; ++i) {
			for(int j=1; j<=C; ++j) {
				sea[i][j] = null;
			}
		}
	}
	
	static void fishing() {
		// 해당 열에서 물고기를 잡는다.
		// 1마리 잡으면 바로 종료
		for(int i=1; i<=R; ++i) {
			if(sea[i][fisherman] != null) {
				ret += sea[i][fisherman].size;
				sea[i][fisherman] = null;
				break;
			}
		}
	}
	
	static void moveFish() {
		Queue<Fish> q = new LinkedList<>();
		for(int i=1; i<=R; ++i) {
			for(int j=1; j<=C; ++j) {
				if(sea[i][j]!=null) {
					q.offer(sea[i][j]);
					sea[i][j] = null;
				}
				
			}
		}
		
		while(!q.isEmpty()) {
			Fish now = q.poll();
			
			int r = now.r;
			int c = now.c;
			int velocity = now.velocity;
			int dir = now.dir;
			int size=  now.size;
			
			// %(R-1)*2, %(C-1)*2 하면 제자리로 오는 것이기 때문에 나머지 연산을 통해 이동할 거리를 갱신한다.
			if( dir==1 || dir==2) 
				velocity %= (R-1)*2;
			else
				velocity %= (C-1)*2;
			
			
			for(int k=0; k<velocity; ++k) {
				int nr = r+dr[dir];
				int nc = c+dc[dir];
				
				// 범위를 벗어나게 되면 방향을 바꾼 후 한칸전진
				if(!(1<=nr&&nr<=R && 1<=nc&&nc<=C)) {
					if( dir==1 || dir==3)
						dir++;
					else
						dir--;
					r += dr[dir]; c+=dc[dir];
					continue;
				}
				
				r= nr;	 c= nc;
			}
			// 비었거나 더 큰 상어가 들어오면 해당 칸에 삽입
			if(sea[r][c] == null || sea[r][c].size < size)
				sea[r][c] = new Fish(r, c, velocity, dir, size);
			
		}
	}
		
	
	public static void main(String[] args) throws Exception {
		
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine(), " ");
		
		R = Integer.parseInt(st.nextToken());
		C = Integer.parseInt(st.nextToken());
		M = Integer.parseInt(st.nextToken());
		
		sea = new Fish[R+1][C+1];
		tmp = new Fish[R+1][C+1];
		
		for(int i=0; i<M; ++i) {
			st = new StringTokenizer(br.readLine(), " ");
			int r = Integer.parseInt(st.nextToken());
			int c = Integer.parseInt(st.nextToken());
			int s = Integer.parseInt(st.nextToken());
			int d = Integer.parseInt(st.nextToken());
			int z = Integer.parseInt(st.nextToken());
			
			sea[r][c] = new Fish(r, c, s,d,z);
		}
		
		fisherman=1; // 초기 위치는 1열
		
		while(fisherman <= C) {
			fishing();	// 낚시
			moveFish();
			fisherman++;
				
		}
		System.out.println(ret);
		
	}
}