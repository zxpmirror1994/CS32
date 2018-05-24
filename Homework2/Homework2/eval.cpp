#include <iostream>
#include <stack>
#include <string>
#include <cassert>
using namespace std;

//determine to execute which operator
int precedence(const char operators);

//erase the spaces in the infix string
string eraseSpace(string infix);

//While encountering '!', just reverse
char reverse(const char operand);

//While encountering '&' or '|', do the accurate evaluation
char trueOrFalse(const char operand1, const char operand2, const char operators);

int evaluate(string infix, string& postfix, bool& result)
{
    postfix = "";
    stack<char> stackOperator;
    
    //The last char of infix cannot be like these
    if (infix[infix.length()] == '|' || infix[infix.length()] == '&' || infix[infix.length()] == '!' || infix[infix.length()] == '(')
    {
        return 1;
    }
    
    //Subsequent operations only involve newString
    string newInfix = eraseSpace(infix);
    
    
    int count1 = 0;
    int count2 = 0;
    for (int i = 0; i < newInfix.length(); i++)
    {
        switch (newInfix[i])
        {
            case 'T':
            case 'F':
                //Operands cannot stay together
                if (newInfix[i - 1] == 'T' || newInfix[i - 1] == 'F')
                {
                    return 1;
                }
                postfix += newInfix[i];
                break;
                
            case '(':
                //'(' cannot follow ')', 'T' and 'F'
                if (newInfix[i - 1] == ')' || newInfix[i - 1] == 'T' || newInfix[i - 1] == 'F')
                {
                    return 1;
                }
                stackOperator.push(newInfix[i]);
                count1++;
                break;
                
            case ')':
                //')' cannot follow '!', '&', '|' and '('
                if (newInfix[i - 1] == '!' || newInfix[i - 1] == '&' || newInfix[i - 1] == '|' || newInfix[i - 1] == '(')
                {
                    return 1;
                }
                while (stackOperator.top() != '(')
                {
                    postfix += stackOperator.top();
                    stackOperator.pop();
                }
                stackOperator.pop();
                count2++;
                break;
                
            case '&':
            case '|':
                //'&' and '|' cannot follow '!', '&', '|' and '('
                if (newInfix[i - 1] == '!' || newInfix[i - 1] == '&' || newInfix[i - 1] == '|' || newInfix[i - 1] == '(')
                {
                    return 1;
                }
                while (!stackOperator.empty() && stackOperator.top() != '(' && precedence(newInfix[i]) <= precedence(stackOperator.top()))
                {
                    postfix += stackOperator.top();
                    stackOperator.pop();
                }
                stackOperator.push(newInfix[i]);
                break;
                
            case '!':
                //'!' cannot follow 'T', 'F' and ')'
                if (newInfix[i - 1] == 'T' || newInfix[i - 1] == 'F' || newInfix[i - 1] == ')')
                {
                    return 1;
                }
                while (!stackOperator.empty() && stackOperator.top() != '(' && precedence(newInfix[i]) < precedence(stackOperator.top()))
                {
                    postfix += stackOperator.top();
                    stackOperator.pop();
                }
                stackOperator.push(newInfix[i]);
                break;
                
            case ' ':
                break;
                
            default:
                return 1;
                break;
        }
    }
    while (!stackOperator.empty())
    {
        postfix += stackOperator.top();
        stackOperator.pop();
    }
    
    //If the number of '(' and the number of ')' are not equal, return 1
    if (count1 != count2)
    {
        return 1;
    }
    
    
    
    stack<char> stackOperand;
    for (int j = 0; j < postfix.length(); j++)
    {
        if (postfix[j] == 'T' || postfix[j] == 'F')
        {
            stackOperand.push(postfix[j]);
            continue;
        }
        else if (postfix[j] == '!')
        {
            if (stackOperand.empty())
            {
                return 1;
            }
            
            char operand = stackOperand.top();
            stackOperand.pop();
            stackOperand.push(reverse(operand));
            continue;
        }
        else if (postfix[j] == '|' || postfix[j] == '&')
        {
            if (stackOperand.size() < 2)
            {
                return 1;
            }
            char operand2 = stackOperand.top();
            stackOperand.pop();
            char operand1 = stackOperand.top();
            stackOperand.pop();
            stackOperand.push(trueOrFalse(operand1, operand2, postfix[j]));
            continue;
        }
    }
    
    if (stackOperand.empty())
    {
        return 1;
    }
    
    char finalResult = stackOperand.top();
    if (finalResult == 'T')
    {
        result = true;
        return 0;
    }
    else if(finalResult == 'F')
    {
        result = false;
        return 0;
    }
    return 2;
    
}


int precedence(const char operators)
{
    switch (operators)
    {
        case '!':
            return 3;
            break;
            
        case '&':
            return 2;
            break;
            
        case '|':
            return 1;
            break;
    }
    return 0;
}

string eraseSpace(string infix)
{
    string newString;
    for (int m = 0; m < infix.length(); m++)
    {
        if (infix[m] != ' ')
        {
            newString += infix[m];
        }
    }
    return newString;
}

char reverse(const char operand)
{
    if (operand == 'T')
    {
        return 'F';
    }
    else if (operand == 'F')
    {
        return 'T';
    }
    return 'E';
}

char trueOrFalse(const char operand1, const char operand2, const char operators)
{
    if (operators == '&')
    {
        if (operand1 == 'T' && operand2 == 'T')
        {
            return 'T';
        }
        else
            return 'F';
    }
    if (operators == '|')
    {
        if (operand1 == 'T' || operand2 == 'T')
        {
            return 'T';
        }
        else
            return 'F';
    }
    return 'E';
}

int main()
{
    string pf;
    bool answer;
    assert(evaluate("T| F", pf, answer) == 0  &&  pf == "TF|"  &&  answer);
    assert(evaluate("T|", pf, answer) == 1);
    assert(evaluate("F F", pf, answer) == 1);
    assert(evaluate("TF", pf, answer) == 1);
    assert(evaluate("()", pf, answer) == 1);
    assert(evaluate("T(F|T)", pf, answer) == 1);
    assert(evaluate("T(&T)", pf, answer) == 1);
    assert(evaluate("(T&(F|F)", pf, answer) == 1);
    assert(evaluate("", pf, answer) == 1);
    assert(evaluate("F  |  !F & (T&F) ", pf, answer) == 0
            &&  pf == "FF!TF&&|"  &&  !answer);
    assert(evaluate(" F  ", pf, answer) == 0 &&  pf == "F"  &&  !answer);
    assert(evaluate("((T))", pf, answer) == 0 &&  pf == "T"  &&  answer);
    assert(evaluate("!!!!!F", pf, answer) == 0 && answer);
    assert(evaluate("(T|F)T", pf, answer) == 0);
    assert(evaluate("F)", pf, answer)== 1);
    cout << "Passed all tests" << endl;
}