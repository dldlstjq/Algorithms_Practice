import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

public class Z_비트 {
	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine(), " ");
		int N = Integer.parseInt(st.nextToken()); // 1 ≤ N ≤ 15
		int r = Integer.parseInt(st.nextToken()); // 0 ≤ r, c < 2^N
		int c = Integer.parseInt(st.nextToken());
		int answer = 0;

		for (int i = N - 1; i >= 0; i--) {
			answer <<= 2; // 자리수 올리기
			answer |= ((r & (1 << i)) != 0 ? 1 : 0) << 1 | ((c & (1 << i)) != 0 ? 1 : 0); // 자리수 추출해서 추가
		}
		
		System.out.println(answer);
	}
}