/*
최소 신장트리 분류에 있었는데 단순히 그래프를 만들어 간선 개수를 구하면 되는 것 같다.
여기선 인접리스트를 만들어 방문한 국가 개수를 카운팅 해주고 방문한 국가이면 넘어가는 방식이다.
*/

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.StringTokenizer;

public class Main {
	
	static int N, M;
	static ArrayList<Integer>[] list;
	static boolean[] visited;
	static int cnt;
	
	public static void main(String[] args) throws Exception {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		
		int T = Integer.parseInt(br.readLine());
		
		for(int t=1; t<=T; ++t) {
			StringTokenizer st = new StringTokenizer(br.readLine());
			N = Integer.parseInt(st.nextToken());
			M = Integer.parseInt(st.nextToken());
			
			list = new ArrayList[N+1];
			for(int i=1; i<=N; ++i)
				list[i] = new ArrayList<>();
			
			visited = new boolean[N+1];
			
			for(int i=0; i<M; ++i) {
				st = new StringTokenizer(br.readLine());
				int a = Integer.parseInt(st.nextToken());
				int b = Integer.parseInt(st.nextToken());
				
				// 왕복 비행기
				list[a].add(b);
				list[b].add(a);
			}
			// 방문안한 국가면 방문
			cnt = 0;
			for(int i=1; i<=N; ++i) {
				if(!visited[i])
					dfs(i);
			}
			System.out.println(cnt);
		}
	}

	private static void dfs(int n) {
		visited[n] = true;
		for(int i=0; i<list[n].size(); ++i) {
			int next = list[n].get(i);
            // 방문 안했으면 카운트
			if(!visited[next]) {
				cnt++;
				dfs(next);
			}
		}
	}
}
