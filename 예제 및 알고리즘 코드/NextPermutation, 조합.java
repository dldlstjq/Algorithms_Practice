/*
C++에서는 next_permutation 함수가 존재하지만 자바는 없어서 직접 만들어야 한다.
다른 블로그 등에 np 원리가 나와있었는데 막연히 보기만 하니까 이해가 잘 안갔었다.
직접 강의를 들으면서 해보니 이해가 잘 갔고 원리만 잘 이해하면 쉽게 구현할 수 있을 것 같다.
조합 역시 np함수를 이용하면 쉽게 할 수 있다.
일반 재귀 순열보다 시간은 더 빠른 것 같다.

순열에서 주의할 건 하기 전에 무조건 오름차순 정렬을 해줘야 한다.
*/

package com.ssafy.p;

import java.util.Arrays;

// N개 서로 다른 수에서 뽑는 수열
public class NextPermutationTest {
	

	public static void main(String[] args) {

		int []input = {7,1,4};
		Arrays.sort(input);	// 가장 작은 순열 만들기 1, 4, 7
		
		// 현재 순열의 상태를 한 번 사용하기 위해 do while 사용
		// do로 먼저 순열을 수행하고 그 다음 순열이 있으면 사용하는 형태
		do {
			// 순열 사용
			System.out.println(Arrays.toString(input));
			
			
		}while(np(input));
	}
	
	// 다음 큰 순열이 있으면 true, 없으면 false
	private static boolean np(int[] numbers) {
		
		int N = numbers.length;
		
		// step1. 꼭대기를 찾는다. 꼭대기를 통해 교환위치 찾기
		int i= N-1;
		while(i>0 && numbers[i-1] >= numbers[i]) --i;
		
		// 맨 앞이 제일 큰 수이면 더 이상 순열이 없다. 종료
		if(i == 0) return false;
		
		// step2. i-1 위치값과 교환할 큰 값 찾기
		int j = N-1;
		while(numbers[i-1] >= numbers[j]) --j;
		
		// step3. i-1 위치값과 j위치 값 교환
		swap(numbers, i-1, j);
		
		// step4. 꼭대기(i)부터 맨 뒤까지 내림차순 형태의 순열을 오름차순으로 처리
		int k = N-1;
		while( i < k) {
			swap(numbers, i++, k--);
		}
		
		return true;
	}

	private static void swap(int[] numbers, int i, int j) {
		int temp = numbers[i];
		numbers[i] = numbers[j];
		numbers[j] = temp;
	}

}



// N개 서로 다른 수에서 R개 뽑는 조합
public class CombNextPermutationTest {
	public static void main(String[] args) {

		int []input = {7,1,4,2,3};
		
		int N = input.length;
		int R = 4;
		
		int [] p = new int[N];
		
		// 뒤쪽부터 R개만큼 1채우기
		int cnt = 0;
		while(++cnt<=R) p[N-cnt] = 1;
		
	
		do {
			// 조합 사용
			for(int i=0; i<N; ++i) {
				if(p[i] == 1) System.out.print(input[i] + " ");
			}
			System.out.println();
			
		}while(np(p));
	}
	
	// 다음 큰 순열이 있으면 true, 없으면 false
	private static boolean np(int[] numbers) {
		
		int N = numbers.length;
		
		// step1. 꼭대기를 찾는다. 꼭대기를 통해 교환위치 찾기
		int i= N-1;
		while(i>0 && numbers[i-1] >= numbers[i]) --i;
		
		// 맨 앞이 제일 큰 수이면 더 이상 순열이 없다. 종료
		if(i == 0) return false;
		
		// step2. i-1 위치값과 교환할 큰 값 찾기
		int j = N-1;
		while(numbers[i-1] >= numbers[j]) --j;
		
		// step3. i-1 위치값과 j위치 값 교환
		swap(numbers, i-1, j);
		
		// step4. 꼭대기(i)부터 맨 뒤까지 내림차순 형태의 순열을 오름차순으로 처리
		int k = N-1;
		while( i < k) {
			swap(numbers, i++, k--);
		}
		
		return true;
	}

	private static void swap(int[] numbers, int i, int j) {
		int temp = numbers[i];
		numbers[i] = numbers[j];
		numbers[j] = temp;
		
	}
}