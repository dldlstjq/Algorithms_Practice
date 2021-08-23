/*
가지치기를 생각하지 않으면 쉽게 풀 수 없는 문제이다.
처음엔 그냥 왼쪽, 오른쪽을 하나씩 더하면서 풀었는데 시간초과를 받았다.
도저히 다른 케이스를 찾을 수 없었는데 남은 추를 모두 오른쪽에 올려도 왼쪽보다 작은 경우를 더 가지치기 해야 한다.
제일 이해가 안됐던게 추의 순서를 미리 구하는 순열을 만들고 나서 답을 구하면 시간초과를 받지 않는다.
이 부분이 너무 이해가 안됐는데 교수님께서 for문을 도는 횟수에 차이가 있다고 하셨다.
*/

import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

public class Solution_3234_준환이의양팔저울_가지치기 {

	static int N;	//추의 개수
	
	static int[] choo; //추 정보
	static boolean[] isSelected; //추 사용여부
	
	static int caseNum; //가능한 경우의 수
	
	public static void main(String[] args) throws IOException {
		System.setIn(new FileInputStream("input2.txt"));
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = null;
		
		int T = Integer.parseInt(br.readLine());
		
		for(int tc=1; tc<=T; tc++) {
			
			N = Integer.parseInt(br.readLine());
			
			//추 정보 입력
			choo = new int[N];
			st = new StringTokenizer(br.readLine());
			int total = 0;	//추의 전체 무게
			for(int i=0; i<N; i++) {
				choo[i] = Integer.parseInt(st.nextToken());
				total += choo[i];
			}
			
			isSelected = new boolean[N];
			
			caseNum=0; //가능한 경우의 수 초기화
			
			
			permutation(0, 0, 0 , total);
			
			System.out.println("#"+tc+" "+caseNum);
		}
	}

	private static void permutation(int cnt, int sumL, int sumR, int unusedSum) {
		
		//오른쪽 추의 무게 합이 왼쪽보다 클 경우 리턴
		if(sumL < sumR) return;
		//성공적으로 무게추 분배 완료
		else if(cnt == N) {
			caseNum++;
			return;
		}
		//현재상태에서 오른쪽무게와 남은 모든 추의 무게를 더한 값이 왼쪽무게보다 작거나 같다면?
		//실제 확인해보지 않아도 남은 추들을 어디에 놓든 가능한 경우(가지치기 가능)
		else if(sumL >= sumR+unusedSum )	{
			
			int unusedCnt = N-cnt; //남은 추의 개수
			//현재 남아있는 추들로 왼쪽 오른쪽에 놓을 수있는 경우의 수
			// (남은 추개수)! * 2^(남은 추개수)	
			caseNum += factorial(unusedCnt)*(1<<unusedCnt);
			return;
		}
		
		for(int i=0; i<N; i++) {
			if(isSelected[i]) continue;
			
			isSelected[i] = true;
			
			//왼쪽에 추 올리기
			permutation( cnt+1, sumL + choo[i], sumR, unusedSum - choo[i]);
			//오른쪽에 추 올리는 경우
			permutation( cnt+1, sumL, sumR + choo[i], unusedSum - choo[i]);
			
			isSelected[i] = false;
		}
		
	}
	
	private static int factorial(int n) {
		if(n==1) return 1;
		
		return n * factorial(n-1);
	}

}
