/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmardi <mmardi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 15:10:18 by mmardi            #+#    #+#             */
/*   Updated: 2023/03/22 16:57:23 by mmardi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "RPN.hpp"

RPN::RPN() {};

bool RPN::checkArguments(std::string arg) {
    if (arg.size() == 0)
        return true;
    for (size_t i = 0; i < arg.size(); i++)
    {
        if(!isdigit(arg[i]) && arg[i] != '*' &&  arg[i] != '+'  &&  arg[i] != '-' &&  arg[i] != '/' && arg[i] != ' ')
            return true;
    }
    
    return false;   
}

void RPN::operation() {
    while(!arguments.empty()) {
        if (isdigit(arguments.top()))
            values.push(arguments.top() - '0');
        else if (arguments.top() == '+' && values.size() >= 2) {
            int a = values.top();
            values.pop();
            int b = values.top();
            values.pop();
            values.push(b + a);
        }
        else if (arguments.top() == '-' && values.size() >= 2) {
            int a = values.top();
            values.pop();
            int b = values.top();
            values.pop();
            values.push(b - a);
        }
        else if (arguments.top() == '/' && values.size() >= 2)  {
            int a = values.top();
            values.pop();
            int b = values.top();
            values.pop();
            if (a == 0)
                throw std::runtime_error("ERROR: can't devide on 0.");
            values.push(b / a);
        }
        else if (arguments.top() == '*' && values.size() >= 2) {
            int a = values.top();
            values.pop();
            int b = values.top();
            values.pop();
            values.push(b * a);
        }
        else {
            throw std::runtime_error("ERROR: bad input.");
        }
        arguments.pop();
    }
    if (values.size() != 1)
        throw std::runtime_error("ERROR: bad input.");
    std::cout << values.top() << std::endl;
}

void RPN::insertArguments(std::string arg) {
 
    char *s = strtok((char *)arg.c_str(), " ");
    std::stack<std::string> tmp;
    while(s) {
        tmp.push(s);
        s = strtok(NULL, " ");
    }

    while(tmp.size() > 0) {
        if (tmp.top().size() > 1)
            throw std::runtime_error("ERROR: bad input.");
        arguments.push(tmp.top()[0]);
        tmp.pop();
    }
    operation();
}

RPN::RPN(int ac, char **av) {
    if (ac != 2)
        throw std::runtime_error("ERROR: too few or too many arguemnts.");
    if (checkArguments(av[1]))
        throw std::runtime_error("ERROR: bad input.");
    insertArguments(av[1]);
}

RPN::RPN(const RPN& x) {
   *this = x;
}

RPN& RPN::operator = (const RPN &x)
{
   arguments = x.arguments;
   values = x.values;
   return  *this;
}

RPN::~RPN(){};