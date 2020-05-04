#pragma once
#include <string>
#include <stack>
#include <queue>
#include <iostream>
#include "Qint.h"

class ExpressionProcessor
{
private:
	std::string expression;
	Qint _result;

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

	bool isOperator(std::string c)
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
	void printQueue(std::queue<std::string> q)
	{
		while (q.size() != 0)
		{
			std::cout << q.front() << " ";
			q.pop();
		}
	}
	Qint simpleCalc(Qint a, Qint* b, std::string _operator)
	{
		if (_operator == "+")
			return a + *b;
		if (_operator == "-")
			return  a - *b;
		if (_operator == "X")
			return a * *b;
		if (_operator == "÷")
			return a / *b;
		if (_operator == "^")
			return a ^ *b;
		if (_operator == "~")
			return ~a;
		if (_operator == ">>") {
			return a >> std::stoi(b->toString());
		}
		if (_operator == "<<") {
			return a << std::stoi(b->toString());
		}
		if (_operator == "&") {
			return a & *b;
		}
		if (_operator == "|") {
			return a | *b;
		}
		if (_operator == "^") {
			return a ^ *b;
		}
		if (_operator == "x++") {
			return a++;
		}
		if (_operator == "x--") {
			return a--;
		}
		if (_operator == "++x") {
			return ++a;
		}
		if (_operator == "--x") {
			return --a;
		}
		if (_operator == "ror") {
			return a.ror(std::stoi(b->toString()));

		}
		if (_operator == "rol") {
			return a.rol(std::stoi(b->toString()));
		}

	}
	Qint calc()
	{
		auto expression = convertInfixToPostfix();
		printQueue(expression);
		std::stack<Qint> s;
		std::string temp;
		while (!expression.empty())
		{
			temp = expression.front();
			if (!isOperator(temp))
			{
				//Là số
				Qint n(temp);
				s.push(n);
				expression.pop();
			}
			else
			{
				Qint a;
				Qint b;
				if (temp == "~" ||
					temp == "x++" ||
					temp == "x--" ||
					temp == "++x" ||
					temp == "--x" 
					) {
					a = s.top();
					s.pop();
					auto result = simpleCalc(a, NULL, temp);
					s.push(result);
					expression.pop();
				}
				else {
					a = s.top();
					s.pop();
					b = s.top();
					s.pop();
					Qint result = simpleCalc(a, &b, temp);
					s.push(result);
					expression.pop();
				}

			}
		}
		return s.top();
	}
public:
	ExpressionProcessor(std::string input);
	Qint GetResult() {
		return _result;
	}
};

