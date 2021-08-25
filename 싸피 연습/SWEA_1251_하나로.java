/*
모든 섬을 연결하는 최소 간선을 찾아야 하므로 MST 문제였다.
프림이나 크루스칼을 이용하면 되고 시작간선이 주어지지 않아 모든 섬을 시작으로 해서 N번 돌렸는데 다행히 시간초과는 안났다.
하지만 다른 사람들 보다 유독 시간이 많이 나왔고 보니까 출발점을 0으로 잡고 해도 무방했다.
그래프 문제가 코테에서 무조건 하나 이상은 나올 가능성이 높기 때문에 MST, 최단거리 알고리즘은 꼭 익혀놔야겠다.
*/
import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.InputStreamReader;
import java.util.Arrays;
import java.util.StringTokenizer;

public class Main {
	
	static class Pos{
		int x, y;

		public Pos(int x, int y) {
			super();
			this.x = x;
			this.y = y;
		}
	
	}
	
	static double getLen(Pos a, Pos b) {
		return E*(Math.pow(a.x-b.x, 2) + Math.pow(a.y-b.y, 2));
	}
	
	static int N;	// 섬 개수
	static double E;	// 환경 부담 세율
	static Pos[] island;	// 섬 좌표 저장
	static int[] distance;	// 각 섬의 환경 부담금
	
	private static long Prim() {
		long result = Long.MAX_VALUE;	// 최소 신장트리 비용
		
		double sum = 0;
		boolean visited[] = new boolean[N];
		double[] minCost = new double[N];
		Arrays.fill(minCost, Double.MAX_VALUE);
		
		minCost[0] = 0;
		
		for(int j=0; j<N; ++j) {
			double min = Double.MAX_VALUE;
			int current = -1;	// 최소 간선 비용 정점번호
			for(int k=0; k<N; ++k) {
				if(!visited[k] && min > minCost[k]) {
					min = minCost[k];
					current = k;
				}
			}
			visited[current] = true;	// 신장트리 포함
			sum += min;	// 간선 비용 누적
			
			// 모든 섬과 환경부담금 체크
			for(int k=0; k<N; ++k) {
				double cost = getLen(island[current], island[k]);
				if(!visited[k] && minCost[k] > cost) {
					minCost[k] = cost;
				}
			}
			
		}
		// 반올림 한 후 long타입으로 변경
		result = (long)Math.round(sum);
		return result;
	}
	
	public static void main(String[] args) throws Exception {
		System.setIn(new FileInputStream("input.txt"));
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = null;
		
		
		int T = Integer.parseInt(br.readLine());
		
		for(int test_case = 1; test_case <= T; test_case++)
		{
			N = Integer.parseInt(br.readLine());
			island = new Pos[N];
			// 좌표 초기화
			for(int i=0; i<N; ++i) 
				island[i] = new Pos(0, 0);
			
			// x, y좌표 입력
			for(int i=0; i<2; ++i) {
				st = new StringTokenizer(br.readLine(), " ");
				for(int j=0; j<N; ++j) {
					if(i == 0)
						island[j].x = Integer.parseInt(st.nextToken());
					else
						island[j].y = Integer.parseInt(st.nextToken());
				}
			}
			
			E = Double.parseDouble(br.readLine());
		
			// 환경부담금이 간선이므로 모든 섬을 연결하는 MST를 찾는다.
			// 프림 사용
			StringBuilder sb=  new StringBuilder();
			sb.append("#"+test_case+" ").append(Prim());
			System.out.println(sb);
		}
	}
}