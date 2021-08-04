/*
첫 오답은 런타임 에러였다.
대칭을 확인할 때 배열 범위를 벗어나는지 먼저 확인했어야 했는데 그러질 못했다.
두번째는 출력형식 에러였다. 
아무리 봐도 출력이 잘못될게 없었는데 20개까지 출력후 한 줄 띄워야 했다...
문제를 잘 읽는것이 얼마나 중요한지 다시 느낄 수 있었다.
*/

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

public class Main {
	
	static int N, S;
	static int arr[];
	
	static void check_switch(int gender, int num) {
		if(gender==1) {
			// 배수만큼 스위치 조작
			for(int i=num; i<=N; i+=num) 
				arr[i] ^= 1;
		}
		
		else {
			arr[num] ^= 1;	// 먼저 현재 스위치 바꾼다
			int i;
			for(i=1;i<=N; ++i) {
				// 좌우 대칭이 아니거나 범위 벗어나면 브레이크
				if(num-i<1 || num+i>N || arr[num-i] != arr[num+i])
					break;
				arr[num-i] ^= 1;
				arr[num+i] ^= 1;
			}
		}
	}

	public static void main(String[] args) throws Exception {
		// TODO Auto-generated method stub
		
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine(), " ");
		
		
		N= Integer.parseInt(st.nextToken());
		arr =  new int[N+1];
		
		st = new StringTokenizer(br.readLine(), " ");
		for(int i=1; i<=N;++i)
			arr[i] = Integer.parseInt(st.nextToken());
		
		S= Integer.parseInt(br.readLine());
		
		for(int i=0; i<S;++i) {
			st = new StringTokenizer(br.readLine(), " ");
			int gender = Integer.parseInt(st.nextToken());
			int num = Integer.parseInt(st.nextToken());
			check_switch(gender, num);
		}

		for(int i=1; i<=N; ++i) {
			if(i%20 == 0)
				System.out.printf("%d\n", arr[i]);
			else
				System.out.printf("%d ", arr[i]);
		}
	}

}