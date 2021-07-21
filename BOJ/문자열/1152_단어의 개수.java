/*
stringtoken으로 잘라 그 개수를 반환하면 끝이다.
hashmap을 사용해서 풀려고 했는데 readLine에서 어디까지 읽고 끊어야하는지를 몰라
잘 안됐다. hashmap으로도 더 생각해봐야겠다.
*/

import java.io.*;
import java.util.StringTokenizer;

public class Main {
	public static void main(String[] args) throws IOException {
		// TODO Auto-generated method stub

		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine(), " ");
		System.out.println(st.countTokens());
	}
}