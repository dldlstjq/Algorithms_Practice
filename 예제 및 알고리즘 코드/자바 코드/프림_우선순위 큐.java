/*
프림도 우선순위 큐를 이용하면 조금 더 간단하다.
1번 노드부터 시작한다고 했을 때, 1번노드와 연결된 간선 중 가장 가중치가 낮은 간선을 찾는다.
없으면 1번과 연결된 간선을 모두 우선순위 큐에 저장한다.
그러면 간선 가중치가 가장 낮은 것이 선택되어 연결된다.
이것도 간선을 직접 구하려면 리스트를 만들어 저장하면 될 듯 하다. 
*/

import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.PriorityQueue;
import java.util.StringTokenizer;

public class Main_SWEA_3124_최소스패닝트리 {
	
	static class Node implements Comparable<Node>{
		int v;
		int weight;
		
		Node(int v, int weight){
			this.v=v;
			this.weight= weight;
		}
		
		@Override
		public int compareTo(Node o) {
			return this.weight-o.weight;
//			return o.weight >= this.weight ? -1 : 1;
		}
	}
	
	static ArrayList<Node> [] arr;
	
	private static long Prim(int V) {
		long result = 0;	// 최소 신장트리 비용
		
		PriorityQueue<Node> pq = new PriorityQueue<>();
		pq.offer(new Node(1, 0));
		
		boolean visited[] = new boolean[V];
		
		while(!pq.isEmpty()) {
			Node curr = pq.poll();
			int weight = curr.weight;
			int v = curr.v;
			
			if(visited[v]) continue;
			visited[v] = true;
			result += weight;
			
			for(int i=0; i<arr[v].size(); ++i) {
				int nextV = arr[v].get(i).v;
				int nextWeight = arr[v].get(i).weight;
				// 아직 신장트리에 포함되지 않았으면 pq에 저장
				if(!visited[nextV])
					pq.offer(new Node(nextV, nextWeight));
			}
		}
		return result;
	}
	
	public static void main(String[] args) throws Exception{
		System.setIn(new FileInputStream("sample_input.txt"));
		BufferedReader br= new BufferedReader(new InputStreamReader(System.in));
		
		int T = Integer.parseInt(br.readLine());
		
		
		
		for(int test_case = 1; test_case <= T; test_case++)
		{
			int V=0, E=0;
			StringTokenizer st = new StringTokenizer(br.readLine());
			V = Integer.parseInt(st.nextToken());
			E = Integer.parseInt(st.nextToken());
			
			arr= new ArrayList[V+1];
			
			for(int i=1; i<=V; ++i)
				arr[i] = new ArrayList<>();
			
			for(int i=0; i<E; ++i) {
				st = new StringTokenizer(br.readLine());
				int A = Integer.parseInt(st.nextToken());
				int B = Integer.parseInt(st.nextToken());
				int C = Integer.parseInt(st.nextToken());
				
				// A, B가 연결되어 있으므로 둘 다 표시
				arr[A].add(new Node(B, C));
				arr[B].add(new Node(A, C));
			}
			
			StringBuilder sb = new StringBuilder();
			sb.append("#"+test_case+" " +Prim(V+1));
			System.out.println(sb);
		}
	}
}
