/*
3~4시간 걸려 해결한 것 같다.
첫 접근은 2차원 배열에 어레이리스트를 적용하여 직접 다 충전 정보를 저장하려 했디.
그러다 보니 2차원 배열 어레이리스트 사용이 처음이라 초기화도 잘 몰랐고 설정도 잘못해서 값이 잘 안들어갔다.

두번째로 생각한 것이 BC 중심과 현재 위치를 일일이 다 확인하는 것이었다.
사용자가 2명밖에 없고 BC도 최대 10개라서 시간내에 가능할 것 같았다.
범위 내에 들어오는 충전기를 리스트에 삽입하고 충전량 내림차순으로 정렬하여 최대 크기를 구하도록 했다.
5개 케이스 중 2개는 잘 나오는데 3개가 조금씩만 다 틀려서 대체 어디가 문제인지 몇시간을 고민해도 답이 안나왔다.
교수님 풀이를 보면서 먼저 이동을 한 후에 검사를 해야 하는데 나는 먼저 검사를 하고 이동해서 제대로 된 답이 안나왔다.
*/

// 내 풀이
import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Collections;
import java.util.StringTokenizer;

public class Solution {
	// BC 정보 저장
	static class Charger{
		int x,y,range,power;
		
		public Charger(int x, int y, int range, int power) {
			this.x = x;
			this.y = y;
			this.range = range;
			this.power = power;
		}
	}
	// 사용자가 사용할 수 있는 BC
	static class BC implements Comparable<BC>{
		int num, power;

		public BC(int num, int power) {
			super();
			this.num = num;
			this.power = power;
		}
		
		@Override
		public int compareTo(BC o) {
			return o.power-this.power;
		}
	}
	
	static int M, A;	// 총 이동시간, BC의 개수
	static int userA[], userB[];	// 사용자 이동 방향
	static Charger[] battery;	// BC 정보 저장
	
	static int dx[] = {0,0,1,0,-1};
	static int dy[] = {0,-1,0,1,0};
	
	static int maxPower;	// 최종 충전량
	
	public static void main(String[] args) throws Exception{
		//System.setIn(new FileInputStream("sample_input.txt"));
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		
		int T = Integer.parseInt(br.readLine());
		
		for(int test_case = 1; test_case <= T; test_case++)
		{
			maxPower = 0;	// 최대 충전량 초기화
			
			StringTokenizer st = new StringTokenizer(br.readLine(), " ");
			M = Integer.parseInt(st.nextToken());
			A = Integer.parseInt(st.nextToken());
			
			userA = new int[M+1];
			userB = new int[M+1];
			battery = new Charger[A];
			
			// 사용자A 이동 정보
			st = new StringTokenizer(br.readLine(), " ");
			for(int i=1; i<=M; ++i)
				userA[i] = Integer.parseInt(st.nextToken());
			// 사용자B 이동 정보
			st = new StringTokenizer(br.readLine(), " ");
			for(int i=1; i<=M; ++i)
				userB[i] = Integer.parseInt(st.nextToken());
			
			//AP 정보
			for(int i=0; i<A; ++i) {
				st = new StringTokenizer(br.readLine(), " ");
				int x = Integer.parseInt(st.nextToken());
				int y = Integer.parseInt(st.nextToken());
				int C = Integer.parseInt(st.nextToken());
				int P = Integer.parseInt(st.nextToken());
				
				battery[i] = new Charger(x, y, C, P);
			}
			
			check();
			
			StringBuilder sb = new StringBuilder();
			sb.append("#"+test_case+" ").append(maxPower);
			System.out.println(sb);
		}
	}
	
	 
	private static void check() {
		int r1 =1, c1=1;	// 사용자 A의 최초 지점
		int r2 =10, c2=10;	// 사용자 B의 최초 지점
		
		// 0초부터 이동시간 만큼 반복
		for(int i=0; i<=M; ++i) {
			// 사용자 이동
			r1 += dy[userA[i]];
			c1 += dx[userA[i]];
			r2 += dy[userB[i]];
			c2 += dx[userB[i]];
			
			ArrayList<BC> charge1 = new ArrayList<>();
			ArrayList<BC> charge2 = new ArrayList<>();
			
			// A,B 좌표와 BC 위치 거리를 구해서 충전범위 이하이면 charge에 추가
			for(int j=0; j<battery.length; ++j) {
				int dist1 = Math.abs(r1-battery[j].y) + Math.abs(c1-battery[j].x);
				int dist2 = Math.abs(r2-battery[j].y) + Math.abs(c2-battery[j].x);
				if(dist1 <= battery[j].range)
					charge1.add(new BC(j, battery[j].power));
				if(dist2 <= battery[j].range)
					charge2.add(new BC(j, battery[j].power));
			}
			
			// 충전량이 큰 것이 오도록 내림차순 정렬
			Collections.sort(charge1);
			Collections.sort(charge2);
			
			int tmp = 0;
			// 둘 다 충전할 수 있는 경우
			if(!charge1.isEmpty() && !charge2.isEmpty()) {
				// BC가 다르면 서로 충전
				if(charge1.get(0).num != charge2.get(0).num) {
					maxPower += charge1.get(0).power;
					maxPower += charge2.get(0).power;
				}
				
				else {
					// 최대 충전량 가진 BC가 같다
					// 1. 둘 다 같은 BC 하나밖에 없다. 하나만 사용
					if(charge1.size() == 1 && charge2.size() == 1) {
						maxPower += charge1.get(0).power;
					}
					// 2. 한쪽은 하나만 있는데 다른 쪽은 두 개 이상 있을 경우
					else if(charge1.size() == 1 && charge2.size()>=2) {
						maxPower += charge1.get(0).power;
						maxPower += charge2.get(1).power;
					}
					else if(charge2.size() == 1 && charge1.size() >= 2) {
						maxPower += charge1.get(1).power;
						maxPower += charge2.get(0).power;
					}
					
					// 3. 둘 다 두개 이상 있는 경우
					// 서로 여러개의 충전소가 있다면 두번째 충전소가 더 큰 것을 충전
					else {
						int p = charge1.get(0).power;
						p = Math.max(p, charge1.get(0).power + charge2.get(1).power);
						p = Math.max(p, charge1.get(1).power + charge2.get(0).power);
						maxPower += p;
					}
					
				}
			}
			
			// 사용자 A만 충전 가능
			else if(!charge1.isEmpty() && charge2.isEmpty()) {
				maxPower += charge1.get(0).power;
			}
			// 사용자 B만 충전 가능
			else if(charge1.isEmpty() && !charge2.isEmpty()) {
				maxPower += charge2.get(0).power;
			}
			
		}
	}
}


