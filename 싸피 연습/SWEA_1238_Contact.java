/*
그래프를 만들어서 가장 거리가 먼 사람들 중 번호가 가장 큰 값을 구하는 것이다.
처음에는 dfs를 사용해 길이를 1씩 더한 값을 매개변수로 넣어 가장 큰 값이면 바꾸도록 했는데 값이 제대로 안나왔다.
반례를 보고 싶었는데 간선 길이가 300개나 되어서 차마 확인할 수 없었고
bfs 방식을 이용해 거리를 1씩 더한 값을 구한 후 최댓값을 구하는 방법,
한꺼번에 저장 후 정렬을 통해 구하는 방법이 있었다.
*/

// 정렬하여 구하는 방법
import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Collections;
import java.util.LinkedList;
import java.util.Queue;
import java.util.StringTokenizer;

public class Solution {
	
	static class Node implements Comparable<Node>{
		int person, len;
		Node link;
		public Node(int person, int len, Node link) {
			super();
			this.person = person;
			this.len = len;
			this.link = link;
		}
		@Override
		public int compareTo(Node o) {
			if(o.len == this.len)
				return o.person-this.person;
			return o.len-this.len;
		}
	}
	
	static int start;	// 시작점
	static int N; // 길이
	static Node[] adj;
	
	static int bigPerson;	// 정답 저장
	
	
	private static void find_bigPerson2() {
		Queue<Node> queue = new LinkedList<>();
		ArrayList<Node> list= new ArrayList<>();	// 시작점부터 각 노드간 길이가 포함된 노드 저장
		boolean[] visited = new boolean[101];
		queue.offer(new Node(start, 0, null));
		visited[start] = true;
		
		while(!queue.isEmpty()) {
			
			Node curr = queue.poll();
			list.add(new Node(curr.person, curr.len, null));	// 노드에 추가
			
			for(Node temp = adj[curr.person]; temp!=null; temp=temp.link) {
				if(!visited[temp.person]) {
					queue.offer(new Node(temp.person, curr.len+1, null));
					visited[temp.person] = true;
				}
					
			}
			
		}
		
		// 거리가 멀고 번호가 큰 순서로 정렬
		Collections.sort(list);
		bigPerson = list.get(0).person;
		
	}

	public static void main(String[] args) throws Exception {
		//System.setIn(new FileInputStream("input.txt"));
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
	
		for(int tc=1; tc<=10; ++tc) {
			StringTokenizer st = new StringTokenizer(br.readLine()," ");
			N = Integer.parseInt(st.nextToken());
			start = Integer.parseInt(st.nextToken());
			
			
			adj = new Node[101];
			
			
			st = new StringTokenizer(br.readLine()," ");
			while(st.hasMoreTokens()) {
				int from = Integer.parseInt(st.nextToken());
				int to = Integer.parseInt(st.nextToken());
				
				// 인접리스트 만들기
				adj[from] = new Node(to, 0, adj[from]);
			}
			
			// 가장 나중에 연락을 받을 사람
			bigPerson = 0;
			find_bigPerson2();
			
			StringBuilder sb = new StringBuilder();
			sb.append("#"+ tc + " " + bigPerson);
			System.out.println(sb);
		}
	}
}


// visited 배열을 통해 거리를 저장하는 방법
import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.LinkedList;
import java.util.Queue;
import java.util.StringTokenizer;

public class Main_SWEA_1238_Contact {
	
	static class Node{
		int person;
		Node link;
		public Node(int person, Node link) {
			super();
			this.person = person;
			this.link = link;
		}
	}
	
	static int start;	// 시작점
	static int N; // 길이
	static ArrayList<ArrayList<Integer>> adjList;	// 인접 리스트
	static Node[] adj;
	
	static int bigPerson;	// 정답 저장
	static int distance;	// 가장 마지막에 연락을 받을 때 길이

	private static void find_bigPerson() {
		Queue<Integer> queue = new LinkedList<>();
		int[] visited = new int[101];
		queue.offer(start);
		visited[start] = 1;
		
		int max_len = 0;
	
		while(!queue.isEmpty()) {
			int curr = queue.poll();
			
			max_len = Math.max(max_len, visited[curr]);
		
			
			for(Node temp = adj[curr]; temp!=null; temp=temp.link) {
				if(visited[temp.person] == 0) {
					queue.offer(temp.person);
					visited[temp.person] = visited[curr]+1;
				}
					
			}
			/*
			for(int i=0; i<adjList.get(curr).size(); ++i) {
				if(visited[adjList.get(curr).get(i)] == 0) {
					queue.offer(adjList.get(curr).get(i));
					visited[adjList.get(curr).get(i)] = visited[curr]+1;
				}
			}
			*/
		}
		
		for(int i=1; i<=100; ++i) {
			if(visited[i] == max_len) {
				bigPerson = Math.max(bigPerson, i);
			}
		}
	}

	public static void main(String[] args) throws Exception {
		System.setIn(new FileInputStream("input.txt"));
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
	
		for(int tc=1; tc<=10; ++tc) {
			StringTokenizer st = new StringTokenizer(br.readLine()," ");
			N = Integer.parseInt(st.nextToken());
			start = Integer.parseInt(st.nextToken());
			
			adjList = new ArrayList<ArrayList<Integer>>();
			for(int i=0; i<=100; ++i)
				adjList.add(new ArrayList<Integer>());
			
			adj = new Node[101];
			
			
			
			st = new StringTokenizer(br.readLine()," ");
			while(st.hasMoreTokens()) {
				int from = Integer.parseInt(st.nextToken());
				int to = Integer.parseInt(st.nextToken());
				
				// 인접리스트 만들기
				adj[from] = new Node(to, adj[from]);
				adjList.get(from).add(to);
			}
			
			// 가장 나중에 연락을 받을 사람
			bigPerson = distance = 0;
			find_bigPerson();
			
			StringBuilder sb = new StringBuilder();
			sb.append("#"+ tc + " " + bigPerson);
			System.out.println(sb);
		}
	}

}