/*
저번에 풀 때 왜 못풀었는지 알면서도 1시간 30분안에는 풀지 못했다.
무지개 보석은 따로 visited 처리 해야 하는걸 알았지만 구현에 실수를 했다.
일반 보석은 전역 visited로 처리해도 되지만 무지개보석은 여러번 포함될 수 있기 때문에 한번에 처리하면 안된다.
여기까지는 잘 구현했지만 무지개보석도 결국 하나의 블록그룹을 구할 때 visited 처리를 해야 무한 루프를 돌지 않으므로 지역변수로 따로 선언해서 해야 하는데 이 부분을 깜빡해서 무한루프를 도는 문제가 발생했다.

중력처리에도 시간이 많이 걸렸는데 -1을 만나는 순간 이떄까지 저장한 보석을 하나씩 밑에서 넣어주는 방식을 썼다.
그것보다 전에 풀었던 방식으로 -1까지 리스트에 넣어준 후 -1을 만나면 행을 한칸 옮기고 이런식이 더 쉽게 구현이 될 것 같다.

마지막으로 블록 파괴나 그룹을 계산할때 빈 공간이라는 조건도 빼먹어 버렸다.
*/

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.LinkedList;
import java.util.List;
import java.util.PriorityQueue;
import java.util.Queue;
import java.util.StringTokenizer;


public class Main
{
	static class Block implements Comparable<Block>{
		int cnt; int rainbow; int row; int col;
		Block(int cnt, int rainbow, int row, int col){
			this.cnt=cnt;
			this.rainbow=rainbow;
			this.row=row;
			this.col=col;
		}
		
		@Override
		public int compareTo(Block o) {
			if(this.cnt==o.cnt) {
				if(this.rainbow == o.rainbow) {
					if(this.row==o.row)
						return Integer.compare(o.col, this.col);
					return Integer.compare(o.row, this.row);
				}
				return Integer.compare(o.rainbow, this.rainbow);
			}
			return Integer.compare(o.cnt, this.cnt);
		}
	}
	
	static class Pos{
		int r; int c;
		Pos(int r, int c){
			this.r=r;
			this.c=c;
		}
	}
	
	static int N, M;
	static int[][] map;
	static int[][] tmp;
	static boolean[][] visited;
	static PriorityQueue<Block> pq;
	
	static int dr[]= {-1,0,1,0};
	static int dc[]= {0,1,0,-1};
	
	static int score;
	
    public static void main(String args[]) throws Exception{
	    BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
	    StringTokenizer st = new StringTokenizer(br.readLine());
	    
	    N = Integer.parseInt(st.nextToken());
	    M = Integer.parseInt(st.nextToken());
	    
	    map = new int[N][N];
	    tmp = new int[N][N];
	    pq = new PriorityQueue<>();
	    
	    for(int i=0; i<N; ++i) {
	    	st = new StringTokenizer(br.readLine());
	    	for(int j=0; j<N; ++j)
	    		map[i][j] = Integer.parseInt(st.nextToken());
	    }
	    
	    while(isBlockGroup()) {
	    	Block b = pq.poll();	// 가장 우선순위가 높은 블록 그룹
	    	
	    	// 블록 그룹 중 우선순위가 높은 것 파괴
	    	destroyBlock(b.row, b.col);
	    	pq.clear();	// pq 초기화
	    	score += b.cnt*b.cnt;	// 블록수 제곱만큼 득점
	    	
	    	// 중력 작용
	    	downBlock();
	    	rotate();
	    	downBlock();
	    }
	    
	    System.out.println(score);
    }

    private static void rotate() {
		int[][] tmp = new int[N][N];
		
		for(int i=0; i<N;++i) {
			int k=N-1;
			for(int j=0; j<N; ++j) {
				tmp[k--][i] = map[i][j];
			}
		}
		copy(tmp);
	}

	private static void copy(int[][] tmp) {
		for(int i=0; i<N; ++i)
			map[i] = tmp[i].clone();
	}

	private static void downBlock() {
		for(int i=0; i<N; ++i) {
			List<Integer> list = new ArrayList<>();
            
			int start = -1;
			for(int j=N-1; j>=0; --j) {
				// 검은 블록을 만나는 순간 list에 저장한 블록을 start부터 현재 위치 전까지 넣어준다.
				if(map[j][i] == -1) {
					int idx=0;
					
					if(!list.isEmpty()) {
						for(int k=start; k>j; --k) {
							map[k][i] = list.get(idx++);
							if(idx == list.size()) break;
						}
						list.clear();
					}
					start = -1;	// 시작좌표 초기화. 현재 검은 블록 위부터 블록을 넣을 수 있다.
					continue;
				}
				
				// 시작 좌표
				else {
					// 시작좌표가 초기화상태라면 갱신
					if(start == -1)
						start = j;
					if(0<=map[j][i] && map[j][i]<=M) {
						list.add(map[j][i]);
						map[j][i] = -4;
					}
						
				}
			}
			
			// 마지막에 든 보석을 모두 내려준다
			int idx=0;
			if(!list.isEmpty()) {
				for(int k=start; k>=0; --k) {
					map[k][i] = list.get(idx++);
					if(idx == list.size()) break;
				}
			}
		}
	}

