/*
입력값인 numbers를 int 배열로 만든 다음 순열을 이용해 해시맵에 저장했다.
저장한 키 값을 소수인지 판별해 카운트 하는 것으로 해결했다.

소수를 에라토스테네스의 체로만 하려고 했는데 최대값이 클수록 메모리를 많이 잡아먹고
제대로 구현하지 못하면 에러만 뜨기 때문에 직접 소수를 구하는 방법도 잘 알아둬야 겠다.

그리고 String 자체로 순열을 돌리는 방법이 있는데 잘 알아놓자.
*/

import java.util.*;

class Solution {
    
    HashMap<Integer, Boolean> map = new HashMap<>();
    int N;
    int[] list;
    
    public int solution(String numbers) {
        int answer = 0;
        
        char[] ch = numbers.toCharArray();
        int[] arr= new int[ch.length];
        
        for(int i=0; i<ch.length; ++i)
            arr[i] = ch[i]-'0';
        
        N = arr.length;
        list = new int[N];
        for(int i=1; i<=numbers.length(); ++i){
            perm(0 ,i, arr, 0);
        }
        // 키 값이 소수이면 카운트
        for(Map.Entry<Integer, Boolean> elem : map.entrySet()){
        	if(prime(elem.getKey()) == true)
                answer++;
        }
        return answer;
    }
    
    void perm(int idx, int len, int[] arr, int flag){
        // len 길이 만큼 차면 map에다 저장
        if(idx == len){
            String s = "";
            for(int i=0; i<len; ++i){
                s += list[i];
            }
            // 중복을 막기 위해 키값이 있는지 먼저 확인
            if(!map.containsKey(Integer.parseInt(s))){
                map.put(Integer.parseInt(s), true);
            }
            return;
        }
        // 순열
        for(int i=0; i<N; ++i){
            if((flag & (1<<i)) != 0) continue;
            list[idx] = arr[i];
            perm(idx+1, len, arr, flag | (1<<i));
        }
    }
    // 소수 판별
     boolean prime(int n) {
		if(n < 2) return false;

		for(int i=2; i*i<=n; ++i) {
			if(n % i == 0) return false;
		}
		return true;
	}
}



// 다른 사람의 풀이
import java.util.HashSet;
class Solution {
    public int solution(String numbers) {
        HashSet<Integer> set = new HashSet<>();
        permutation("", numbers, set);
        int count = 0;
        while(set.iterator().hasNext()){
            int a = set.iterator().next();
            set.remove(a);
            if(a==2) count++;
            if(a%2!=0 && isPrime(a)){
                count++;
            }
        }        
        return count;
    }

    public boolean isPrime(int n){
        if(n==0 || n==1) return false;
        for(int i=3; i<=(int)Math.sqrt(n); i+=2){
            if(n%i==0) return false;
        }
        return true;
    }

        public void permutation(String prefix, String str, HashSet<Integer> set) {
        int n = str.length();
        //if (n == 0) System.out.println(prefix);
        if(!prefix.equals("")) set.add(Integer.valueOf(prefix));
        for (int i = 0; i < n; i++)
          permutation(prefix + str.charAt(i), str.substring(0, i) + str.substring(i+1, n), set);
    }

}