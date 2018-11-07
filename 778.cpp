#include<iostream>
#include<string>
				//#define STACK_SIZE 7000//ջ�Ĵ�С����������1000�����ʽ              ʹ�ú궨��ȫ�ֱ����������޸�
				//#define StringNode_SIZE 7000//StringNode ������е��ַ��������С
using namespace std;
				// ����ջ�����ݽṹ��
int JudgePriority(char c);			//��ǰ��������  �ж������c�����ȼ�
int Length;//ȫ�ֱ���
class StringNode 
{//Stringnode�ڵ㣬�洢ÿһ�����ʽ�������ȼ�
	private:
		string STring;
		int priority;//���ȼ�
	public:
		StringNode() 
		{
		//	STring = "\0";
			priority = 10;//Ĭ�ϳ�ʼ״̬
		}
	StringNode(char Char1) {//�����ַ���������ֻ����ĸ����Ҫ�������
	STring = Char1;
	priority = 4;//�趨��ĸ���ȼ�Ϊ4�������,����4�뵥����ĸ�ȼۣ��׳�3
}

	StringNode(string ExpressionString, int Priority1) 
	{													//���ʽ�ַ�����������
														//	STring.at(0) = '\0';//��ֹջ���ʳ���
		STring = ExpressionString;
		priority = Priority1;
	}
friend StringNode Compose(StringNode &SN1, char Operator, StringNode &SN2) 
{//���������ʽ��һ����������һ���µı��ʽ ������Ҳ������һ��
AutoAddBrackets(SN1, Operator, SN2);//�����Ҫ�Ļ��Զ���SN1��2������
return StringNode(SN1.STring + Operator + SN2.STring, JudgePriority(Operator));
}
friend StringNode Compose(StringNode &SN1, char Operator) {//��һ�����ʽ��һ����Ŀ��������������һ���µı��ʽ ������Ҳ������һ��
AutoAddBrackets(SN1, Operator);//�����Ҫ�Ļ��Զ���SN1������
SN1.STring += Operator;
return StringNode(SN1.STring, 3);//�������������ȼ��͸��˺ϳɵı��ʽ����Ȼ�ǽ׳˵�3��
}
friend void AutoAddBrackets(StringNode &SN1, char Operator, StringNode &SN2) {//ʹ�����ã�Ϊ���޸�ʵ��
if (SN1.priority >= JudgePriority(Operator) && JudgePriority(Operator) >= SN2.priority) {
SN2.AddBrackets();return;
}
else if (SN1.priority == 1 && (Operator=='*'|| Operator == '/') && SN2.priority >= 3) {
SN1.AddBrackets();return;
}
else if (SN1.priority == 1 && (Operator == '*' || Operator == '/') && SN2.priority <= 2) {
SN1.AddBrackets();SN2.AddBrackets();return;
}
else//���߶�����������������
return;
}
friend void AutoAddBrackets(StringNode &SN1, char Operator) {
if (SN1.priority<3 ) {//����ǣ�
SN1.AddBrackets();
}
}
void AddBrackets() {
	STring=STring.insert(0,1,'(') + ")";
priority = 4;//�������Ժ����ȼ���ú�����һ����
}
void PrintString() {//����������е�STring�ַ���
cout << STring;
}
};
class Stack {
private:
StringNode *Buffer; //����ջ�е����ݣ�ָ��ջ��
int top; //ջ�����
public:
Stack(int Len) {
Buffer = new StringNode[Len];//�������ֻ����Buffer��ָʾ��������һ��������
top = 0;//��ʼû��Ԫ�أ�topָ�������
}
void push(StringNode val) { //ѹջ���� 
Buffer[top++] = val;
}
StringNode pop() { //��ջ���� 
top--;//����top����ָ����һ����û��ֵ��λ�ã������Ҫ��top����һλ
return Buffer[top];
}
void PrintStack() {//���յ����
Buffer[0].PrintString();
}
};
bool IsCharacter(char c) {//����ĸ����
return c >= 'a'&&c <= 'z';
}
bool IsBiOperator(char c) {//�ж�Ԫ�����
return c == '+' || c == '*' || c == '/' || c == '-';
}
bool IsSingleOperator(char c) {//��һԪ�����������
return c == '!';
}
int JudgePriority(char c) {//���ز������ŵ����ȼ�
if (c == '+' || c == '-')//if�жϱ�������ţ�return���Բ���
return 1;
else if (c == '*' || c == '/')
return 2;
else if (c == '!')
return 3;
else
return 10;//�������
}
int main()
{
int c = 0;//����һ��һ����ȡ�ַ�
string Str;
cin >> Str;
Length = Str.size();
Stack StackObject(Length);//����ջ����
while (c < Str.size()) {//ͨ��c��ȡһ���ַ�
if (IsCharacter(Str.at(c))) {//�������ĸ����ջ
StackObject.push(StringNode(Str.at(c)));
}
else if (IsBiOperator(Str.at(c))) {//����Ƕ�Ŀ���������ջ�����ڵ��ϳ�����ջ
StringNode TempSN1 = StackObject.pop();
StringNode TempSN2 = StackObject.pop();//ע���ջ���˳��
StackObject.push(Compose(TempSN2, Str.at(c), TempSN1));//2��ǰ��
}
else if (IsSingleOperator(Str.at(c))) {//�����һĿ�����
StringNode TempSN = StackObject.pop();
StackObject.push(Compose(TempSN, Str.at(c)));
}
c++;
}
StackObject.PrintStack();
return 0;
}