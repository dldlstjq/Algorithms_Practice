/*
말 그대로 재귀함수를 연습할 수 있는 문제인 것 같다.
처음엔 마침표나 큰따옴표 등 출력형식을 못 맞춰서 오답을 많이 받았다.
처음 푼 풀이는 반복되는 문장이 많았는데 최적화 시켜 최소한의 코드만 나올 수 있도록 했다.
StringBuilder 쓰는 연습을 계속 해야겠다.
*/

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class Main{
	
	static int N;
	static StringBuilder sb = new StringBuilder();
    
	static void recursive(int cnt, String line) {
		if(cnt == N) {
			sb.append(line).append("\"재귀함수가 뭔가요?\""+'\n');
			sb.append(line).append("\"재귀함수는 자기 자신을 호출하는 함수라네\""+'\n');
			sb.append(line).append("라고 답변하였지." + '\n');
			return;
		}
			
		
		sb.append(line).append("\"재귀함수가 뭔가요?\""+'\n');
		sb.append(line).append("\"잘 들어보게. 옛날옛날 한 산 꼭대기에 이세상 모든 지식을 통달한 선인이 있었어."+'\n');
		sb.append(line).append("마을 사람들은 모두 그 선인에게 수많은 질문을 했고, 모두 지혜롭게 대답해 주었지."+'\n');
		sb.append(line).append("그의 답은 대부분 옳았다고 하네. 그런데 어느 날, 그 선인에게 한 선비가 찾아와서 물었어.\""+'\n');
		recursive(cnt+1, line+"____");
		sb.append(line).append("라고 답변하였지." + '\n');
	}
	

	public static void main(String[] args) throws IOException {
		
		BufferedReader br=  new BufferedReader(new InputStreamReader(System.in));
		
		N = Integer.parseInt(br.readLine());
        sb.append("어느 한 컴퓨터공학과 학생이 유명한 교수님을 찾아가 물었다."+'\n');
		recursive(0, "");
		System.out.println(sb);
	}
}