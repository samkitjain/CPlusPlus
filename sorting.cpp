#include<iostream>
#include<vector>

using namespace std;
#define HOARES_QUICKSORT_PARTITION 0

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
        void qsort_r(int lo, int hi);
        int partition(int i, int j, int p);
        int partition(int i, int j);
};

template <typename CONTAINER_T>
void quicksort<CONTAINER_T>::sort(){
    this->qsort_r(0,this->container.size()-1);
}

#if HOARES_QUICKSORT_PARTITION
template <typename CONTAINER_T>
void quicksort<CONTAINER_T>::qsort_r(int lo, int hi){
    if(lo<hi){
        int j = lo+(rand()%(hi-lo+1));
        j = this->partition(lo, hi, j);
        this->qsort_r(lo,j);
        this->qsort_r(j+1,hi);
    }
}

template <typename CONTAINER_T>
int quicksort<CONTAINER_T>::partition(int lo, int hi, int p){
    int i = lo-1;
    int j = hi+1;
    int pivot = this->container[p];

    while(true){
        while(this->container[++i]<pivot);
        while(this->container[--j]>pivot);
	if(i>=j)
	    break;
        this->swap(this->container[j],this->container[i]);
    }
    return j;
}

#else
template <typename CONTAINER_T>
void quicksort<CONTAINER_T>::qsort_r(int lo, int hi){
    if(lo<hi){
        int j = this->partition(lo, hi);
        this->qsort_r(lo,j-1);
        this->qsort_r(j+1,hi);
    }
}

template <typename CONTAINER_T>
int quicksort<CONTAINER_T>::partition(int lo, int hi){
    int i = lo;
    int j = hi;
    int pivot = this->container[lo];

    while(i<j){
        while(this->container[i]<=pivot && i<hi)i++;
        while(this->container[j]>pivot && j>lo)j--;
	if(i<j)
            this->swap(this->container[j],this->container[i]);
    }
    this->swap(this->container[j],this->container[lo]/*aka pivot*/);
    cout<<"New Pivot is "<<j<<endl;
    return j;
}
#endif

/* Merge Sort API */
template <typename CONTAINER_T>
class mergesort:public sortingutils<CONTAINER_T>, public sortingalgosI<CONTAINER_T>{ 
    public: 
        mergesort(vector<CONTAINER_T> vec):sortingutils<CONTAINER_T>(vec){}
        void sort();
    private:
        void msort(int lo, int hi);
        void merge(int lo, int mid, int hi);
};


template <typename CONTAINER_T>
void mergesort<CONTAINER_T>::sort(){
    msort(0,this->container.size()-1);
}

template <typename CONTAINER_T>
void mergesort<CONTAINER_T>::msort(int lo,int hi){
    if(lo<hi){
        int mid = (lo+hi)/2;
	msort(lo,mid);
	msort(mid+1,hi);
	merge(lo,mid,hi);
    }
}

template <typename CONTAINER_T>
void mergesort<CONTAINER_T>::merge(int lo, int mid, int hi){
    int m = mid-lo+1;
    int n = hi - mid;

    vector<CONTAINER_T> tmp(m+n);
   
    // Create 3 iterator i (for lo-mid) , j (for mid+1 , hi) and 
    // k (intermediate storage)
    int i = lo;
    int j = mid+1;
    int k = 0;

    // Advance pointers till i or j hasn't crossed over its bounds
    while (i<=mid && j<=hi){
        // Check if vec[i] >= vec[j] : If yes, copy vec[i] value into tmp[k] and advance i and k
        if(this->container[i]>= this->container[j]){ // For ascending order container[lo+i] < container[mid+j]
	    tmp[k++] = this->container[i++];
	}
        // Check if vec[i] < vec[j] : If yes, copy vec[j] value into tmp[k] and advance j and k
        else{
	    tmp[k++] = this->container[j++];
	}
    }

    // Copy remaining elements of 2 sub arrays of container into tmp
    for(;i<=mid;i++) tmp[k++] = this->container[i];
    for(;j<=hi;j++) tmp[k++] = this->container[j];

    // Copy tmp vector back into original vector
    for(int idx = 0 ; idx < tmp.size(); idx++)
        this->container[lo+idx] = tmp[idx];
}

int main(void){

   //vector<int> v = {10,9,8,7,6,5,4,3,2,1};
   //vector<int> v = {3,2,3,1,2,4,5,5,6};
   vector<int> v = {1,2,3,4,5,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,-5,-4,-3,-2,-1};
   //vector<int> v = {5,6,4,1,7,3,5,4,10,6,4,8,2,12,5,5,2,6,1,4};
   //vector<int> v = {1,1};
   quicksort<int> qs(v);
   cout<<"Array before sorting:"<<endl;
   qs.printcontainer();
   qs.sort();
   cout<<"Array after sorting:"<<endl;
   qs.printcontainer();

   vector<int> v1 = {1,2,3,4,5,6,7,8,9,10};
   mergesort<int> ms(v1);
   cout<<"Array before sorting:"<<endl;
   ms.printcontainer();
   ms.sort();
   cout<<"Array after sorting:"<<endl;
   ms.printcontainer();

   return 0;
}
