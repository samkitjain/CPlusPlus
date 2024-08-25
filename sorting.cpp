#include<iostream>
#include<vector>

using namespace std;


/*
 * Goal : Mergesort and Quicksort. Heapsort is covered in heap.cpp
 * 
 * Class design:
 *
 *     sortingutils : Container and related APIs
 *     sortingalgosI: Interface class which defines sorting API
 *     quicksort    : Inherits sortingalgoI,sortingutils. Defines quicksort related functions
 *     mergesort    : Inherits sortingalgoI,sortingutils. Defines mergesort related functions
 *
 */

/* Container and related API */
template <typename CONTAINER_T>
class sortingutils{
    public:
        sortingutils(vector<CONTAINER_T> vec):container(move(vec)){}
	void copyintocontainer(const vector<CONTAINER_T>&vec);
        void printcontainer();
        vector<CONTAINER_T> container;
    protected:
	void swap(CONTAINER_T &a, CONTAINER_T &b);
        void compare(){}
};

template <typename CONTAINER_T>
void sortingutils<CONTAINER_T>::copyintocontainer(const vector<CONTAINER_T>&vec){
    this->container = vec;
}

template <typename CONTAINER_T>
void sortingutils<CONTAINER_T>::printcontainer(){

    for(auto it=this->container.begin();it<this->container.end();it++)
        cout<<*it<<endl;
}

template <typename CONTAINER_T>
void sortingutils<CONTAINER_T>::swap(CONTAINER_T &a, CONTAINER_T &b){
    CONTAINER_T tmp = a;
    a = b;
    b = tmp;
}

/* Interface class for sorting API */
template <typename CONTAINER_T>
class sortingalgosI{
    public:
        virtual void sort()=0;
};

/* Quick Sort API */
template <typename CONTAINER_T>
class quicksort:public sortingutils<CONTAINER_T>, public sortingalgosI<CONTAINER_T>{ 
    public:
        quicksort(vector<CONTAINER_T> vec):sortingutils<CONTAINER_T>(vec){}
        void sort();
    private:
        void qsort(int lo, int hi);
        int partition(int i, int j);
};

template <typename CONTAINER_T>
void quicksort<CONTAINER_T>::sort(){
    this->qsort(0,this->container.size()-1);
}

template <typename CONTAINER_T>
void quicksort<CONTAINER_T>::qsort(int lo, int hi){
    if(lo<hi){
        int j = this->partition(lo, hi);
        this->qsort(lo,j);
        this->qsort(j+1,hi);
    }
}

template <typename CONTAINER_T>
int quicksort<CONTAINER_T>::partition(int lo, int hi){
    int i = lo;
    int j = hi;
    int pivot = this->container[lo];

    while(i<j){
        while(this->container[i]<=pivot && i<=hi)i++;
        while(this->container[j]>pivot && j>=lo)j--;
	if(i<j)
            this->swap(this->container[j],this->container[i]);
    }
    this->swap(this->container[j],this->container[lo]);
    return j;
}

/* Merge Sort API */
template <typename CONTAINER_T>
class mergesort:public sortingutils<CONTAINER_T>, public sortingalgosI<CONTAINER_T>{ 
    public: 
        void sort(){}
};

int main(void){

   vector<int> v = {10,9,8,7,6,5,4,3,2,1};
   quicksort<int> qs(v);
   cout<<"Array before sorting:"<<endl;
   qs.printcontainer();
   qs.sort();
   cout<<"Array after sorting:"<<endl;
   qs.printcontainer();

    return 0;
}
