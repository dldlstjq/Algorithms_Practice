/*
단어 첫 글자가 크로아티아 알파벳 후보일때 뒤에 나오는 문자를 검사해서 알아낸다.
문제는 인덱스가 string 범위를 벗어날때가 있는데 이 조건을 고려하지 않으면
StringIndexOutOfBounds 에러가 난다.
*/


import java.io.*;
import java.util.StringTokenizer;

public class Main {
	public static void main(String[] args) throws IOException {
		// TODO Auto-generated method stub

		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine(), " ");
		
		String str = st.nextToken();
		
		int ret = 0;
		for(int i=0; i<str.length(); ++i) {
			if(i< str.length()-1 && str.charAt(i) == 'c') {
				if(str.charAt(i+1)== '=' || str.charAt(i+1)== '-') {
					ret++;
					i++;
				}
				else
					ret++;
			}
			
			else if(str.charAt(i) == 'd') {
				if(i< str.length()-1 && str.charAt(i+1)== '-') {
					ret++;
					i++;
				}
				else if(i< str.length()-2 && str.charAt(i+1)== 'z' && str.charAt(i+2)== '=') {
					ret++;
					i+=2;
				}
				else
					ret++;
			}
			
			else if(i< str.length()-1 && str.charAt(i) == 'l') {
				if(str.charAt(i+1)== 'j') {
					ret++;
					i++;
					continue;
				}
				ret++;
			}
			else if(i< str.length()-1 && str.charAt(i) == 'n') {
				if(str.charAt(i+1)== 'j') {
					ret++;
					i++;
					continue;
				}
				ret++;
			}
			else if(i< str.length()-1 && str.charAt(i) == 's') {
				if(str.charAt(i+1)== '=') {
					ret++;
					i++;
					continue;
				}
				ret++;
			}
			else if(i< str.length()-1 && str.charAt(i) == 'z') {
				if(str.charAt(i+1)== '=') {
					ret++;
					i++;
					continue;
				}
				ret++;
			}
			else
				ret++;
		}
		System.out.println(ret);
	}
}