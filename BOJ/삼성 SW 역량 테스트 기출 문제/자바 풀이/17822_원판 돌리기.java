/*
디버깅이 쉬운 예제를 줘서 다행이지 아니었으면 한참 걸렸을 문제이다.
우선 원판을 2차원 배열에 저장했고 +1씩 해서 인덱스 1부터 시작하게 했다.
원래 시계, 반시계 방향 이동을 배열 하나를 더 만들어서 했는데 이번에는 수 하나를 따로 저장해서 원 배열 하나로 해결했다.
k의 경우 최대 M인데 모듈러 연산을 해서 최소한만 회전하게 했다.
다행히 회전은 한 번에 잘 구현했고 문제는 인접한 수를 지우는 작업이었다.

이 역시 한 번 계산해서 바로 지우는 것이 아니라 모든 수를 검사한 다음 한 번에 지워야 한다.
이를 위해 리스트에다 지울 수의 좌표를 저장했다.
여기서 이미 지운 수를 0으로 했다면 이건 제외해야 한다.
또한 4방 탐색을 이용하는데 - 1번 원판은 자기보다 위의 원판과 양 옆만, 마지막 원판은 자기 밑의 원판과 양 옆 만- 3곳만 검사해야 한다.
그리고 양 옆은 범위를 벗어나면 맨 처음이나 끝으로 인덱스를 맞춰줘야 한다.

같은 수를 찾는 과정을 얼마나 빨리 하느냐가 관건인 것 같다.
*/

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.StringTokenizer;

public class Main {
	
	static class Pos{
		int r, c;
		Pos(int r, int c){
			this.r=r;
			this.c=c;
		}
	}
	
	static int N, M, T;
	
	static int[][] circle;
	
	static int dr[] = {-1,0,1,0};
	static int dc[] = {0,1,0,-1};
	
	static ArrayList<Pos> list;
	
	public static void main(String[] args) throws Exception {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine());
		
		N = Integer.parseInt(st.nextToken());
		M = Integer.parseInt(st.nextToken());
		T = Integer.parseInt(st.nextToken());
		
		circle = new int[N+1][M+1];
		
		for(int i=1; i<=N; ++i) {
			st = new StringTokenizer(br.readLine());
			for(int j=1; j<=M; ++j)
				circle[i][j] = Integer.parseInt(st.nextToken());
		}
		
		for(int i=0; i<T; ++i) {
			st = new StringTokenizer(br.readLine());
			int x = Integer.parseInt(st.nextToken());
			int d = Integer.parseInt(st.nextToken());
			int k = Integer.parseInt(st.nextToken());
			
			for(int j=x; j<=N; j+=x) {
				rotate(j, d, k);
			}
			
			list = new ArrayList<>();
			// 원판 조사
			if(search())
				deleteNumber();
			else
				setAverage();
		}
		
		System.out.println(getSum());
	}
	
	private static void rotate(int idx, int d, int k) {
		int[] arr = circle[idx];
		k %= M;
		
		// 시계 방향
		if(d == 0) {
			while(k-- > 0) {
				int tmp = arr[M];
				for(int i=M; i>=2; --i) 
					arr[i] = arr[i-1];
				arr[1] = tmp;
			}
			
		}
		
		// 반 시계 방향
		else {
			while(k-- > 0) {
				int tmp = arr[1];
				for(int i=1; i<M; ++i) 
					arr[i] = arr[i+1];
				arr[M] = tmp;
			}
		}
	}
	
	private static boolean search() {
		for(int i=1; i<=N; ++i) {
			for(int j=1; j<=M; ++j) {
				if(circle[i][j] == 0) continue;
					
				// 4방 탐색
				for(int d=0; d<4; ++d) {
					int nr = i+dr[d];
					int nc = j+dc[d];
					
					// 1번 원판과 N번 원판은 3방향만 검사
					if(i == 1 && d==0) {
						continue;
					}
					
					else if(i == N && d==2) {
						continue;
					}
					
					// 좌, 우가 범위를 벗어나면 재조정
					if(d==3 && nc<1)
						nc = M;
					
					else if(d==1 && nc > M)
						nc = 1;
					
					// 숫자가 같으면 i,j 저장
					if(circle[i][j] != 0 && (circle[nr][nc] == circle[i][j]))
						list.add(new Pos(i, j));
				}
			}
		}
		
		if(list.isEmpty())
			return false;
		return true;
	}
	
	// 삭제
	private static void deleteNumber() {
		for(int i=0; i<list.size(); ++i) {
			int r= list.get(i).r;
			int c= list.get(i).c;
			circle[r][c] = 0;
		}
	}
	
	// 평균 구해서 값 갱신
	private static void setAverage() {
		int sum=0, cnt = 0;
		// 평균 구하기
		for(int i=1; i<=N; ++i) {
			for(int j=1; j<=M; ++j) {
				if(circle[i][j] > 0) {
					sum += circle[i][j];
					cnt++;
				}
			}
		}
		// 평균보다 큰 수에서 1을 빼고, 작은 수에는 1을 더한다.
		double avg = (double)sum/cnt;
		for(int i=1; i<=N; ++i) {
			for(int j=1; j<=M; ++j) {
				if(circle[i][j] == 0) continue;
				if(avg > circle[i][j]) 
					circle[i][j]++;
				else if(avg < circle[i][j])
					circle[i][j]--;
			}
		}
	}
			
	private static int getSum() {
		int sum = 0;
		for(int i=1; i<=N; ++i) 
			for(int j=1; j<=M; ++j) 
				sum += circle[i][j];
		return sum;
	}	
}