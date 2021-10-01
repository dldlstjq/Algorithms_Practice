/*
자바로 다시 풀었을 때 시간이 많이 나온걸로 기억난 문제이다.
처음에 좌표 저장하는데 시간을 조금 썼던것 같고 전에 봤을 때 제자리로 돌아오는 경우를 생각해서 모듈러 연산을 진행했다.
근데 나누는 값을 잘못 정해서 시작하자마자 틀렸다.
좌우 이동은 (C+1)*2, 상하 이동은 (R+1)*2 배수만큼 돌면 제자리로 돌아온다.
하지만 나는 입력 예제만 보고 값을 잘못 정해서 틀렸다.

그래도 한 번 풀었던 문제를 다시 푸는데 시간이 덜 걸리는데서 위안을 얻어야겠다.
구현 능력이 많이 좋아진 것 같긴 하다.
*/

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.StringTokenizer;


public class Main {
	
	static class Shark{
		int r, c, s, dir, size;
		Shark(int r, int c, int s, int dir, int size){
			this.r=r;
			this.c=c;
			this.s=s;
			this.dir=dir;
			this.size=size;
		}
	}
	
	static int R, C, M;
	static Shark[][] map;
	static Shark[][] tmp;	// 이동한 상어 저장
	
	static int dr[] = {0,-1,1,0,0};	// 상하우좌 순서
	static int dc[] = {0,0,0,1,-1};
	
	public static void main(String[] args) throws Exception {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine());
		
		R = Integer.parseInt(st.nextToken());
		C = Integer.parseInt(st.nextToken());
		M = Integer.parseInt(st.nextToken());
		
		map = new Shark[R+1][C+1];
		
		for(int i=0; i<M; ++i) {
			st = new StringTokenizer(br.readLine());
			int r = Integer.parseInt(st.nextToken());
			int c = Integer.parseInt(st.nextToken());
			int s = Integer.parseInt(st.nextToken());
			int d = Integer.parseInt(st.nextToken());
			int z = Integer.parseInt(st.nextToken());
			
			map[r][c] = new Shark(r, c, s, d, z);	// r,c에 상어 속도, 방향, 크기 저장
		}
		
		int ans = 0;
		for(int i=1; i<=C; ++i) {
			for(int j=1; j<=R; ++j) {
				// 상어를 잡는다
				if(map[j][i] != null) {
					ans += map[j][i].size;
					map[j][i] = null;
					break;
				}
			}
			
			tmp = new Shark[R+1][C+1];
			searchShark();
			
            // tmp를 다시 map에 복사
			copyArray();
		}
		
		System.out.println(ans);
	}

	private static void copyArray() {
		// map에다 다시 정보 저장
		for(int i=0; i<=R; ++i)
			map[i] = tmp[i].clone();
	}
	
	// 상어 위치를 찾아서 이동
	private static void searchShark() {
		for(int j=1; j<=R; ++j) {
			for(int k=1; k<=C; ++k) {
				if(map[j][k] != null)
					moveShark(map[j][k]);
			}
		}
	}

	private static void moveShark(Shark fish) {
		// 상어 정보
		int r =fish.r;	
		int c= fish.c;
		int s= fish.s;	
		int dir = fish.dir;
		int size = fish.size;
		
		// 경계면에 붙어있는 경우 이동방향이 반대로 되나
		// 다시 이동할 때는 방향을 바꾸기 때문에 방향은 바꿔줄 필요 없음.
		
		// 방향이 위나 아래인 경우 2*(R-1)의 배수 만큼 이동하면 제자리
		if(dir == 1 || dir == 2)
			s %= 2*(R-1);
		// 좌,우 방향은 2*(C-1) 배수만큼 이동하면 제자리
		else if(dir== 3 || dir == 4)
			s %= 2*(C-1);
		
		int time = s;	// 속력만큼 이동
		while(time > 0) {
			int nr = r+dr[dir];
			int nc = c+dc[dir];
			// 범위를 벗어나면 방향을 반대로 하고 한 칸 이동
			if(!inRange(nr, nc)) {
				if(dir==1 || dir==3) 
					dir++;
				else 
					dir--;
				r += dr[dir];
				c += dc[dir];
				time--;
				continue;
			}
			r=nr; c=nc;
			time--;
		}
		
		// r, c에 다른 물고기가 있다면 크기 비교해서 큰 상어만 남긴다.
		if(tmp[r][c] != null) {
			if(size > tmp[r][c].size)
				tmp[r][c] = new Shark(r, c, s, dir, size);
		}
		// 없으면 그냥 저장
		else
			tmp[r][c] = new Shark(r, c, s, dir, size);
	}

	private static boolean inRange(int r, int c) {
		return 1<=r && r<=R && 1<=c && c<=C;
	}
}