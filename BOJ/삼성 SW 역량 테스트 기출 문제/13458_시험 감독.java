/*
알고리즘 자체는 쉽다.
다만 결과값이 long 형이 나올 수 있기 때문에 이 부분을 고려해야 한다.
*/

import java.io.*;
import java.util.StringTokenizer;

public class Main {

	final static int MAX = 1000000+1;
	static int [] A = new int[MAX];
	public static void main(String[] args) throws IOException {
		// TODO Auto-generated method stub

		BufferedReader bf = new BufferedReader(new InputStreamReader(System.in));
		
		int B=0, C=0;
		int N = Integer.parseInt(bf.readLine());
		long ret = 0;
		
		StringTokenizer st = new StringTokenizer(bf.readLine(), " ");
		for(int i=0; i<N; ++i) {
			A[i] = Integer.parseInt(st.nextToken());
		}
		st = new StringTokenizer(bf.readLine(), " ");
		B = Integer.parseInt(st.nextToken());
		C = Integer.parseInt(st.nextToken());
		
		for(int i=0; i<N; ++i) {
			// 총감독관 감시 수만큼 감소
			A[i] -= B;
			ret++;	// 총감독관은 무조건 1명 필요
			// 총감독관만으로 감시 충분
			if(A[i]<=0)
				continue;
			// 부감독관이랑 나눴을 때 나머지가 0이면 몫만큼 감독관 필요
			// 나눠지지 않으면 남은 나머지 만큼 감시할 감독관 수 1명 더 필요
			if(A[i]%C == 0)
				ret += A[i]/C;
			else
				ret += A[i]/C+1;
		}
		System.out.println(ret);
	}
}
