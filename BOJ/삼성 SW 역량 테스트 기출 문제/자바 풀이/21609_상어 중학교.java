/*
2시간 가까이 다되서야 해결했다.
실제 시험에서 값이 잘 안나와서 결국 못풀었던 문제였다.
값이 제대로 안나온 이유는 조건을 제대로 확인하지 않은 것, 구현을 잘못한 것 2가지로 나뉜다.

구현 문제
1. 중력에 의해 내려오는 블록을 제대로 구현하지 못했다.
중간에 검은색 블록이 있는 경우 더 이상 내려오지 못하는데, 검은색 블록이 한 열에 여러개 있는 경우를 고려하지 못했다.
이 부분에서 구현을 못해 답이 제대로 안나왔다.

2. 무지개 블록
블록 그룹을 구할 때 무지개 블록은 모든 블록에 속할 수 있다. 
그래서 번호가 있는 블록의 경우 한 번 블록 그룹에 속하면 그룹안에 있는 블록은 다시 그룹 계산할 필요가 없다.
하지만 무지개 블록은 한 그룹에 속했다고 해서 그룹 계산을 하지 않는 것이 아니라 인접한 또 다른 블록에도 속할 수 있기 때문에 visited 계산을 따로 해야 한다.
이 부분을 생각하지 못했다

조건 문제
1. 블록 그룹의 기준은 무지개 블록이 아닌 블록 중 행, 열번호가 가장 작은 블록
무지개 블록이 아닌 블록들이 기준이 될 수 있지만 무지개 블록도 기준이 될 수 있도록 구현해버렸다.
그리고 기준 블록은 행, 열 번호가 가장 작은 것이고 그것들 중 행, 열이 가장 큰 것이 없어질 블록인데 이것도 잘못생각해서 그룹중 가장 행, 열번호가 큰 블록 좌표를 기준으로 잡아버렸다.

즉, 블록 그룹을 계산할 때 시작 좌표가 기준 블록이 되는 것이다.
크기, 무지개 블록 수, 기준 시작 좌표(r,c) 총 4개를 정렬 기준으로 삼아서 정렬하면 된다.

직접 표를 그려가며 뭐가 잘못됐는지 파악해서 해결할 수 있었다.
문제를 잘 읽어야 함을 다시 깨달았고 그룹을 셀 때 무지개 블록은 여러 곳에 속할 수 있다는 것을 잘 알아야지만 해결할 수 있는 문제인 것 같다.
*/

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.LinkedList;
import java.util.List;
import java.util.Queue;
import java.util.StringTokenizer;


/**
 * 무지개 보석을 visited 하나로 관리하면 다른 번호 보석들은 인접한 무지개보석을 세지 못한다.
 * 블록 그룹의 기준 블록은 무지개 블록이 아닌 블록 중에서 행, 열번호가 가장 작은 블록이다.
 * 중력이 내려올 떄 검은색 보석은 내려오지 않는다.
 * 검은색 보석 위에 있는 보석들은 검은색 보석까지만 내려온다.
 * 중력발동 시 검은색 보석이 여러개인 경우 내려올 떄 가장 가까운 검은색 보석에서 멈춘다.
 * */

public class Main {
	
	static class Block implements Comparable<Block>{
		int size; int rainbow; int r; int c;
		
		Block(int size, int rainbow, int r, int c){
			this.size=size;
			this.rainbow=rainbow;
			this.r=r;
			this.c=c;
		}
		
		Block(int r, int c){
			this.r=r;
			this.c=c;		
		}
		
		@Override
		public int compareTo(Block o) {
			if(this.size == o.size) {
				if(this.rainbow == o.rainbow) {
					if(this.r == o.r)
						return Integer.compare(o.c, this.c);
					return Integer.compare(o.r, this.r);
				}
				return Integer.compare(o.rainbow, this.rainbow);
			}
			return Integer.compare(o.size, this.size);
		}
	}
	
	static int N, M;
	static int board[][];
	static int tmp[][];
	
	static List<Block> cand;
	static boolean[][] visited;
	static boolean[][] rainbowVisited;
	static int dr[]= {-1,0,1,0};
	static int dc[]= {0,1,0,-1};
	
	
	public static void main(String[] args) throws Exception {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine());
		
		N = Integer.parseInt(st.nextToken());
		M = Integer.parseInt(st.nextToken());
		
		board = new int[N][N];
		for(int i=0; i<N; ++i) {
			st = new StringTokenizer(br.readLine());
			for(int j=0; j<N; ++j) {
				board[i][j] = Integer.parseInt(st.nextToken());
			}
		}
		
		int score = 0;
		// 오토 플레이 시작
		while(true) {
			
			cand = new ArrayList<>();
			visited = new boolean[N][N];
			
			findBlockGroup();
			
			// 블록 그룹이 없으면 종료
			if(cand.isEmpty()) break;
			
			Collections.sort(cand);	// 기준에 따라 정렬
			
			// 블록 부수기 
			breakBlock(cand.get(0).r, cand.get(0).c);

			// 점수 계산
			score += cand.get(0).size*cand.get(0).size;
			
			// 중력작용
			downBlock();
			
			// 90도 반시계 회전
			rotateBlock();
			
			// 중력작용
			downBlock();
		}
		
