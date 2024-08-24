/* Covers following concept:
 * 
 * 1. Static variables : All objects of the class defining static member variable share its value. Single copy for all and hence must
                         be defined outside the class separately (once).
 * 
 * 2.
 */

#include<iostream>

using namespace std;

class staticvarclass{

     public:
         static int staticvar;
         staticvarclass(){staticvar++;}
	 static void printobjcount(){
	     cout<<"staticvarclass obj count : "<<staticvar<<endl;
	 }
};

int staticvarclass::staticvar = 0;



class constfuntion{

    public:
        constfuntion(int v1, int v2):var1(v1),var2(v2){}
        const int var1;
        int var2;
	void printvar1 (void) const { cout << var1<<endl;}
	void printvar2 (void) const { cout << var2<<endl;}

};



template <class T>
class mygenericdatatype{
    public:
        void genericfunc();

    private:
        T value;
};



template <class T>
void mygenericdatatype<T>::genericfunc(){

    cout<<"My value is "<<this->value;
}



template <>
class mygenericdatatype<char>{
    public:
        void genericfunc();
	void upcase(void){cout<<"Special function for this template type"<<endl;}

    private:
        char value;
};



class specializedconstructor{

    public:
        specializedconstructor(int val):x(val){}
	// Copy constructor
        specializedconstructor(specializedconstructor& obj):x(obj.x){}
        int x;
};

int main(void){

    /////////////////
    // Static varialbe
    /////////////////
    staticvarclass sobj1;
    staticvarclass sobj2;
    staticvarclass::printobjcount();

    /////////////////
    // Const variable and member function
    /////////////////
    const constfuntion c(1,2);
    c.printvar1();
    c.printvar2();

    /////////////////
    // Template Specialization
    /////////////////
    mygenericdatatype<char> myT1;
    myT1.upcase();
    //mygenericdatatype<int> myT2;
    //myT2.upcase();                  // Errors out : error: ‘class mygenericdatatype<int>’ has no member named ‘upcase’


    /////////////////
    // Copy Constructor
    /////////////////
    specializedconstructor cnstr1(100);
    specializedconstructor cnstr2(cnstr1);
    cout<<cnstr2.x<<endl;
    
    return 0;
}
