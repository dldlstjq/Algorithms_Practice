/*
시간내에 해결하지 못한 첫 문제이다.
우선 문제이해를 잘못했다. 궁수의 위치는 N+1위치에만 있을 수 있는데 이를 0, 1, 2 ... N행 모두에 위치할 수 있다고 생각하여 왜 예제 답이 저렇게 나오는지 이해를 못했다.
잘못 이해한채로 코드를 짜기 시작했고 한참이 지나서야 문제를 이해했다.

문제 이해 후에 재귀적 방식을 이용했는데 31%쯤에서 틀렸다.
궁수의 위치에서부터 거꾸로 올라가며 거리가 가장 가까운 적을 찾고 거리가 같다면 열 좌표가 작은 순으로 정렬하는 방식을 사용했다.
하지만 어디가 문제인지 찾지 못했다.

교수님 풀이를 들으니 거꾸로 올라가지 말고 1,1부터 시작해 차례로 훑으면서 거리가 짧은 것을 찾아 제거하면 쉽게 풀렸다.
문제 이해를 잘못한것, 완전탐색 방법을 잘못쓴 것 크게 두가지로 풀지 못했던 것 같다.
때로는 단순하게 생각해서 그냥 처음부터 검사해보는 사고를 가질 필요성을 느꼈다.
*/

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.LinkedList;
import java.util.Queue;
import java.util.StringTokenizer;

public class Main {
	
	static class Castle{
		int r,c;
		public Castle(int r, int c) {
			this.r = r;
			this.c = c;
		}
	}
	
	static int N, M, D;	// 행, 열, 공격 거리
	static int[][] origin;	// 원본 배열
	static int[][] tmp;	// 임시 배열
	static Castle[] arrow;	// 궁수 저장
	static int maxKill;	// 정답 저장
	static int kill;
	
	static void solve(int idx, int start) {
		if(idx == 3) {
			kill = 0;
			copyArray();
			int turn = 0;
			while(isEnemy()) {
				killEnemy();
				moveEnemy();
			}
			 
			maxKill = Math.max(maxKill, kill);
			return;
		}
		
		for(int i=start; i<=M; ++i) {
			// 맨 마지막 행에서 3개 조합
			arrow[idx] = new Castle(N+1, i);
			solve(idx+1, i+1);
		}
	}
	
	private static void moveEnemy() {
		for(int i=N; i>=1; i--) {
			tmp[i] = tmp[i-1];
		}

	}

	private static void killEnemy() {
		Queue<Castle> queue = new LinkedList<>();
		ArrayList<Castle> list = new ArrayList<>();
//		kill = 0;
		
		for(int k=0; k<arrow.length; ++k) {
			Castle castle = arrow[k];
			int r = 0;
			int c = M+1;	// 제일 우측 상단
			list.clear();
			
			int minDist = D;	// 제일 길어봤자 D 거리이다.
			
			for(int i=1; i<=N; ++i) {
				for(int j=1; j<=M; ++j) {
					if(tmp[i][j] == 0)
						continue;
					int dist = Math.abs(castle.r-i)+ Math.abs(castle.c-j);
					if(minDist>dist || (minDist == dist && j<c)) {
						minDist = Math.min(minDist, dist);
						r=i;
						c=j;
					}
				}
				
			}
			if(r!=0 && c!= M+1)
				queue.offer(new Castle(r,c));
		}
		while(!queue.isEmpty()) {
			Castle now = queue.poll();
			if(tmp[now.r][now.c] != 0)
				kill++;
			tmp[now.r][now.c] = 0;
		}
	}

	// 1이 있다는 건 적이  맵에 있다.
	private static boolean isEnemy() {
		for(int i=1; i<=N; ++i)
			for(int j=1; j<=M; ++j)
				if(tmp[i][j] == 1)
					return true;
		return false;
	}


	private static void copyArray() {
		tmp = new int[N+1][M+1];
		for(int i=1; i<=N; ++i)
			tmp[i] = origin[i].clone();
	}


	public static void main(String[] args) throws Exception{
		
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine(), " ");
		
		N = Integer.parseInt(st.nextToken());
		M = Integer.parseInt(st.nextToken());
		D = Integer.parseInt(st.nextToken());
		
		origin = new int[N+1][M+1];

		arrow = new Castle[3];
		
		maxKill = 0;
		
		for(int i=1; i<=N; ++i) {
			st = new StringTokenizer(br.readLine(), " ");
			for(int j=1; j<=M; ++j) {
				origin[i][j] =  Integer.parseInt(st.nextToken());
			}
		}
		
		solve(0, 1);
		
		System.out.println(maxKill);
	}
}
