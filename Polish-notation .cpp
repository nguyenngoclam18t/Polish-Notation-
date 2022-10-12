#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include"Queue.h"
#include"Stack.h"
#include<string.h>
#include<math.h>
int checkPriority(char c) {
	if (c == '^')return 1;
	if (c == '*' || c == '/')return 2;
	if (c == '+' || c == '-')return 3;
}
void Balan(Stack<char>& S, Queue<char>& Q, char str[100]) {
	for (int i = 0; i < strlen(str); i++) {
		//add số vào queue
		if (str[i] >= '0' && str[i] <= '9') {
			EnQueue<char>(Q, str[i]);
		}
		else
		{
			//add mở ngoặc
			if (str[i] == '(') {
				Push<char>(S, str[i]);
			}
			else
			{
				//so sánh độ ưu tiên của toán tử
				if (str[i] == '^' || str[i] == '/' || str[i] == '*' || str[i] == '-' || str[i] == '+') {
					while (S.top != NULL && checkPriority(str[i]) >= checkPriority(S.top->data) && S.top->data != '(')
					{
						NODES<char>* temp = Pop<char>(S);
						EnQueue<char>(Q, temp->data);
					}
					Push<char>(S, str[i]);
				}
				else
				{
					//gặp đóng ngoặc đổ hết vô 
					if (str[i] == ')') {
						while (S.top != NULL && S.top->data != '(')
						{
							EnQueue<char>(Q, S.top->data);
							Pop<char>(S);
						}
						Pop<char>(S);
					}
				}
			}

		}

	}
	//đổ hết những gì còn thừa vô lại queue
	while (S.top != NULL && S.top->data != '(')
	{
		EnQueue<char>(Q, S.top->data);
		Pop<char>(S);
	}


	for (NODEQ<char>* i = Q.Head; i != NULL; i = i->Next)
	{
		printf("%c ", i->Data);
	}

}
float calcu(int x, int y, char c) {
	if (c == '+')return x + y;
	if (c == '-')return x - y;
	if (c == '*')return x * y;
	if (c == '/')return 1.0*x / y;
	if (c == '^')return pow(x, y);
}
void Calculator(Queue<char>Q, Stack<float>S) {
	for (NODEQ<char>* i = Q.Head; i !=NULL ; i=i->Next)
	{
		if (i->Data >= '0' && i->Data <= '9') {
			Push<float>(S,i->Data - '0');
		}
		else
		{
			float a = calcu(S.top->next->data, S.top->data, i->Data);
			Pop<float>(S);
			Pop<float>(S);
			Push<float>(S, a);
		}
	}
	printf("\nket qua: %.2f", S.top->data);
}
int main() {
	Stack<char>S;
	Queue<char>Q;
	char str[100]="(2*3+8/2)*(5-1)";
	//gets_s(str);
	InitQueue(Q);
	InitStack(S);
	Balan(S, Q, str);
	Stack<float>Tinh;
	InitStack(Tinh);
	Calculator(Q, Tinh);
	return 0;
}