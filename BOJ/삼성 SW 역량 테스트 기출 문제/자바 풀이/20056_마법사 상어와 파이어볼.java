/*
문제자체는 그렇게 어렵지 않았는데 정답이 잘 안나왔다.
풀다가 잘 안 풀려서 며칠뒤에 다시 풀어봐야지 했는데 다시 풀때도 한 2~3시간 붙잡아서 겨우 해결했다.
로직은 이렇다.

1. map변수에 초기 상태를 저장
2. map 변수에서 파이어볼 이동을 tmp에 저장
   2-1. (r,c)에 든 파이어볼을 모두 tmp로 이동했다면 r,c 비워주기
3. tmp 변수에서 1개인 파이어볼은 map에 옮겨주고 2개이상은 조건에 맞춰 계산 후 map에 저장
4. tmp를 초기화 한 후 다시 1번부터 반복

2번에서 파이어볼 이동에 실수가 있었다.
첫번째, 대각선이동을 잘 해야한다. 각 행, 열이 모두 붙어있기 때문에 범위를 벗어났을 경우 제일 끝으로 이동하도록 만들어야 한다.
두번째, nr, nc 값 선언을 r,c로 해줘야 한다.
배열이 전부 이어져있기 때문에 N의 배수만큼 반복하면 원래자리로 돌아온다.
그래서 모듈러 연산을 통해 최소한만 움직이도록 했는데, 만약 속력이 N의 배수이면 이동은 하지 않으므로 원래 자리에 남아있게 된다.
하지만 처음에 nr, nc를 0으로 선언해버리니 이동을 안했을 때 0,0으로 이동한 것처럼 돼서 정답이 안나왔다.

반례를 보고 디버깅해서 겨우 해결할 수 있었는데 실제 시험이었다면 아마 반례를 못찾아서 끝내 못풀지 않았을까 한다.
이런 실수를 많이 줄이도록 해야겠다.
*/

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.List;
import java.util.StringTokenizer;

public class Main {

	static class Fireball{
		int m; int s; int d;
		Fireball(int m, int s, int d){
			this.m=m;
			this.d=d;
			this.s=s;
		}
	}
	
	static class Pos{
		int r; int c;
		Pos(int r, int c){
			this.r=r;
			this.c=c;
		}
	}
	
	static int N, M, K;
	static List<Fireball>[][] map;
	static List<Fireball>[][] tmp;
	static int ans;
	
