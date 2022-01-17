/*
문제 자체는 단순했는데 풀이가 중요했다.
분명 단순히 중첩 반복을 쓰면 시간초과가 날게 뻔했다.
dp를 써야되나 싶었는데 규칙성을 찾지 못했다.
질문을 보니 슬라이딩 윈도우 방식을 썼다고 해서 그걸 이용하면 n만큼만 반복해도 충분히 답을 구할 수 있었다.
두 개의 포인터 start, end를 이용하되 start는 0부터, end는 1부터 시작하도록 했다.
그렇게 해야 n이 1일때도 적용되었다.
start ~ end 사이 값이 크다면 start++, 작으면 end++ 를 해줬다.
n과 똑같으면 카운트하고 end를 하나 옮겨줬다.

마지막에 end가 n을 넘으면 종료되도록 해서 에러가 안나도록 했다.
*/

class Solution {
    public int solution(int n) {
        int answer = 0;

        int[] arr = new int[n+1];
        for(int i=1; i<=n; ++i)
            arr[i] = i;


        int start = 0, end = 1;

        while(start<=end){

            int sum = 0;
            for(int i=start; i<=end; ++i)
                sum += arr[i];

            if(sum > n)
                start++;
            else if(sum < n)
                end++;

            else if(sum == n){
                answer++;
                end++;
            }

            if(end > n)
                break;

        }
        return answer;
    }
}
