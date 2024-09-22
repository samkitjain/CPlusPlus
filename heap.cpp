#include<iostream>
#include<vector>

/* We can implement heap with vector of deq STL.
 * 
 * Vector  : Provides fast indexing as elements are allocated
             contiguously.
 * Dequeue : Supports operations at head and tail but indexing is
             comparatively NOT as fast as vector as elements are NOT
	     allocated in contiguous memory. 

 * 
 * If first element at heap sits in idx 0 then [CURRENT CODE]:
 * 
 * For any node i :
 * Parent node : i-1/2
 * Left child  : 2i+1
 * Right child : 2i+2
 *
 * If first element at heap sits in idx 1 then: 
 * 
 * For any node i :
 * Parent node : i/2
 * Left child  : 2i
 * Right child : 2i+1
 */

using namespace std;

template<class T>
class heap{

    public:
        heap(bool mode):max_priority(mode),occupancy(0){}
        heap(vector<T> vec, bool mode):space(vec),max_priority(mode),occupancy(vec.size()){}
	void printheap();
        void printheapstorage();
	void push(T val);
	T pop(void);
        void rise(int idx);
	void sink(int idx);
	void heapify();
	void heapsort(void);
	bool inline compare(heap<T> *h, int idx1, int idx2);
	void swap(int idx1, int idx2);

    private:
	// Members
	vector<T> space;
	bool max_priority; // Max heap if true else min heap
	int occupancy;
};

template <class T>
void heap<T>::printheap(){
    for(int i=0; i < this->occupancy;i++)
        cout<<"Element "<<i<<" is "<<this->space.at(i)<<endl;
}

template <class T>
void heap<T>::printheapstorage(){
    for(int i=0; i < this->space.size();i++)
        cout<<"Element "<<i<<" is "<<this->space.at(i)<<endl;
}

template <typename T>
void heap<T>::swap(int idx1, int idx2){
    // Swap parent and child
    T tmp = this->space.at(idx1);
    this->space.at(idx1) = this->space.at(idx2);
    this->space.at(idx2) = tmp;
}

template <typename T>
bool inline heap<T>::compare(heap<T>* h,int idx1, int idx2){
    return ((h->max_priority)? (h->space.at(idx1)>h->space.at(idx2)):(h->space.at(idx1)<h->space.at(idx2)));
}

template <class T>
void heap<T>::rise(int idx){

    int i = idx;
    while(i>0 && this->compare(this,i,(i-1)/2)){
	this->swap(i, (i-1)/2);
	i=(i-1)/2;
    }
}


//
// Worst Complexity is : O(log N)
// Best Complexity is  : O(1)
// 
// Add element to the leaf and make it rise (upwards)
//

template<class T>
void heap<T>::push(T val){
    this->space.push_back(val);
    this->occupancy++;
    this->rise(this->occupancy-1);
}


template <class T>
void heap<T>::sink(int idx){
    int i= idx;

    while( i < this->occupancy){
        // Find the biggest of 2 child nodes of parent node i
        if(2*i+1 < this->occupancy && (2*i+2) < this->occupancy ){
	    if(this->compare(this,i*2+1,i*2+2)){
	        if(this->compare(this,i*2+1,i)){
	            this->swap(i,2*i+1);
	            i = 2*i+1;
		}
		else
		    return;
	    }
	    else{
	        if(this->compare(this,i*2+2,i)){
	            this->swap(i,2*i+2);
	            i = 2*i+2;
		}
		else
		    return;
	    }
	}
	// Only one child is present
        else if(2*i+1 < this->occupancy || (2*i+2) < this->occupancy){
	    // Which child is present ? Left or right
	    int childid = (2*i+1 < this->occupancy) ? (2*i+1) : (2*i+2);
	    // Compare child and parent and swap them if required
	    if(this->compare(this,childid, i)){
	        this->swap(i,childid);
		// Update parent id
	        i = childid; 
	    }
	    else
                return;
	}
        else /* No children. Only node. Quick return */
            return;
    }
}

//
// Obtaining min/max element time complexity : O(1)
// But we have to rebalance heap. Time complexity for balancing is : O(logN)
//
// Overall Complexity is : O(logN)
// 
// Remove top. Copy last leaf element in the top and sink top to bottom.
//
template<class T>
T heap<T>::pop(){

    if(this->occupancy == 0)
        return -1;
    
    auto val = this->space.front();
    this->space.at(0) = this->space.back();
    this->space.pop_back();
    this->occupancy--;
    this->sink(0 /* first element of vector */);
    return val; 
}


// Worst Complexity is : O(N) if you use sink(). It becomes O(NlogN) if we use rise() approach.
template<typename T>
void heap<T>::heapify(){
    for(int i=this->occupancy;i>=0;i--)
       this->sink(i); 
}


//
// Worst Complexity is : O(log N) to add element to heap. So O(N logN) to create entire heap.
// Worst Complexity is : O(log N) to pop element from heap. So O(N logN) to remove all elements and add to sorted array
// 
// Avg and worst complexity is same for heapsort 
//
template<typename T>
void heap<T>::heapsort(){
    if(this->occupancy == 0)
        return; 

    while(this->occupancy){
        auto val = this->space.at(0);
        this->space.at(0) = this->space.at(this->occupancy-1);
        this->space.at(this->occupancy-1) = val;
        this->occupancy--;
        this->sink(0 /* first element of vector */);
    }
    return;
}


int main(void){

    heap<int> h(true);
    h.push(10);
    h.push(100);
    h.push(1000);
    h.push(1);
    h.printheap();
    cout<<h.pop()<<endl;
    cout<<h.pop()<<endl;
    cout<<h.pop()<<endl;
    cout<<h.pop()<<endl;

    vector<int> v = {8,16,24,32,40};
    heap<int> h2(v,true);
    h2.printheap();
    h2.heapify();
    h2.printheap();
    cout<<h2.pop()<<endl;
    cout<<h2.pop()<<endl;
    cout<<h2.pop()<<endl;
    cout<<h2.pop()<<endl;
    cout<<h2.pop()<<endl;

    vector<int> v1 = {8,7,9,2,11};

    // Sort array in decreaseing order (min heap).
    // Use max heap if increasing order is needed.
    heap<int> h3 = heap(v1,false/*min heap*/); 
    h3.heapify();
    h3.heapsort();
    h3.printheapstorage();

    return 0;
}
