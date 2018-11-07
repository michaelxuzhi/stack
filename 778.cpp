#include<iostream>
#include<string>
				//#define STACK_SIZE 7000//栈的大小，可以容纳1000个表达式              使用宏定义全局变量，方便修改
				//#define StringNode_SIZE 7000//StringNode 类对象中的字符串数组大小
using namespace std;
				// 定义栈的数据结构。
int JudgePriority(char c);			//向前引用声明  判断运算符c的优先级
int Length;//全局变量
class StringNode 
{//Stringnode节点，存储每一个表达式及其优先级
	private:
		string STring;
		int priority;//优先级
	public:
		StringNode() 
		{
		//	STring = "\0";
			priority = 10;//默认初始状态
		}
	StringNode(char Char1) {//单个字符建立对象，只有字母是需要这种情况
	STring = Char1;
	priority = 4;//设定字母优先级为4，是最高,括号4与单个字母等价，阶乘3
}

	StringNode(string ExpressionString, int Priority1) 
	{													//表达式字符串建立对象
														//	STring.at(0) = '\0';//防止栈访问出错
		STring = ExpressionString;
		priority = Priority1;
	}
friend StringNode Compose(StringNode &SN1, char Operator, StringNode &SN2) 
{//由两个表达式和一个运算符组成一个新的表达式 加括号也是在这一步
AutoAddBrackets(SN1, Operator, SN2);//如果需要的话自动给SN1，2加括号
return StringNode(SN1.STring + Operator + SN2.STring, JudgePriority(Operator));
}
friend StringNode Compose(StringNode &SN1, char Operator) {//由一个表达式和一个单目运算符（！）组成一个新的表达式 加括号也是在这一步
AutoAddBrackets(SN1, Operator);//如果需要的话自动给SN1加括号
SN1.STring += Operator;
return StringNode(SN1.STring, 3);//这个运算符的优先级就给了合成的表达式（必然是阶乘的3）
}
friend void AutoAddBrackets(StringNode &SN1, char Operator, StringNode &SN2) {//使用引用！为了修改实参
if (SN1.priority >= JudgePriority(Operator) && JudgePriority(Operator) >= SN2.priority) {
SN2.AddBrackets();return;
}
else if (SN1.priority == 1 && (Operator=='*'|| Operator == '/') && SN2.priority >= 3) {
SN1.AddBrackets();return;
}
else if (SN1.priority == 1 && (Operator == '*' || Operator == '/') && SN2.priority <= 2) {
SN1.AddBrackets();SN2.AddBrackets();return;
}
else//两边都不加括号情况，最多
return;
}
friend void AutoAddBrackets(StringNode &SN1, char Operator) {
if (SN1.priority<3 ) {//如果是！
SN1.AddBrackets();
}
}
void AddBrackets() {
	STring=STring.insert(0,1,'(') + ")";
priority = 4;//加括号以后，优先级变得和数字一样高
}
void PrintString() {//输出本对象中的STring字符串
cout << STring;
}
};
class Stack {
private:
StringNode *Buffer; //保存栈中的数据，指向栈首
int top; //栈的深度
public:
Stack(int Len) {
Buffer = new StringNode[Len];//这个数组只能用Buffer来指示，不能起一个数组名
top = 0;//初始没有元素，top指代第零个
}
void push(StringNode val) { //压栈操作 
Buffer[top++] = val;
}
StringNode pop() { //出栈操作 
top--;//由于top总是指向下一个还没有值的位置，因此先要把top后退一位
return Buffer[top];
}
void PrintStack() {//最终的输出
Buffer[0].PrintString();
}
};
bool IsCharacter(char c) {//判字母函数
return c >= 'a'&&c <= 'z';
}
bool IsBiOperator(char c) {//判二元运算符
return c == '+' || c == '*' || c == '/' || c == '-';
}
bool IsSingleOperator(char c) {//判一元运算符（！）
return c == '!';
}
int JudgePriority(char c) {//返回操作符号的优先级
if (c == '+' || c == '-')//if判断必须加括号，return可以不用
return 1;
else if (c == '*' || c == '/')
return 2;
else if (c == '!')
return 3;
else
return 10;//出错情况
}
int main()
{
int c = 0;//用于一个一个读取字符
string Str;
cin >> Str;
Length = Str.size();
Stack StackObject(Length);//建立栈对象
while (c < Str.size()) {//通过c读取一个字符
if (IsCharacter(Str.at(c))) {//如果是字母就入栈
StackObject.push(StringNode(Str.at(c)));
}
else if (IsBiOperator(Str.at(c))) {//如果是二目运算符，出栈两个节点后合成再入栈
StringNode TempSN1 = StackObject.pop();
StringNode TempSN2 = StackObject.pop();//注意出栈后的顺序
StackObject.push(Compose(TempSN2, Str.at(c), TempSN1));//2在前面
}
else if (IsSingleOperator(Str.at(c))) {//如果是一目运算符
StringNode TempSN = StackObject.pop();
StackObject.push(Compose(TempSN, Str.at(c)));
}
c++;
}
StackObject.PrintStack();
return 0;
}