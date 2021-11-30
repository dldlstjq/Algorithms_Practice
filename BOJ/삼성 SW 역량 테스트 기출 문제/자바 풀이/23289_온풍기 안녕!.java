/*
전체 해결하는데 3시간 이상 걸렸다.
문제 이해 부터 어려웠는데 내 블로그에 상세히 정리했다.
문제조건이 많아 더 까다로운 것 같았는데 그래도 하나씩 잘 처리했다.
해결한 것에 의의를 두고 싶다.
*/

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.LinkedList;
import java.util.List;
import java.util.Queue;
import java.util.StringTokenizer;

public class Main {
	
	static class Pos{
		int x; int y; int t;
		Pos(int x, int y){
			this.x=x;
			this.y=y;
		}
//		Pos(int x, int y, int t){
//			this.x=x;
//			this.y=y;
//			this.t=t;
//		}
	}
	
	static class wallPos{
		int x; int y; int t;
		wallPos(int x, int y, int t){
			this.x=x;
			this.y=y;
			this.t=t;
		}
	}
	
	static int R,C,K,W;
	static int x,y,t;
	static int map[][];		// 온풍기, 조사해야할 칸 정보 저장
	static int value[][];	// 열 정보 저장
	
    // 온도가 퍼지는 방향 
	static int dr[][] = {
			{},
			{-1,0,1},
			{-1,0,1},
			{-1,-1,-1},
			{1,1,1},
	};
	static int dc[][] = {
			{},
			{1,1,1},
			{-1,-1,-1},
			{-1,0,1},
			{-1,0,1},
	};
	
	static int dr2[] = {-1,0,1,0};
	static int dc2[] = {0,1,0,-1};
	
	static int borderDr[] = {0,1,0,-1};	// 경계 검사할때 사용
	static int borderDc[] = {1,0,-1,0};
	
	static List<Pos> hitter;	// 온풍기 좌표
	static List<Pos> checkPos;	// 조사해야 할 칸
	static List<wallPos> wall;	// 벽 위치
	
	static int choco;	// 먹은 초코
	
	public static void main(String[] args) throws Exception {
		//System.setIn(new FileInputStream("input.txt"));
		BufferedReader br=  new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine());
		
		R = Integer.parseInt(st.nextToken());
		C = Integer.parseInt(st.nextToken());
		K = Integer.parseInt(st.nextToken());
		
		map = new int[R][C];
		value = new int[R][C];
		checkPos = new ArrayList<>();
		hitter = new ArrayList<>();
		wall = new ArrayList<>();
		
		for(int i=0; i<R; ++i) {
			st = new StringTokenizer(br.readLine());
			for(int j=0; j<C; ++j) {
				map[i][j] = Integer.parseInt(st.nextToken());
				// 온풍기 좌표
				if(1<=map[i][j] && map[i][j]<=4)
					hitter.add(new Pos(i, j));
				
				// 조사해야 할 좌표 저장
				if(map[i][j] == 5)
					checkPos.add(new Pos(i, j));
			}
		}
		
		W = Integer.parseInt(br.readLine());
		for(int i=0; i<W; ++i) {
			st = new StringTokenizer(br.readLine());
			x = Integer.parseInt(st.nextToken());
			y = Integer.parseInt(st.nextToken());
			t = Integer.parseInt(st.nextToken());
			// t==0 이면 (x, y)와 (x-1, y) 사이에 벽이 있는 것
			// t==1 이면 (x, y)와 (x, y+1) 사이에 벽이 있는 것
			wall.add(new wallPos(x-1,y-1,t));
		}    
		
