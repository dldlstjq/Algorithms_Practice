/*
문제가 간단해 보였는데 해결못했어서 왜 이걸 해결 못했지하면서 다시 보니까 초기화를 안해줬다.

배열 전체에서 2x2 모양이 같은 블록이 있는지 확인하고 한번에 터뜨린 다음 블록을 내리는 형태를 반복한다.
블록을 지워야 하는지에 대한 값을 저장한 broken을 초기화 안해줘서 못풀었었다.
*/

import java.util.*;
class Solution {
    public int solution(int m, int n, String[] board) {
        int answer = 0;
        
        char[][] map = new char[m][n];
        
        
        for(int i=0; i<m; ++i){
            map[i] = board[i].toCharArray();
            //System.out.println(Arrays.toString(map[i]));
        }
        
        while(true){
            boolean[][] broken = new boolean[m][n]; // 부서진 블록 초기화
            
            for(int i=0; i<m-1; ++i){
                for(int j=0; j<n-1; ++j){
                    // 2x2 블록이 모두 같으면서 빈칸이 아닐 때 broken = true
                    if(map[i][j] == map[i][j+1] && map[i][j] == map[i+1][j] && 
                            map[i][j] == map[i+1][j+1] && map[i][j] != ' '){
                        broken[i][j] = true; broken[i][j+1] = true; 
                        broken[i+1][j] = true; broken[i+1][j+1] = true; 
                    }
                }
            }


            boolean flag=true;
            
            // broken=true인 부분은 다 꺠진다.
            for(int i=0; i<m; ++i){
                for(int j=0; j<n; ++j){
                    if(broken[i][j]){
                        map[i][j] = ' ';
                        answer++;
                        flag= false; 
                    } 
                }
            }
            
            // 하나라도 깨진 부분이 없다면 게임 종료
            if(flag) break;

            // 중력
            for(int i=0; i<n; ++i){
                List<Character> list = new ArrayList<>();
                for(int j=m-1; j>=0; --j){
                    if(map[j][i] != ' '){
                        list.add(map[j][i]);
                        map[j][i] = ' ';
                    }
                }
                int k=m-1;
                for(int j=0; j<list.size(); ++j){
                    map[k--][i] = list.get(j);
                }
            }
        }

        
        return answer;
    }
}