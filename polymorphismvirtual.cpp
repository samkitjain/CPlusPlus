#include<iostream>

using namespace std;

//
// Polygon class defines a virtual function (area). Square inherits polygon.
// Both Polygon and Square classes are called polymorphic classes. Declaring virtual
// function in parent class allows derived class to re-define (NOT compulsory) those 
// functions and use parent class pointers that point to derived class to access 
// these functions in derived class.
//
// In general we can redefine parent class functions in derived class but we cannot access
// redefined function in derived class with pointer of parent class !
//
//
class polygon1{

    public:
        polygon1(){}
        void setdim(int x, int y){this->x=x;this->y=y;}
	// Define area() as virtual function
	virtual int area();
    protected:
        int x;
	int y;
};

int polygon1::area(){
 return 0;
}

class square1:public polygon1{
    public:
        int area();
};

// Derived class can redefine virtual function area() of parent class
int square1::area(){
 return (this->x * this->y);
}




//
// Virtual functions can be made pure virtual functions by skipping function
// implementation or body in parent class. It can be decared as following:
// 
// virtual int area()=0;
//
// If a class defines atleast 1 pure virtual function, it is then called as abstract
// class. Abstract class cannot instantiate objects of itself ! But we can still access
// abstract class methods and variables by parent class pointer that is pointing to the
// derived class object.
//
//
// For a derived class it is optional to define virtual function of parent class. If 
// derived class doesn't define the virtual function then they also become abstract class
// and you can't create objects of that derived class !
//
//
// Virtual template methods are NOT allowed !
class polygon2{

    public:
        
        void setdim(int x, int y){this->x=x;this->y=y;}
	// Define area() as pure virtual function
	virtual int area() = 0;
	void printxy(){cout<<this->x<<endl;cout<<this->y<<endl;}
    protected:
        int x;
	int y;
};


class square2:public polygon2{
    public:
        int area();
};

// Derived class can redefine virtual function area() of parent class
int square2::area(){
 return (this->x * this->y);
}

class rectangle2:public polygon2{
};

class triangle2:public polygon2{
    public:
        int area();
};

int triangle2::area(){
 return (0.5* this->x * this->y);
}

///////////////////////////////////////////////
// Mixing Class Templates and Abstract classes
///////////////////////////////////////////////

template <typename T>
class polygon3{

    public:
        
        void setdim(int x, int y){this->x=x;this->y=y;}
	// Define area() as pure virtual function
	virtual int area() = 0;
	void printxy(){cout<<this->x<<endl;cout<<this->y<<endl;}
    protected:
        T x;
	T y;
	T z;
};


template <typename T>
class square3:public polygon3<T>{
    public:
        int area();
};

// Derived class can redefine virtual function area() of parent class
template <typename T>
int square3<T>::area(){
    return (this->x * this->y);
}


int main(void){

    polygon1 p;
    p.setdim(5,5);
    cout<<p.area()<<endl;


    square1 s; 
    polygon1 *p1 = &s;
    p1->setdim(6,6);
    cout<<p1->area()<<endl;


    square2 s2; 
    polygon2 *p2 = &s2;

    //  rectangle2 class didn't define the pure virtual function area2() of the polygon class
    //  hence it is also an abstract class and thus we can't create objects of the rectangle2 class !
    //    rectangle2 r2; 
    //    polygon2 *p3 = &r2;

    triangle2 t2; 
    polygon2 *p4 = &t2;


    //
    // Now we can use pointer to base class pointing to derived class to access parent class methods as 
    // well as derived class methods !
    //
    p2->setdim(7,7);
    p4->setdim(8,8);
    cout<<p2->area()<<endl;
    cout<<p4->area()<<endl;


    //
    // Class Template can have pure virtual function. But pure virtual function cannot be templated !
    //
    square3<int> s3; 
    polygon3<int>  *p3 = &s3;



    return 0;
}
