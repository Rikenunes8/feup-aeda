# include <iostream>
# include <stack>

using namespace std;

template <class T>
class StackExt {
    stack<T> pilha;
    stack<T> min;
public:
	StackExt() {};
	bool empty() const; 
	T &top();
	void pop();
	void push(const T & val);
	T &findMin();
};

// a alterar
template <class T> 
bool StackExt<T>::empty() const
{
	return pilha.empty();
}

//a alterar
template <class T> 
T& StackExt<T>::top()
{
    return pilha.top();
}

//a alterar
template <class T> 
void StackExt<T>::pop()
{
    pilha.pop();
    min.pop();
}

//a alterar
template <class T> 
void StackExt<T>::push(const T & val)
{
    if (pilha.empty())
        min.push(val);
    else
        if (pilha.top() < val)
            min.push(pilha.top());
        else
            min.push(val);
    pilha.push(val);
}

//a alterar
template <class T> 
T& StackExt<T>::findMin()
{
    return min.top();
}

