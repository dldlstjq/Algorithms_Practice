/*
제법 쉬운 문제이다.
N이 4의 배수이므로 N/4 만큼 반복하면서 N/4크기 만큼 잘라서 저장한다.
중복을 위해 Set을 이용했고 다 저장하면 다시 list를 돌면서 16진수 계산 후 내림차순 정렬해서 구했다.

 */

import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Collections;
import java.util.HashSet;
import java.util.List;
import java.util.Set;
import java.util.StringTokenizer;

public class Solution {

	static int N, K;
	static long ret;
	static String str;
	static List<String> list;
	static List<Long> num;
	static Set<String> set;

	static int alpha[] = {10,11,12,13,14,15};

	public static void main(String[] args) throws IOException {
		//System.setIn(new FileInputStream("sample_input.txt"));

		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		int T;
		T=Integer.parseInt(br.readLine());

		for(int test_case = 1; test_case <= T; test_case++)
		{

			StringTokenizer st = new StringTokenizer(br.readLine());
			N = Integer.parseInt(st.nextToken());
			K = Integer.parseInt(st.nextToken());

			str = br.readLine();
			set = new HashSet<>();
			list = new ArrayList<>();
			num = new ArrayList<>();

			ret=0;
			saveNum();
			calc();

			ret = num.get(K-1);

			StringBuilder sb = new StringBuilder();
			sb.append("#").append(test_case).append(" ").append(ret);
			System.out.println(sb);

		}

	}

	// 10진수 계산
	private static void calc() {
		for(String s: list) {
			int len = s.length()-1;
			long sum = 0;
			// 16진수 계산
			for(int i=0; i<s.length(); ++i) {
				int n= 0;
				if('0'<=s.charAt(i) && s.charAt(i) <='9')
					n = s.charAt(i)-'0';
				else if('A'<=s.charAt(i) && s.charAt(i) <='F')
					n = alpha[s.charAt(i)-'A'];

				sum += n*(int)Math.pow(16, len--);
			}
			num.add(sum);
		}
		// 내림차순 정렬
		Collections.sort(num, Collections.reverseOrder());
	}

	private static void saveNum() {
		// N/4 만큼 자르기
		for(int i=0; i<N/4; ++i) {
			for(int j=0; j<str.length(); j+=N/4) {
				String tmp = str.substring(j, j+N/4);
				if(set.isEmpty() || !set.contains(tmp)) {
					set.add(tmp);
					list.add(tmp);
				}
			}
			str = rotate();
		}
	}

	// 시계방향 회전
	private static String rotate() {
		char[] ch = str.toCharArray();
		char tmp = ch[ch.length-1];

		for(int i=ch.length-1; i>=1; --i)
			ch[i] = ch[i-1];
		ch[0] = tmp;

		String s ="";
		for(int i=0; i<ch.length; ++i)
			s+=ch[i];
		return s;
	}


}
