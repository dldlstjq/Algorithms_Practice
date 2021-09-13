/*
처음엔 어떻게 접근해야할지 조차 몰랐던 문제이다.
코스요리가 2개 이상부터 가능하므로 2개부터 가능한 모든 코스요리 후보를 구해야 했다.
처음엔 방법을 몰라서 지나쳤다면 순열, 조합을 공부한 이후로 조금 자신감이 생겼다.

가장 먼저 든 생각은 모든 코스요리 후보를 해시맵에다 저장해 나온 횟수를 카운트 하는 것이었다.
그리고 코스요리 개수별로 가장 많이 주문된 후보를 저장하는 것이었다.
조합으로 가능한 코스요리를 해시맵에 저장한 다음 course 개수를 만족하면서 2개 이상 주문한 요리 후보를 리스트에 저장한다.
여기서 주문량이 많은 것을 선택해야 하기 때문에 클래스를 따로 만들어서 정렬해줬다.
그런 다음 주문량이 같은게 있을 수 있기 때문에 한 번 더 리스트를 돌면서 같은 주문량이 있는지 검사한다.
이렇게 검사한 뒤 마지막에 저장한 리스트를 다시 정렬해서 조건에 맞춰주니 통과했다.

알파벳 오름차순 정렬인것을 간과한 것, 가능한 모든 코스요리 후보를 어떻게 구해야 하는지를 몰라서 접근하기가 어려웠던 문제인 것 같다.

다른 사람 풀이를 보니 우선순위 큐를 활용해서 정렬을 따로 안해주게 만든 것 같다.
그리고 후보를 만들자 마자 최대 주문량을 구해서 저장했다.
*/

// 내 풀이
import java.util.*;

class Solution {
    // 주문 순서가 많은 순, 같으면 알파벳 순서로 정렬
    class Cook implements Comparable<Cook>{
		String food;
		int freq;
		
		Cook(String food, int freq){
			this.food = food;
			this.freq = freq;
		}
		
		@Override
		public int compareTo(Cook o) {
			if(this.freq == o.freq)
				return this.food.compareTo(o.food);
			return o.freq-this.freq;
		}
	}
    
    HashMap<String, Integer> dishes = new HashMap<>();
    int flag;
    
    void Comb(int start, int cnt, int limit, String str, String origin){
        if(cnt == limit){
            // 코스요리는 알파벳 오름차순으로 정렬
        	char[] StringtoChar = str.toCharArray();
            Arrays.sort(StringtoChar);
            String tmp = String.valueOf(StringtoChar);
           
            // 코스요리 후보가 없으면 추가
            if(!dishes.containsKey(tmp)){
                dishes.put(tmp, 1);
            }
            // 요리 후보가 있으면 갯수 추가
            else{
                int num = dishes.get(tmp);
                dishes.put(tmp, num+1);
            }
            return;
        }
        
        for(int i=start; i<origin.length(); ++i){
            Comb(i+1, cnt+1, limit, str+origin.charAt(i), origin);
        }
    }
    
    public String[] solution(String[] orders, int[] course) {
        String[] answer = {};
        
        for(int i=0; i<orders.length; ++i){
            // 2개부터 조합할 수 있는 모든 코스요리 후보 조합
            for(int j=2; j<=orders[i].length(); ++j){
                Comb(0, 0,j, "", orders[i]);
            }
        }
        
        ArrayList<String> list= new ArrayList<>();
        
        for(int i=0; i<course.length; ++i) {
        	ArrayList<Cook> cand= new ArrayList<>();
        	
        	for(HashMap.Entry<String, Integer> entry: dishes.entrySet()){
                String tmp = entry.getKey();
                int cnt = entry.getValue();
                // 코스요리 개수와 같으면서 2개 이상인 것들만 cand에 저장
                if(course[i] == tmp.length() && cnt >= 2){
                    cand.add(new Cook(tmp, cnt));
                }
            }
        	
        	// 아무것도 없으면 다른 코스 검사
        	if(cand.isEmpty())
        		continue;
        	// 주문량이 많은 순서대로 정렬
        	Collections.sort(cand);
        	list.add(cand.get(0).food);   // 제일 주문 많은 코스요리
        	for(int j=1; j<cand.size(); ++j) { 
        		if(cand.get(j).freq == cand.get(0).freq)     // 갯수가 똑같은 것이 있다면 추가
        			list.add(cand.get(j).food);
        		else
        			break;
        	}
        }
        
        Collections.sort(list);
        answer = new String[list.size()];
        
        for(int i=0;i<list.size(); ++i)
            answer[i] = list.get(i);
        return answer;
    }
}