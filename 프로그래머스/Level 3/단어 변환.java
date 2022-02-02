/*
처음에 알파벳 하나하나 다 검사해야 하나 싶었지만 다른 알파벳이 하나인 문자를 찾으면 됐다.
타겟 단어가 words에 없으면 바로 0을 리턴하고 아니면 bfs로 검사한다.
words를 순회하며 단어가 하나 차이나는 것을 큐에 계속 넣고 target이면 종료한다.
방문 표시를 해줄 때 map을 사용했는데 visited 1차원 배열 하나를 사용해도 될 것 같다.
*/

import java.util.*;
class Solution {
    static class Word {
        String word; int cnt;
        Word(String word, int cnt){
            this.word=word;
            this.cnt=cnt;
        }
    }
    
    public int solution(String begin, String target, String[] words) {
        int answer = 0;
        
        // 변환 단어가 없으면 0 리턴
        if(!findWord(target, words))
            return answer;
        
        Map<String, Boolean> map = new HashMap<>();
        for(int i=0; i<words.length; ++i)
            map.put(words[i], false);
        
        
        Queue<Word> q = new LinkedList<>();
        q.offer(new Word(begin, 0));
        while(!q.isEmpty()){
            Word now = q.poll();
            String str = now.word;
            int cnt = now.cnt;
            
            // target 문자가 나오면 종료
            if(str.equals(target)){
                answer = cnt;
                break;
            }
            
            for(int i=0; i<words.length; ++i){
                if(!compareWord(str, words[i])) continue;
                if(map.get(words[i])) continue;
                
                q.offer(new Word(words[i], cnt+1));
                map.put(words[i], true);
            }
        }
        
        
        return answer;
    }
    
    static boolean compareWord(String str1, String str2){
        int cnt = 0;
        
        for(int i=0; i<str1.length(); ++i){
            if(str1.charAt(i) != str2.charAt(i))
                cnt++;
        }
        
        if(cnt == 1) return true;
        else return false;
    }
    
    static boolean findWord(String str, String[] words){
        for(int i=0; i<words.length; ++i){
            if(str.equals(words[i]))
                return true;
        }
        return false;
    }
}