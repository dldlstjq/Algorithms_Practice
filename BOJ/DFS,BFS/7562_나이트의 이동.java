/*
나이트가 목적지로 이동할 수 있는지 여부를 따진다.
이동할때 이동 횟수를 같이 가지고 가야 정확한 답을 구할 수 있다.
bfs를 활용해서 이미 지난 곳은 가지 않고 목적지에 도착하면 답을 출력한다.
*/

import java.awt.Point;
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.LinkedList;
import java.util.List;
import java.util.Queue;
import java.util.StringTokenizer;


public class Main {
	
	static class Pos{
		int r; int c; int cnt;
		Pos(int r, int c, int cnt){
			this.r=r;
			this.c=c;
			this.cnt=cnt;
		}
	}
	
	public static void main(String[] args) throws Exception {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

		int n=Integer.parseInt(br.readLine());
		
		int[] dr = {-1,-2,-2,-1,1,2,2,1};
		int[] dc = {-2,-1,1,2,2,1,-1,-2};
		
		for(int t=0; t<n; ++t) {
			
			int size = Integer.parseInt(br.readLine());
			boolean[][] visited = new boolean[size][size];
			
			StringTokenizer st= new StringTokenizer(br.readLine());
			int cr = Integer.parseInt(st.nextToken());
			int cc = Integer.parseInt(st.nextToken());
			
			st= new StringTokenizer(br.readLine());
			int er = Integer.parseInt(st.nextToken());
			int ec = Integer.parseInt(st.nextToken());
			
			int ans = 0;
			Queue<Pos> q =new LinkedList<>();
			q.add(new Pos(cr, cc, 0));
			visited[cr][cc] = true;
			
			boolean end = false;
			while(!q.isEmpty()) {
				Pos now = q.poll();
				
				for(int i=0; i<8; ++i) {
					int nr = now.r+dr[i];
					int nc = now.c+dc[i];
					
					if(!(0<=nr&&nr<size && 0<=nc&&nc<size)) continue;
					if(visited[nr][nc]) continue;
					
					if(nr == er && nc==ec) {
						end = true;
						ans = now.cnt+1;
						break;
					}
					
					q.add(new Pos(nr, nc, now.cnt+1));
					visited[nr][nc] = true;
				}
				
				if(end) break;
			}
			
			System.out.println(ans);
		}
	}
}