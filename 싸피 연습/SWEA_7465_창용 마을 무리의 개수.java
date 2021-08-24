/*
문제 자체에서 하나의 무리를 계산하는 것이라고 해서 유니온파인드를 사용하면 쉽게 풀 수 있다.
문제에서 바로 유니온 파인드라고 알 수 있는 건 쉬운데 같은 집합으로 나타내야 하는 어떤 자료구조가 필요하다면 유니온 파인드를 사용하면 될 것 같다.
*/

import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

public class Solution {
	
	static int N, M;
	static int parents[], rank[];
	
	static void make() {
		for(int i=1; i<=N; ++i) {
			parents[i] = i;
			rank[i] = 0;
		}
			
	}
	
	static int find(int a) {
		if(a == parents[a]) return a;
		return parents[a] = find(parents[a]);
	}
	
	static void union(int a, int b) {
		a = find(a); b= find(b);
		if(a == b) return;
		if(rank[a] > rank[b]) {
			int tmp = b;
			b = a;
			a = tmp;
		}
		parents[a] = b;
		if(rank[a] == rank[b]) rank[b]++;
	}
	

	public static void main(String[] args) throws Exception {
		//System.setIn(new FileInputStream("s_input.txt"));
		BufferedReader br= new BufferedReader(new InputStreamReader(System.in));
		
		int T = Integer.parseInt(br.readLine());

		for(int test_case = 1; test_case <= T; test_case++)
		{
			StringTokenizer st= new StringTokenizer(br.readLine(), " ");
			
			N = Integer.parseInt(st.nextToken());
			M = Integer.parseInt(st.nextToken());
			
			parents = new int[N+1];
			rank = new int[N+1];
			make();
			
			for(int i=0; i<M; ++i) {
				st= new StringTokenizer(br.readLine(), " ");
				int a = Integer.parseInt(st.nextToken());
				int b = Integer.parseInt(st.nextToken());
				
				// b를 a의 부모로 만든다
				union(a, b);
			}
			
			// 한 번 나온 사람은 true로 표시
			int cnt = 0;
			boolean visited[] = new boolean[N+1];
			for(int i=1; i<=N; ++i) {
				if(!visited[find(i)]) {
					cnt++;
					visited[find(i)] = true;
				}
			}

			System.out.printf("#%d %d%n", test_case, cnt);
		}
	}
}
