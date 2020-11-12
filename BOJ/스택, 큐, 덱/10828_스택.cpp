/*
C++ 풀이. #include <stack>에서 스택 지원.
push,pop 구현하지 않고도 쉽게 스택 이용 가능
*/

#include <iostream>
#include <string>
#include <stack>


using namespace std;


int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n;
	cin >> n;

	stack<int> st; //int type의 stack 선언. 
	string str;

	for (int i = 0; i < n; i++) {
		cin >> str;

		if (str == "push") { //push 명령어 일때. 

			int num;
			cin >> num;
			st.push(num);

		}
		else if (str == "pop") {    //pop 명령어 일때. 

			if (!st.empty()) {
				cout << st.top() << endl;
				st.pop();
			}
			else {
				cout << "-1" << endl;
			}

		}
		else if (str == "size") {        //size 명령어 일때. 

			cout << st.size() << endl;

		}
		else if (str == "empty") {    //empty 명령어 일때. 

			if (st.empty()) {
				cout << "1" << endl;
			}
			else {
				cout << "0" << endl;
			}

		}
		else if (str == "top") {        //top 명령어 일때. 

			if (!st.empty()) {
				cout << st.top() << endl;
			}
			else {
				cout << "-1" << endl;
			}

		}

	}
	return 0;
}


////////////////////////////////////////////
/*
C 풀이. 자료구조 시간때 한 거 사용.
PUSH, POP을 전부 직접 구현해서 사용.
push, pop 명령어도 토큰 잘라서 구분.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MAX_STACK_SIZE 10000

typedef struct {
	int n;
}element;
element stack[MAX_STACK_SIZE];
int top = -1;


void stackFull();
element stackEmpty();
void push(element item);
element pop();



void stackFull() {
	fprintf(stdout, "stakc is full");
	exit(EXIT_FAILURE);
}

element stackEmpty() {
	element item;
	item.n = -1;
	return item;
}

void push(element item) {
	if (top >= MAX_STACK_SIZE)
		stackFull();
	stack[++top] = item;
}

element pop() {
	if (top == -1)
		return stackEmpty();
	return stack[top--];
}

int main()
{
	int n = 0;
	int i = 0;
	char ch[100] = { 0 };
	char* ptoken = NULL;
	element item;

	scanf("%d", &n);
	getchar();
	while (i < n) {

		gets(ch);
		ptoken = strtok(ch, " ");
		if (!(strcmp(ptoken, "push"))) {
			sscanf(ch + strlen(ptoken) + 1, "%d", &item.n);
			push(item);
		}
		else if (!(strcmp(ptoken, "pop"))) {
			printf("%d\n", pop());
		}
		else if (!(strcmp(ptoken, "size"))) {
			printf("%d\n", top + 1);
		}
		else if (!(strcmp(ptoken, "empty"))) {
			if (top == -1)
				printf("1\n");
			else
				printf("0\n");
		}
		else if (!(strcmp(ptoken, "top"))) {
			if (top == -1)
				printf("-1\n");
			else
				printf("%d\n", stack[top]);
		}
		i++;
	}

	return 0;
}