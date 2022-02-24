/*
쉬운줄 알고 접근했다가 꽤나 애먹은 문제이다.
전체 사각형에서 빈 영역을 빼면 된다고 생각했는데 빈 영역을 어떻게 구하는 지가 관건이었다.
시작점이 어디인가에 따라 꺾이는 부분이 다르다는 것을 이용하여 전체 4가지로 구분했다.
1. 4 2 3 1 3 1 처럼 ㄱ자로 꺾이는 부분이 연속
2. 1 3 1 4 2 3 처럼 3번 연속 꺾이고 마지막에 꺾이는 부분이 들어오는 경우
3. 3 1 4 2 3 1 처럼 2번 연속 꺾이고 마지막에 두번 연속 꺾이는 경우
4. 1 4 2 3 1 3 처럼 마지막에 3번연속 꺾이는 경우

전체 4가지 경우를 나눠서 빈 영역을 계산했다.
구글링 해보니 반시계로 가기 때문에 잘리지 않는 변이 총 2개 나오는데 
두번째로 잘리지 않는 영역 인덱스에서 +2, +3번쨰는 반드시 작은 사각형 가로, 세로 길이가 나온다는 것을 이용하면 됐다.

*/

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.List;
import java.util.StringTokenizer;


public class Main {
	static class Pos{
		int dir; int len;
		Pos(int dir, int len){
			this.dir=dir;
			this.len=len;
		}
	}
	public static void main(String[] args) throws Exception {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		int K = Integer.parseInt(br.readLine());
		
		StringTokenizer st = null;
		int allWidth = 0;
		int allHeight = 0;
		int space = 0;	// 빈 공간 면적
		
		List<Pos> order= new ArrayList<>();
		
		for(int i=0; i<6; ++i) {
			int dir=0;
			int len= 0;
			st = new StringTokenizer(br.readLine());
			
			dir = Integer.parseInt(st.nextToken());
			len = Integer.parseInt(st.nextToken());
			
			order.add(new Pos(dir, len));
			
			if(dir == 1) allWidth += len;
			else if(dir == 3) allHeight += len;
		}
		
		for(int i=0; i<order.size(); ++i) {
			// 전체 4가지 케이스
			int first = order.get(i).dir;		// 현재 i 위치
			int second = order.get(i+1).dir;	// i+1
			int third = order.get(i+2).dir;		// i+2
			int fourth = order.get(i+3).dir;	// i+3
			
			int fifth = order.get(order.size()-2).dir;	// 맨 마지막 전
			int sixth = order.get(order.size()-1).dir;	// 맨마지막
			
			// 1. 꺾이는 부분이 연속
			if(first == third && second == fourth) {
				space = order.get(i+1).len *order.get(i+2).len;
				break;
			}
			
			// 2. 처음 3개, 마지막 1개
			else if(first == third && second == sixth) {
				space = order.get(i).len *order.get(i+1).len;
				break;
			}
			
			// 3. 처음 두개, 마지막 2개
			else if(first == fifth && second == sixth) {
				space = order.get(i).len *order.get(order.size()-1).len;
				break;
			}
			
			// 4. 처음 1개, 마지막 3개
			else if(first == fifth){
				space = order.get(order.size()-2).len *order.get(order.size()-1).len;
				break;
			}
		}
		
		int rect = allWidth*allHeight;	// 직사각형 전체 면적
		
		System.out.println((rect-space)*K);
	}

}
