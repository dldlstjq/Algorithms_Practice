/*
무수한 시간초과 끝에 다시 풀 수 있었다.
전체 N 중에 N/2개를 조합으로 뽑아서 차의 최소를 구하면 된다.
로직은 맞는데 계속 시간초과를 받으니 어디서 잘못됐는지를 찾지 못했다.
계속 시도하고 코드를 비교해본 결과 조합을 구할 때 재귀에 인덱스를 잘못줘서
코드가 제대로 안 돌아갔다....
실수를 계속 줄여야 하는데 문제를 제대로 읽고 안되면 코드를 다시 천천히 살펴봐야겠다. 
*/

import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

public class Main {
	
	static int N;
	static boolean [] visited;
	static int [][] football;
	static int ret = Integer.MAX_VALUE;
	
	static void make_team(int idx, int cnt) {
		if(cnt == N/2) {
			int p1=0, p2=0;
			
			for(int i=0; i<N-1; ++i) {
				for(int j= i+1; j<N; ++j) {
					if(visited[i] == true && visited[j] == true) {
						p1 += football[i][j];
						p1 += football[j][i];
					}
					else if(visited[i] == false && visited[j] == false) {
						p2 += football[i][j];
						p2 += football[j][i];
					}
				}
			}
			ret = Math.min(ret, Math.abs(p1-p2));
			return;
		}
		
		for(int i=idx; i<N; ++i) {
			if(visited[i]) continue;
			
			visited[i] = true;
			make_team(i+1, cnt+1);
			visited[i] = false;
		}
	}

	public static void main(String[] args) throws Exception {
		
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		
		N = Integer.parseInt(br.readLine());
		
		visited = new boolean[N];
		football = new int[N][N];
		
		for(int i=0; i<N; ++i) {
			StringTokenizer st = new StringTokenizer(br.readLine(), " ");
			for(int j=0; j<N; ++j) {
				football[i][j] = Integer.parseInt(st.nextToken());
			}
		}
		make_team(0, 0);
		System.out.println(ret);
	}

}