/*
정렬하면 아마 시간초과가 날거고 포인터 2개를 이용해 하나씩 접근하며 크기를 비교해 작은 것부터 새로운 배열에 넣는다.
만약 두 배열 중 하나의 포인터가 끝에 다다르면 아직 남은 배열의 나머지를 최종적으로 다 넣어준다.
여기서 입력은 BufferedReader를 사용해야하고 출력은 StringBuilder, BufferedWriter 둘 중에 하나를 써야 시간초과가 안 나는 것 같다.
*/

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.Arrays;
import java.util.StringTokenizer;


public class Main {
	
	
	
	public static void main(String[] args) throws Exception {
		//System.setIn(new FileInputStream("input.txt"));
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine());
		
		int N = Integer.parseInt(st.nextToken());
		int M = Integer.parseInt(st.nextToken());
		
		int arr1[] = new int[N];
		int arr2[] = new int[M];
		st = new StringTokenizer(br.readLine());
		for(int i=0; i<N; ++i)
			arr1[i] = Integer.parseInt(st.nextToken());
		
		st = new StringTokenizer(br.readLine());
		for(int i=0; i<M; ++i)
			arr2[i] = Integer.parseInt(st.nextToken());
			
		int ans[] = new int[N+M];
		
		
		int idx1 =0, idx2=0;
		int k=0;
		
		while(idx1 < N && idx2 < M) {
			if(arr1[idx1]>= arr2[idx2])
				ans[k++] = arr2[idx2++];
			else
				ans[k++] = arr1[idx1++];
		}
		
		while(idx1 < N) ans[k++] = arr1[idx1++];
		while(idx2 < M) ans[k++] = arr2[idx2++];
	
		StringBuilder sb = new StringBuilder();
		for(int i=0; i<N+M; ++i)
			sb.append(ans[i]).append(' ');

		System.out.println(sb);
	}

}
