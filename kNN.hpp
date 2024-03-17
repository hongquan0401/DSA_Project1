#include "main.hpp"

/* TODO: Please design your data structure carefully so that you can work with the given dataset
 *       in this assignment. The below structures are just some suggestions.
 */
template<typename T>
class ArrList;

template<typename T>
class SLinkedList;

template<typename T>
class List {
public:
    virtual ~List() = default;
    virtual void push_back(T value) = 0;
    virtual void push_front(T value) = 0;
    virtual void insert(int index, T value) = 0;
    virtual void remove(int index) = 0;
    virtual T& get(int index) const = 0;
    virtual int length() const = 0 ;
    virtual void clear() = 0;
    virtual void print() const = 0;
    virtual void print(int start_idx, int end_idx) const = 0;
    virtual void reverse() = 0;
    //virtual void traverse(std::function <void (T &)> op) = 0;
    // virtual ArrList<T>* _to_Array() = 0;
    // virtual SLinkedList<T>* _to_SLinkedList() = 0;
};

// class Dataset {
// private:
//     List<List<int>*>* data; // data->length() = rows
//     List<string>* label; //label->length() = data->get(i)->length() = cols
//     //You may need to define more
// public:
//     Dataset(): data(new SLinkedList<List<int>*>), label(new SLinkedList<string>) {};
//     ~Dataset() {
//         for (int i = 0; i < data->length(); i++){
//             data->get(i)->clear();
//         }
//         data->clear();
//         label->clear();
//     };
//     Dataset(const Dataset& other) {
//         data = new SLinkedList<List<int>*>();
//         for (int i = 0; i < other.data->length(); i++){
//             data->push_back(new SLinkedList<int>(other.data->get(i)));
//         }
//         label = new SLinkedList<string>(other.label);
//     };
//     Dataset& operator=(const Dataset& other);
//     bool loadFromCSV(const char* fileName);
//     void printHead(int nRows = 5, int nCols = 5) const;
//     void printTail(int nRows = 5, int nCols = 5) const;
//     void getShape(int& nRows, int& nCols) const {
//         nRows = data->length();
//         nCols = label->length();
//     };
//     void columns() const { label->print(); };
//     bool drop(int axis = 0, int index = 0, std::string columns = "");
//     Dataset extract(int startRow = 0, int endRow = -1, int startCol = 0, int endCol = -1) const;
// };

// class kNN {
// private:
//     int k;
//     //You may need to define more
// public:
//     kNN(int k = 5);
//     void fit(const Dataset& X_train, const Dataset& y_train);
//     Dataset predict(const Dataset& X_test);
//     double score(const Dataset& y_test, const Dataset& y_pred);
// };

// void train_test_split(Dataset& X, Dataset& y, double test_size, 
//                         Dataset& X_train, Dataset& X_test, Dataset& y_train, Dataset& y_test);

// Please add more or modify as needed
template<typename T>
class SLinkedList : public List<T> {
    public:
        class Node;
    protected: 
        Node* head;
        int count;
    public:
        SLinkedList(): count(0), head(nullptr) {};
        SLinkedList(List<T> *other):head(nullptr), count(0) {
            Node** pp = &head;
            //other->traverse([&pp](T& val) {*pp = new Node(val,nullptr); pp = &((*pp)->next);});
            count = other->length();
            int i = 0;
            while (i < count)
            {
                *pp = new Node(other->get(i),nullptr);
                pp = &((*pp)->next);
                i++;
            }
        };
        ~SLinkedList() { clear(); };
        void push_back(T value){
            insert(count,value);
        };
        void push_front(T value) {
            insert(0,value);
        };
        void insert(int index, T value) {
            if (index < 0) index = 0;
            else if (index > count) index = count;
            Node** pp = &head;
            while (index)
            {
                pp = &((*pp)->next);
                index--;
            }
            *pp = new Node(value,*pp);
            count++;
        };
        void remove(int index) {
            if (index < 0 || index >= count) return;
            Node** pp = &head;
            while (index)
            {
                pp = &((*pp)->next);
                index--;
            }
            Node* p = *pp;
            *pp = p->next;
            delete p;
            count--;
        };
        T& get(int index) const {
            if (index < 0 || index >= count) throw "Invalid index";
            Node* p = head;
            while (index){ p = p->next; index--;};
            return p->data;
        };
        int length() const {return count;};
        void clear() {
            while (head)
            {
                Node* p = head;
                head = head->next;
                delete p;
            }
            count = 0;
        };
        void print() const {
            // traverse([](T & val)->void{cout << val << " ";});
            if (count == 0) return;
            Node* tmp = head;
            while (tmp->next)
            {
                cout << tmp->data << " ";
                tmp = tmp->next;
            }
            cout << tmp->data;
        };
        void print(int start_idx, int end_idx) const {
            if (count == 0) return;
            if (start_idx > end_idx) return;
            if (start_idx < 0) start_idx = 0;
            if (end_idx > count) end_idx = count - 1;
            int idx = start_idx;
            while (idx < end_idx) {
                cout << this->get(idx++) << " ";
            }
            cout << this->get(idx);
        };
        void reverse() {
            Node* pNL = 0;
            while (head)
            {
                Node* p = head;
                head = p->next;
                p->next = pNL;
                pNL = p;
            }
            head = pNL;
        };
        // void traverse(std::function<void (T &)> op){
        //     for (Node* p = head; p; p = p->next) op(p->data);            
        // }
        // ArrList<T>* _to_Array() {
        //     ArrList<T>* p = new ArrList<T>(0,count);
        //     for (int i = 0; i < count; i++){
        //         p->push_back(this->get(i));
        //     }
        //     return p;
        // };
        // SLinkedList<T>* _to_SLinkedList() {
        //     SLinkedList<int>* p = new SLinkedList();
        //     for (int i = 0; i < count; i++)
        //     {
        //         p->push_back(this->get(i));
        //     }
        //     return p;
        // };
    public:
        class Node
        {
        private:
            /* data */
            T data;
            Node* next;
            friend class SLinkedList<T>;
        public:
            Node(/* args */) : next(nullptr) {};
            Node(T data, Node* next = nullptr) : data(data), next(next) {};
        };
};

