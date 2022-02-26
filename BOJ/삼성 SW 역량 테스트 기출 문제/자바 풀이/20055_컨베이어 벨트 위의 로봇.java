/*
풀이 자체는 어렵지 않고 문제 이해를 얼마나 완벽하게 했냐가 관건인 것 같다.
컨베이어 벨트 길이는 전체 2N이 감싸고 있고 1에서 로봇을 올리고 N에서 로봇을 내린다.

로봇을 옮기는 과정을 그대로 수행하면 되는데
벨트가 회전하거나 로봇이 이동할 때 N에서 로봇이 있다면 무조건 로봇을 내려야 한다.
그리고 로봇이 이동할 때는 가장 먼저 올라간 로봇부터 이동해야한다.
그러므로 i를 N-2부터 0으로 거꾸로 수행해야 맞다.  (N-1은 로봇을 내리는 곳이기 때문에 N-2부터 수행하면 된다)
처음에 0부터 시작했다가 제대로 된 답이 안나왔다.

벨트가 한칸씩 이동할때도 이동 시킨 다음에 위치가 N-1인 곳은 로봇을 내려주도록 잘 잡아야 한다.
*/

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.List;
import java.util.StringTokenizer;

public class Main {
	
	static class Robot{
		int num; boolean robot;
		Robot(int num, boolean robot){
			this.num=num;
			this.robot=robot;
		}
	}
	static int N, K;
	static Robot[] A;
	static int step;
	
	public static void main(String[] args) throws Exception {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st= new StringTokenizer(br.readLine());
		
		N = Integer.parseInt(st.nextToken());
		K = Integer.parseInt(st.nextToken());
		
		A = new Robot[N*2];
		
		st= new StringTokenizer(br.readLine());
		for(int i=0; i<N*2; ++i) {
			A[i] = new Robot(0, false);
			A[i].num = Integer.parseInt(st.nextToken());
		}
			
		step = 1;
		while(true) {
			rotate();
			moveRobot();
			robotUp();
			
			if(check() >= K) break;
			step++;
		}
		System.out.println(step);
				
	}

	private static int check() {
		int durability = 0;
		for(int i=0; i<2*N; ++i)
			if(A[i].num <= 0) durability++;
		return durability;
	}

	private static void robotUp() {
		if(A[0].num > 0) {
			A[0].robot = true;
			A[0].num--;
		}
	}

	private static void moveRobot() {
		// 가장 먼저 벨트에 올라간 로봇부터 이동
		for(int i=N-1; i>=0; --i) {
			// 로봇이 없으면 패스
			if(!A[i].robot) continue;
			
			// 이동하려는 칸에 로봇이 없고 내구도 1이상인 경우만 이동
			if(!A[i+1].robot && A[i+1].num >= 1) {
				A[i].robot = false;
				A[i+1].robot = true;
				A[i+1].num--;
			}
		}
		
		// 내리는 위치에 로봇이 있으면 즉시 내린다
		if(A[N-1].robot) A[N-1].robot = false;
	}

	private static void rotate() {
		// 벨트 한 칸 회전
		Robot tmp = A[2*N-1];
		for(int i=2*N-2; i>=0; --i) {
			
			A[i+1] = A[i];
			
			// 옮기고 나서 N-1번째에 오면 로봇을 내림
			if(i+1 == N-1 && A[i+1].robot)
				A[i+1].robot = false;
		}
		A[0] = tmp;
		
	}
}