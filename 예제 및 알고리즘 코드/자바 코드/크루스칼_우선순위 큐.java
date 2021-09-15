/*
우선순위 큐를 이용한 크루스칼이다.
가중치가 아니라 간선까지 같이 구하고 싶다면 리스트를 만들어 유니온 한 뒤에 간선을 저장하면 된다.
*/

import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.PriorityQueue;
import java.util.StringTokenizer;

public class Main_SWEA_3124_최소스패닝트리_크루스칼 {
	
	static class Node implements Comparable<Node>{
		int from, to;
		int weight;
		
		Node(int from, int to, int weight){
			this.from=from;
			this.to=to;
			this.weight= weight;
		}
		
		@Override
		public int compareTo(Node o) {
			return Integer.compare(this.weight, o.weight);
//			return o.weight >= this.weight ? -1 : 1;
		}
	}
	
	static ArrayList<Node> [] arr;
	static int[] parents;
	
	// 부모를 자기 자신
	static void make(int n) {
		parents = new int[n+1];
		for(int i=1; i<=n; ++i)
			parents[i] = i;
	}
	// 최상위 부모를 찾는다.
	static int find(int num) {
		if(num == parents[num]) return num;
		return parents[num] = find(parents[num]);
	}
	// 같은 집합을 묶는다.
	static boolean union(int a, int b) {
		a = find(a); b= find(b);
		if(a == b) return false;
		
		int minParent= Math.min(a, b);
		parents[a] = minParent;
		parents[b] = minParent;
		return true;
	}
	
	private static long Kruskal(PriorityQueue<Node> pq, int V) {
		long result = 0;
		int cnt = 0;
		// 가중치가 최소인 것이 맨 앞에 나온다.
		while(!pq.isEmpty()) {
			Node curr = pq.poll();
			
			int a= find(curr.from);
			int b= find(curr.to);
			// 같은 집합이면 사이클 발생
			if(a== b)
				continue;
			// 같은 집합으로 만들고 가중치 합산
			union(a, b);
			result += curr.weight;
			
			// 정점만큼 반복하면 종료
			if (++cnt == V) {
				break;
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
			
			PriorityQueue<Node> pq = new PriorityQueue<>();
			for(int i=0; i<E; ++i) {
				st = new StringTokenizer(br.readLine());
				int A = Integer.parseInt(st.nextToken());
				int B = Integer.parseInt(st.nextToken());
				int C = Integer.parseInt(st.nextToken());
				
				pq.offer(new Node(A,B,C));
			}
			
			make(V);

			StringBuilder sb = new StringBuilder();
			sb.append("#"+test_case+" " +Kruskal(pq, V));
			System.out.println(sb);
		}
	}
}