// 교수님 풀이
import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

public class Solution_5644_무선충전_sol {

	
	// 상 우 하 좌
	final static int[] dx = {0,  0, 1, 0, -1};
	final static int[] dy = {0, -1, 0, 1, 0};
	
	static BC[] bc;	//무선 충전기 정보
	
	static User userA;	//사용자 A
	static User userB;	//사용자 B
	
	static int M, A;	//이동정보 개수, 배터리 개수
	
	static int amount;	//총 충전량
	
	static class BC{
		int x, y, C, P; //좌표, 범위, 성능
		public BC(int x, int y, int C, int P) {
			this.x = x;
			this.y = y;
			this.C = C;
			this.P = P;
		}
		//해당 배터리의 범위내에 사용자가 있는지 여부 반환
		public boolean isInArea(User u) {
			int dis = Math.abs(this.x - u.x) + Math.abs(this.y - u.y);
			if( C >= dis ) return true;
			return false;
		}
		
	}
	
	static class User{
		int x,y;	//좌표
		public User(int x, int y) {
			this.x = x;
			this.y = y;
		}
		//사용자 이동 메소드
		public void move(int dir) {
			this.x += dx[dir];
			this.y += dy[dir];
		}
	}
	
	public static void main(String[] args) throws IOException {
		System.setIn(new FileInputStream("input.txt"));
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = null;
		
		int T = Integer.parseInt(br.readLine());
		for(int tc=1; tc<=T; tc++) {
			
			st = new StringTokenizer(br.readLine());
			M = Integer.parseInt(st.nextToken());
			A = Integer.parseInt(st.nextToken());
			
			//A, B이동 정보 입력
			int[] moveA = new int[M+1];
			int[] moveB = new int[M+1];
			st = new StringTokenizer(br.readLine());
			for(int i=1; i<=M; i++) moveA[i] = Integer.parseInt(st.nextToken());
			st = new StringTokenizer(br.readLine());
			for(int i=1; i<=M; i++) moveB[i] = Integer.parseInt(st.nextToken());
			
			//무선충전기 정보 입력
			bc = new BC[A];
			for(int i=0; i<A;i++) {
				st = new StringTokenizer(br.readLine());
				int x = Integer.parseInt(st.nextToken());
				int y= Integer.parseInt(st.nextToken());
				int C= Integer.parseInt(st.nextToken());
				int P= Integer.parseInt(st.nextToken());
				bc[i] = new BC(x, y, C,P);
			}
			
			//유저 생성
			userA = new User(1,1);
			userB = new User(10, 10);
			
			
			amount = 0;	//총 충전량 초기화
			
			//이동정보만큼 반복
			for(int i=0; i<=M; i++) {
				//이동
				userA.move( moveA[i] );
				userB.move(  moveB[i]);
				
				//현재 최대 충전량 구해서 전체 충전량에 +
				amount += getCurPower();
				
			}
			
			System.out.println("#"+tc+" "+amount);
			
		}
	}
	//현재 얻을 수 있는 최대 파워 반환
	private static int getCurPower() {
		//현재 초의 충전량의 최댓값 저장
		int max = 0;
		
		//배터리 A개에서 2개 뽑는 중복순열
		for(int i=0; i<A; i++) {
			for(int j=0; j<A; j++) {
				boolean checkA = bc[i].isInArea(userA);	//사용자 A의 해당배터리 충전 가능 여부
				boolean checkB = bc[j].isInArea(userB);	//사용자 B의 해당배터리 충전 가능 여부
				
				//선택된 무선충전기 충전량 구하기
				int sum =0;
				
				//같은 충전기이고 둘다 범위 내에 있는 경우
				if( i == j && checkA && checkB) {
					sum += bc[i].P;
				}
				//그 외에
				else {
					if(checkA) sum+= bc[i].P;
					if(checkB) sum+= bc[j].P;
				}
				
				//최댓값 비교
				max = Math.max(max, sum);
			}
		}
		
		return max;
	}

}

