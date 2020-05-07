#pragma once
#include <string>
#include <stack>
#include <queue>
#include <iostream>
#include "Qint.h"
#include "BigNumberDlg.h"
#include <regex>


class ExpressionProcessor
{
private:
	std::string _expression;
	std::string _result;
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

		_expression = "(" + _expression;
		_expression = _expression + ")";
		for (int i = 0; i < _expression.length(); i++)
		{
			if (_expression[i] == '(')
			{
				std::string temp(1, _expression[i]);
				stackExp.push(temp);
			}
			else if (_expression[i] == ')')
			{
				while (stackExp.top() != "(")
				{
					queueExp.push(stackExp.top());
					stackExp.pop();
				}
				stackExp.pop();
			}
			else if (isNumber(_expression[i]))
			{
				std::string numTemp;
				while (isNumber(_expression[i]))
				{
					std::string temp(1, _expression[i]);
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
				std::string subStr = _expression.substr(i, std::string::npos);
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
					currentOperator = _expression[i];
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
			return b >> std::stoi(a->ToString());
		}
		if (_operator == "<<") {
			return b << std::stoi(a->ToString());
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
			return b.ror(std::stoi(a->ToString()));

		}
		if (_operator == "rol") {
			return b.rol(std::stoi(a->ToString()));
		}

	}
	void Solved() {

		if (_mode == DEC) {
			_result = calcQint();
		}

	}
	std::string calcQint()
	{
		if (_expression == "") throw "Emty";

		auto expression = convertInfixToPostfix();
		if (expression.empty()) throw "Empty queue";
		PrintQueue(expression);
		std::stack<Qint> s;
		std::string temp;
		while (!expression.empty())
		{
			temp = expression.front();
			if (!IsOperator(temp))
			{
				//Là số
				Qint n(temp,_mode == BIN);
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
		return s.top().ToString();
	}
	/*static bool IsContainAllowedInput(std::string  currentChar,Mode mode) {
		
		std::vector<std::string> dec = 
		{ "&", "|", "^", "~", "ror", "rol",">>",
			"<<","(",")","%","÷","X","-","+",".","0","1","2","3","4","5","6","7","8","9"};
		std::vector<std::string> hex = { "A","B","C","D","E","F" ,"0","1","2","3","4","5","6","7","8","9" };
		std::vector<std::string> bin = {"<<",">>","+","-","X","÷","%","0","1","ror","rol","&","|","^","~","2","3","4","5","6","7","8","9" };
		std::vector<std::string> current;

		if (mode == DEC) {
			current = dec;
		}
		else if (mode == BIN) {
			current = bin;
		}
		else if (mode == HEX) {
			current = hex;
			
		}
		for (auto i : current) {
			if (i == currentChar)
				return true;
		}
		return false;


	}*/
public:
	static CString ConvertStringToCString(std::string input)
	{
		return CString(input.c_str());
	}

	static void Debug(std::string message) {
		_cwprintf(_T("%s"), ConvertStringToCString(message));
	}
	ExpressionProcessor(std::string input,Mode mode);
	std::string GetResult() {
		return _result;
	}
	static bool CheckValidInput(std::string expression,Mode mode) {

		//DO:
		/*if (!checkValidBacket(expression)) {
			return false;
		}*/

		std::string modifiedExpression = "";
		for (char currentChar : expression) {
			if(currentChar != '('&&currentChar!=')'){
				modifiedExpression += currentChar;
			}			
		}
		modifiedExpression = '(' + modifiedExpression;
		modifiedExpression += ')';
		if (mode == DEC) {
			
			std::regex pattern("^\\(((\\+{0,2}|\\-{0,2}|~)?\\d+(\\+{0,2}|\\-{0,2}|~)?(\\+|\\-|X|÷|&|\\||^|ror|rol)?)+\\)$");   // matches words beginning by "sub"

			std::regex_iterator<std::string::iterator> rit(modifiedExpression.begin(), modifiedExpression.end(), pattern);
			std::regex_iterator<std::string::iterator> rend;

			if (rit == rend) {
				return false;
			}
			else {
				return true;
			}
		}
		else if (mode == BIN) {
			
		}
		return false;
	/*	bool flag = true;
		
		std::vector<std::string> dec =
		{ "&", "|", "^", "~", "ror", "rol",">>",
			"<<","(",")","%","÷","X","-","+",".","0","1","2","3","4","5","6","7","8","9" };
		std::vector<std::string> hex = { "A","B","C","D","E","F" ,"0","1","2","3","4","5","6","7","8","9" };
		std::vector<std::string> bin = { "<<",">>","+","-","X","÷","%","0","1","ror","rol","&","|","^","~","2","3","4","5","6","7","8","9" };
		std::vector<std::string> current;

		if (mode == DEC) {
			current = dec;
		}
		else if (mode == BIN) {
			current = bin;
		}
		else if (mode == HEX) {
			current = hex;

		}
		

		if (mode == BIN) {
			std::string pattern1 = "<<";
			std::string pattern2 = ">>";
			bool found = false;
			for (int i = 0; i < expression.length(); i++) {
				auto currentSubstr = expression.substr(i, 2);
				if (currentSubstr == pattern1 || currentSubstr == pattern2) {
					found = true;
					break;
				}
				if (!found && '1'<expression[i]&& expression[i] <='9') {
					return false;
				}

			}

		}

		return true;*/

	}
};

