/*
오랜만에 MST 문제를 풀었다.
자주 풀거나 알고리즘을 보지 않으면 금방 잊어먹는 것 같다.
크루스칼, 프림 두 가지 방법이 있는데 크루스칼은 유니온 파인드를 이용해야 한다.
수업시간때 배운 방법은 정점, 간선이 많을 때 시간초과가 발생했다.
우선순위 큐를 이용하면 따로 정렬하지 않아도 가장 간선 가중치가 낮은 것이 큐의 맨 앞에 오기 때문에 코드가 간단해 지는 것 같다.
두 가지 방법 다 알아놓자.
*/

// 크루스칼
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



// 프림
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

