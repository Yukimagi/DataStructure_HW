#ifndef MAZE_H
#define MAZE_H

template<class row, class col>//=struct items
class Items {

public:
    Items() {};
    Items(row r, col c) :row(r), column(c) {
        row = r;
        column = c;
    };

    row row;
    col column;
};
//題目要求 the template for the stack class
template<class T>
class Stack {
private:
    T* stack;//array for stack elements  
    int TheStackMaxSize;//capacity of stack array
    int top;//array position of top element
    int count;            

public:
    Stack(int max_size) :TheStackMaxSize(max_size)
    {
        stack = new T[TheStackMaxSize];
        top = -1;//; //initialize this value for emptiness check
    };
    ~Stack() {
        delete[]stack;
    };
    // stack是否滿
    bool IsFull()
    {
        if (top == TheStackMaxSize - 1) {
            return true;
        }
        else {
            return false;
        }
    }
    // stack是否空
    bool IsEmpty() {

        if (top == -1) {
            return true;
        }
        else {
            return false;
        }
    }
   //加入stack
    void Push(T x) {
        // add an item to the stack
        /*if (IsFull())
            stack_full( );
        else*/
        stack[++top] = x;
        count++;

    }

    void Pop() {
        /*
        // return the top element from the stack
        if (IsEmpty())
        {
            stack_empty( );
            return;
        }
        */
        if (!IsEmpty())
        {
            stack[top--].~T();//destructor for T;
            count--;
        }

    }

    T Top() {
        return stack[top];
    }

    int Size() {
        return count;
    }
};


#endif
