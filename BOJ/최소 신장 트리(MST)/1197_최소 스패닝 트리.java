/*
최소 스패닝 트리를 연습하는 문제인 것 같다.
대표적인게 프림, 크루스칼이 있는데 둘 다 알아둬야 될 것 같다.
두개 다 우선순위 큐를 사용하는게 더 편한 것 같다. 
*/

// 프림
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.PriorityQueue;
import java.util.StringTokenizer;


public class Main {
	
	static class Node implements Comparable<Node>{
		int node, weight;
		Node(int node, int weight){
			this.node = node;
			this.weight = weight;
		}
		
		@Override
		public int compareTo(Node o) {
			return Integer.compare(this.weight, o.weight);
		}
	}
	
	static int V,E;
	static ArrayList<Node>[] list;
	
	public static void main(String[] args) throws Exception {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine());
		
		V = Integer.parseInt(st.nextToken());
		E = Integer.parseInt(st.nextToken());
		
		list = new ArrayList[V+1];
		for(int i=1; i<=V; ++i)
			list[i] = new ArrayList<>();
		
		for(int i=0; i<E; ++i) {
			st = new StringTokenizer(br.readLine());
			int a = Integer.parseInt(st.nextToken());
			int b = Integer.parseInt(st.nextToken());
			int c = Integer.parseInt(st.nextToken());
			
			list[a].add(new Node(b, c));
			list[b].add(new Node(a, c));
		}
		
		System.out.println(Prim());
	}

	private static int Prim() {
		int ret = 0;
		boolean[] visited = new boolean[V+1];
		PriorityQueue<Node> pq = new PriorityQueue<>();
		pq.offer(new Node(1, 0));
		
		while(!pq.isEmpty()) {
			Node curr = pq.poll();
			
			if(visited[curr.node]) continue;
			ret += curr.weight;
			visited[curr.node] = true;
			
			for(int i=0; i<list[curr.node].size(); ++i) {
				if(!visited[list[curr.node].get(i).node])
					pq.offer(list[curr.node].get(i));
			}
		}
		return ret;
	}
}




// 크루스칼
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.Arrays;
import java.util.PriorityQueue;
import java.util.StringTokenizer;


public class Main {
	
	static class Node implements Comparable<Node>{
		int from, to, weight;
		Node(int from, int to, int weight){
			this.from = from;
			this.to = to;
			this.weight = weight;
		}
		
		@Override
		public int compareTo(Node o) {
			return Integer.compare(this.weight, o.weight);
		}
	}
	
	static int V,E;
	static int[] parents;
	
	public static void main(String[] args) throws Exception {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine());
		
		V = Integer.parseInt(st.nextToken());
		E = Integer.parseInt(st.nextToken());
		
		PriorityQueue<Node> pq = new PriorityQueue<>();
		
		for(int i=0; i<E; ++i) {
			st = new StringTokenizer(br.readLine());
			int a = Integer.parseInt(st.nextToken());
			int b = Integer.parseInt(st.nextToken());
			int c = Integer.parseInt(st.nextToken());
			
			pq.offer(new Node(a, b, c));
		}
		
		parents = new int[V+1];
		for(int i=1; i<=V; ++i)
			parents[i] = i;
		
		int ret=0, cnt = 0;
		while(!pq.isEmpty()) {
			Node curr = pq.poll();
			
			if(union(curr.from, curr.to)) {
				ret += curr.weight;
				cnt++;
				
				if(cnt == V-1)
					break;
			}
		}
		System.out.println(ret);
	}

	private static int find(int a) {
		if(parents[a] == a) return a;
		return parents[a] = find(parents[a]);
	}
	
	private static boolean union(int a, int b) {
		a = find(a); b= find(b);
		if(a == b) return false;
		parents[b] = a;
		return true;
	}
}