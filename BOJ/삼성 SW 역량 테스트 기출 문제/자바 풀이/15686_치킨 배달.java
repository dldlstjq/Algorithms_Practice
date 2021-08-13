/*
삼성 기출에 있는 문제인데 조합이다보니 수업시간에 풀게 됐다.
치킨집 중에서 M개를 뽑아 각 집과의 거리가 최소가 되도록 구하면 된다.
전체 치킨집 중 순서 상관없이 M개를 뽑기 때문에 조합을 이용했고 처음엔 재귀로 접근하여 해결했다.
nextpermutation으로도 조합이 가능해서 np로도 풀어봤다.

집과의 거리를 구해야 하기 때문에 집 정보, 치킨 정보를 모두 따로 저장해야하고 구할때마다 거리 값을 갱신해주면 쉽게 풀리는 것 같다.
*/

// 재귀 풀이
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.StringTokenizer;

public class Main {
	static class City{
		int r,c;
		public City(int r, int c) {
			super();
			this.r = r;
			this.c = c;
		}
	}
	
	static int N, M;
	static int[][] map;		// 도시 정보
	static ArrayList<City> home = new ArrayList<City>();	// 집 저장
	static ArrayList<City> chicken = new ArrayList<City>();	// 치킨집 저장
	static City[] selectChicken;	// 선택할 치킨집 저장
	static int ans;	// 정답 저장
	
	private static int calcDist() {
		int ret = 0;
		// 한 집에서 모든 치킨 가게 중 최소 거리를 구해 ret에 저장한다.
		for(int i=0; i<home.size(); ++i) {
			int dist = Integer.MAX_VALUE;
			for(int j=0; j<selectChicken.length; ++j) {
				// 각 집과 치킨 집 거리 사이 최소 거리를 dist에 저장
				dist = Math.min(dist, Math.abs(home.get(i).r-selectChicken[j].r) + Math.abs(home.get(i).c-selectChicken[j].c));
			}
			ret += dist;
		}
		return ret;
	}
	
	static void solve(int idx, int start) {
		// M개를 뽑았으면 치킨 거리 최솟값을 구한다.
		if(idx == M) {
			ans = Math.min(ans, calcDist());
			return;
		}
		
		// chicken에 저장된 치킨집 수에서 M개를 뽑는다
		for(int i=start; i<chicken.size(); ++i) {
			selectChicken[idx] = chicken.get(i);
			solve(idx+1, i+1);
		}
	}
	
	public static void main(String[] args) throws Exception{
		
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine(), " ");
		
		N = Integer.parseInt(st.nextToken());
		M = Integer.parseInt(st.nextToken());
		
		map= new int[N][N];
		selectChicken = new City[M];	// 선택할 치킨집 저장
		ans = Integer.MAX_VALUE;	// 최소값을 구하기 때문에 정답은 최대로
		
		for(int i=0; i<N; ++i) {
			st = new StringTokenizer(br.readLine(), " ");
			for(int j=0; j<N; ++j) {
				map[i][j] = Integer.parseInt(st.nextToken());
				// 집 정보는 home에 저장
				if(map[i][j] == 1)
					home.add(new City(i, j));
				// 치킨 집 정보는 chicken에 저장
				if(map[i][j] == 2)
					chicken.add(new City(i, j));
			}
		}
		
		solve(0, 0);
		System.out.println(ans);
	}
}



// nextpermutation 풀이
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Collections;
import java.util.StringTokenizer;

public class Main {
	
	static class City{
		int r,c;
		public City(int r, int c) {
			super();
			this.r = r;
			this.c = c;
		}
	}
	
	static int N, M;
	static int[][] map;		// 도시 정보
	static ArrayList<City> home = new ArrayList<City>();	// 집 정보 저장
	static ArrayList<City> chicken = new ArrayList<City>();	// 치킨집 정보 저장
	static int ans;	// 정답 저장

	public static void main(String[] args) throws Exception{
		
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine(), " ");
		
		N = Integer.parseInt(st.nextToken());
		M = Integer.parseInt(st.nextToken());
		
		map= new int[N][N];
		ans = Integer.MAX_VALUE;	// 최소값을 구하기 때문에 정답은 최대로
		
		for(int i=0; i<N; ++i) {
			st = new StringTokenizer(br.readLine(), " ");
			for(int j=0; j<N; ++j) {
				map[i][j] = Integer.parseInt(st.nextToken());
				// 집 정보는 home에 저장
				if(map[i][j] == 1)
					home.add(new City(i, j));
				// 치킨 집 정보는 chicken에 저장
				if(map[i][j] == 2)
					chicken.add(new City(i, j));
			}
		}
		
		getDist();
		System.out.println(ans);
	}
	
	// np 풀이
	static void getDist() {
		int size = chicken.size();
		
        // M개 만큼 뒤에서부터 1로 채움
		int[] p = new int[size];
		for(int i=size-1; i>=size-M; --i)
			p[i] = 1;
		
        // p[j]==1인 부분만 선택한 치킨 집
		do {
			int ret = 0;
			// 한 집에서 모든 치킨 가게 중 최소 거리를 구해 ret에 저장한다.
			for(int i=0; i<home.size(); ++i) {
				int dist = Integer.MAX_VALUE;
				for(int j=0; j<chicken.size(); ++j) {
					if(p[j] == 1)
					// 각 집과 치킨 집 거리 사이 최소 거리를 dist에 저장
						dist = Math.min(dist, Math.abs(home.get(i).r-chicken.get(j).r) + Math.abs(home.get(i).c-chicken.get(j).c));
				}
				ret += dist;
			}
			ans = Math.min(ans, ret);	
		}while(np(p));
	}
	
	static boolean np(int[] numbers) {
		int N = numbers.length;
		
		int i=N-1;
		while(i>0 && numbers[i-1]>= numbers[i])
			--i;
		
		if(i==0)
			return false;
		
		int j= N-1;
		while(numbers[i-1]>= numbers[j])
			--j;
		
		swap(numbers, i-1, j);
		
		int k=N-1;
		while(i<k)
			swap(numbers, i++, k--);
		
		return true;
	}

	private static void swap(int[] numbers, int i, int j) {
		int tmp = numbers[i];
		numbers[i] = numbers[j];
		numbers[j] = tmp;
	}
}