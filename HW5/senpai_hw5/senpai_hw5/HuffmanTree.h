#include <iostream>
#include <algorithm>

// only use in test
#include <queue>
template<class T1, class T2>
class Pair{

    public:
        Pair(){;};
        Pair(T1 f,T2 s):first(f),second(s){;};
        T1 first;
        T2 second;

        bool operator>(const Pair &b) const
        {
            if(first > b.first)
            return true;
            else if(first==b.first&&second>b.second)
            return true;
            else
            return false;

        }

        bool operator<(const Pair &b) const
        {
            if(first < b.first)
            return true;
            else if(first==b.first&&second<b.second)
            return true;
            else
            return false;

        }

        bool operator==(const Pair &b) const
        {
            
            if(first==b.first&&second==b.second)
            return true;
            else
            return false;

        }

        void operator=(const Pair &b) 
        {
            
            first=b.first;
            second=b.second;

        }
        
};


class HuffmanTree;
class HuffmanNode{
    friend class HuffmanTree;
    public:
        //HuffmanNode() {};
        HuffmanNode(int n):ch(char(0)),freq(n),left(nullptr),right(nullptr){;};
        HuffmanNode(char c,int n):ch(c),freq(n),left(nullptr),right(nullptr){;};
    private:
        char ch;
        int freq;
        HuffmanNode*left;
        HuffmanNode*right;


};


//test
template<class T>
class Queue{
private:
    template<class T1>
    class QueueNode {
        friend class Queue;
    public:
        QueueNode(T1 d) :data(d), next(nullptr) { ; };
    private:
        QueueNode* next;
        T1 data;
    };
    QueueNode<T>* first;
    QueueNode<T>* last;
    
    public:

        Queue():first(nullptr),last(nullptr){;};

        void push(T d){

            if (first == nullptr) {
                last = first=new QueueNode<T>(d);
                //QueueNode<T> first = new QueueNode<T>(d);
            }
            else
                last->next=new QueueNode<T>(d),last=last->next;

        }   

        T front(){

            return first->data;
        }

        void pop(){

            if(first==nullptr)
                return;
            
            if(first==last)
            {
                delete first;
                first=last=nullptr;
                return;
            }
            
            QueueNode<T> *tmp=first;
            first=first->next;
            delete tmp;

            return;

        }

        bool empty(){

            if(first==nullptr)
                return true;
            else
                return false;

        }

};

class HuffmanTree{

    public:
        HuffmanTree(Pair<int,char>character_freq[],int char_num):root(nullptr){

            // Pair<int,char> character_freq[char_num];

            // for(int i=0;i<char_num;i++)
            // character_freq[i]=c[i];
            
            //n * log(n)
            std::sort(character_freq,character_freq+char_num,std::greater<Pair<int,char> >());


            HuffmanNode *current_tree[100];//

            for(int i=0;i<char_num;i++)
                current_tree[i]=new HuffmanNode(character_freq[i].second,character_freq[i].first);

            while(char_num!=1)
            {
                
                HuffmanNode *combine_node=new HuffmanNode(current_tree[char_num-1]->freq+current_tree[char_num-2]->freq);
                combine_node->left=current_tree[char_num-1];
                combine_node->right=current_tree[char_num-2];
                char_num--;

                //log(n)
                int pos=lower_bound(current_tree,combine_node->freq,char_num);
                
                for(int i=char_num-1;i>=pos;i--)
                    current_tree[i]=current_tree[i-1];

                current_tree[pos]=combine_node;

                
            }

            root=current_tree[0];
            
            generate_code(root,"");
        }
        //test
        ~HuffmanTree(){
            Queue<HuffmanNode*>qe;
            qe.push(root);

            while(!qe.empty()){
                HuffmanNode* tmp= qe.front();
                qe.pop();

                if(tmp->left!=nullptr)
                    qe.push(tmp->left);
                if(tmp->right!=nullptr)
                    qe.push(tmp->right);

                
                delete tmp;
            }
            
            // std::cout<<"!";
        }

        //test 
        void traversal()
        {
            Queue<Pair<HuffmanNode*,int> >qe;
            Pair<HuffmanNode*,int> tmp(root,0);

            qe.push(tmp);
            int current_level=0;

            while(!qe.empty())
            {
                tmp=qe.front();
                qe.pop();

                if(tmp.first->left!=nullptr)
                qe.push(Pair<HuffmanNode*,int>(tmp.first->left,tmp.second+1));

                if(tmp.first->right!=nullptr)
                qe.push(Pair<HuffmanNode*,int>(tmp.first->right,tmp.second+1));

                if(tmp.second!=current_level)
                {
                    std::cout<<"\n";
                    current_level=tmp.second;
                }

                std::cout<<"( "<<tmp.first->ch<<" , "<<tmp.first->freq<<" ) ";

            }
            std::cout<<std::endl;

        }

        void print_code()
        {
            for(int i=0;i<256;i++)
            {
                if(HuffmanTable[i]!="")
                {
                    std::cout<<char(i)<<" "<<HuffmanTable[i]<<std::endl;
                }
            }
        }

        std::string encode(std::string s)
        {
            std::string result="";
            for(int i=0;i<s.size();i++)
            {
                result+=HuffmanTable[s[i]-0];
            }

            return result;
        }

    private:
        HuffmanNode* root;
        std::string HuffmanTable[256]={""};

        int lower_bound(HuffmanNode *current_tree[],int new_freq,int tree_num)
        {
            int st=0,ed=tree_num-1;
            int mid;

            while(st<=ed)
            {
                mid=(ed+st)/2;
                // std::cout<<st<<" "<<mid<<" "<<ed<<std::endl;
                if(current_tree[mid]->freq>new_freq)
                st=mid+1,mid++;
                else
                ed=mid-1;

            }

            return mid;


        }

        void generate_code(HuffmanNode *current,std::string current_code)
        {

            if(current->ch==char(0))
            {
                generate_code(current->left,current_code+"0");
                generate_code(current->right,current_code+"1");
            }
            else
            {
                HuffmanTable[current->ch-0]=current_code;     
            }
        }


};


