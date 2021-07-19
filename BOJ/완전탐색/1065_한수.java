/*
함수를 만들어서 각 자리가 등차수열인지 확인했다.
*/
import java.io.*;

public class Main {

	public static void main(String[] args) throws IOException {
		// TODO Auto-generated method stub

		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		
		int N = Integer.parseInt(br.readLine());
		
		int cnt=0;
		for(int i=1; i<=N; ++i) {
			if(hansu(i))
				cnt++;
		}
		System.out.println(cnt);
	}
	
	public static boolean hansu(int n) {
        // 100 미만은 등차수열 ok
		if(n<100)
			return true;
		
        // 비교를 쉽게 하기 위해 string으로 변환
		String s = Integer.toString(n);
		int diff = s.charAt(1) - s.charAt(0) - '0';
		for(int i=2; i<s.length(); ++i) {
            // 차이가 다르면 false.
			if(diff != s.charAt(i) - s.charAt(i-1) - '0')
				return false;
		}
		return true;
	}
}