/*
C++ 풀이. #include <queue>에서 queue 자료구조 제공.
직접 push, pop 함수 구현 안해도 됨
*/
#include <iostream>
#include <string>
#include <queue>

using namespace std;


int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	queue<int> q;
	int n;
	string str;
	cin >> n;

	for (int i = 0; i < n; i++) {
		cin >> str;

		if (str == "push") {
			int num;
			cin >> num;
			q.push(num);
		}

		else if (str == "pop") {
			if (q.empty())
				cout << "-1" << '\n';
			else {
				cout << q.front() << '\n';
				q.pop();
			}
		}

		else if (str == "pop") {
			if (q.empty())
				cout << "-1" << '\n';
			else {
				cout << q.front();
				q.pop();
			}
		}

		else if (str == "size") {
			cout << q.size() << '\n';
		}

		else if (str == "empty") {
			if (q.empty())
				cout << "1" << '\n';
			else
				cout << "0" << '\n';
		}

		else if (str == "front") {
			if (q.empty())
				cout << "-1" << '\n';
			else
				cout << q.front() << '\n';
		}

		else if (str == "back") {
			if (q.empty())
				cout << "-1" << '\n';
			else
				cout << q.back() << '\n';
		}

	}
	return 0;
}



////////////////////////////////////
/*
C 풀이. 자료구조시간에 배운거 사용.
직접 큐 함수 구현.
*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_QUEUE_SIZE 10000

int queue[MAX_QUEUE_SIZE];
int front = -1;
int rear = -1;

int main() {
	int n = 0;
	int item = 0;
	char ch[100] = { 0 };
	char* ptoken;
	int k = 0;

	scanf("%d", &n);
	getchar();
	for (int i = 0; i < n; i++) {

		gets(ch);

		ptoken = strtok(ch, " ");

		if (!(strcmp(ptoken, "push"))) {
			sscanf(ch + strlen(ch) + 1, "%d", &item);
			queue[++rear] = item;		//push
		}

		else if (!(strcmp(ptoken, "pop"))) {
			if (front == rear) {
				printf("-1\n");
				front = rear = -1;					//큐 안을 다 빼내면 front랑 rear를 다시 -1로 설정
			}

			else {
				printf("%d\n", queue[++front]);		//큐에 원소가 있는 경우 pop
				for (k = 0; front < rear; k++)
					queue[k] = queue[++front];
				queue[rear] = 0;
				front = -1;
				rear = k - 1;					//인덱스 0부터 시작하도록 정렬
			}

		}

		else if (!(strcmp(ptoken, "size"))) {
			if (front == rear)
				printf("0\n");
			else
				printf("%d\n", rear + 1);
		}

		else if (!(strcmp(ptoken, "empty"))) {
			if (front == rear)
				printf("1\n");
			else
				printf("0\n");
		}
		else if (!(strcmp(ptoken, "front"))) {
			if (front == rear)
				printf("-1\n");
			else {
				printf("%d\n", queue[front + 1]);
			}
		}
		else if (!(strcmp(ptoken, "back"))) {
			if (front == rear)
				printf("-1\n");
			else
				printf("%d\n", queue[rear]);
		}
	}
	return 0;
}