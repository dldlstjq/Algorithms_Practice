/*
방을 모두 탐색해야 하기 때문에 bfs, dfs 둘 다 쓸 수 있다.
처음 생각난 것은 dfs였다.
dfs로 탐색해서 갈 수 있으면 가고 갈 수 없을 때 방 개수와 숫자를 갱신해줬다.
나는 전역으로 선언해서 함수 하나에서 다 끝내는 편인데
다른 사람들은 리턴 값을 설정해줘서 메인함수 내에서 값을 갱신했다.

아마 장단점이 있을 듯 한데 개인적으로 전역을 선언하지 않고 하는 것이 더 좋은 것 같다.
코드 스타일을 조금씩 바꿔봐야겠고 bfs는 다른 사람 풀이를 보고 사용할 수 있다는 것을 알았다.
c++로 하면 좌표를 페어로 저장해서 사용하지만 자바는 페어가 없어 클래스를 선언한 후 클래스 자체를 큐의 제네릭으로 사용해야 한다. 
다른 사람 코드를 보면서 많은 것을 배우는 것 같다.
*/

//dfs 풀이
import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

class Solution
{
    static int N;
	static int dy[] = {-1,0,1,0};
	static int dx[] = {0,1,0,-1};
	static int ans, num;	// 최종 방 번호와 방 개수
	
	// r, c는 현재 방의 좌표, room은 방 개수, start는 출발 방 번호, room는 방 배열
	static void check(int r, int c, int cnt, int start, int room[][]) {
		// 4방향 탐색해서 갈 수 있으면 계속 간다.
		for(int i=0; i<4; ++i) {
			int ny = r+dy[i];
			int nx = c+dx[i];
			
			// 다음 방이 범위를 벗어나거나 1보다 크지 않으면 다른 방향 탐색
			if(!(0<=ny&&ny<N && 0<=nx&&nx<N) || room[r][c]+1 != room[ny][nx])
				continue;
			
			// 갈 수 없는 경우를 제외하고는 갈 수 있기 때문에 현재 좌표를 ny, nx로 갱신, 방 개수 1 추가
			check(ny, nx, cnt+1, start, room);
		}
		
		// 더 이상 갈 수 없다면 그 때 방의 개수와 방 번호 갱신
		// 갱신 조건 1. 갈 수 있는 방 개수가 더 많다.
		// 2. 방 개수가 최대인 방이 여럿이라면 방 번호가 작은 값이 정답
		if(ans < cnt || (ans == cnt && num > start)) {
			ans = cnt;
			num = start;
		}
	}
    
	public static void main(String args[]) throws Exception
	{
		
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		
		int T = Integer.parseInt(br.readLine());
				
		for(int test_case = 1; test_case <= T; test_case++)
		{
			N = Integer.parseInt(br.readLine());
			int [][]arr = new int[N][N];
			
			// 방 개수 =1, 방 번호 =0으로 초기화
			ans = 1;
			num = 0;
			
			StringTokenizer st;
			for(int i=0; i<N; ++i) {
				st =  new StringTokenizer(br.readLine(), " ");
				for(int j=0; j<N; ++j) {
					arr[i][j] = Integer.parseInt(st.nextToken());
				}
			}
			
			// 제일 먼저 생각 나는 건 재귀를 이용한 완탐. 1보다 크면 하나씩 들어가는 것.
			for(int i=0; i<N; ++i) 
				for(int j=0; j<N; ++j) 
					check(i, j, 1, arr[i][j], arr);
			
			
			StringBuilder sb = new StringBuilder();
			sb.append("#"+test_case+" " + num +" "+ ans);
			System.out.println(sb);
			
		}
	}
}


// bfs풀이
import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.InputStreamReader;
import java.util.LinkedList;
import java.util.Queue;
import java.util.StringTokenizer;

class Point {
	int y;
	int x;
	Point(int y, int x) {
		this.y=y;
		this.x=x;
	}
}

class Solution
{
    static int N;
	static int dy[] = {-1,0,1,0};
	static int dx[] = {0,1,0,-1};
	static int ans, num;	// 최종 방 번호와 방 개수
	static int map[][];
	
	// bfs를 이용한 풀이
	static void bfs(int r, int c) {
		// 현재 좌표 큐에 푸시
		Queue<Point> q = new LinkedList<>();
		q.offer(new Point(r,c));
		int cnt = 0;	// 방 개수 카운트
		
		while(!q.isEmpty()) {
			// 큐에서 꺼내어 방 개수 증가
			Point cur = q.poll();
			cnt++;
			
			for(int i=0; i<4; ++i) {
				int ny = cur.y+dy[i];
				int nx = cur.x+dx[i];
				
				// 다음 방이 범위를 벗어나거나 1보다 크지 않으면 다른 방향 탐색
				if(!(0<=ny&&ny<N && 0<=nx&&nx<N) || map[cur.y][cur.x]+1 != map[ny][nx])
					continue;
				
				q.offer(new Point(ny, nx));
			}
		}
		
		// 조건 동일. r, c가 시작 좌표
		if(ans < cnt || (ans == cnt && num > map[r][c])) {
			ans = cnt;
			num = map[r][c];
		}
	}
    
	public static void main(String args[]) throws Exception
	{
		
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		int T = Integer.parseInt(br.readLine());
				
		for(int test_case = 1; test_case <= T; test_case++)
		{
			N = Integer.parseInt(br.readLine());
			int [][]arr = new int[N][N];
			
			map = new int[N][N];
			// 방 개수 =1, 방 번호 =0으로 초기화
			ans = 1;
			num = 0;
			
			StringTokenizer st;
			for(int i=0; i<N; ++i) {
				st =  new StringTokenizer(br.readLine(), " ");
				for(int j=0; j<N; ++j) {
					map[i][j] = Integer.parseInt(st.nextToken());
				}
			}
			
			// 재귀를 이용한 완탐. 1보다 크면 하나씩 들어가는 것.
			for(int i=0; i<N; ++i) 
				for(int j=0; j<N; ++j) 
					bfs(i, j);
			
			StringBuilder sb = new StringBuilder();
			sb.append("#"+test_case+" " + num +" "+ ans);
			System.out.println(sb);
		}
	}
}