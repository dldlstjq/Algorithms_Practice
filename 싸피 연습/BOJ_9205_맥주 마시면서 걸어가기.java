/*
플로이드 와샬을 쓰는 건데 어떻게 적용해야할지 몰라서 많이 헤맸다.
맥주를 50m마다 한병씩 마시기 때문에 1000m를 갈 때 20병을 마셔야 한다.
그래서 맨해튼 거리가 1000m 보다 작으면 연결하고 아니면 연결하지 않는다.
이 상태에서 플로이드 와샬을 이용해 거리를 구하고 마지막 페스티벌에 갈 수 있는지 없는지 확인하면 된다.

여기서 또 틀린게 거리를 50으로 나눠 20병 밑인지 계산하려 했는데 50으로 딱 나누어 떨어지지 않는 경우도 있어 double 형으로 형 변환을 해야 답이 나왔다.

플로이드 와샬을 이용하지 않고 그래프로 나타낸 뒤 bfs, dfs로 마지막까지 갈 수 있는지 확인하는 방법도 있다.
*/

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.StringTokenizer;

public class Main {
	
	static class Pos{
		int x, y;
		Pos(int x, int y){
			this.x=x;
			this.y=y;
		}
	}
	
	static int getLen(Pos a, Pos b) {
		return Math.abs(a.x-b.x)+Math.abs(a.y-b.y);
	}
	
	
	public static void main(String[] args) throws Exception {
	
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		
		int T;
		T= Integer.parseInt(br.readLine());

		for(int test_case = 1; test_case <= T; test_case++)
		{
		
			int N = Integer.parseInt(br.readLine());
			
			int[][] adj = new int[N+2][N+2];
			int INF = 102;
			
			ArrayList<Pos> list = new ArrayList<>();
			
			for(int i=0; i<N+2; ++i) {
				StringTokenizer st = new StringTokenizer(br.readLine());
				int x = Integer.parseInt(st.nextToken());
				int y = Integer.parseInt(st.nextToken());
				list.add(new Pos(x,y));
			}
			
			for(int i=0; i<N+2; ++i) {
				for(int j=0; j<N+2; ++j) {
					if (i == j) {
						adj[i][j]=INF;
						continue;
					}
	                    
					int dist= getLen(list.get(i), list.get(j));
					// 20병 이하로 갈 수 있으면 연결
					if(dist<=1000)
						adj[i][j]=1;
					else
						adj[i][j]=INF;
				}
			}
			
			// 경출도
			for(int k =0; k<N+2; ++k) {
				for(int i=0; i<N+2; ++i) {
					for(int j=0; j<N+2; ++j)
						adj[i][j] = Math.min(adj[i][j], adj[i][k]+adj[k][j]);
				}
			}
			
			
			if(0< adj[0][N+1] && adj[0][N+1] < INF )
				System.out.println("happy");
			else
				System.out.println("sad");
		}
	}
}
