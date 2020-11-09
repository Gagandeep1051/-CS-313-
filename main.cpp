//
//  main.cpp
//  HW2
//
//  Created by GAGANDEEP SINGH  on 11/9/20.
//  Copyright © 2020 GAGANDEEP SINGH . All rights reserved.
//


#include <iostream>
#include <cstdlib>
using namespace std;

#ifndef H_StackType
#define H_StackType

#include <iostream>
#include <cassert>

#include "stackADT.h"


// QUESTION 1
//Header File: linkedStack.h

using namespace std;

//Definition of the node
template <class Type>
struct nodeType
{
    Type info;
    nodeType<Type> *link;
};

template <class Type>
class linkedStackType: public stackADT<Type>
{
public:
    const linkedStackType<Type>& operator=
    (const linkedStackType<Type>&);
    //Overload the assignment operator.
    
    bool isEmptyStack() const;
    //Function to determine whether the stack is empty.
    //Postcondition: Returns true if the stack is empty;
    //               otherwise returns false.
    
    bool isFullStack() const;
    //Function to determine whether the stack is full.
    //Postcondition: Returns false.
    
    void initializeStack();
    //Function to initialize the stack to an empty state.
    //Postcondition: The stack elements are removed;
    //               stackTop = nullptr;
    
    void push(const Type& newItem);
    //Function to add newItem to the stack.
    //Precondition: The stack exists and is not full.
    //Postcondition: The stack is changed and newItem
    //               is added to the top of the stack.
    
    Type top() const;
    //Function to return the top element of the stack.
    //Precondition: The stack exists and is not empty.
    //Postcondition: If the stack is empty, the program
    //               terminates; otherwise, the top
    //               element of the stack is returned.
    
    void pop();
    //Function to remove the top element of the stack.
    //Precondition: The stack exists and is not empty.
    //Postcondition: The stack is changed and the top
    //               element is removed from the stack.
    
    linkedStackType();
    //Default constructor
    //Postcondition: stackTop = nullptr;
    
    linkedStackType(const linkedStackType<Type>& otherStack);
    //Copy constructor
    
    ~linkedStackType();
    //Destructor
    //Postcondition: All the elements of the stack are
    //               removed from the stack.
    
private:
    nodeType<Type> *stackTop; //pointer to the stack
    
    void copyStack(const linkedStackType<Type>& otherStack);
    //Function to make a copy of otherStack.
    //Postcondition: A copy of otherStack is created and
    //               assigned to this stack.
};


//Default constructor
template <class Type>
linkedStackType<Type>::linkedStackType()
{
    stackTop = nullptr;
}

template <class Type>
bool linkedStackType<Type>::isEmptyStack() const
{
    return(stackTop == nullptr);
} //end isEmptyStack

template <class Type>
bool linkedStackType<Type>:: isFullStack() const
{
    return false;
} //end isFullStack

template <class Type>
void linkedStackType<Type>:: initializeStack()
{
    nodeType<Type> *temp; //pointer to delete the node
    
    while (stackTop != nullptr)  //while there are elements in
        //the stack
    {
        temp = stackTop;    //set temp to point to the
        //current node
        stackTop = stackTop->link;  //advance stackTop to the
        //next node
        delete temp;    //deallocate memory occupied by temp
    }
} //end initializeStack


template <class Type>
void linkedStackType<Type>::push(const Type& newElement)
{
    nodeType<Type> *newNode;  //pointer to create the new node
    
    newNode = new nodeType<Type>; //create the node
    
    newNode->info = newElement; //store newElement in the node
    newNode->link = stackTop; //insert newNode before stackTop
    stackTop = newNode;       //set stackTop to point to the
    //top node
} //end push


template <class Type>
Type linkedStackType<Type>::top() const
{
    assert(stackTop != nullptr); //if stack is empty,
    //terminate the program
    return stackTop->info;    //return the top element
}//end top