template<typename T>
class ArrList : public List<T>
{
private:
    T* pD;
    int count, cap;
public:
    ArrList (): count(0), cap(5) { pD = new T[5]; };
    ArrList (int count = 0, int cap = 5) { this->count = count; this->cap = cap; pD = new T[cap];}
    ArrList (List<T> *other) {
        count = other->length();
        cap = count * 1.5;
        pD = new T[cap];
        for (int i = 0; i < other->length(); i++){
            pD[i] = other->get(i);
        }
    };
    ~ArrList() { clear(); };
    void resize(int n) {
        if (n >= cap){
            cap*= 1.5;
            T* temp = new T[cap];
            for ( int i = 0; i < count; i++)
            {
                temp[i] = pD[i];
            }
            delete[] pD;
            pD = temp;
            temp = nullptr;
        }
    };
    void push_back(T value) {
        if (isFull())
        {
            resize(count);
        }
        pD[count] = value;
        count++;
    };
    bool isFull() { return count == cap; };
    void push_front(T value) {
        if (isFull())
        {
            resize(count);
        }
        count++;
        for (int i = count; i > 0; i--)
        {
            pD[i] = pD[i-1];
        }
        pD[0] = value;
    };
    void insert(int index, T value) {
        if (index < 0 || index > count)
        {
            return;
        }
        if (index == 0)
        {
            push_front(value);
            return;
        }
        if (index == count) {
            push_back(value);
            return;
        }
        if (isFull())
        {
            resize(count);
        }
        count++;
        for (int i = count; i > index; i--){
            pD[i] = pD[i-1];
        }
        pD[index] = value;
    };
    void remove(int index) {
        if (index < 0 || index >= count) return;
        for (int i = index; i < count - 1; i++)
        pD[i] = pD[i + 1];
        count--;
    };
    T& get(int index) const {
        return pD[index];
    };
    int length() const { return count; } ;
    void clear() {
        if (count != 0){
            delete[] pD;
            pD = new T[5];
            count = 0;
            cap = 5;
        }
    };
    void print() const {
        if (count == 0) return;
        int i = 0;
        for (i; i < count - 1; i++)
        {
            cout << pD[i] << " ";
        }
        cout << pD[i];
    };
    void print(int start_idx, int end_idx) const {
        if (count == 0) return;
        if (start_idx > end_idx) return;
        if (start_idx < 0) start_idx = 0;
        if (end_idx > count) end_idx = count - 1;
        for (int i = start_idx; i < end_idx; i++)
        {
            cout << pD[i] << " ";
        }
        cout << pD[end_idx];
    }
    void reverse() {
        T* pL = pD, *pR = pD + count - 1;
        while (pL < pR)
        {
            std::swap(*pL,*pR);
            pL++;
            pR--;
        }
    };
    // ArrList<T>* _to_Array() {
    //     ArrList<T>* p = new ArrList<T>(0,cap);
    //     for (int i = 0; i < count; i++)
    //     {
    //         p[i] = pD[i];
    //     }
    //     return p;
    // };
    // SLinkedList<T>* _to_SLinkedList() {
    //     SLinkedList<T>* p = new SLinkedList<T>();
    //     for(int i = 0; i < count; i++) {
    //         p->push_back(this->get(i));
    //     }
    //     return p;
    // };
};
