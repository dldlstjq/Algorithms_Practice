/*
스킬이 알파벳 전체이기 때문에 순서를 배열에 저장한다.
스킬트리에 든 스킬을 스킬 순서와 비교해서 순서에 맞지 않으면 카운트하지 않고 맞으면 카운트 한다.
*/

import java.util.*;
class Solution {
    public int solution(String skill, String[] skill_trees) {
        int answer = 0;
        
        int[] skills = new int[26];
        char[] ch = skill.toCharArray();
        
        // 스킬트리 순서
        int n = 1;
        for(Character c: ch)
            skills[c-'A'] = n++;
        
        
        for(String str: skill_trees){
            char[] tmp = str.toCharArray();
            
            int order = 1;
            boolean flag = true;
            for(Character c: tmp){
                // 선행 스킬인 아닌 경우
                if(skills[c-'A'] == 0) continue;
                
                // 선행스킬이면 order이랑 순서가 같아야 함
                if(skills[c-'A'] != order) {
                    flag = false;
                    break;
                }
                order++;
                
            }
            if(flag) answer++;
            
        }
        
        return answer;
    }
}