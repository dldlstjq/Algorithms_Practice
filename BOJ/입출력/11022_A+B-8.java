// 입출력 연습을 위해 풀어봤다. scanner 사용과 br, bw 사용 둘 다 잘 익혀놔야겠다.

import java.io.*;
import java.util.Scanner;
import java.util.StringTokenizer;

public class Main {
	public static void main(String[] args) throws IOException {
		// TODO Auto-generated method stub
		
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
		
		int t = Integer.parseInt(br.readLine());
 
		for (int i = 1; i <= t; i++) {
			StringTokenizer st = new StringTokenizer(br.readLine()," ");
			bw.write("Case #"+i+": ");
			int a= Integer.parseInt(st.nextToken());
			int b= Integer.parseInt(st.nextToken());
			bw.write(a+" + "+b+" = " );
			bw.write(a+b+"\n");
		}
		br.close();
		bw.flush();
		bw.close();
	}

}