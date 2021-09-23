/*
유니온을 먼저 하고 find를 하면 당연히 답이 안나온다.
find를 통해 부모가 같은지 확인한 후 다르면 유니온, 같으면 같은 집합이므로 사이클이 만들어진다.
*/

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

public class Main {
	
	static int n,m;
	static int[] parents;
	static int[] rank;
	
	static void make() {
		parents = new int[n];
		rank = new int[n];
		for(int i=0; i<n; ++i) {
			parents[i] = i;
			rank[i] = 1;
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
			int tmp = a;
			a = b;
			b = tmp;
		}
		parents[b] = a;
		if(rank[a] == rank[b]) ++rank[b];
	}
	
	public static void main(String[] args) throws Exception {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine());
		
		n = Integer.parseInt(st.nextToken());
		m = Integer.parseInt(st.nextToken());
		
		make();
		
		int cycle = 0;
		for(int i=1; i<=m; ++i) {
			st = new StringTokenizer(br.readLine());
			int from = Integer.parseInt(st.nextToken());
			int to = Integer.parseInt(st.nextToken());
			// 부모가 같으면 사이클
			if(find(from) == find(to)) {
				cycle = i;
				break;
			}
			union(from, to);    // 사이클이 아니면 유니온
		}
		
		System.out.println(cycle);
	}
}