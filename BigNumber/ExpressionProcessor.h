#pragma once
#include <string>
#include <stack>
#include <queue>
#include <iostream>
#include "Qint.h"
#include "BigNumberDlg.h"

class ExpressionProcessor
{
private:
	std::string expression;
	Qint _result;
	Mode _mode;

	int getPrioritize(std::string c)
	{
		const int MAX = 100;
		if ((c == "x++" || c == "x--" )) {
			return MAX;
		}
		else if (c == "++x" || c == "--x" || c == "~") {
			return MAX - 1;
		}
		else if (c == "X" || c == "÷" || c == "%") {
			return MAX - 2;
		}
		else if (c == "+" || c == "-") {
			return MAX - 3;
		}
		else if (c == ">>" || c == "<<" || c == "ror" || c == "rol") {
			return MAX - 4;
		}
		else if (c == "&") {
			return MAX - 5;
		}
		else if (c == "^") {
			return MAX - 6;
		}
		else if (c == "|") {
			return MAX - 7;
		}
		return MAX - 8;
	}
	bool isNumber(char c)
	{
		if (c >= '0' && c <= '9')
			return true;
		else
			return false;
	}

	bool IsOperator(std::string c)
	{
		if (
			c == "rol" ||
			c == "ror" ||
			c == "x++" ||
			c == "x--" ||
			c == "++x" ||
			c == "--x" ||
			c == "~" ||
			c == "X" ||
			c == "÷" ||
			c == "%" ||
			c == "+" ||
			c == "-" ||
			c == ">>" ||
			c == "<<" ||
			c == "&" ||
			c == "^" ||
			c == "|")
			return true;
		return false;
	}
	std::queue<std::string> convertInfixToPostfix()
	{
		std::stack<std::string> stackExp;
		std::queue<std::string> queueExp;

		expression = "(" + expression;
		expression = expression + ")";
		for (int i = 0; i < expression.length(); i++)
		{
			if (expression[i] == '(')
			{
				std::string temp(1, expression[i]);
				stackExp.push(temp);
			}
			else if (expression[i] == ')')
			{
				while (stackExp.top() != "(")
				{
					queueExp.push(stackExp.top());
					stackExp.pop();
				}
				stackExp.pop();
			}
			else if (isNumber(expression[i]))
			{
				std::string numTemp;
				while (isNumber(expression[i]))
				{
					std::string temp(1, expression[i]);
					numTemp += temp;
					i++;
				}
				i--;
				queueExp.push(numTemp);
			}
			else
			{
				std::string currentOperator = "";
				bool isPostFix = true;
				std::string subStr = expression.substr(i, std::string::npos);
				if (subStr.length()>=2&&
					(
						(subStr[0] == '>' && subStr[1] == '>') || 
						(subStr[0] == '<' && subStr[1] == '<'))
					) {
					currentOperator = subStr.substr(0, 2);
					i++;
				}
				else if (subStr.length()>=3 &&
					(subStr.substr(0,3) == "ror"|| subStr.substr(0, 3) == "rol"))  {
					currentOperator = subStr.substr(0, 3);
					i += 2;
				}
				else 
					if (subStr.substr(0, 2) == "++" ||
					subStr.substr(0, 2) == "--") {
					currentOperator = subStr.substr(0, 2);

					if (subStr.length() >= 3) {
						if (isNumber(subStr[2])) {
							isPostFix = false;
						}
					}
					if (isPostFix == false) {
						//Prefix
						currentOperator = currentOperator + "x";
					}
					else {
						currentOperator = "x" + currentOperator;
					}
					i++;

				}
				else {
					currentOperator = expression[i];
				}

				while ((stackExp.top() != "(") &&
					(getPrioritize(stackExp.top()) >= getPrioritize(currentOperator)))
				{
					queueExp.push(stackExp.top());
					stackExp.pop();
				}

				stackExp.push(currentOperator);
			}
		}
		return queueExp;
	}
	void PrintQueue(std::queue<std::string> q)
	{
		while (q.size() != 0)
		{
			std::cout << q.front() << " ";
			q.pop();
		}
	}
	Qint SimpleCalc(Qint *a, Qint b, std::string _operator)
	{
		if (_operator == "+")
			return b+ *a;
		if (_operator == "-")
			return  b-*a;
		if (_operator == "X")
			return b**a;
		if (_operator == "÷")
			return b/(*a);
		if (_operator == "^")
			return b^*a;
		if (_operator == "~")
			return ~b;
		if (_operator == ">>") {
			return b >> std::stoi(a->toString());
		}
		if (_operator == "<<") {
			return b << std::stoi(a->toString());
		}
		if (_operator == "&") {
			return*a&b;
		}
		if (_operator == "|") {
			return *a | b;
		}
		
		if (_operator == "x++") {
			return b++;
		}
		if (_operator == "x--") {
			return b++;
		}
		if (_operator == "++x") {
			return ++b;
		}
		if (_operator == "--x") {
			return --b;
		}
		if (_operator == "ror") {
			return b.ror(std::stoi(a->toString()));

		}
		if (_operator == "rol") {
			return b.rol(std::stoi(a->toString()));
		}

	}
	Qint calc()
	{
		auto expression = convertInfixToPostfix();
		PrintQueue(expression);
		std::stack<Qint> s;
		std::string temp;
		while (!expression.empty())
		{
			temp = expression.front();
			if (!IsOperator(temp))
			{
				//Là số
				Qint n(temp, false);
				s.push(n);
				expression.pop();
			}
			else
			{
				
				if (temp == "~" ||
					temp == "x++" ||
					temp == "x--" ||
					temp == "++x" ||
					temp == "--x" 
					) {
				
					Qint b;
					b = s.top();
					s.pop();
					auto result = SimpleCalc(NULL, b, temp);
					s.push(result);
					expression.pop();
				}
				else {
					Qint a;
					Qint b;
					a = s.top();
					s.pop();
					b = s.top();
					s.pop();
					Qint result = SimpleCalc(&a, b, temp);
					s.push(result);
					expression.pop();
				}

			}
		}
		return s.top();
	}
	bool CheckValidInput() {

		for (int i = 0; i < expression.length(); i++) {
			auto _3chars = expression.substr(i, 3);
			auto _2chars = expression.substr(i, 2);
			auto _1char = expression.substr(i, 1);
			
			if (!IsContainAllowInput(_3chars) &&
				!IsContainAllowInput(_2chars) &&
				!IsContainAllowInput(_1char)) {
				return false;
			}

			

		}
		
		return true;

	}
	bool IsContainAllowInput(std::string  currentChar) {
		
		std::vector<std::string> dec = 
		{ "&", "|", "^", "~", "ror", "rol",">>",
			"<<","(",")","%","÷","X","-","+",".","0","1","2","3","4","5","6","7","8","9"};
		std::vector<std::string> hex = { "A","B","C","D","E","F" ,"0","1","2","3","4","5","6","7","8","9" };
		std::vector<std::string> bin = {"<<",">>","+","-","X","÷","%","0","1","ror","rol","&","|","^","~"};
		std::vector<std::string> current;

		if (_mode == DEC) {
			current = dec;
		}
		else if (_mode == BIN) {
			current = bin;
		}
		else if (_mode == HEX) {
			current = hex;
			
		}
		for (auto i : current) {
			if (i == currentChar)
				return true;
		}
		return false;


	}
public:
	ExpressionProcessor(std::string input,Mode mode);
	Qint GetResult() {
		return _result;
	}
};

