/*
14502 연구소 문제와 비슷한데 이번엔 활성, 비활성 바이러스가 추가됐다.
거기다 바이러스 중 M개를 선택하는 것이기 때문에 조합까지 섞어야 된다.
우선 조합을 잘 사용하지 못했다.
싸피에서 순열, 조합을 연습하며 마스터했다고 생각했지만 시간이 지나면서 사용하지 않다 보니 인덱스 설정이 많이 헷갈렸다.

두번째로 비활성 바이러스가 활성 바이러스가 되는 순간을 이해하지 못했다.
처음에는 비활성 바이러스가 활성으로 바뀌는 순간은 1초가 걸리지 않는다고 생각하여 접근했는데 그게 아니었다.
활성 바이러스가 비활성 바이러스로 이동하는 순간 역시 1초가 걸리지만, 이미 바이러스가 있었기 때문에 퍼지는 시간으로는 치지 않는다는 것이다.
그래서 예제 7을 보게 되면 걸리는 시간은 0으로 나와있다.
즉, 퍼지는 건 1초가 계속 걸리지만 빈 칸으로 퍼질때만 해당 시간을 체크한다는 뜻이다.

조합 구현 모호함, 문제 이해 어려움으로 인해 해결하지 못했다.
이 문제를 계기로 다시 한번 순열, 조합 문제를 풀어보거나 복습해야겠고 문제를 좀 더 꼼꼼히 봐야겠다.
*/

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.LinkedList;
import java.util.Queue;
import java.util.StringTokenizer;

public class Main {
	
	static class Pos{
		int x,y;
		Pos(int x, int y){
			this.x=x;
			this.y=y;	
		}
	}
	
	static int N,M;
	static int[][] map;
	static int[][] visited;
	
	static ArrayList<Pos> list = new ArrayList<>(); // 바이러스 저장
	static Pos[] virus;	// 바이러스 M개 저장
	
	static int dx[] = {-1,0,1,0};
	static int dy[] = {0,1,0,-1};
	
	static int minTime;	// 최소 시간
	static int blank;	// 빈 칸 개수
	
	static void combination(int idx, int start) {
		if(idx == M) {
			int[][] tmp = new int[N][N];
			copyArray(map, tmp);
			
			// 바이러스 퍼지기 시작
			spreadVirus(tmp);
			return;
		}
		
		for(int i=start; i<list.size(); ++i) {
			virus[idx] = list.get(i);
			combination(idx+1, i+1);
		}
	}

	private static void spreadVirus(int[][] arr) {
		Queue<Pos> q= new LinkedList<>();
		int infectCnt = 0;	//  빈칸만 카운트
		int time = 0;	// 빈칸일때 시간
		// visited -1로 초기화
		for(int i=0; i<N; ++i)
			Arrays.fill(visited[i], -1);
		
		// 활성화 바이러스를 큐에 저장하고 visited 0으로 변경
		for(int i=0; i<virus.length; ++i) {
			q.offer(virus[i]);
			visited[virus[i].x][virus[i].y] = 0;
		}
		
		while(!q.isEmpty()) {
			int size = q.size();
			
			while(size-- > 0) {
				Pos curr = q.poll();
				
				for(int i=0; i<4; ++i) {
					int nx = curr.x+dx[i];
					int ny = curr.y+dy[i];
					
					// 범위 체크, 벽이 있는 부분, 이미 바이러스가 퍼진 부분은 제외
					if(!inRange(nx, ny) || arr[nx][ny] == 1 || visited[nx][ny] != -1)
						continue;
					
					// 1초마다 바이러스가 퍼진다.
					q.offer(new Pos(nx, ny));
					visited[nx][ny] = visited[curr.x][curr.y]+1;
					
					// 빈 칸인 경우에만 퍼진 시간 저장하고 카운트
					if(arr[nx][ny] == 0) {
						time = visited[nx][ny];
						infectCnt++;
					}
				}
			}
			
		}
		
		// 원래 빈칸과 퍼진 칸의 개수가 같으면 시간 갱신
		// 비활성 바이러스가 활성된 경우는 바이러스가 퍼진것으로 생각하지 않는다.
		if(blank == infectCnt)
			minTime = Math.min(minTime, time);
			
	}
	
	private static void copyArray(int[][] arr1, int[][] arr2) {
		for(int i=0; i<N; ++i)
			arr2[i] = arr1[i].clone();
	}

	private static boolean inRange(int x, int y) {
		return 0<=x && x<N && 0<=y && y<N;
	}

	public static void main(String[] args) throws Exception {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine());
		
		N = Integer.parseInt(st.nextToken());
		M = Integer.parseInt(st.nextToken());
		
		map = new int[N][N];
		visited = new int[N][N];
		virus = new Pos[M];
		minTime = Integer.MAX_VALUE;
		
		for(int i=0; i<N; ++i) {
			st = new StringTokenizer(br.readLine());	
			for(int j=0; j<N; ++j) {
				map[i][j] = Integer.parseInt(st.nextToken());
				if(map[i][j] == 2)
					list.add(new Pos(i,j));
				else if(map[i][j] ==0)
					blank++;
				
			}
		}
		
		// 조합
		combination(0, 0);
		
		if(minTime== Integer.MAX_VALUE)
			System.out.println(-1);
		else
			System.out.println(minTime);
		
	}

}
