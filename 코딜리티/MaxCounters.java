/*
코딜리티라는 알고리즘 사이트를 처음 접했다.
문제가 영어라서 해석해야 하나 싶지만 번역해서 최대한 빨리 이해하는게 좋은 것 같다.
난이도가 미디움인 문제를 풀어봤다.

크기가 N인 카운터가 있고 A 배열에 숫자가 있다.
A[i]에 적힌 숫자의 카운터를 1씩 증가시키고, 만약 A[i]=N+1인 경우 현재 배열의 카운터 값 중 최대값으로 모든 배열의 숫자를 최대값으로 통일한다.

문제 이해에 10분정도 쓴것 같다.
어쨌든 처음 풀이는 시간복잡도를 생각하지 않고 N+1이 나올 때마다 배열을 최대로 갱신하니 N^2이 나와 시간초과가 났다.

매번 배열을 최대로 갱신하는 것이 아니라 최대값을 저장한 후 그 최대값에 따라 배열을 조정해야하는 것 같았는데 생각이 잘 안났다.
풀이를 참고해보니 N+1이 나올 때 현재 최대값을 prevMax에 따로 저장한 후, 다시 카운터를 증가시킬때 값이 prevMax보다 작으면 prevMax+1을 저장하고 크거나 같으면 1 증가한다.
그리고 max값을 계속 갱신하고 가장 마지막에 prevMax보다 작은 원소를 prevMax로 만들어주면 된다.

아이디어가 중요한 문제인 것 같은데 코테를 너무 손놓고 있던 것 같긴 하다.
하루에 한문제라도 풀면서 감각을 잃지 않도록 해야겠다.
*/


// you can also use imports, for example:
 import java.util.*;

// you can write to stdout for debugging purposes, e.g.
// System.out.println("this is a debug message");

class Solution {
    public int[] solution(int N, int[] A) {
        // write your code in Java SE 8
        int[] counter = new int[N];
		int max = 0;
		int prevMax = 0;	// N+1 값이 나올때의 최대값
		for(int i=0; i<A.length; ++i) {
			if(A[i] == N+1) {
				prevMax = max;
			}
			else {
                // N+1이 나왔을때의 최대값보다 작다면 N+1이 나왔을떄의 최대값+1을 저장
				if(counter[A[i]-1] < prevMax)
					counter[A[i]-1] = prevMax+1;
				else    // 그게 아니라면 그냥 1 증가
					counter[A[i]-1]++;
				
				max = Math.max(max, counter[A[i]-1]);   // 최대값 갱신
			}
		}
		// prevMax보다 작은 값이 있으면 새로 갱신
		for(int i=0; i<N; ++i)
			if(counter[i] < prevMax)
				counter[i] = prevMax;
        return counter;
    }
}