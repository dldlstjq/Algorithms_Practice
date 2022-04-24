/*
어찌저찌 풀긴 풀었는데 풀이가 많이 복잡한 것 같다.
사람이 10명이고 계단도 2개밖에 없기 때문에 모든 사람이 2개 계단을 다 이용했을 때 최소를 구하려고 했다.
그래서 두 그룹으로 나누어 한 그룹은 1번계단, 다른 그룹은 2번계단을 사용하려 했다.
만약 사람이 4명이면 (0,4) (1,3) (2,2) 이렇게 나누어 계단 하나씩 보내면 전체 경우를 다 구할 수 있다고 판단했다.
모든 조합을 구해서 1, 2번계단을 각각 이용했을 때 최소를 구했다.
여기서 입구까지 이동시간이랑 전체 시간이랑 같은 경우 대기시간이 포함되지만
입구까지 이동했는데 계단이 꽉차서 기다리는 상태일때는 대기시간 1분이 포함되지 않는다.
그 점을 생각해서 제출하니 풀렸다.

다른 풀이를 찾아보니 그냥 사람 한 명씩 1번으로 보내고 2번으로 보내서 전체 걸리는 시간을 구했다.
굳이 두 그룹으로 나눌 필요도 없었다. 한명씩 1번, 2번으로 보내서 전부 계산하면 된다.
계산 방법은 좀 더 효율적인 방안을 찾아봐야 할 것 같다.
계단에 도착했을 때 시간을 따로 저장한 후 계단을 내려올 때, 계단크기+계단도착시간=전체 경과시간이면 계단을 모두 내려온 것임을 이용하면 쉽게 해결할 수 있을 것 같다.
*/

import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.LinkedList;
import java.util.List;
import java.util.PriorityQueue;
import java.util.Queue;
import java.util.StringTokenizer;


public class Solution
{
	static class Pos{
		int r; int c;
		Pos(int r, int c){
			this.r=r;
			this.c=c;
		}
	}
	
	static int N;
	static int[][] map;
	static Pos stair1;
	static Pos stair2;
	
	static List<Pos> list;
	static Pos[] arr1;
	static Pos[] arr2;
	
	static int time;
	
    public static void main(String args[]) throws Exception{
    	//System.setIn(new FileInputStream("sample_input.txt"));
    	
	    BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
	    
		int T = Integer.parseInt(br.readLine());

		for(int test_case = 1; test_case <= T; test_case++)
		{
			StringTokenizer st = null;
			N = Integer.parseInt(br.readLine());
			map = new int[N][N];
			list=  new ArrayList<>();
			stair1 = new Pos(0, 0);
			stair2 = new Pos(0, 0);
			
			for(int i=0; i<N; ++i) {
				st = new StringTokenizer(br.readLine());
				for(int j=0; j<N; ++j) {
					map[i][j] = Integer.parseInt(st.nextToken());
					if(map[i][j] == 1) list.add(new Pos(i, j));
					
					else if(2<= map[i][j] && map[i][j]<=10) {
						if(stair1.r==0 && stair1.c==0) {
							stair1.r=i;
							stair1.c=j;
						}
						else {
							stair2.r=i;
							stair2.c=j;
						}
					}
				}
			}
			
			
			time = Integer.MAX_VALUE;
			if(list.size()==1) {
				
				for(int i=0; i<list.size(); ++i) {
					arr1 = new Pos[i];
					arr2 = new Pos[list.size()-i];
					solve(i, 0, 0);
				}
			}
			else {
				for(int i=0; i<=list.size()/2; ++i) {
					arr1 = new Pos[i];
					arr2 = new Pos[list.size()-i];
					solve(i, 0, 0);
				}
			}
			
			
			StringBuilder sb= new StringBuilder();
			sb.append("#").append(test_case).append(" ").append(time);
			System.out.println(sb);
			
		}
    }

	private static void solve(int size, int idx, int visited) {
		if(idx==size) {
			// arr2 원소 삽입
			int k=0;
			
			for(int i=0; i<list.size(); ++i) {
				if((visited&(1<<i)) !=0) continue;
				arr2[k++] = list.get(i);
			}
			
			time = Integer.min(time, useStair1());
			time = Integer.min(time, useStair2());
			
			return;
		}
		
		for(int i=0; i<list.size(); ++i) {
			if((visited&(1<<i)) !=0) continue;
			arr1[idx] = list.get(i);
			solve(size, idx+1, visited|1<<i);
		}
	}