template <class Type>
void linkedStackType<Type>::pop()
{
    nodeType<Type> *temp;   //pointer to deallocate memory
    
    if (stackTop != nullptr)
    {
        temp = stackTop;  //set temp to point to the top node
        
        stackTop = stackTop->link;  //advance stackTop to the
        //next node
        delete temp;    //delete the top node
    }
    else
        cout << "Cannot remove from an empty stack." << endl;
}//end pop

template <class Type>
void linkedStackType<Type>::copyStack
(const linkedStackType<Type>& otherStack)
{
    nodeType<Type> *newNode, *current, *last;
    
    if (stackTop != nullptr) //if stack is nonempty, make it empty
        initializeStack();
    
    if (otherStack.stackTop == nullptr)
        stackTop = nullptr;
    else
    {
        current = otherStack.stackTop;  //set current to point
        //to the stack to be copied
        
        //copy the stackTop element of the stack
        stackTop = new nodeType<Type>;  //create the node
        
        stackTop->info = current->info; //copy the info
        stackTop->link = nullptr;  //set the link field of the
        //node to nullptr
        last = stackTop;        //set last to point to the node
        current = current->link;    //set current to point to
        //the next node
        
        //copy the remaining stack
        while (current != nullptr)
        {
            newNode = new nodeType<Type>;
            
            newNode->info = current->info;
            newNode->link = nullptr;
            last->link = newNode;
            last = newNode;
            current = current->link;
        }//end while
    }//end else
} //end copyStack

//copy constructor
template <class Type>
linkedStackType<Type>::linkedStackType(
                                       const linkedStackType<Type>& otherStack)
{
    stackTop = nullptr;
    copyStack(otherStack);
}//end copy constructor

//destructor
template <class Type>
linkedStackType<Type>::~linkedStackType()
{
    initializeStack();
}//end destructor

//overloading the assignment operator
template <class Type>
const linkedStackType<Type>& linkedStackType<Type>::operator=
(const linkedStackType<Type>& otherStack)
{
    if (this != &otherStack) //avoid self-copy
        copyStack(otherStack);
    
    return *this;
}//end operator=

#endif
//Postflix

//***********************************************************
// Author: D.S. Malik
//
// Program: Postfix Calculator
// This program evaluates postfix expressions.
//***********************************************************

#include <iostream>
#include <iomanip>
#include <fstream>
#include "mystack.h"

using namespace std;

void evaluateExpression(ifstream& inpF, ofstream& outF,
                        stackType<double>& stack,
                        char& ch, bool& isExpOk);
void evaluateOpr(ofstream& out, stackType<double>& stack,
                 char& ch, bool& isExpOk);
void discardExp(ifstream& in, ofstream& out, char& ch);
void printResult(ofstream& outF, stackType<double>& stack,
                 bool isExpOk);

int main()
{
    bool expressionOk;
    char ch;
    stackType<double> stack(100);
    ifstream infile;
    ofstream outfile;
    
    infile.open("RpnData.txt");
    
    if (!infile)
    {
        cout << "Cannot open the input file. "
        << "Program terminates!" << endl;
        return 1;
    }
    
    outfile.open("RpnOutput.txt");
    
    outfile << fixed << showpoint;
    outfile << setprecision(2);
    
    infile >> ch;
    while (infile)
    {
        stack.initializeStack();
        expressionOk = true;
        outfile << ch;
        
        evaluateExpression(infile, outfile, stack, ch,
                           expressionOk);
        printResult(outfile, stack, expressionOk);
        infile >> ch; //begin processing the next expression
    } //end while
    
    infile.close();
    outfile.close();
    
    return 0;
    
} //end main


void evaluateExpression(ifstream& inpF, ofstream& outF, stackType<double>& stack,char& ch, bool& isExpOk)
{
    double num;
    
    while (ch != '=')
    {
        switch (ch)
        {
            case '#':
                inpF >> num;
                outF << num << " ";
                if (!stack.isFullStack())
                    stack.push(num);
                else
                {
                    cout << "Stack overflow. "
                    << "Program terminates!" << endl;
                    exit(0);  //terminate the program
                }
                
                break;
            default:
                evaluateOpr(outF, stack, ch, isExpOk);
        }//end switch
        
        if (isExpOk) //if no error
        {
            inpF >> ch;
            outF << ch;
            
            if (ch != '#')
                outF << " ";
        }
        else
            discardExp(inpF, outF, ch);
    } //end while (!= '=')
} //end evaluateExpression


