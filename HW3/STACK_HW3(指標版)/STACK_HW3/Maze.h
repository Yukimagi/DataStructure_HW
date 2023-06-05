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
template<class T> class Stack;

template<class T>//指標方法
class element {
private:
    T data;
    element<T>* next;//最上層的前一個

public:
    friend class Stack<T>;
    element() {
    };
    element(T d, element<T>* ptr) :data(d), next(ptr) {
        data = d;
        next = ptr;
    };

};

template<class T>
class Stack {
private:
    element<T>* stack;  //array for stack elements
    int up;            //array position of top element

public:
    Stack() :stack(nullptr), up(0)
    {
        stack = nullptr;
        up = 0;
    };
    ~Stack() {
        element<T>* now = stack;

        while (now != nullptr) {

            element<T>* temp = now;
            now = now->next;

            delete temp;

        }
    };

    bool IsEmpty() {

        if (stack == nullptr)
            return true;
        else
            return false;
    }

    void Push(T d) {

        stack = new element<T>(d, stack);
        up++;

    }

    void Pop() {

        if (stack != nullptr)
        {
            element<T>* temp = stack->next;
            delete stack;
            stack = temp;
            up--;
        }

    }

    T Top() {
        return stack->data;
    }

    int Size() {
        return up;
    }
};


#endif
