/*
LIS를 일반 DP 방식이 아닌 이진탐색을 이용해 길이가 N일때 가장 마지막에 올 수 있는 수 중 가장 작은 수를 저장한다.
수가 중복되지 않을 때만 가능하고 중복되면 다른 방법을 이용해야 한다.
*/

import java.util.Arrays;
import java.util.Scanner;

public class DP2_LISTest2 {

	public static void main(String[] args) {
		Scanner sc=  new Scanner(System.in);
		int N = sc.nextInt();
		
		int[] arr = new int[N];	// 모든 원소의 값은 다르다.
		int[] LIS = new int[N];	// 해당 길이를 증가수열 중 맨 끝을 최소값으로 유지
		
		for(int i=0; i<N; ++i)
			arr[i] = sc.nextInt();
		
		
		int size = 0;	// LIS에 채워진 원소 수
		for(int i=0; i<N; ++i) {
			// 중복값이 없으므로 탐색 실패
			int temp = Math.abs(Arrays.binarySearch(LIS, 0, size, arr[i]))-1;
			LIS[temp] = arr[i];
			
			// temp와 size가 같다는 건 맨 뒤에 삽입이 됐다.
			// 추가된 위치가 맨 뒤라면 사이즈 증가
			if(temp == size) ++size;
		}
		System.out.println(size);
	}

}
