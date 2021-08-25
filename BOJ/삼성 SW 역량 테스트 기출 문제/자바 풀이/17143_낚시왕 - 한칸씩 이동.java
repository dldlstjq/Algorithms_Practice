/*
골드 2 치고는 괜찮게 푼 것 같다.
배열에 물고기 방향과 크기, 속도를 저장한 후 이동하는게 관건이다.
배열 하나를 더 만들어 복사하는 방식으로 풀었는데 큐에다 물고기를 다 저장해두고
하나씩 꺼내면서 배열에 넣으면 배열 하나를 더 안만들어도 된다.
한 번 고기를 잡으면 물고기가 이동해야하는데 그걸 넣지 않아 디버깅하는데 시간이 걸렸다.

생각보다 채점에 시간이 많이 걸렸는데 한칸씩 다 이동해서 그런 것 같다.
다른 풀이는 좌표를 지정하여 이동을 줄여 시간을 줄였다.
2680ms
*/

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.Arrays;
import java.util.StringTokenizer;


public class Main {
	
	static class Fish{
		int velocity, dir, size;
		public Fish(int velocity, int dir, int size) {
			super();
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
		
		// sea 초기화. 상어 이동 할 때 좌표 넣어주기 위함
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
		
		arrayCopy();
		
		for(int i=1; i<=R; ++i) {
			for(int j=1; j<=C; ++j) {
				if(tmp[i][j] == null)
					continue;
				
				int r = i;
				int c = j;
				int velocity = tmp[i][j].velocity;
				int dir = tmp[i][j].dir;
				int size=  tmp[i][j].size;
				
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
					sea[r][c] = new Fish(velocity, dir, size);
				
			}
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
			
			sea[r][c] = new Fish(s,d,z);
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