		System.out.println(score);
		
	}

    // 90도 반시계 회전
	private static void rotateBlock() {
		tmp = new int[N][N];
		
		for(int i=0; i<N; ++i){
			int k = N-1;
			for(int j=0; j<N; ++j) {
				tmp[k--][i] = board[i][j];
			}
		}
		
		copyArray(tmp, board);	// tmp를 board에 복사
	}

	private static void downBlock() {
		
		for(int i=0; i<N; ++i) {
			// 검은색 블록을 만나면 -1, 아니면 블록 번호를 리스트에 저장
			List<Integer> list = new ArrayList<>();
			for(int j=N-1; j>=0; --j) {
				// 검은색 브록은 -1
				if(board[j][i] == -1) {
					list.add(-1);
					continue;
				}
				// 빈칸은 패스
				else if(board[j][i] ==- 2) continue;
				
				list.add(board[j][i]);    
				board[j][i] = -2;	// 빈 칸 만들기
			}
			
			int k=0;
			if(list.isEmpty()) continue;    // 내릴 블록이 없으면 패스
			
			for(int j=N-1; j>=0; --j)  {
                // 검은색 블록을 만나면 리스트 인덱스 증가, j 감소
				if(board[j][i] == -1) {
					k++;
					if(k == list.size()) break;
					continue;
				}
				// 리스트 값이 -1이면 j만 감소
				else if(list.get(k) == -1) continue;
				
				else if(list.get(k) != -1) {
					board[j][i] = list.get(k++);
					if(k == list.size()) break;
				}
			}
		}
	}

	
	// 블록 그룹 부수기
	private static void breakBlock(int r, int c) {
		Queue<Block> q=  new LinkedList<>();
		boolean[][] isbroken = new boolean[N][N];
		int num = board[r][c];	// 부술 블록 번호
		isbroken[r][c] = true;
		
		board[r][c] = -2;
		q.offer(new Block(r, c));
		
		
		while(!q.isEmpty()) {
			Block now = q.poll();
			
			for(int i=0; i<4; ++i) {
				int nr = now.r+dr[i];
				int nc = now.c+dc[i];
				
				if(!isIn(nr, nc) || isbroken[nr][nc]) continue;

				// 같은 그룹이거나 무지개색이면 연결
				if(board[nr][nc] == num || board[nr][nc] ==0) {
					
					board[nr][nc] = -2;
					isbroken[nr][nc] = true;
					q.offer(new Block(nr, nc));
				}
			}
		}
	}
	
    // 블록 찾기
	private static void findBlockGroup() {
		for(int i=0; i<N; ++i) {
			for(int j=0; j<N; ++j) {
				// 검은색, 무지개, 빈칸은 패스 
				if(board[i][j] == 0 || board[i][j]==-1 || 
						board[i][j]==-2 || visited[i][j]) continue;
				saveBlockGroup(i, j);
			}
		}
	}

    // 블록 그룹 검사
	private static void saveBlockGroup(int r, int c) {
		
		Queue<Block> q=  new LinkedList<>();
		rainbowVisited = new boolean[N][N];
		
		visited[r][c] = true;
		q.offer(new Block(r, c));
		
		int size = 1;
		int rainbow = 0;
		int maxR=r, maxC =c;
		
		while(!q.isEmpty()) {
			Block now = q.poll();
			
			for(int i=0; i<4; ++i) {
				int nr = now.r+dr[i];
				int nc = now.c+dc[i];
				
				// 범위 아웃
				if(!isIn(nr, nc)) continue;	
				
				// 같은 블록인데 방문했다면 패스
				else if(board[nr][nc] == board[r][c] && visited[nr][nc]) continue;

				// 무지개 블록인데 방문했다면 패스
				else if(board[nr][nc] == 0 && rainbowVisited[nr][nc]) continue;
				
				// 같은 그룹이거나 무지개색이면 연결
				if(board[nr][nc] == board[r][c] || board[nr][nc] ==0){
					size++;
					
                    // 무지개 블록은 무지개 블록 방문 표시
					if(board[nr][nc] == 0) {
						rainbow++;
						rainbowVisited[nr][nc] = true;
					}
					else visited[nr][nc] = true;    // 일반 블록 방문 표시
					
					q.offer(new Block(nr, nc));
				}
				
			}
		}
		
		// 크기 2 이상인 후보 그룹을 cand에 저장
		if(size>=2)
			cand.add(new Block(size, rainbow, r, c));
	}
	
	private static void copyArray(int[][] board, int[][] tmp) {
		for(int i=0; i<N; ++i)
			tmp[i] = board[i].clone();
	}



	private static boolean isIn(int r, int c) {
		return 0<=r && r<N && 0<=c && c<N;
	}
	
}
