#include<iostream>
#include<memory>
#include<cassert>
using namespace std;


class Person
{
public:
    string name;
    int age;

    Person();
    ~Person();
};

Person::Person()
{
    name = "hhh";
    age = 24;
    cout << "construction func" << endl;
}

Person::~Person()
{
    cout <<"de-construc func"<< endl;
}


template<class T>
class smart_pointer
{
private:
    T* _ptr;
    size_t* _count;
public:
    smart_pointer(T* p = nullptr)
{
    _ptr = p;
    if(p == nullptr){
        _count = new size_t{0};
    }
    else{
        _count = new size_t{1};
    }
}
    smart_pointer(smart_pointer& sp){
        _ptr = sp._ptr;
        _count = sp._count;
        (*_count)++;
    }

    T* operator->(){
        assert(_ptr != nullptr);
        return _ptr;
    }
    T& operator*(){
        assert(_ptr != nullptr);
        return *_ptr;
    }

    smart_pointer& operator=(smart_pointer& sp){
        if(sp._ptr == _ptr){
            return *this;
        }

        (*_count)--;
        if((*_count) == 0){
            delete _ptr;
            delete _count;
            cout << "the object that pointer point to has been released" << endl;
        }

        _ptr = sp._ptr;
        _count = sp._count;
        (*_count)++;

        return *this;
    }

    size_t use_count(){
        return *_count;
    }
    ~smart_pointer(){
        if(_ptr == nullptr){
            cout << "pointer is nullptr";
            delete _count;
            return; 
        }

        (*_count)--;
        if((*_count) == 0){
            delete _ptr;
            delete _count;
            cout << "the object that pointer point to has been released" << endl;
        }
    }
};


int main(){
    smart_pointer<Person> sp(new Person());
    cout<<sp->name<<endl;
    cout << (*sp).age << endl;
    cout << sp.use_count() << endl;

    smart_pointer<Person> sp2(sp);       // copy construction
    cout << sp.use_count() << endl;

    smart_pointer<Person> sp3(new Person());
    sp3 = sp;                            // assignment
    cout << sp3.use_count() << endl;


    return 0;
}