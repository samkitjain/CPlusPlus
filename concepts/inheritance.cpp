#include<iostream>

using namespace std;

class relative{

};

class parent{
    public:
        parent(int x, int y, int z):x(x),y(y),z(z){}
	int x;
    protected:
	int y;
    private:
	int z;

};

class child1 : public parent, public relative {
    public:
        child1(int a, int x, int y, int z): parent(x,y,z), a(a){}
	int a;
	void printprivateprotected();
};

void child1::printprivateprotected(){
    // print protected parent member
    cout<<this->y<<endl;
    // print private parent member
    //cout<<this->z<<endl; // ERROR: Private member of base class is NOT inherited
}

class child2 : protected parent, protected relative {
    public:
        child2(int a, int x, int y, int z): parent(x,y,z), a(a){}
	int a;
	void printprivateprotected();
};

void child2::printprivateprotected(){
    // print protected parent member
    cout<<this->x<<endl;
    // print protected parent member
    cout<<this->y<<endl;
    // print private parent member
    //cout<<this->z<<endl; // ERROR: Private member of base class is NOT inherited
}

class child3 : private parent, private relative {
    public:
        child3(int a, int x, int y, int z): parent(x,y,z), a(a){}
	int a;
	void printprivateprotected();
};

void child3::printprivateprotected(){
    // print private parent member
    cout<<this->x<<endl;
    // print private parent member
    cout<<this->x<<endl;
    // print private parent member
    //cout<<this->z<<endl; // ERROR: Private member of base class is NOT inherited
}

int main(void){

    cout<<"Printing child1 members"<<endl;
    child1 c1(1,2,3,4);
    cout<<c1.a<<endl;
    cout<<c1.x<<endl; // x is loaded from parent class and has public access
    // cout<<c1.y<<endl; // ERROR : y is loaded from parent class and has protected access. Hence, can't be accessed outside scope
    // cout<<c1.z<<endl; // ERROR : z is loaded from parent class and has private access. Hence, can't be accessed outside scope
    c1.printprivateprotected();
    


    cout<<"Printing child2 members"<<endl;
    child2 c2(10,20,30,40);
    cout<<c2.a<<endl;
    //cout<<c2.x<<endl; // ERROR : x is loaded from parent class and has protected access. Hence, can't be accessed outside scope
    //cout<<c2.y<<endl; // ERROR : y is loaded from parent class and has protected access. Hence, can't be accessed outside scope
    //cout<<c2.z<<endl; // ERROR : z is loaded from parent class and has private access. Hence, can't be accessed outside scope
    c2.printprivateprotected();
 



    cout<<"Printing child3 members"<<endl;
    child3 c3(100,200,300,400);
    cout<<c3.a<<endl;
    //cout<<c3.x<<endl; // ERROR : x is loaded from parent class and has privated access. Hence, can't be accessed outside scope
    //cout<<c3.y<<endl; // ERROR : y is loaded from parent class and has private access. Hence, can't be accessed outside scope
    //cout<<c3.z<<endl; // ERROR : z is loaded from parent class and has privated access. Hence, can't be accessed outside scope
    c3.printprivateprotected();
    return 0;
}
