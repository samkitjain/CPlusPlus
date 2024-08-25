#include <iostream>

using namespace std;


class classA{

    public:
        classA(int x,int y, int z):x(x),y(y),z(z){}

	// variables
	int x;

	// methods
	friend void printprivateprotected(const classA& p);
	friend class classB;

    private:
        int y;
    protected:
        int z;

};

void printprivateprotected(const classA& p){
    cout<<p.y<<endl;
    cout<<p.z<<endl;
}


class classB{
    public:
        classB(){}
        void printclassAvars(classA &obj);
};

void classB::printclassAvars(classA &obj){

   cout<<obj.x<<endl; 
   cout<<obj.y<<endl; 
   cout<<obj.z<<endl; 
}


int main(void){
    
    classA p1(10,100,1000);
    cout<<p1.x<<endl;
    printprivateprotected(p1);         // Friend function can be directly invoked. But a class object must be passsed to it
    //cout<<p1.y<<endl; // y is private and hence it cannot be accessed outside the class context
    //cout<<p1.z<<endl; // z is protected and hence it cannot be accessed outside the class context

    classB p2;
    p2.printclassAvars(p1);

    return 0;
}