	private static int useStair2() {
		// arr1이 2번계단, arr2가 1번계단 사용
		PriorityQueue<Integer> wait1 = new PriorityQueue<>();	// 1번계단 까지 이동시간
		PriorityQueue<Integer> wait2 = new PriorityQueue<>();	// 2번계단 까지 이동시간
		
		Queue<Integer> upstair1 = new LinkedList<>();	// 1번계단 상태
		Queue<Integer> upstair2 = new LinkedList<>();	// 2번계단 상태
		
		int total = 0;	// 전체 경과 시간
		
		// 계단까지 이동시간
		for(int i=0; i<arr1.length; ++i) {
			Pos p = arr1[i];
			wait2.add(Math.abs(stair2.r-p.r)+Math.abs(stair2.c-p.c));
		}
		
		for(int i=0; i<arr2.length; ++i) {
			Pos p = arr2[i];
			wait1.add(Math.abs(stair1.r-p.r)+Math.abs(stair1.c-p.c));
		}
		
		// 계단 입구까지 걸리는시간+ 계단 내려가는 시간 계산
		while(true) {
			total++;
			
			// 계단 내려가는 중
			int size = upstair1.size();
			while(size-- > 0) {
				int t = upstair1.poll();
				if(t-1!=0) upstair1.add(t-1);
			}
			
			size = upstair2.size();
			while(size-- > 0) {
				int t = upstair2.poll();
				if(t-1!=0) upstair2.add(t-1);
			}
			
			// 계단 입구까지 이동 중
			size = wait1.size();
			int min = map[stair1.r][stair1.c];
			while(size-- > 0) {
				int t = wait1.poll();
				// 전체 시간이랑 이동 시간이 딱 맞으면 입구에서 대기하는 시간+1
				if(t==total && upstair1.size() < 3) 
					upstair1.add(min+1);
				// 전체 시간이 입구까지 이동시간보다 크면 대기하지 않고 바로 출발
				else if(t<total && upstair1.size() < 3) 
					upstair1.add(min);
				
				else wait1.offer(t);
			}
			
			size = wait2.size();
			min = map[stair2.r][stair2.c];
			while(size-- > 0) {
				int t = wait2.poll();
				if(t==total && upstair2.size() < 3) 
					upstair2.add(min+1);
				else if(t<total && upstair2.size() < 3) 
					upstair2.add(min);
				else wait2.offer(t);
			}
			
			if(wait1.isEmpty() && wait2.isEmpty()
				&& upstair1.isEmpty() && upstair2.isEmpty())
				break;
			
		}
		return total;
	}

	private static int useStair1() {
		// arr1이 1번계단, arr2가 2번계단 사용
		PriorityQueue<Integer> wait1 = new PriorityQueue<>();	// 1번계단 까지 이동시간
		PriorityQueue<Integer> wait2 = new PriorityQueue<>();	// 2번계단 까지 이동시간
		
		Queue<Integer> upstair1 = new LinkedList<>();	// 1번계단 상태
		Queue<Integer> upstair2 = new LinkedList<>();	// 2번계단 상태
		
		int total = 0;
		
		for(int i=0; i<arr1.length; ++i) {
			Pos p = arr1[i];
			wait1.add(Math.abs(stair1.r-p.r)+Math.abs(stair1.c-p.c));
		}
		
		for(int i=0; i<arr2.length; ++i) {
			Pos p = arr2[i];
			wait2.add(Math.abs(stair2.r-p.r)+Math.abs(stair2.c-p.c));
		}
		
		while(true) {
			total++;
			
			int size = upstair1.size();
			while(size-- > 0) {
				int t = upstair1.poll();
				if(t-1!=0) upstair1.add(t-1);
			}
			
			size = upstair2.size();
			while(size-- > 0) {
				int t = upstair2.poll();
				if(t-1!=0) upstair2.add(t-1);
			}
			
			
			size = wait1.size();
			int min = map[stair1.r][stair1.c];
			while(size-- > 0) {
				int t = wait1.poll();
				if(t==total && upstair1.size() < 3)
					upstair1.add(min+1);
				else if(t<total && upstair1.size() < 3) {
					upstair1.add(min);
				}
				else wait1.offer(t);
			}
			
			size = wait2.size();
			min = map[stair2.r][stair2.c];
			while(size-- > 0) {
				int t = wait2.poll();
				if(t==total && upstair2.size() < 3) 
					upstair2.add(min+1);
				else if(t<total && upstair2.size() < 3) 
					upstair2.add(min);
				else wait2.offer(t);
			}
			
			if(wait1.isEmpty() && wait2.isEmpty()
				&& upstair1.isEmpty() && upstair2.isEmpty())
				break;
			
		}
		return total;
		
	}

    
   
}