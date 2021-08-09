/*
c++의 경우 stable_sort로 순서를 지키면서 정렬하는 함수가 있는데 자바는 조건에 맞으면 바꾸고 아니면 그대로 가는 형식으로 하면 될 것 같았다.
나이순으로만 체크를 하고 같으면 그냥 들어온 순서대로 출력하면 끝이다.
*/

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.Arrays;
import java.util.Comparator;
import java.util.StringTokenizer;

class Person{
	int age;
	String name;
	public Person(int age, String name) {
		this.age = age;
		this.name = name;
	}
}

public class Main {
	
	// Comparator를 익명객체로 구현
	// Comparator 인터페이스의 compare 함수를 재정의
	// 원래는 두 원소 중 첫번째가 두번째보다 작으면 음수, 같으면 0, 두번째가 더 크면 양수를 리턴한다.
	// 단순히 뺄셈 연산을 하면 경우를 안 나눠도 되지만 언더, 오버플로우 문제가 발생할 수 있기에 뺄셈은 주의해야 한다.
	static Comparator<Person> comp = new Comparator<Person>(){
		@Override
		public int compare(Person e1, Person e2) {
			return e1.age - e2.age;
		}
	};

	public static void main(String[] args) throws Exception {
		
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		
		int N = Integer.parseInt(br.readLine());
		
		Person arr[] = new Person[N];
		StringTokenizer st;
		for(int i=0; i<N; ++i) {
			st = new StringTokenizer(br.readLine(), " ");
			int age =Integer.parseInt(st.nextToken());
			String name = st.nextToken();
			arr[i] = new Person(age, name);
		}
		// 3. 2의 람다식을 더 간단하게
		Arrays.sort(arr, (e1, e2) -> {
			return e1.age - e2.age;
		});
		
		StringBuilder sb = new StringBuilder();
		for(int i=0; i<N; ++i) 
			sb.append(arr[i].age + " " + arr[i].name).append('\n');
		
		System.out.println(sb);
	}

}