//
// Created by ZhouP on 4/5/2019.
//

#ifndef CPPSANDBOX_VALIDPARENTHESIS_H
#define CPPSANDBOX_VALIDPARENTHESIS_H

bool isValid(string s) {
    std::stack<char> ss;
    for (char c : s)
    {
        if (c=='(' || c=='[' || c=='{')
            ss.push(c);
        else if (c==')')
        {
            if (!ss.empty()&&ss.top()=='(')
                ss.pop();
            else
                return false;
        }
        else if (c==']')
        {
            if (!ss.empty()&&ss.top()=='[')
                ss.pop();
            else
                return false;
        }
        else if (c=='}')
        {
            if (!ss.empty()&&ss.top()=='{')
                ss.pop();
            else
                return false;
        }
        else
        {
            return false;
        }

    }

    return ss.empty();
}

void test_validParenthesis ()
{
    std::string s = "()";
    std::cout << std::boolalpha << isValid(s) << std::endl;
}

#endif //CPPSANDBOX_VALIDPARENTHESIS_H
