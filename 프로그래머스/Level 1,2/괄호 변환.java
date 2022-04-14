/*
처음엔 문제 이해를 못했다가 하나씩 보다보니 이해가 갔다.
문제에 적힌대로 재귀함수로 구현하면 되는데 괄호를 뒤집을때 문자열 전체를 뒤집는 것이 아니라
괄호 방향을 바꿔줘야 한다. ( -> ), ) -> ( 이렇게 하나씩 바꿔주면 정답을 받는다.
*/

import java.util.*;

class Solution {
    public String solution(String p) {
        String answer = "";
        
        answer = solve(p);
        return answer;
    }
    
    static String solve(String p){
        if("".equals(p)) return "";
        
        StringBuilder u = new StringBuilder();
        StringBuilder v = new StringBuilder();

        int cnt=0;
        int idx=0;
        for(int i=0; i<p.length(); ++i){
            if(p.charAt(i) == '(') cnt++;
            else cnt--;
            
            if(cnt == 0){
                idx = i;
                break;
            }
        }
        
        u.append(p.substring(0, idx+1));
        v.append(p.substring(idx+1, p.length()));
        
        // u가 올바른 괄호문자열이 v에 대해 다시 수행
        if(complete(u.toString())){
            return u.append(solve(v.toString())).toString();
        }
        
        StringBuilder str = new StringBuilder("(");
        str.append(solve(v.toString()));
        str.append(")");
        
        String tmp ="";
        if(u.length() > 2)  tmp = u.substring(1, u.length()-1);
        
        // ( -> ) , ) -> ( 로 괄호 하나를 뒤집는다.
        String s ="";
        for(int i=0; i<tmp.length(); ++i){
            if(tmp.charAt(i) == '(') s += ')';
            else s += '(';
        }
            
        //StringBuilder t = new StringBuilder(tmp);
        
        
        return str.append(s).toString();
        
    }
    
    // 올바른 괄호 문자열 검사
    static boolean complete(String s){
        Stack<Character> st = new Stack<>();
        int cnt = 0;
        for(int i=0; i<s.length(); ++i){
            if(s.charAt(i) =='(') st.push(s.charAt(i) );
            else{
                if(st.isEmpty()) return false;
                else st.pop();
            }
        }
        return true;
    }
}