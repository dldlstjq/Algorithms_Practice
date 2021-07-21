/*
한번 나온 문자가 연속인지 아닌지 확인하는게 관건이다.
한번 나온 문자는 true로 걸어주고 이미 나온 문자라면 연속인지 확인하는 식으로 구현했다.
*/

import java.io.*;
import java.util.StringTokenizer;

public class Main {
	public static void main(String[] args) throws IOException {
		// TODO Auto-generated method stub

		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine(), " ");
		int N = Integer.parseInt(st.nextToken());
		
		int ret=0;
		for(int i=0; i<N; ++i) {
			st = new StringTokenizer(br.readLine(), " ");
			String str = st.nextToken();
			boolean[] alpha = new boolean[26];
			boolean flag = true;
			
			for(int j=0; j<str.length(); ++j) {
				// 나오지 않은 문자면 true
				if(!alpha[str.charAt(j)-'a'])
					alpha[str.charAt(j)-'a'] = true;
				else {
					// 이미 한번 나왔다면 연속해서 나왔는지 확인
					if(str.charAt(j-1) != str.charAt(j))
						flag = false;
				}
			}
			
			if(flag)
				ret++;
		}
		System.out.println(ret);
	}
}