/*
미세먼지가 동시에 이동한다는 부분만 잘 이해하면 어느정도 쉽지 않나 생각한다.
미세먼지 이동할 때 이동하는 좌표설정이 헷갈려 조금 시간이 걸렸다.
공기가 나오는 처음 공간은 무조건 0으로 설정해야 맞는 답이 나온다.
배열을 복사한 후에 복사한 배열값을 원본 배열에 넣은 것이 나중에 또 복사 안해도 된다.
일단 여기서는 두 번 복사하긴 했는데 나중에는 다르게 풀어보자.
*/

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.StringTokenizer;


public class Main {
	
	static class Pair implements Comparable<Pair>{
		int r,c;

		public Pair(int r, int c) {
			super();
			this.r = r;
			this.c = c;
		}

		@Override
		public int compareTo(Pair o) {
			return this.r-o.r;
		}
	}
	
	static int R,C,T;	// 가로, 세로, 초
	static int[][] origin;	//미세먼지 배열
	static int[][] tmp;
	
	static int[] dr= {0,-1,0,1}; // 우상좌하
	static int[] dc= {1,0,-1,0};
	
	static int[] up = {0,1,2,3};	// 위쪽 공기 방향
	static int[] down = {0,3,2,1};	// 아래쪽 공기 방향
	
	static Pair[] airCleaner = new Pair[2];
	
	// 미세먼지 확산
	// 확산은 동시에 -> 값을 미리 더하지 말고 따로 계산한뒤 한꺼번에 합친다.
	// 확산 되는 양 Ar,c/5
	// (r, c)에 남은 미세먼지의 양은 Ar,c - (Ar,c/5)×(확산된 방향의 개수)
	
	private static void spread_dust() {
		// 미세먼지 퍼질 때 퍼진 미세먼지를 tmp에 저장
		arrayCopy(origin, tmp);
		
		for(int i=0; i<R; ++i) {
			for(int j=0; j<C; ++j) {
				if(origin[i][j] ==0 || origin[i][j] ==-1 )
					continue;
				
				for(int k=0; k<4; ++k) {
					int nr = i+dr[k];
					int nc = j+dc[k];
					
					// 범위를 벗어나거나 공기청정기가 있으면 안됨
					if(!(0<=nr&&nr<R && 0<=nc&&nc<C) || origin[nr][nc] == -1)
						continue;
					
					tmp[nr][nc] += origin[i][j]/5;	// 확산되는 미세먼지 양
					tmp[i][j] -= origin[i][j]/5;	// 미세먼지 양 빼줌
				}
			}
		}
		
		// 퍼진 미세먼지 양을 origin에 저장
		arrayCopy(tmp, origin);
	}
	
	// 공기 청정기 동작
	private static void activate_airCleaner() {
		arrayCopy(origin, tmp);
		
		// 위쪽 공기청정기
		int up_R = airCleaner[0].r;
		int up_C = airCleaner[0].c;
		
		int dir =0;
		int nr = up_R+dr[up[dir]], nc = up_C+dc[up[dir]];	// 미리 방향 이동
		while(true) {
			nr += dr[up[dir]];
			nc += dc[up[dir]];
			
			// 범위를 벗어나면 방향을 바꿈
			if(!(0<=nr&&nr<R && 0<=nc&&nc<C) ) {
				nr -= dr[up[dir]];
				nc -= dc[up[dir]];
				dir++;
				continue;
			}
			
			// 공기 청정기 위치면 종료
			if( origin[nr][nc] == -1)
				break;

			tmp[nr][nc] = origin[nr-dr[up[dir]]][nc-dc[up[dir]]];
		}
		
		// 아래쪽 공기청정기
		int down_R = airCleaner[1].r;
		int down_C = airCleaner[1].c;
		
		
		dir =0;
		nr = down_R+dr[down[dir]]; nc = down_C+dc[down[dir]];	// 미리 방향 이동
		while(true) {
			nr += dr[down[dir]];
			nc += dc[down[dir]];
			
			// 범위를 벗어나면 방향을 바꿈
			if(!(0<=nr&&nr<R && 0<=nc&&nc<C) ) {
				nr -= dr[down[dir]];
				nc -= dc[down[dir]];
				dir++;
				continue;
			}
			
			if( origin[nr][nc] == -1)
				break;
			
			tmp[nr][nc] = origin[nr-dr[down[dir]]][nc-dc[down[dir]]];
		}
		
		arrayCopy(tmp, origin);	// 다시 원래 배열로 복사
	}
	
	
	private static void arrayCopy(int[][] a, int[][] b) {
		for(int i=0; i<R; ++i)
			b[i] = a[i].clone();
	}

	public static void main(String[] args) throws Exception {
		
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine(), " ");
		
		R = Integer.parseInt(st.nextToken());
		C = Integer.parseInt(st.nextToken());
		T = Integer.parseInt(st.nextToken());
		
		origin = new int[R][C];
		tmp = new int[R][C];
		int k=0;
		
		for(int i=0; i<R; ++i) {
			st = new StringTokenizer(br.readLine(), " ");
			for(int j=0; j<C; ++j) {
				origin[i][j] = Integer.parseInt(st.nextToken());
				if(origin[i][j] == -1) {
					airCleaner[k++] = new Pair(i, j);	// 공기청정기 위치
				}
			}
		}
		
		for(int i=0; i<T; ++i) {
			spread_dust();	// 먼지 확산
			activate_airCleaner();	// 공기 청정기 가동
			// 공기 청정기 바로 옆에 있는 먼지는 없앤다.
			origin[airCleaner[0].r][airCleaner[0].c+1] = 0;
			origin[airCleaner[1].r][airCleaner[1].c+1] = 0;
		}
	
		int sum = 0;
		for(int i=0; i<R; ++i) {
			for(int j=0; j<C; ++j) {
				if(origin[i][j] != -1)
					sum+=origin[i][j];
			}
		}
		
		System.out.println(sum);
	}
}