		while(true) {
			// 온풍기 위치에서 열이 나온다.
			for(int i=0; i<hitter.size(); ++i) {
				int r = hitter.get(i).x;
				int c = hitter.get(i).y;
				spreadHit(r, c, map[r][c]);
			}
			
//			for(int i=0; i<R; ++i)
//				System.out.println(Arrays.toString(value[i]));
			
			// 온도 조절
			adjustTemperature();
//			System.out.println();
//			for(int i=0; i<R; ++i)
//				System.out.println(Arrays.toString(value[i]));
			
			outsideTempDown();	// 가장 바깥쪽 온도 1씩 감소
//			System.out.println();
//			for(int i=0; i<R; ++i)
//				System.out.println(Arrays.toString(value[i]));
			
			choco++;
			// 먹는 초콜릿의 개수가 100을 넘어가면 101 출력
			if(choco > 100) {
				choco = 101;
				break;
			}
	
			// 검사 좌표의 온도가 K이상인지 확인
			int cnt = 0;
			for(int i=0; i<checkPos.size(); ++i) {
				int r = checkPos.get(i).x;
				int c = checkPos.get(i).y;
				if(value[r][c] >= K)
					cnt++;
			}
			// 모든 좌표가 K 이상이면 종료
			if(cnt == checkPos.size())
				break;
		}
		System.out.println(choco);
	}
	
	// 가장 바깥쪽 온도 1 감소
	private static void outsideTempDown() {
		for(int i=0; i<C; ++i) 
			if(value[0][i] > 0) value[0][i]--;
		
		for(int i=1; i<R; ++i) 
			if(value[i][C-1] > 0) value[i][C-1]--;
		
		for(int i=0; i<C-1; ++i) 
			if(value[R-1][i] > 0) value[R-1][i]--;
		
		for(int i=1; i<R-1; ++i) 
			if(value[i][0] > 0) value[i][0]--;
	}

	// 온도 조절
	private static void adjustTemperature() {
		int tmp[][] = new int[R][C];
		
		for(int i=0; i<R; ++i) {
			for(int j=0; j<C; ++j) {
				if(value[i][j] == 0) continue;
				tmp = checkTemp(i, j, tmp);
			}
		}
		copyArray(value, tmp);	// tmp를 value에 저장
	}

	
	private static void copyArray(int[][] a, int[][] b) {
		for(int i=0; i<R; ++i)
			a[i] = b[i].clone();
	}

	// 인접한 곳 온도 확인
	private static int[][] checkTemp(int r, int c, int[][] tmp) {
		int sum = 0;
		
		// 인접한 네 곳 
		for(int i=0; i<4; ++i) {
			int nr = r+dr2[i];
			int nc = c+dc2[i];
			// 범위를 벗어나거나 값이 크거나 같으면 조절 안됨
			if(!isIn(nr, nc) || value[nr][nc] >= value[r][c]) continue;
			
			// 벽이 있으면 안됨
			if(i==0 && isContains(r, c, 0)) continue;
			if(i==1 && isContains(r, c, 1)) continue;
			if(i==2 && isContains(r+1, c, 0)) continue;
			if(i==3 && isContains(r, c-1, 1)) continue;
			
			// 온도가 높은 칸에서 낮은 칸으로 ⌊(두 칸의 온도의 차이)/4⌋만큼 온도가 조절
			int temperature = (int) Math.floor((double)(value[r][c]-value[nr][nc])/4);
			tmp[nr][nc] += temperature;	// 온도 추가
			sum += temperature;	// (r,c)에서 빠질 온도
		}
		// 기존 온도에서 sum만큼 없어진 값을 r,c에 저장
		tmp[r][c] += value[r][c]-sum>=0 ? value[r][c]-sum : 0;
		return tmp;
	}

	// 열이 퍼진다.
	private static void spreadHit(int r, int c, int dir) {
		int tmp[][] = new int[R][C];
		boolean visited[][] = new boolean[R][C];
		Queue<Pos> q = new LinkedList<>();
		int start = 5;	// 처음 온도
		
		// 1: 오른쪽 2: 왼쪽 3:위 4:아래
        // 시작 좌표를 설정한다
		if(dir == 1) c+=1;
		else if(dir == 2) c-=1;
		else if(dir == 3) r-=1;
		else if(dir == 4) r+=1;
		
		// 맨 처음
		tmp[r][c] = start;
		q.offer(new Pos(r, c));
		visited[r][c] = true;
		
		
		while(!q.isEmpty()) {
			int size = q.size();
			int num = --start;	// 온풍기의 온도
			
//			for(int i=0; i<R; ++i)
//				System.out.println(Arrays.toString(tmp[i]));
//			System.out.println();
			
			if(num == 0) break;	// 온도가 0이면 더 할 필요 없음
			
			for(int a=0; a<size; ++a) {
				Pos now = q.poll();
				
				for(int i=0; i<3; ++i) {
					// 다음 좌표
					int nr = now.x+dr[dir][i];
					int nc = now.y+dc[dir][i];
					
					// 범위를 벗어나거나 한 번 온도가 퍼지면 패스
					if(!isIn(nr, nc) || visited[nr][nc]) continue;
					
					// 벽이 있으면 안됨
					if(isWall(now.x, now.y, dir, i)) continue;
					
					visited[nr][nc] = true;
					tmp[nr][nc] = num;
					q.offer(new Pos(nr, nc));
				}
			}
		}
		
		// 온도를 value에다가 합침
		for(int i=0; i<R; ++i) {
			for(int j=0; j<C; ++j) {
				value[i][j] += tmp[i][j];
			}
		}	
	}

	private static boolean isWall(int r, int c, int dir, int d) {
		// 오른쪽 방향이면 위에서부터 d=0,1,2
		if(dir == 1) {
			// t==0 이면 (x, y)와 (x-1, y) 사이에 벽이 있는 것
			// t==1 이면 (x, y)와 (x, y+1) 사이에 벽이 있는 것
			if(d == 0) {
				if(isContains(r, c, 0) || isContains(r-1, c, 1))
					return true;
			}
			else if(d == 1) {
				if(isContains(r, c, 1) )
					return true;
			}
			else if(d == 2) {
				if(isContains(r+1, c, 0) || isContains(r+1, c, 1))
					return true;
			}
		}
		
		// 왼쪽 방향이면 위에서부터 d=0,1,2
		else if(dir == 2) {
			// t==0 이면 (x, y)와 (x-1, y) 사이에 벽이 있는 것
			// t==1 이면 (x, y)와 (x, y+1) 사이에 벽이 있는 것
			if(d == 0) {
				if(isContains(r, c, 0) || isContains(r-1, c-1, 1))
					return true;
			}
			else if(d == 1) {
				if(isContains(r, c-1, 1))
					return true;
			}
			else if(d == 2) {
				if(isContains(r+1, c-1, 1) || isContains(r+1, c, 0))
					return true;
			}
		}
		
		// 위쪽 방향이면 왼쪽에서부터 d=0,1,2
		else if(dir == 3) {
			// t==0 이면 (x, y)와 (x-1, y) 사이에 벽이 있는 것
			// t==1 이면 (x, y)와 (x, y+1) 사이에 벽이 있는 것
			if(d == 0) {
				if(isContains(r, c-1, 0) || isContains(r, c-1, 1))
					return true;
			}
			else if(d == 1) {
				if(isContains(r, c, 0))
					return true;
			}
			else if(d == 2) {
				if(isContains(r, c, 1) || isContains(r, c+1, 0))
					return true;
			}
		}
		
		// 아래쪽 방향이면 왼쪽에서부터 d=0,1,2
		else if(dir == 4) {
			// t==0 이면 (x, y)와 (x-1, y) 사이에 벽이 있는 것
			// t==1 이면 (x, y)와 (x, y+1) 사이에 벽이 있는 것
			if(d == 0) {
				if(isContains(r, c-1, 1) || isContains(r+1, c-1, 0))
					return true;
			}
			else if(d == 1) {
				if(isContains(r+1, c, 0))
					return true;
			}
			else if(d == 2) {
				if(isContains(r, c, 1) || isContains(r+1, c+1, 0))
					return true;
			}
		}
		return false;
	}

	// 벽 정보가 있는지 검사
	private static boolean isContains(int r, int c, int ti) {
		for(int i=0; i<wall.size(); ++i) {
			if(wall.get(i).x == r && wall.get(i).y == c && wall.get(i).t == ti)
				return true;
		}
		return false;
	}
	
	// 범위 벗어나는지 검사
	private static boolean isIn(int r, int c) {
		return 0<=r && r<R && 0<=c && c<C;
	}
}