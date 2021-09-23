/*
각 도시들이 같은 집합에 속해 있으면 방문 가능하고 같은 집합이 아니면 방문할 수 없다.
1인 도시들을 유니온 해주고 첫번째 도시는 따로 저장해서 두번째 도시부터 첫번째 도시와 같은 집합인지 확인한다.
*/

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.StringTokenizer;

public class Main {
	
	static int N, M;
	static ArrayList<Integer> [] arr;
	static int[][] map;
	static int[] parents;
	static int[] rank;
	
	static int[] city;
	
	static void make() {
		for(int i=0; i<N; ++i) {
			parents[i] = i;
			rank[i] = 0;
		}
	}
	
	static int find(int a) {
		if(parents[a] == a) return a;
		return parents[a] = find(parents[a]);
	}
	
	static boolean union(int a, int b) {
		a = find(a); b= find(b);
		if(a == b) return false;
		
		if(rank[a] > rank[b]) {
			int tmp = b;
			b = a;
			a = tmp;
		}
		parents[a] = b;
		if(rank[a] == rank[b]) rank[b]++;
		return true;
	}
	
	public static void main(String[] args) throws Exception {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
//		StringTokenizer st = new StringTokenizer(br.readLine());
		
		N = Integer.parseInt(br.readLine());
		M = Integer.parseInt(br.readLine());
		
		map = new int[N][N];
		city = new int[M];
		parents = new int[N];
		rank = new int[N];
		
		StringTokenizer st;
		for(int i=0; i<N; ++i) {
			st = new StringTokenizer(br.readLine());
			for(int j=0; j<N; ++j) {
				map[i][j] = Integer.parseInt(st.nextToken());
			}
		}
		
		st = new StringTokenizer(br.readLine());
		for(int i=0; i<M; ++i)
			city[i] = Integer.parseInt(st.nextToken());
		
		make();
		
		for(int i=0; i<N; ++i) {
			for(int j=0; j<N; ++j) {
				if(map[i][j] == 0) 
					continue;
				union(i, j);
			}
		}
		
		boolean flag = true;
		int root = 0;
		for(int i=0; i<M; ++i) {
			if(i == 0)
				root = find(city[i]-1);
			else {
				if(find(city[i]-1) != root) {
					flag = false;
					break;
				}
			}
		}
		
		if(flag)
			System.out.println("YES");
		else
			System.out.println("NO");
	}
}
