/*
최대, 최소를 구해야 하기 때문에 처음에 정렬을 써서 풀었다.
하지만 매번 반복할때마다 정렬을 쓰는게 시간이 많이 걸릴것 같았는데
최대, 최소를 구하기 위해 계속 반복하는 것도 비슷한 것 같았다.
그냥 정렬써서 쉽게 풀이하자.
*/

import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

public class Main_1208_이인섭 {
	

	public static void main(String[] args) throws IOException {
		
		System.setIn(new FileInputStream("input.txt"));
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st;
		
		for(int test_case = 1; test_case <= 10; test_case++)
		{
			int ret = 0;	
			int dump = Integer.parseInt(br.readLine());	// 덤프 횟수
			int arr[] = new int [100];
			st = new StringTokenizer(br.readLine(), " ");
			
			for(int i=0; i<100; ++i) 
				arr[i] = Integer.parseInt(st.nextToken());
	
			int max = 0;
			int min = 101;
			int min_idx = 0, max_idx = 0;
			// 덤프 횟수만큼 반복
			for(int i=0; i<dump; ++i) {
				if(i!=0) {
					arr[max_idx]--;
					arr[min_idx]++;
					
				}
				max = 0;
				min = 101;
				
				for(int j=0; j<100; ++j) {
					if(max<arr[j]) {
						max = arr[j];
						max_idx = j;
					}
					if(min>arr[j]) {
						min = arr[j];
						min_idx = j;
					}
				}
				
				if(max-min<=1)
					break;
			}
		
			ret = max-min;

			StringBuilder sb = new StringBuilder();	// 정답 출력
			sb.append("#").append(test_case).append(" "+ret);
			System.out.println(sb.toString());
		}
	}

}
