/*
조건에 맞게 구현하면 되는 문제이다.
특별한 알고리즘은 필요로 하지 않지만 조건을 한두개씩 빼먹으면 답이 제대로 나오지 않는다.
처음 풀때는 좀 지저분하게 풀었다가 조금씩 리팩토링을 거쳐 그나마 최소한의 코드로 나오게 했다.
이번문제도 출력조건을 잘못 설정하여 틀렸는데 문제를 꼼꼼이 잘 읽어야한다.
*/

import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.InputStreamReader;
import java.util.HashMap;
import java.util.StringTokenizer;

public class Main_1873_이인섭 {
	
	static int H, W, N;
	static char map[][];	// 전체 좌표
	static char order[];	// 명령 저장
	static int dy[] = {-1,0,1,0};	//위 오른 아래 왼쪽 순서
	static int dx[] = {0,1,0,-1};
	static int t_y, t_x;	// 전차의 좌표
	
	static HashMap<Character, Integer> hashDir = new HashMap<Character, Integer>();
	static HashMap<Character, Integer> hashCommand = new HashMap<Character, Integer>();
	
	static void move_shoot(int sy, int sx, int dir) {
		while(true) {
			// dir 방향으로 포탄 이동
			sy += dy[dir]; sx += dx[dir];
			
			// 포탄이 게임 맵 밖으로 나가거나 강철 벽과 부딪히면 아무일도 일어나지 않는다.
			if(!(0<=sy&&sy<H && 0<=sx&&sx<W) || map[sy][sx]=='#')
				break;
			
			// 벽돌이면 이 벽은 평지가 된다.
			if( map[sy][sx]=='*' ) {
				map[sy][sx] = '.';
				break;
			}

		}
	}
	
	static void move_tank(int dir) {
		// 해당 방향 으로 한 칸 갔을 때 갈 수 있으면 이동
		int ny = t_y+dy[dir];
		int nx = t_x+dx[dir];
		
		// 맵 안이고 평지일때만 이동
		if((0<=ny&&ny<H && 0<=nx&&nx<W) && map[ny][nx]=='.') {
			map[t_y][t_x] = '.';
			t_y=ny; t_x=nx;	// 전차 좌표 변경
		}
		
		for(Character key : hashDir.keySet()) {
			if(hashDir.get(key) == dir)
				map[t_y][t_x] = key;
		}
	}
	
	// 전차 이동
	static void game() {
		for(int i=0; i<order.length; ++i) {
			
			if(order[i] == 'S') {
				// 포탄의 좌표
				int sy = t_y;
				int sx = t_x;
				move_shoot(sy, sx, hashDir.get(map[t_y][t_x]));
			}
			
			else
				move_tank(hashCommand.get(order[i]));
		}
	}
	
	public static void main(String[] args) throws Exception {

		System.setIn(new FileInputStream("input.txt"));
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st;
		
		hashDir.put('^', 0);
		hashDir.put('>', 1);
		hashDir.put('v', 2);
		hashDir.put('<', 3);
		
		hashCommand.put('U', 0);
		hashCommand.put('R', 1);
		hashCommand.put('D', 2);
		hashCommand.put('L', 3);
		
		int T = Integer.parseInt(br.readLine());
		
		for(int test_case = 1; test_case <= T; test_case++)
		{
			st = new StringTokenizer(br.readLine(), " ");
			H = Integer.parseInt(st.nextToken());
			W = Integer.parseInt(st.nextToken());
			
			map = new char[H][W];
			
			
			for(int i=0; i<H; ++i) {
				map[i] = br.readLine().toCharArray();
				for(int j=0; j<W; ++j) {
					if(map[i][j] == '^' ||map[i][j] == 'v'||map[i][j] == '<'||map[i][j] == '>' ) {
						t_y=i; 
						t_x=j;
					}
				}
			}
				
			
			N = Integer.parseInt(br.readLine());
			order = br.readLine().toCharArray();
			
			game();	// 게임 실행
			
			// 출력
			StringBuilder sb = new StringBuilder();
			sb.append('#').append(test_case).append(' ');
			for(int i=0; i<H; ++i) {
				for(int j=0; j<W; ++j) {
					sb.append(map[i][j]);
				}
				sb.append('\n');
			}
			sb.setLength(sb.length()-1);
			System.out.println(sb);
		}
	}
}
