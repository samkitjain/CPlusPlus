//
// Diamond problem: When we have diamond inheritance, 
//         A
//      B     C
//         D
// Object creation for D derived class, result in duplicate object
// creation for super parent base class A.
//
// This is solved by making class A as virtual
//
#include<iostream>

using namespace std;

/////////////////////////////////////
// Example showcasing diamond problem
/////////////////////////////////////
class mammal{
    public:
        mammal(){cout<<"mammal obj constructor called"<<endl;}
        void sound(){cout<<"No sound"<<endl;}
//    void color()=0;
};

class donkey: public mammal{
    public:
        donkey(){cout<<"donkey obj constructor called"<<endl;}
        void sound(){cout<<"dhanchu"<<endl;}
};

class zebra: public mammal{
    public:
        zebra(){cout<<"zebra obj constructor called"<<endl;}
        void sound(){cout<<"hehehe"<<endl;}
};

class zonkey: public donkey,public zebra{
    public:
        zonkey(){cout<<"zonkey obj constructor called"<<endl;}
        void sound(){cout<<"Unknown"<<endl;}
};

/////////////////////////////////////////////////////////
// Solution for diamond problem. Mark A as virtual class
// during inheritance. This results in creation of 
// single object creation for for super base class A or 
// mammal and it is shared by all classes inheriting it.
/////////////////////////////////////////////////////////

class mammal1{
    public:
        mammal1(){cout<<"mammal obj default constructor called"<<endl;}
        mammal1(int x){cout<<"mammal obj parametrized constructor called"<<endl;}
        void sound(){cout<<"No sound"<<endl;}
};

class donkey1: virtual public mammal1{
    public:
        donkey1(){cout<<"donkey obj default constructor called"<<endl;}
        donkey1(int x):mammal1(x){cout<<"donkey obj parametrized constructor called"<<endl;}
        void sound(){cout<<"dhanchu"<<endl;}
};

class zebra1: virtual public mammal1{
    public:
        zebra1(){cout<<"zebra obj default constructor called"<<endl;}
        zebra1(int x):mammal1(x){cout<<"zebra obj parametrized constructor called"<<endl;}
        void sound(){cout<<"hehehe"<<endl;}
};

class zonkey1: public donkey1,public zebra1{
    public:
        zonkey1(){cout<<"zonkey obj constructor called"<<endl;}
        zonkey1(int x):donkey1(x),zebra1(x){cout<<"zonkey obj parametrized constructor called"<<endl;}
        void sound(){cout<<"Unknown"<<endl;}
};

int main(void){
    // Suffers from diamond problem
    zonkey z;

    // How to access members of other functions.
    z.sound();
    z.donkey::sound();
    z.zebra::sound();
    
    //
    // NOT ALLOWED: D derived class can only access its immediate parents (B,C).
    // It CANNOT access its super parent (A) directly.
    
    //z.mammal::sound();

    

    // Only case when derived derived (D)
    // class calls super base class (A) is when A is made virtual class ! Hence when we
    // create zonkey object, zonkey is responsible for instantiating one copy of mammal 
    // class and then create 1 copy each of donkey and zebra class. Above example proves that
    // D creates A object as its default constructor is called (we did not specify parametrized
    // constructor in D's initialization list, where as both B and C call A's parametrized
    // constructor !
    //
    // We can make D call A's parametrized constructor by calling A's parametrized constructor
    // in D's initialization list:
    // 
    //
    // zonkey1(int x):mammal(x), donkey1(x),zebra1(x){cout<<"zonkey obj parametrized constructor called"<<endl;}
    //



////////////////////////////////////////////


    // Doesnt' have diamond problem
    zonkey1 z1(1);

    zebra1 *ze1;
    donkey1 *do1;
    mammal1 *ma1;
    ze1 = &z1;
    do1 = &z1;
    ma1 = &z1;

    z1.sound();
    ze1->sound();
    do1->sound();
    ma1->sound();

    return 0;
}
