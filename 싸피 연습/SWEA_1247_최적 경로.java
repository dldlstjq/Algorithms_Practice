/*
처음엔 TSP문제인줄 알았지만 단순히 경로 길이의 최소를 구하면 됐다.
최대가 10이라서 순열을 이용해 풀어도되고 백트래킹을 하면 시간이 더 적게 걸린다.
*/

// 순열 풀이
import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.StringTokenizer;

public class Solution {
	
	static class Point{
		int x, y;

		public Point(int x, int y) {
			super();
			this.x = x;
			this.y = y;
		}
		
		public int dist(Point p) {
			return Math.abs(this.x - p.x) + Math.abs(this.y - p.y);
		}
	}

	static int N;
	static Point home, company;	// 집과 회사 좌표
	static Point[] customer;	// 고객 좌표
	static Point[] arr;	// 순열로 만든 배열
	
	static int minDist;
	
	// 거리 계산
	private static int calcDist() {
		// 첫번쨰 고객과 회사 거리 구함
		int distance = arr[0].dist(company);
		for(int i=1; i<N; ++i) {
			// 현재 고객과 이전 고객 사이 거리를 다 더함
			distance += arr[i].dist(arr[i-1]);
		}
		// 마지막에 집에 돌아오는 거리를 저장
		distance += arr[N-1].dist(home);
		return distance;
	}
	
	private static void perm(int idx, int flag) {
		// 순열을 다 만들었으면 거리를 계산한다.
		if(idx == N) {
			minDist = Math.min(minDist, calcDist());
			return;
		}
		
		// 고객 좌표를 순열로 모두 구한다.
		for(int i=0; i<N; ++i) {
			if((flag&(1<<i))!=0) continue;
			arr[idx] = customer[i];
			perm(idx+1, flag|1<<i);
		}
	}
    
	public static void main(String[] args) throws Exception{
		//System.setIn(new FileInputStream("input.txt"));
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		
		int T = Integer.parseInt(br.readLine());
		
		for(int test_case = 1; test_case <= T; test_case++)
		{
			N = Integer.parseInt(br.readLine());
			customer = new Point[N];
			arr = new Point[N];
			
			StringTokenizer st = new StringTokenizer(br.readLine(), " ");
			// 집과 회사 좌표 저장
			home = new Point(Integer.parseInt(st.nextToken()), Integer.parseInt(st.nextToken()));
			company = new Point(Integer.parseInt(st.nextToken()), Integer.parseInt(st.nextToken()));
			
			// 고객 좌표 저장
			for(int i=0; i<N; ++i) {
				customer[i] =new Point(Integer.parseInt(st.nextToken()), Integer.parseInt(st.nextToken()));
			}
			
			// 최소거리 초기화
			minDist = Integer.MAX_VALUE;
			
			// 순열로 모든 고객 좌표를 구해서 최소거리를 구한다.
			perm(0, 0);
			
			StringBuilder sb = new StringBuilder();
			sb.append("#"+test_case+" ").append(minDist);
			System.out.println(sb);
		}
	}
}



// np풀이
import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.StringTokenizer;

public class Solution {
	
	static class Point implements Comparable<Point>{
		int x, y;

		public Point(int x, int y) {
			super();
			this.x = x;
			this.y = y;
		}
		
		public int dist(Point p) {
			return Math.abs(this.x - p.x) + Math.abs(this.y - p.y);
		}
		
		@Override
		public int compareTo(Point o) {
			if(this.x == o.x)
				return this.y-o.y;
			return this.x-o.x;
		}
	}
	
	static int N;
	static Point home, company;	// 집과 회사 좌표
	static Point[] customer;	// 고객 좌표
	
	static int minDist;	// 최종 정답
	
	public static void main(String[] args) throws Exception{
		//System.setIn(new FileInputStream("input.txt"));
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		
		int T = Integer.parseInt(br.readLine());
		
		for(int test_case = 1; test_case <= T; test_case++)
		{
			N = Integer.parseInt(br.readLine());
			customer = new Point[N];
			
			StringTokenizer st = new StringTokenizer(br.readLine(), " ");
			// 집과 회사 좌표 저장
			home = new Point(Integer.parseInt(st.nextToken()), Integer.parseInt(st.nextToken()));
			company = new Point(Integer.parseInt(st.nextToken()), Integer.parseInt(st.nextToken()));
			
			// 고객 좌표 저장
			for(int i=0; i<N; ++i) {
				customer[i] =new Point(Integer.parseInt(st.nextToken()), Integer.parseInt(st.nextToken()));
			}
			
			// 최소거리 초기화
			minDist = Integer.MAX_VALUE;
			
			// nextPermutation
			Arrays.sort(customer);	// x좌표 오름차순으로 정렬
			do {
				minDist = Math.min(minDist, calcDist2(customer));
			}while(np(customer));
			
			StringBuilder sb = new StringBuilder();
			sb.append("#"+test_case+" ").append(minDist);
			System.out.println(sb);
		}
	}
	
	private static int calcDist2(Point[] p) {
		// 첫번쨰 고객과 회사 거리 구함
		int distance = p[0].dist(company);
		for(int i=1; i<N; ++i) {
			// 현재 고객과 이전 고객 사이 거리를 다 더함
			distance += p[i].dist(p[i-1]);
		}
		// 마지막에 집에 돌아오는 거리를 저장
		distance += p[N-1].dist(home);
		return distance;
	}

	private static boolean np(Point[] p) {
		int N = p.length;
		int i = N-1;
		while(i>0 && p[i-1].x>=p[i].x) --i;
		if(i==0)
			return false;
		
		int j = N-1;
		while(p[i-1].x>=p[j].x) --j;
		swap(p, i-1, j);
		int k = N-1;
		while(i<k) swap(p, i++, k--);
		return true;
	}

	private static void swap(Point[] p, int i, int j) {
		Point tmp = p[i];
		p[i] = p[j];
		p[j] = tmp;
	}
	
}
