// BufferedReader, BufferedWriter 사용
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.StringTokenizer;
import java.io.IOException;
import java.io.BufferedWriter;
import java.io.OutputStreamWriter;
 
public class Main {
	public static void main(String args[]) throws IOException {
 
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
		
		int a = Integer.parseInt(br.readLine());
 
		StringTokenizer st;
		for (int i = 1; i <= a; i++) {
			st = new StringTokenizer(br.readLine()," ");
			bw.write("Case #"+i+": ");
			bw.write(Integer.parseInt(st.nextToken())
				+Integer.parseInt(st.nextToken())+"\n");
		}
		br.close();
		bw.flush();
		bw.close();
	}
 
}


////////////////////////////////////////////
// scanner 사용
import java.io.*;
import java.util.Scanner;
import java.util.StringTokenizer;

public class Main {
	public static void main(String[] args) throws IOException {
		// TODO Auto-generated method stub
		
	    Scanner sc = new Scanner(System.in);
	    int t = sc.nextInt();
	    
	    for(int i=0; i<t; ++i) {
	    	int A = sc.nextInt();
	    	int B = sc.nextInt();
	    	
	    	System.out.printf("Case #%d: %d\n", i+1, A+B);
	    }

	}

}
