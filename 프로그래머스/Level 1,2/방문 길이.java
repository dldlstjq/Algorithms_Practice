/*
map과 list를 사용해서 중복여부를 확인했는데 contains가 잘 먹히지 않았다.
그래서 list를 돌면서 일일이 확인해줬고 중북 좌표가 아니라 중복 선을 계산하기 때문에 현재, 나중 이동 위치를 클래스로 잡았다.

문제는 두 곳을 계속 왔다갔다 하는 경우는 중복이기 때문에 시작과 끝이 서로 같거나 시작과 끝, 끝과 시작이 같으면 같은 길이기 때문에 카운트 해주면 안된다.
(0,0) -> (1,0) -> (0,0) -> (1,0) 다 같은 길.
*/

import java.util.*;

class Solution {
    static class Pos{
        int sr; int sc; int er; int ec;
        Pos(int sr, int sc, int er, int ec){
            this.sr=sr;
            this.sc=sc;
            this.er=er;
            this.ec=ec;
        }
    }
    
    static int dr[] ={1,0,-1,0};
    static int dc[] ={0,1,0,-1};
    
    static List<Pos> list;
    
    public int solution(String dirs) {
        int answer = 0;
        char[] ch = dirs.toCharArray();
        //Pos point = new Pos(0, 0);
        list = new ArrayList<>();
        
        int sr = 0;
        int sc = 0;
        int nr = 0;
        int nc = 0;
        for(int i=0; i<ch.length; ++i){
            if(ch[i] =='U'){
                if(move(0, nr, nc)){
                    nr = sr+dr[0];
                    nc = sc+dc[0];
                    if(!search(sr, sc, nr, nc)){
                        list.add(new Pos(sr, sc, nr, nc));
                        answer++;
                    }
                     sr = nr;
                    sc = nc;
                }
            }
            else if(ch[i] =='R'){
                if(move(1, nr, nc)){
                	nr = sr+dr[1];
                    nc = sc+dc[1];
                    if(!search(sr, sc, nr, nc)){
                    	list.add(new Pos(sr, sc, nr, nc));
                        answer++;
                    }
                }
                  sr = nr;
            sc = nc;
            }
            else if(ch[i] =='D'){
                if(move(2, nr, nc)){
                	nr = sr+dr[2];
                    nc = sc+dc[2];
                    if(!search(sr, sc, nr, nc)){
                    	list.add(new Pos(sr, sc, nr, nc));
                        answer++;
                    }
                }
                  sr = nr;
            sc = nc;
            }
            else if(ch[i] =='L'){
                if(move(3, nr, nc)){
                	nr = sr+dr[3];
                    nc = sc+dc[3];
                    if(!search(sr, sc, nr, nc)){
                    	list.add(new Pos(sr, sc, nr, nc));
                        answer++;
                    }
                }
                  sr = nr;
            sc = nc;
            }
            
          
        }
        
        return answer;
    }
    
    static boolean search(int sr, int sc, int nr, int nc) {
    	for(int i=0; i<list.size(); ++i) {
            // 두 개 좌표를 왔다갔다 하는 경우 모두 검색
    		if((list.get(i).sr == sr && list.get(i).sc == sc
              && list.get(i).er == nr && list.get(i).ec == nc) ||
              (list.get(i).er == sr && list.get(i).ec == sc
              && list.get(i).sr == nr && list.get(i).sc == nc)) return true;
    	}
    	return false;
    }
    
    static boolean move(int dir, int r, int c){
        return -5<=r+dr[dir]&&r+dr[dir]<=5 && -5<=c+dc[dir]&&c+dc[dir]<=5;
    }
}