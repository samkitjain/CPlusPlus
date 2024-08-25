#include<iostream>

using namespace std;


template <class T>
class vec{ 

    public:
        vec():x(0),y(0){}
        vec(T xcoord,T ycoord):x(xcoord),y(ycoord){}
	void printvec();
        vec<T> operator+(const vec<T> &v);
	vec<T> operator-(const vec<T> &v);

    private:
        T x;
	T y;

};

template<class T>
void vec<T>::printvec(){

    cout<<"Vector is : x = "<<this->x<<" y = "<<this->y<<endl;
}


template<class T>
vec<T> vec<T>::operator+(const vec<T> &v){
   vec<T> result;
   result.x = this->x + v.x;
   result.y = this->y + v.y;
   return result;
}

template<class T>
vec<T> vec<T>::operator-(const vec<T> &v){
    vec<T> result;

    result.x = this->x - v.x;
    result.y = this->y - v.y;
    return result;
}


int main(void){

    vec<int> v1(2,3);
    vec<int> v2(4,6);
    vec<int> v3 = v1 + v2;
    vec<int> v4 = v2 - v1;
    v3.printvec();
    v4.printvec();

    return 0;
}
