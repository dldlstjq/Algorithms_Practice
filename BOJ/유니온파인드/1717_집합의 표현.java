/*
같은 집합인지 판별하는 유니온 파인드 문제이다.
알면 쉽지만 모르면 많이 어려울 것 같다.
find까지는 쉬운데 union은 길이가 긴 곳에 짧은 것을 붙일 때 rank를 잘 따져야 하는데
그게 잘 기억이 나지 않을 것 같다.
*/

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.StringTokenizer;


public class Main {
	
	static int n, m;
	static int[] parents;
	static int[] rank;
	
	static void init() {
		for(int i=1; i<=n; ++i) {
			parents[i] = i;
			rank[i] = 0;
		}
	}
	
	static int find(int num) {
		if(num == parents[num]) return num;
		return parents[num] = find(parents[num]);
	}
	
	static void union(int a, int b) {
		a = find(a);
		b = find(b);
		if(a == b) return;
		if(rank[a] > rank[b]) {
			int tmp = b;
			b = a;
			a = tmp;
		}
		parents[a] = b;
		if(rank[a] == rank[b]) rank[b]++;
	}
    
	public static void main(String[] args) throws Exception{
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine(), " ");

		n = Integer.parseInt(st.nextToken());
		m = Integer.parseInt(st.nextToken());
		
		parents = new int[n+1];
		rank = new int[n+1];
		init();
		for(int i=0; i<m; ++i) {
			int num, a, b;
			st = new StringTokenizer(br.readLine(), " ");
			num = Integer.parseInt(st.nextToken());
			a = Integer.parseInt(st.nextToken());;
			b = Integer.parseInt(st.nextToken());
			
			if(num == 0) {
				union(a,b);
			}
			else {
				if(find(a) == find(b))
					System.out.println("YES");
				else
					System.out.println("NO");
			}
		}
	}
}