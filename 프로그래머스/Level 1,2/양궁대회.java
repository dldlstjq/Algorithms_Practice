/*
21년 하반기 때 카카오 문제로 나왔던 문제이다.
그때 당시에는 못 풀었었는데 내 힘으로 다시 풀 수 있어 다행이라고 해야하나.
점수차이가 최고가 나야하고 그 중에서도 낮은 점수를 많이 맞힌 배열을 리턴해야 한다.
점수 차이가 최고라는 것, 그 중에서 낮은 점수라는 것에서 지레 겁먹고 어렵다고 판단한 것 같다.
n이 최대 10이었기 때문에 모든 경우를 다 한다해도 10초안에는 될 것이라 생각했다.
10점부터 모두 맞추면서 하나씩 해본다. 그리고 점수 계산을 한 뒤 차이가 많이 나는 것, 그 중에서도 낮은 점수가 많은 것을 걸러주면 된다.

둘 다 화살을 못 맞힌 경우는 점수 계산을 하면 안되는 것을 꼭 걸러줘야 한다.
그렇지 않으면 둘 다 못맞혔는데 점수가 계산되는 일이 발생한다.
*/

class Solution {
    static int[] lion;
    static int diff;
    static int[] ret;

    public int[] solution(int n, int[] info) {
        int[] answer = {};

        // n = 쏜 화살 개수
        // info = 어피치가 쏜 화살
        // i번쨰 원소는 10-i를 맞힌 화살개수
        // 

        lion = new int[11];
        ret = new int[11];
        diff = Integer.MIN_VALUE;

        solve(n, info, 0, 0);

        if(diff == Integer.MIN_VALUE){
            answer = new int[1];
            answer[0] = -1;
        }

        else{
            answer = new int[11];
            answer = ret.clone();
        }


        return answer;
    }

    static void solve(int n, int[] info, int idx, int score){
        if(n == 0){
            int lion_sum = 0;
            int apeach_sum = 0;
            for(int i=0; i<lion.length; ++i){
                if(info[i] == 0 && lion[i] == 0) continue;  // 둘 다 0점이면 계산 안함

                // 점수 계산
                if(info[i] >= lion[i]) apeach_sum += 10-i;
                else lion_sum += 10-i;
            }

            // 어피치 점수가 크거나 같다면 리턴
            if(apeach_sum >= lion_sum) return;

            // 차이가 기존보다 더 클때
            if(diff < lion_sum-apeach_sum){
                diff = lion_sum-apeach_sum; // diff 최신화
                ret = lion.clone(); // 그때의 맞힌 경우
            }

            // 점수차이가 같다면 가장 낮은 점수를 더 많이 맞힌 경우
            else if(diff == lion_sum-apeach_sum){
                for(int i=lion.length-1; i>=0; --i){
                    // 기존의 ret이 더 낮은 점수가 많다면 종료
                    if(ret[i] > lion[i]) break;

                    // 새로운 배열이 더 낮은점수가 많다면 ret 교환 후 종료
                    else if(ret[i] < lion[i]){
                        ret = lion.clone();
                        break;
                    }
                }
            }
            return;
        }

        // idx번째 부터 하나씩 다 맞혀본다
        for(int i=idx; i<lion.length; ++i){
            lion[i]++;
            solve(n-1, info, i, score);
            lion[i]--;
        }
    }
}