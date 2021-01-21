// CStack.h - uma Stack simples de inteiros implementada com arrays

#include <iostream>
#include <string>

using namespace std;

class CStack { 
    int top, d_size, *items;
public:
    CStack(int size) { top = -1; d_size = size; items = new int[size]; }
    ~CStack() { delete []items;} 
    bool empty() const { return top==-1; } 
    int size() const { return top+1; } 
    void push(int elem) { 
        if(size()==d_size) cerr << "Stack Full!\n";
        else { top++; items[top] = elem; }
    }
    void pop() { 
        if(this->empty()) cerr << "Empty stack\n";
        else top--;
    }
    int peek() const { 
        if(this->empty()) cerr << "Empty stack\n";
        else return items[top];
        return 0;
    }
    string toStr() const {
        stringstream oss;
        for(int i = size()-1; i>=0; i--)
        	oss << items[i] << " ";
        return oss.str();
    }
    void print() const { 
        cout << "Stack with " << size() << " elements: ";
        for(int i = size()-1; i>=0; i--)
            cout << items[i] << " ";
        cout << endl;
    }
    void adicionaN(int n)
	{  //Grupo 2 a)
        int v = peek();
    	for (int i = 1; i <= n;i++) {
    	    push(v+i);
    	}
	}
	bool inverte4() 
	{   //Grupo 2 b)
    	if (size() < 4)
    	    return false;
    	int n;
    	CStack c1(4);
    	CStack c2(4);
    	for (int i = 0; i < 4; i++){
            n = peek();
            this->pop();
            c1.push(n);
    	}
        for (int i = 0; i < 4; i++){
            n = c1.peek();
            c1.pop();
            c2.push(n);
        }
        for (int i = 0; i < 4; i++){
            n = c2.peek();
            c2.pop();
            this->push(n);
        }
        return true;
	}	
}; 

