/*
리스트만 사용한 풀이.
하나의 좌표에 여러 세포가 들어간 경우를 위해 행, 열 값으로 세포번호를 지정해준다.
세포번호순서로 정렬하면 같은 위치의 세포가 붙어있게 되고, 같은 세포번호라면 수가 가장 많은 것이 앞에 오도록 정렬 기준을 잡아주면 겹치는 부분을 쉽게 해결 가능하다.

수가 가장 많은 것만 남겨두고 하나씩 remove 해주면 리스트 하나로 해결 가능.
시간도 2차원 쓰는 것 보다 절반 가까이 절약
*/
import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Collections;
import java.util.LinkedList;
import java.util.List;
import java.util.Queue;
import java.util.StringTokenizer;

public class Solution {
	static class Cell implements Comparable<Cell>{
		int num; int r; int c; int cnt; int dir;
		Cell(int num, int r, int c, int cnt, int dir){
			this.num=num;
			this.r=r;
			this.c=c;
			this.cnt=cnt;
			this.dir=dir;
		}
		@Override
		public int compareTo(Cell o) {
			if(this.num==o.num)
				return Integer.compare(o.cnt, this.cnt);
			return Integer.compare(this.num, o.num);
		}
		
//		Cell(int num, int dir){
//			this.num=num;
//			this.dir=dir;
//		}
	}
	
	static int N, M, K;
	static List<Cell> list;	// 이동한 세포 기준 좌표 저장
	
	static int dr[]= {0,-1,1,0,0};
	static int dc[]= {0,0,0,-1,1};
	
	public static void main(String[] args) throws Exception {
		//System.setIn(new FileInputStream("sample_input.txt"));
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		
		int T = Integer.parseInt(br.readLine());

		for(int test_case = 1; test_case <= T; test_case++)
		{
			StringTokenizer st = new StringTokenizer(br.readLine());
			N = Integer.parseInt(st.nextToken());
			M = Integer.parseInt(st.nextToken());
			K = Integer.parseInt(st.nextToken());
			
			list = new ArrayList<>();
			
			for(int i=0; i<K; ++i) {
				st = new StringTokenizer(br.readLine());
				int r = Integer.parseInt(st.nextToken());
				int c = Integer.parseInt(st.nextToken());
				int n = Integer.parseInt(st.nextToken());
				int d = Integer.parseInt(st.nextToken());
				
				list.add(new Cell(r*N+c, r, c, n, d));
			}
			
			for(int i=0; i<M; ++i) {
				start();
			}
			StringBuilder sb = new StringBuilder();
			sb.append("#").append(test_case).append(" ").append(getSum());
			System.out.println(sb);
			
		}
	}

	private static void start() {
		for(int i=0; i<list.size(); ++i) {
			Cell cell = list.get(i);
			cell.r = cell.r+dr[cell.dir];
			cell.c = cell.c+dc[cell.dir];
			cell.num = cell.r*N+cell.c;

			// 빨간 약품
			if(cell.r==0 || cell.r==N-1 || cell.c==0 || cell.c==N-1) {
				cell.cnt /=2;
				if(cell.dir%2==0) cell.dir--;
				else cell.dir++;
				if(cell.cnt==0) {
					list.remove(i);
					--i;
				}
			}
		}
		
		Collections.sort(list);
		for(int i=0; i<list.size()-1; ++i) {
			Cell now = list.get(i);
			Cell next = list.get(i+1);
			
			if(now.num == next.num) {
				now.cnt += next.cnt;
				list.remove(i+1);
				--i;
			}
		}
		
	}

	private static int getSum() {
		int sum = 0;
		for(int i=0; i<list.size(); ++i)
			sum += list.get(i).cnt;
		return sum;
	}
}
