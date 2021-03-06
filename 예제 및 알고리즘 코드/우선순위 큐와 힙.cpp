﻿//정수를 저장하는 힙
vector<int> heap;

//정수 원소를 갖는 최대 힙에 새 원소 삽입하기
void push_heap(vector<int>& heap, int newValue) {
	//힙의 맨 끝에 newValue를 삽입한다.
	heap.push_back(newValue);
	//현재 newValue의 위치
	int idx = heap.size() - 1;
	//루트에 도달하거나 newValue 이상의 원소를 가진 조상을 만날때 까지
	whlie(idx > 0 && heap[(idx - 1) / 2] < heap[idx]) {
		swap(heap[idx], heap[(idx - 1) / 2);
		idx = (idx - 1) / 2;
	}
}

//정수 원소를 갖는 최대 힙에서 최대 원소 삭제하기
void pop_heap(vector<int>& heap) {
	//힙의 맨 끝에서 값을 가져와 루트에 덮어 씌운다.
	heap[0] = heap.back();
	heap.pop_back();
	int here = 0;
	while (true) {
		int left = here * 2 + 1, right = here * 2 + 2;
		//리프에 도달한 경우
		if (left >= heap.size())break;
		//heap[here]가 내려갈 위치를 찾는다.
		int next = here;
		if (heap[next] < heap[left])
			next = left;
		if (right < heap.size() && heap[next] < heap[right])
			next = right;
		if (next == here)break;
		swap(heap[here], heap[next]);
		here = next;
	}
}