	static int dr[]= {-1,-1,0,1,1,1,0,-1};
	static int dc[]= {0,1,1,1,0,-1,-1,-1};
	
	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine());
		
		 N = Integer.parseInt(st.nextToken());
		 M = Integer.parseInt(st.nextToken());
		 K = Integer.parseInt(st.nextToken());
		 
		 map = new ArrayList[N][N];
		 tmp = new ArrayList[N][N];
		 for(int i=0; i<N; ++i)
			 for(int j=0; j<N; ++j)
				 map[i][j] = new ArrayList<>();
		 
		 for(int i=0; i<M; ++i) {
			 st= new StringTokenizer(br.readLine());
			 int r = Integer.parseInt(st.nextToken());
			 int c = Integer.parseInt(st.nextToken());
			 int m = Integer.parseInt(st.nextToken());
			 int s = Integer.parseInt(st.nextToken());
			 int d = Integer.parseInt(st.nextToken());
			 
			 map[r-1][c-1].add(new Fireball(m, s, d));
		 }
		 
		 for(int a=0; a<K; ++a) {
			 
			initTmp();	// tmp 초기화
			start();	// 파이어볼 이동
			sum();	// 2개이상 파이어볼 합침
		 }
        
		 checkSum();    // 남은 파이어볼 질량 합
		 System.out.println(ans);
	}
	
	private static void checkSum() {
		for(int i=0; i<N; ++i) {
			 for(int j=0; j<N; ++j) {
				 if(map[i][j].isEmpty()) continue;
				 for(int k=0; k<map[i][j].size(); ++k)
				 	ans += map[i][j].get(k).m;
			 }
		 }
	}
	
	private static void start() {
		for(int i=0; i<N; ++i) {
			 for(int j=0; j<N; ++j) {
				 if(map[i][j].isEmpty()) continue;
				 moveFireball(i, j);
			 }
		 }
	}
	
	private static void sum() {
		for(int i=0; i<N; ++i) {
			 for(int j=0; j<N; ++j) {
				 if(tmp[i][j].size() < 2) map[i][j] = tmp[i][j];
				 else sumFireball(i, j);
			 }
		 }
	}

	private static void sumFireball(int r, int c) {
		int size = tmp[r][c].size();
		int sumM = 0;	// 질량 합
		int sumS = 0;	// 속력 합
		int odd = 0;	// 홀수
		int even = 0;	// 짝수
		
		for(int i=0; i<size; ++i) {
			sumM += tmp[r][c].get(i).m;
			sumS += tmp[r][c].get(i).s;
			int d = tmp[r][c].get(i).d;
			if(d % 2 == 0) even++;
			else odd++;
		}
		
		int divideM = sumM/5;
		int divideS = sumS/size;
		int d1 = 0;
		int d2 = 1;
		
		if(divideM == 0) return;    // 질량 0이면 종료
		
		for(int i=0; i<4; ++i) {
            // 모두 짝수이거나 홀수인 경우 2,4,6,8
			if(even == size || odd == size) {
				map[r][c].add(new Fireball(divideM, divideS, d1));
				d1 += 2;
			}
			else {    // 아닌건 1,3,5,7
				map[r][c].add(new Fireball(divideM, divideS, d2));
				d2 += 2;
			}
		}
		
	}

	private static void moveFireball(int r, int c) {
		int size = map[r][c].size();
		for(int i=0; i<size; ++i) {
			Fireball f = map[r][c].get(i);
			int nr=r;	// 다음 좌표
			int nc=c;
			int speed = f.s%N;
			
			if(f.d == 2 || f.d == 4) {    // 아래 위 증가
				nr = (r+dr[f.d]*speed)%N;
				nc = (c+dc[f.d]*speed)%N;
			}
			
			else if(f.d == 0 || f.d == 6) {    // 아래 위 감소
				nr = (r+dr[f.d]*speed);
				nc = (c+dc[f.d]*speed);
				if(nr < 0) nr += N;
				else if(nc < 0 )nc += N;
			}
			
			else {    // 대각선
				int row = r;
				int col = c;
				for(int j=0; j<speed; ++j) {
					nr = row+dr[f.d];
					nc = col+dc[f.d];
					// 왼쪽 위 모서리
					if(nr < 0 && nc < 0) {
						nr = N-1;
						nc = N-1;
					}
					// 오른쪽 위 모서리
					else if(nr <0  && nc >=N) {
						nr = N-1;
						nc = 0;
					}
					// 왼쪽 아래 모서리
					else if(nr >= N && nc <0) {
						nr = 0;
						nc = N-1;
					}
					// 오른쪽 아래 모서리
					else if(nr >= N && nc >=N) {
						nr = 0;
						nc = 0;
					}
					
					// r, c가 각각 범위 벗어 났을 때
					else if(nr < 0 && (0<=nc&& nc < N)) {
						nr = N-1;
					}
					else if(nr >=N && (0<=nc&& nc < N)) {
						nr = 0;
					}
					else if(nc < 0 && (0<=nr&& nr < N)) {
						nc = N-1;
					}
					else if(nc >=N && (0<=nr&& nr < N)) {
						nc = 0;
					}
					
					row=nr;	// 좌표 갱신
					col=nc;
				}
				
			}
			
			tmp[nr][nc].add(new Fireball(f.m, f.s, f.d));	// 새로운 tmp에 파이어볼 저장
		}
		map[r][c].clear();	// 다 끝났으면 비워줌
	}
	
	private static void initTmp() {
		for(int i=0; i<N; ++i)
			for(int j=0; j<N; ++j)
				tmp[i][j] = new ArrayList<>();
	}
}
