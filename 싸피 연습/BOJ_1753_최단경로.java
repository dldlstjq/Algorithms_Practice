/*
다익스트라를 이용한 최단경로찾기이다.
정점이 최대 20,000개여서 행렬로 표현하면 메모리 초과가 난다.
그리고 수업시간에 배웠던 일반 반복문, 종만북에 있는 우선순위 큐 방법을 사용해봤는데
우선순위 큐 방법이 시간이 2배는 덜 걸렸다.
우선순위 큐의 경우 다른 클래스를 타입으로 사용할 때 정렬 방법을 미리 만들어줘야 한다.

우선순위 큐: 1144ms
반복문: 2264ms
*/

// 우선순위 큐 풀이
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.PriorityQueue;
import java.util.StringTokenizer;

public class Main {
	
	static class Node implements Comparable<Node>{
		int v, weight;

		public Node(int v, int weight) {
			super();
			this.v = v;
			this.weight = weight;
		}

		@Override
		public int compareTo(Node o) {
			// TODO Auto-generated method stub
			return this.weight-o.weight;
		}
	}
	
	static int V, E, K;	// 정점, 간선 개수, 시작 정점
	static ArrayList<ArrayList<Node>> adjList = new ArrayList<ArrayList<Node>>();

	public static void main(String[] args) throws Exception {
		// TODO Auto-generated method stub

		BufferedReader br= new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st= new StringTokenizer(br.readLine(), " ");
		
		V = Integer.parseInt(st.nextToken());
		E = Integer.parseInt(st.nextToken());
		
		K = Integer.parseInt(br.readLine());
		
		for(int i=0; i<V+1; ++i)
			adjList.add(new ArrayList<Node>());
				
		for(int i=0; i<E; ++i) {
			st= new StringTokenizer(br.readLine(), " ");
			int u = Integer.parseInt(st.nextToken());
			int v = Integer.parseInt(st.nextToken());
			int w = Integer.parseInt(st.nextToken());
			
			adjList.get(u).add(new Node(v, w));	// 인접 리스트 생성
		}
		
		int distance[] = new int[V+1];
		final int INF = Integer.MAX_VALUE;
		PriorityQueue<Node> pq = new PriorityQueue<>();
		
		Arrays.fill(distance, INF);
		
		// 시작점 방문, 길이 표시
		distance[K] = 0;
		pq.offer(new Node(K, 0));
		
		while(!pq.isEmpty()) {
			Node now = pq.poll();
			int cost = now.weight;
			int current = now.v;
			// 지금 꺼낸 것보다 더 짧은 경로를 알고 있으면 지금 꺼낸 것 무시
			if(distance[current]<cost) continue;
			
			for(int i=0; i<adjList.get(current).size(); ++i) {
				int vertex = adjList.get(current).get(i).v;
				int nextDist = adjList.get(current).get(i).weight + cost;
				// 더 짧은 경로를 발견하면 dist[]를 갱신하고 우선순위 큐에 넣는다.
				if(distance[vertex] > nextDist) {
					distance[vertex] = nextDist;
					pq.offer(new Node(vertex, nextDist));
				}
			}
		}
		
		for(int i=1; i<=V; ++i) {
			if(distance[i] == INF)
				System.out.println("INF");
			else
				System.out.println(distance[i]);
		}
		
	}
}



// 일반 반복문 풀이
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.StringTokenizer;

public class Main {
	
	static class Node{
		int to, weight;
		Node link;

		public Node(int to, int weight, Node link) {
			super();
			this.to = to;
			this.weight = weight;
			this.link = link;
		}
	}
	
	static int V, E, K;	// 정점, 간선 개수, 시작 정점
	static Node[] adj;

	public static void main(String[] args) throws Exception {
		// TODO Auto-generated method stub

		BufferedReader br= new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st= new StringTokenizer(br.readLine(), " ");
		
		V = Integer.parseInt(st.nextToken());
		E = Integer.parseInt(st.nextToken());
		
		K = Integer.parseInt(br.readLine());
	
		adj = new Node[V+1];
		
		for(int i=0; i<E; ++i) {
			st= new StringTokenizer(br.readLine(), " ");
			int u = Integer.parseInt(st.nextToken());
			int v = Integer.parseInt(st.nextToken());
			int w = Integer.parseInt(st.nextToken());
			
			adj[u] = new Node(v, w, adj[u]);	// 인접 리스트 생성
		}
		
		boolean visited[] = new boolean[V+1];
		int distance[] = new int[V+1];
		final int INF = Integer.MAX_VALUE;
		
		Arrays.fill(distance, INF);
		
		// 시작점 방문, 길이 표시
		distance[K] = 0;
		
		int min =0, current = -1;
		for(int i=1; i<=V; ++i) {
			min = INF;
			
			// 방문하지 않았으면서 연결된 간선 중 제일 작은 거리를 찾는다.
			for(int j=1; j<=V; ++j) {
				if(!visited[j] && min>distance[j]) {
					min = distance[j];
					current = j;
				}
			}
			
			visited[current] = true;
			
            // 선택된 정점인 current와 연결된 정점과 경로를 최단거리가 되게 만든다.
			for(Node curr = adj[current]; curr != null; curr=curr.link) {
				int v = curr.to;
				int w = curr.weight;
				if(!visited[v] && distance[v] > min+w)
					distance[v] = min+w;
			}
		}
		
		for(int i=1; i<=V; ++i) {
			if(distance[i] == INF)
				System.out.println("INF");
			else
				System.out.println(distance[i]);
		}
		
	}
}