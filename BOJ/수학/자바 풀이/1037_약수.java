/*
1과 자기자신을 제외한 약수가 입력으로 들어오기 때문에 정렬하여 제일 큰 수와 작은 수를 곱해서 구했다.
*/

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.Arrays;
import java.util.StringTokenizer;


public class Main {
	
	
	public static void main(String[] args) throws Exception {
		
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		
		int N=0;
		
		N=Integer.parseInt(br.readLine());
		StringTokenizer st = new StringTokenizer(br.readLine(), " ");
		
		int arr[] = new int[N];
		for(int i=0; i<N; ++i) 
			arr[i]= Integer.parseInt(st.nextToken());
		
		Arrays.sort(arr);
		System.out.println(arr[0]*arr[arr.length-1]);
	}
}