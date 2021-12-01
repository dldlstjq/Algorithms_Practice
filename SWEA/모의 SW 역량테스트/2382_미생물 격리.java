/*
이런 문제는 어느 정도 익숙해졌다고 생각했는데 그래도 좀 연습이 필요한 것 같다.
하나의 좌표에는 하나의 미생물만 존재할 수 있기 때문에 굳이 리스트로 선언할 필요가 없었다.
그리고 M시간 동안 NxN 배열을 전부 돌아야 하므로 N*N*M 시간이 들고 합쳐지는 미생물도 4방에서만 올 수 있으므로 최대 4개밖에 되지 않는다.
시간복잡도를 잘못 알았던게 좀 어렵게 접근한 것 같았고 미생물의 좌표를 따로 저장해서 했는데 N*N 자체를 돌아도 상관없는 것 같다.
*/

import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.HashSet;
import java.util.List;
import java.util.Set;
import java.util.StringTokenizer;

public class Solution {
	
	static class Info{
		int cnt; int dir;
		Info(){}
		Info(int cnt, int dir){
			this.cnt=cnt;
			this.dir=dir;
		}
	}
	
	static class Pos{
		int x; int y;
		Pos(int x, int y){
			this.x=x;
			this.y=y;
		}
	}
	
	static int N, M, K;
	static Info map[][];	// 전체 배열
	
	static List<Pos> cell;		// 세포 좌표
	static List<Pos> overlap;	// 세포가 여러개 있는 좌표
	static Set<Pos> over;
	
	// 상: 1, 하: 2, 좌: 3, 우: 4
	static int dr[]= {0, -1,1,0,0};
	static int dc[]= {0, 0,0,-1,1};
	
	
	public static void main(String[] args) throws Exception {
		//System.setIn(new FileInputStream("sample_input.txt"));

		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		
		int T = Integer.parseInt(br.readLine());
		
		for(int test_case = 1; test_case <= T; test_case++)
		{
			StringTokenizer st = new StringTokenizer(br.readLine());
			N = Integer.parseInt(st.nextToken());
			M = Integer.parseInt(st.nextToken());
			K = Integer.parseInt(st.nextToken());
			
			initMap();
			
			cell = new ArrayList<>();
			
			for(int i=0; i<K; ++i) {
				st = new StringTokenizer(br.readLine());
				int r = Integer.parseInt(st.nextToken());
				int c = Integer.parseInt(st.nextToken());
				int cnt = Integer.parseInt(st.nextToken());
				int dir = Integer.parseInt(st.nextToken());
				map[r][c].cnt = cnt;
				map[r][c].dir = dir;
				cell.add(new Pos(r, c));
			}
			
			for(int i=0; i<M; ++i) {
				moveCell();
				
			}
			
			System.out.println("#"+test_case+" "+getCnt());
		}
	}
	
	private static int getCnt() {
		int sum = 0;
		for(int i=0; i<N; ++i)
			for(int j=0; j<N; ++j)
				sum += map[i][j].cnt;
		return sum;
	}

    // tmp 출력
	static void print(List<Info>[][] tmp) {
		for(int i=0; i<N; ++i)
			for(int j=0; j<N; ++j)
				for(int k=0; k<tmp[i][j].size(); ++k)
					System.out.println("("+i+", "+j+"): "
				+ tmp[i][j].get(k).cnt+"개, 방향: "+tmp[i][j].get(k).dir);
	}
	// map 출력
	private static void printMap() {
		for(int i=0; i<N; ++i)
			for(int j=0; j<N; ++j)
				if(map[i][j].cnt != 0)
					System.out.println("("+i+", "+j+"): "
				+ map[i][j].cnt+"개, 방향: "+map[i][j].dir);
	}


	private static void moveCell() {
		List<Info> tmp[][] = new ArrayList[N][N];	// 임시 배열
		init(tmp);
		
		overlap = new ArrayList<>();
		over = new HashSet<>();
		
		for(int i=0; i<cell.size(); ++i) {
			int r = cell.get(i).x;
			int c = cell.get(i).y;
			
			int cnt = map[r][c].cnt;
			int dir = map[r][c].dir;
			
			// 다음 좌표
			int nr = r+dr[dir];
			int nc = c+dc[dir];
			
			if(isBoundary(nr, nc)) {
				//  살아남은 미생물 수 = 원래 미생물 수를 2로 나눈 후 소수점 이하를 버림 한 값
				cnt = (int) Math.floor((double)cnt/2);
				// 이동방향 반대 1 3:상, 좌  2 4: 하, 우
				dir = dir%2 ==0 ?dir-1:dir+1;
			}
			
			// 미생물이 0이면 군집이 사라진다.
			if(cnt == 0) continue;
			
			// 중복된 좌표값 저장
			if(!tmp[nr][nc].isEmpty())
//				overlap.add(new Pos(nr, nc));	
				if(!over.contains(new Pos(nr, nc)))
					over.add(new Pos(nr, nc));
			
			tmp[nr][nc].add(new Info(cnt, dir));
		}
		
		initMap();
		
//		print(tmp);
		
		// 하나만 있는 미생물 이동
		copyMap(tmp);
		
		// 중복 미생물 합친다.
		addOverlap(tmp);
		
//		System.out.println();
//		printMap();
		
		cell.clear();
		for(int i=0; i<N; ++i)
			for(int j=0; j<N; ++j)
				if(map[i][j].cnt != 0)
					cell.add(new Pos(i, j));
		
		
	}
	
	
	// 좌표에 미생물이 하나만 있으면 map에다가 이동
	private static void copyMap(List<Info>[][] tmp) {
		for(int i=0; i<N; ++i)
			for(int j=0; j<N; ++j)
				if(tmp[i][j].size() == 1) {
					map[i][j].cnt = tmp[i][j].get(0).cnt;
					map[i][j].dir = tmp[i][j].get(0).dir;
				}
	}

	// 여러개 미생물이 중복되어 있으면 하나로 합쳐서 map에 저장
	private static void addOverlap(List<Info>[][] tmp) {
		for (Pos pos : over) {
			int r = pos.x;
			int c = pos.y;
			
			// 전체 미생물 수, 최대 값의 방향
			int sum=0;int max=0;
			int dir=0;
			
			for(int k=0; k<tmp[r][c].size(); ++k) {
				int cnt = tmp[r][c].get(k).cnt;
				sum += cnt;
				
				if(max < cnt) {
					max=cnt;
					dir=tmp[r][c].get(k).dir;
				}
			}
			// 원래 배열에 수와 방향 저장
			map[r][c].cnt=sum;
			map[r][c].dir=dir;
		}
	}

	// 가장자리
	private static boolean isBoundary(int r, int c) {
		if(0<=r && r<N && c==0) return true;
		else if(0<=r && r<N && c==N-1) return true;
		else if(0<=c && c<N && r==0) return true;
		else if(0<=c && c<N && r==N-1) return true;
		else return false;
	}

	// tmp 초기화
	private static void init(List<Info>[][] tmp) {
		for(int i=0; i<N; ++i)
			for(int j=0; j<N; ++j)
				tmp[i][j] = new ArrayList<>();
	}
	
	// map 초기화
	private static void initMap() {
		map = new Info[N][N];
		for(int i=0; i<N; ++i)
			for(int j=0; j<N; ++j)
				map[i][j] = new Info();
	}

}