	private static void destroyBlock(int r, int c) {
    	Queue<Pos> q = new LinkedList<>();
		
		// 무지개 보석 전용 방문 배열
		boolean[][] v = new boolean [N][N];
		
		// 번호르 따로 저장 후 시작 좌표를 먼저 파괴
		int num = map[r][c];
		map[r][c] = -4;
		q.offer(new Pos(r, c));
		v[r][c] = true;
		
		// 인접한 블록 그룹 찾기
		while(!q.isEmpty()) {
			Pos now = q.poll();
			
			for(int i=0; i<4; ++i) {
				int nr = now.r+dr[i];
				int nc = now.c+dc[i];
				
				// 범위 아웃이거나 방문한 것이면 패스
				if(!isIn(nr, nc) || v[nr][nc]) continue;
				
				// 검은색 블록이나 빈 공간, 자기 번호랑 다르면 패스
				if(map[nr][nc] == -1 || map[nr][nc] == -4 || (map[nr][nc]>=1 && map[nr][nc] != num)) continue;
				
				map[nr][nc] = -4;	// 파괴된 것은 -4로 표시
				q.offer(new Pos(nr, nc));
				v[nr][nc] = true;
			}
		}
	}

	// 블록 그룹이 존재하는지 확인
	private static boolean isBlockGroup() {
		visited = new boolean[N][N];
		for(int i=0; i<N; ++i) {
	    	for(int j=0; j<N; ++j) {
	    		// 무지개 블록과 검은 블록, 빈 공간은, 검사한 블록은 패스
	    		if(map[i][j]==0 || map[i][j] == -1 || map[i][j] == -4 || visited[i][j]) continue;
	    		calcBlock(i, j);
	    	}
	    }
		if(pq.isEmpty()) return false;
		return true;
	}

	private static void calcBlock(int r, int c) {
		Queue<Pos> q = new LinkedList<>();
		
		// 무지개 보석 전용 방문 배열
		boolean[][] rainbowVisited = new boolean [N][N];
		int cnt = 1;
		int rainbowCnt = 0;
		
		q.offer(new Pos(r, c));
		visited[r][c] = true;
		
		// 인접한 블록 그룹 찾기
		while(!q.isEmpty()) {
			Pos now = q.poll();
			
			for(int i=0; i<4; ++i) {
				int nr = now.r+dr[i];
				int nc = now.c+dc[i];
				
				// 범위 아웃이거나 방문한 것이면 패스
				if(!isIn(nr, nc) || visited[nr][nc]) continue;
				
				// 검은색 블록이나 자기 번호랑 다르면 패스
				if(map[nr][nc] == -1 || map[nr][nc] == -4|| (map[nr][nc]>=1 && map[nr][nc] != map[r][c])) continue;
				
				
				// 무지개 블록인데 방문 했으면 패스
				if(map[nr][nc] == 0 && rainbowVisited[nr][nc]) continue;
				
				// 기준 블록 선택
				// 무지개 블록이 아니고 자기랑 같은 번호 블록 중 크기
				if(map[nr][nc] != 0 && map[nr][nc] == map[r][c]) {
					// 색깔이 있는 블록만 방문 표시
					// 무지개 블록은 어떤 번호의 색깔이던지 모두 포함 가능하므로 true로 설정하면 다른 색에 포함이 안되게 됨
					visited[nr][nc] = true;	
				}
				
				// 무지개 블록 카운팅
                // 무지개 블록 전용 방문 표시
				if(map[nr][nc] == 0) {
					rainbowCnt++;
					rainbowVisited[nr][nc] = true;
				}
				
				q.offer(new Pos(nr, nc));
				cnt++;	// 그룹에 속한 블록 개수
			}
		}
		
		// 그룹에 속한 블록 개수는 2보다 크거나 같아야 한다.
		if(cnt< 2) return;
		
		// 블록 그룹의 기준 블록은 무지개 블록이 아닌 블록 중에서 행의 번호가 가장 작은 블록, 
		// 그러한 블록이 여러개면 열의 번호가 가장 작은 블록이다.
		// 제일 첫 시작 블록이 기준 블록
		pq.offer(new Block(cnt, rainbowCnt, r, c));
	}

	private static boolean isIn(int r, int c) {
		return 0<=r&&r<N && 0<=c&&c<N;
	}
}