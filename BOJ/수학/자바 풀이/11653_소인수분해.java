/*
이 문제도 에라토스테네스의 체를 이용하면 쉽게 풀 수 있다.
미리 소인수를 다 저장해 놓고 N을 나눠가면서 소인수를 저장하면 된다.
알고보면 쉽지만 막상 오래 지나서 다시 풀어보라하면 에라토스테네스 체를 안쓰고 노가다를 해서 하기 때문에 자주 보는게 좋을 것 같다.
*/

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Arrays;

public class Main {
	
	final static int MAX= 10000000+1;
	static int factor[] = new int[MAX];
	static int N;
	
	static void eratosthenes2() {
		factor[0] = factor[1] = -1;
		for(int i=2; i<=N; ++i)
			factor[i] = i;
		
		for(int i=2; i<= (int)Math.sqrt(N); ++i) {
			if(factor[i] == i) {
				for(int j=i*i; j<=N; j+=i)
					if(factor[j] == j)
						factor[j] = i;
			}
		}
	}

	public static void main(String[] args) throws Exception {
		
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		
		N = Integer.parseInt(br.readLine());
		
		eratosthenes2();
		
		ArrayList<Integer> list = new ArrayList<Integer>();
		
		while(N > 1) {
			list.add(factor[N]);
			N /= factor[N];
		}
		
		for(int num: list)
			System.out.println(num);
	}

}