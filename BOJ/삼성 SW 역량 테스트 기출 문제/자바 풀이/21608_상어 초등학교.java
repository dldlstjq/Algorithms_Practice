/*
실제 시험장에서 풀어봤던 문제라 그런지 이해는 잘 됐다.
여러가지 기준에 따라 우선순위가 달라지는 문제는 클래스를 이용해 정렬 기준을 정해두고
리스트에 저장해 정렬을 통해 쉽게 풀어내는 방식을 사용하고 있다.
c++로 풀 때는 그 방법을 몰라 좀 어렵게 풀었던 것 같은데 자바는 이 방식을 활용하니 그나마 깔끔하게 풀 수 있었던 것 같다.

문제 자체는 그리 어렵지 않아 시험에서 1시간 10분정도만에 풀었던 걸로 기억한다.
지금 실력으로 이런 비슷한 문제가 나오면 1시간 이내에 풀 수 있어야 되지 않나 싶다.
*/

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.List;
import java.util.StringTokenizer;

public class Main {
	
	static class Student implements Comparable<Student>{
		int like; int space; int r; int c;
		
		Student(int like, int space, int r, int c){
			this.like = like;
			this.space = space;
			this.r = r;
			this.c = c;
		}
		
		// 좋아하는 학생이 많고, 비어있는 칸이 많고, 행 번호가 작고, 열 번호가 작은 순서
		@Override
		public int compareTo(Student o) {
			if(this.like == o.like) {
				if(this.space == o.space) {
					if(this.r == o.r)
						return Integer.compare(this.c, o.c);
					return Integer.compare(this.r, o.r);
				}
				return Integer.compare(o.space, this.space);
			}
			return Integer.compare(o.like, this.like);
		}
	}
	
	static int N;
	static int snum;
	static int order[];
	static int room[][];
	static List<Integer>[] list;
	static int dr[] = {-1,0,1,0};
	static int dc[] = {0,1,0,-1};
	static int ret;
	
	public static void main(String[] args) throws Exception {
//		System.setIn(new FileInputStream("sample_input.txt"));
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		
		N = Integer.parseInt(br.readLine());
		
		room = new int[N][N];	// 교실 크기는  n*n
		order = new int [N*N];	// 앉는 순서 저장
		
		// 번호별로 좋아하는 친구 저장
		list= new ArrayList[N*N+1];
		for(int i=0; i<=N*N; ++i)
			list[i] = new ArrayList<>();
		
		for(int i=0; i<N*N; ++i) {
			StringTokenizer st = new StringTokenizer(br.readLine());
			int[] tmp = new int[5];
			for(int j=0; j<5; ++j)
				tmp[j] = Integer.parseInt(st.nextToken());
			
			order[i] = tmp[0];	// 순서 저장
			for(int j=1; j<5; ++j)
				list[tmp[0]].add(tmp[j]);
		}
			
		// 앉을 자리를 찾는다.
		for(int i=0; i<N*N; ++i) 
			searchArea(order[i]);
		
		// 점수 계산
		ret = calcScore();
			
		System.out.println(ret);
	}

	private static int calcScore() {
		int sum = 0;
		
		// 모든 좌석 검사
		for(int i=0; i<N; ++i) {
			for(int j=0; j<N; ++j) {
			
				int like = 0;
				// 인접 4방향 검사
				for(int d=0; d<4; ++d) {
					int nr = i+dr[d];
					int nc = j+dc[d];
					
					if(!isIn(nr, nc) ) continue;
					
					// 다음 좌표의 학생 번호
					int next = room[nr][nc];
					
					// 인접한 좋아하는 학생 수
					if(list[room[i][j]].indexOf(next) != -1) like++;
				}
				if(like ==1) sum += 1;
				else if(like ==2) sum += 10;
				else if(like ==3) sum += 100;
				else if(like ==4) sum += 1000;
			}
		}
		return sum;
	}

	private static void searchArea(int num) {
		
		// 좌석 후보
		List<Student> cand = new ArrayList<>();
		
		boolean visited[][] = new boolean[N][N];
		
		// 모든 좌석 검사
		for(int i=0; i<N; ++i) {
			for(int j=0; j<N; ++j) {
				// 이미 사람이 있으면 패스
				if(room[i][j] !=0 ) continue;
				
				int like = 0;
				int space = 0;
				// 인접 4방향 검사
				for(int d=0; d<4; ++d) {
					int nr = i+dr[d];
					int nc = j+dc[d];
					
					if(!isIn(nr, nc) ) continue;
					
					// 다음 좌표의 학생 번호
					int next = room[nr][nc];
					
					// 빈칸 개수
					if(next == 0) space++;
					// 인접한 좋아하는 학생 수
					if(list[num].indexOf(next) != -1) like++;
					
				}
				// 후보 좌표 저장
				cand.add(new Student(like, space, i, j));
			}
		}
		
		// 정렬 후 만족하는 좌표에 앉는다.
		Collections.sort(cand);
		room[cand.get(0).r][cand.get(0).c] = num;
		
	}

	private static boolean isIn(int r, int c) {
		return 0<=r && r<N && 0<=c && c<N;
	}

}
