/*
규칙만 찾으면 쉽게 풀 수 있는데 규칙 찾는게 어려웠다.
이때까지 그린 선분 모두를 90도 회전시켜야 하기 때문에 이전에 진행했던 방향정보가 필요하다 생각해 direction이란 리스트를 선언했다.

이때까지 진행한 방향을 direction에 저장하고 현재 direction크기-3 부터 0번째까지 거꾸로 진행하며 (해당 인덱스방향 +1)%4로 방향을 바꿔주며 표시를 하니까 답이 나왔다.
한 2~3시간 생각하며 찾아낸 규칙이고 아마 더 쉬운 방법이 있을 것 같았는데 이전에 찾아봤던 풀이도 맥락은 거의 똑같았다.

다만 첫 시작점만 표시하고 바로 방향을 저장한다. 
그 다음 세대 수 만큼 반복하여 리스트를 거꾸로 순회하며 해당 방향에 +1%4를 하여 저장 후 이것에 맞게 커브를 표시했다. 아마 이게 한결 더 이해하기 쉬울 것 같다.

*/

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.StringTokenizer;

public class Main {
	
	static int N;
	static int map[][]= new int[101][101];
	static int dr[]= {0,-1,0,1};    //0,1,2,3 방향
	static int dc[]= {1,0,-1,0};
	// 드래곤 커브 방향 저장
	static ArrayList<Integer> direction = new ArrayList<>();
	
	// d는 현재 방향, g는 드래곤커브 세대
	private static void draw_curve(int c, int r, int d, int g) {
		// 세대 0이면 종료
		if(g == 0)
			return;
		
		// 현재 방향에서 90도 이동 후 표시하고 방향 저장
		d = (d+1)%4;
		r += dr[d];
		c += dc[d];
		map[r][c] = 1;
		direction.add(d);

		// 현재 방향 리스트 사이즈 기준-3 부터 0까지 방향들에 1 더한 것이 전체적인 90도 회전 후 방향 표시
		// 걍 따라가다 보면 나옴. 현재 생각나는 것 이 방법뿐.
		int idx = direction.size()-3;
		for(int j=idx; j>=0; --j) {
			int prev_dir = direction.get(j);
			prev_dir = (prev_dir+1)%4;
			r += dr[prev_dir];
			c += dc[prev_dir];
			map[r][c] = 1;
			direction.add(prev_dir);
			d = prev_dir;	// d 갱신
		}

		draw_curve(c, r, d, g-1);
		
	}
	
	public static void main(String[] args) throws Exception {
		
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

		N = Integer.parseInt(br.readLine());
		
		for(int i=0; i<N; ++i) {
			StringTokenizer st = new StringTokenizer(br.readLine(), " ");
		
			int x = Integer.parseInt(st.nextToken());
			int y = Integer.parseInt(st.nextToken());
			int d = Integer.parseInt(st.nextToken());
			int g = Integer.parseInt(st.nextToken());
            
			direction.clear();
			map[y][x] = 1;	// (y,x) 최초 시작점
			// d 방향으로 이동하여 해당 좌표 표시
			int nr = y+dr[d];
			int nc = x+dc[d];
			map[nr][nc] = 1;
			direction.add(d);	// 현재 방향 저장
			draw_curve(nc, nr, d, g);	// 드래곤커브 그리기
		}
		
		// 정사각형이 드래곤커브인 경우 카운트
		int square = 0;
		for(int i=0; i<100; ++i) {
			for(int j=0; j<100; ++j) {
				if(map[i][j] == 1) {
					if(map[i+1][j] == 1 && map[i][j+1] == 1 && map[i+1][j+1]==1)
						square++;
				}
			}
		}
		
		System.out.println(square);
	}
}