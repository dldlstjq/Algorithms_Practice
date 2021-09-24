/*
7576 토마토랑 같은 문제인데 3차원에서 구해야 한다.
높이를 설정하고 그에 따라 좌표나 배열을 바꿔줘야 하는데 3차원이라서 조금 헷갈렸다.
3차원은 높이, 가로, 세로 순서로 배열을 저장해야하고 클래스에서는 가로, 세로, 높이 순서로 설정했기 때문에 잘 보고 넣어줘야 한다.
탐색을 위한 값은 상하좌우 사방에다가 위, 아래 2개를 추가해줘야 한다.
*/
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.Arrays;
import java.util.LinkedList;
import java.util.Queue;
import java.util.StringTokenizer;

public class Main {
	
	static class Pos{
		int r, c, h;
		Pos(int r, int c, int h){
			this.r=r;
			this.c=c;
			this.h=h;
		}
	}
	
	static int N, M, H;
	static int[][][]map;

	static int dr[] = {0,0,-1,0,1,0};
	static int dc[] = {0,0,0,1,0,-1};
	static int dh[] = {1,-1,0,0,0,0};
	
	static Queue<Pos> q;
	
	public static void main(String[] args) throws Exception{
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine());
		
		M = Integer.parseInt(st.nextToken());
		N = Integer.parseInt(st.nextToken());
		H = Integer.parseInt(st.nextToken());
		map = new int[H][N][M];
		q = new LinkedList<>();
		
		int blank = 0;	// 빈칸 개수
		for(int i=0; i<H; ++i) {
			for(int j=0; j<N; ++j) {
				st = new StringTokenizer(br.readLine());
				for(int k=0; k<M; ++k) {
					map[i][j][k] = Integer.parseInt(st.nextToken());
					if(map[i][j][k] == 1)
						q.offer(new Pos(j, k, i));	// 가로, 세로, 높이로 저장
					if(map[i][j][k] == 0)
						blank++;
				}
			}
		}
		
		System.out.println(bfs(blank));
	}

	// 토마토가 익는다.
	private static int bfs(int blank) {
		int tomatoCnt=0;
		int day=0;
		while(!q.isEmpty()) {
			int size = q.size();
			
			day++;
			while(size-- > 0) {
				Pos curr = q.poll();
				
				for(int i=0; i<6; ++i) {
					int nr = curr.r+dr[i];
					int nc = curr.c+dc[i];
					int nh = curr.h+dh[i];
					
					// 경계 체크
					if(nr<0 || nr>=N || nc<0 || nc>=M || nh<0 || nh>=H) continue;
					
					// 익지 않은 토마토만 익을 수 있다.
					if(map[nh][nr][nc] != 0) continue;
					
					// 익은 토마토에 +1을 해서 저장
					map[nh][nr][nc] = 1;
					q.offer(new Pos(nr, nc, nh));
					tomatoCnt++;
				}
			}
		}
		
		if(blank != tomatoCnt)
			day = 0;
		return day-1;
	}
}