void evaluateOpr(ofstream& out, stackType<double>& stack,
                 char& ch, bool& isExpOk)
{
    double op1, op2;
    
    if (stack.isEmptyStack())
    {
        out << " (Not enough operands)";
        isExpOk = false;
    }
    else
    {
        op2 = stack.top();
        stack.pop();
        
        if (stack.isEmptyStack())
        {
            out << " (Not enough operands)";
            isExpOk = false;
        }
        else
        {
            op1 = stack.top();
            stack.pop();
            
            switch (ch)
            {
                case '+':
                    stack.push(op1 + op2);
                    break;
                case '-':
                    stack.push(op1 - op2);
                    break;
                case '*':
                    stack.push(op1 * op2);
                    break;
                case '/':
                    if (op2 != 0)
                        stack.push(op1 / op2);
                    else
                    {
                        out << " (Division by 0)";
                        isExpOk = false;
                    }
                    break;
                default:
                    out << " (Illegal operator)";
                    isExpOk = false;
            }//end switch
        } //end else
    } //end else
} //end evaluateOpr


void discardExp(ifstream& in, ofstream& out, char& ch)
{
    while (ch != '=')
    {
        in.get(ch);
        out << ch;
    }
} //end discardExp

void printResult(ofstream& outF, stackType<double>& stack,
                 bool isExpOk)
{
    double result;
    
    if (isExpOk) //if no error, print the result
    {
        if (!stack.isEmptyStack())
        {
            result = stack.top();
            stack.pop();
            
            if (stack.isEmptyStack())
                outF << result << endl;
            else
                outF << " (Error: Too many operands)" << endl;
        } //end if
        else
            outF << " (Error in the expression)" << endl;
    }
    else
        outF << " (Error in the expression)" << endl;
    
    outF << "_________________________________"
    << endl << endl;
} //end printResult

//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//QUESTION 2



// default capacity of the stack
#define SIZE 10

// Class for stack
class stack
{
    int *arr;
    int top;
    int capacity;
    
public:
    stack(int size = SIZE);
    void push(int);
    int pop();
    int peek();
    
    int size();
    bool isEmpty();
    bool isFull();
};

// Constructor to initialize stack
stack::stack(int size)
{
    arr = new int[size];
    capacity = size;
    top = -1;
}

// Utility function to add an element x in the stack
void stack::push(int x)
{
    
    if (isFull())
    {
        cout << "OverFlow\nProgram Terminated\n";
        exit(EXIT_FAILURE);
    }
    
    cout << "Inserting " << x << endl;
    arr[++top] = x;
}

// Utility function to pop top element from the stack
int stack::pop()
{
    
    if (isEmpty())
    {
        cout << "UnderFlow\nProgram Terminated\n";
        exit(EXIT_FAILURE);
    }
    
    cout << "Removing " << peek() << endl;
    
    // decrease stack size by 1 and (optionally) return the popped element
    return arr[top--];
}

// Utility function to return top element in a stack
int stack::peek()
{
    if (!isEmpty())
        return arr[top];
    else
        exit(EXIT_FAILURE);
}

// Utility function to return the size of the stack
int stack::size()
{
    return top + 1;
}

// Utility function to check if the stack is empty or not
bool stack::isEmpty()
{
    return top == -1;   // or return size() == 0;
}

// Utility function to check if the stack is full or not
bool stack::isFull()
{
    return top == capacity - 1;   // or return size() == capacity;
}


int main()
{
    stack pt(5);
    
    pt.push(3);
    pt.push(1);
    
    pt.pop();
    pt.pop();
    
    pt.push(2);
    
    cout << "Top element is: " << pt.peek() << endl;
    
    cout << "Stack size is " << pt.size() << endl;
    
    pt.pop();
    
    if (pt.isEmpty())
        cout << "Stack Is Empty\n";
    else
        cout << "Stack Is Not Empty\n";
    
    return 0;
}



