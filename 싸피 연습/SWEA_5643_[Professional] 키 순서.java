/*
처음엔 들어오는 간선, 나가는 간선이 동일해야 하는 줄 알았는데 그건 아니었고 
자기보다 키가 작은사람, 큰 사람 합이 N-1개여야 했다.

그래서 DFS를 이용해 노드에 간선이 들어올때 마다 해당 노드 간선을 추가하고 자기보다 큰 노드를 전부 카운트해서 구했다. 
*/

import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.StringTokenizer;

public class Solution {
	
	static int N, M;
	static ArrayList<Integer>[] list;
	static int[] inout;
	static int bigger;	// 자기보다 키가 큰 사람의 수
	static boolean[] visited;

	public static void main(String[] args) throws Exception {
		//System.setIn(new FileInputStream("sample_input.txt"));
		
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		
		int T;
		T=Integer.parseInt(br.readLine());
		
		for(int test_case = 1; test_case <= T; test_case++)
		{
			
			N = Integer.parseInt(br.readLine());
			M = Integer.parseInt(br.readLine());
			
			inout = new int[N+1];	// 들어오는 노드, 나가는 노드 합
			list = new ArrayList[N+1];
			for(int i=1; i<=N; ++i)
				list[i] = new ArrayList<>();
			
			for(int i=0; i<M; ++i) {
				StringTokenizer st= new StringTokenizer(br.readLine());
				int a = Integer.parseInt(st.nextToken());
				int b = Integer.parseInt(st.nextToken());
				
				list[a].add(b);
			}
			
			for(int i=1; i<=N; ++i) {
				visited = new boolean[N+1];
				bigger = 0;
				searchInline(i);	// 해당 노드로 들어오는 간선 조사
				inout[i] += bigger;	// 자기보다 키가 큰 사람을 추가
			}
			
			int cnt = 0;
			for(int i=1; i<=N; ++i) {
				if(inout[i] == N-1)
					cnt++;
			}
			System.out.printf("#%d %d%n", test_case, cnt);
		}
	}

	private static void searchInline(int node) {
		visited[node] = true;
		for(int i=0; i<list[node].size(); ++i) {
			int next= list[node].get(i);
			if(!visited[next]) {
				inout[next]++;	// next보다 작은 사람 추가
				bigger++;	// 자기보다 키가 큰 사람 추가
				searchInline(next);
			}
		}
	}
}