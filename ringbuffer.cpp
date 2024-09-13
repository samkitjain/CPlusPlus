/*
 * Ring Buffer  a.k.a. Circular Queue a.k.a Circular Buffer
 *
 * By default :
 *              Insert at rear
 *              Remove from front
 * 
 * Both front and rear grow in right direction.
 * 
 * Also implements Circular Dequeue (enqueue/dequeue both at rear and front)
 *
 */
#include<iostream>

using namespace std;

template<typename DATATYPE_T>
class ringbuffer{

    public:
        ringbuffer(int size):buffsize(size){
	    buffer = new DATATYPE_T[size];
	    occupancy = 0, frontptr  = 0, rearptr = 0;
	}
	int size();
	bool isfull();
	bool isempty();
	// Default enqueue at rear
        bool enqueue(DATATYPE_T element, bool rear=true);
	// Default dequeue at front
        bool dequeue(bool rear=false);
	DATATYPE_T front();
	DATATYPE_T rear();
	void printbuffer();
	

    private:
	int buffsize;
	int occupancy;
        DATATYPE_T *buffer;
	int frontptr;
	int rearptr;
        bool enqueue_r(DATATYPE_T element);
        bool enqueue_f(DATATYPE_T element);
        bool dequeue_r();
        bool dequeue_f();
};

template<typename DATATYPE_T>
int ringbuffer<DATATYPE_T>::size(){
    return this->buffsize;
}

template<typename DATATYPE_T>
bool ringbuffer<DATATYPE_T>::enqueue(DATATYPE_T element, bool rear){
    if(rear)
        return this->enqueue_r(element);
    else
        return this->enqueue_f(element);
}

template<typename DATATYPE_T>
bool ringbuffer<DATATYPE_T>::enqueue_r(DATATYPE_T element){
    if(this->isfull()) return false;
    
    this->buffer[this->rearptr] = element;
    this->occupancy++;
    this->rearptr = ++this->rearptr % this->buffsize;
    return true;
}

template<typename DATATYPE_T>
bool ringbuffer<DATATYPE_T>::enqueue_f(DATATYPE_T element){
    if(this->isfull()) return false;
    this->frontptr = (--this->frontptr + this->buffsize) % this->buffsize ;
    this->buffer[this->frontptr] = element;
    this->occupancy++;
    return true;
}

template<typename DATATYPE_T>
bool ringbuffer<DATATYPE_T>::dequeue(bool rear){
    if(rear)
        return this->dequeue_r();
    else
        return this->dequeue_f();
}

template<typename DATATYPE_T>
bool ringbuffer<DATATYPE_T>::dequeue_f(){
    if(this->isempty()) return false; 
    
    int element = this->buffer[this->frontptr];
    this->buffer[this->frontptr] = -1;
    cout<<"Dequeued element : "<<element<<endl;
    this->occupancy--;
    this->frontptr = ++this->frontptr % this->buffsize;
    return true;
}

template<typename DATATYPE_T>
bool ringbuffer<DATATYPE_T>::dequeue_r(){
    if(this->isempty()) return false; 
    this->rearptr = (--this->rearptr + this->buffsize) % this->buffsize ;
    int element = this->buffer[this->rearptr];
    this->buffer[this->rearptr] = -1;
    cout<<"Dequeued element : "<<element<<endl;
    this->occupancy--;
    return true;
}

template<typename DATATYPE_T>
bool ringbuffer<DATATYPE_T>::isfull(){
    return (this->occupancy==this->buffsize);
}

template<typename DATATYPE_T>
bool ringbuffer<DATATYPE_T>::isempty(){
    return (this->occupancy==0);
}

template<typename DATATYPE_T>
DATATYPE_T ringbuffer<DATATYPE_T>::front(){
    if(this->isempty()) return -1; 
    return this->buffer[this->frontptr];
}

template<typename DATATYPE_T>
DATATYPE_T ringbuffer<DATATYPE_T>::rear(){
    if(this->isempty()) return -1;
    int reareleat = (this->rearptr - 1 + this->buffsize) % this->buffsize ;
    return this->buffer[reareleat];
}

template<typename DATATYPE_T>
void ringbuffer<DATATYPE_T>::printbuffer(){

    for(int i=0; i < this->buffsize ; i++)
        cout<<"Buffer[ "<< i <<" ] = "<<this->buffer[i]<<endl;

    cout<<"Front (dequeue from) : Buffer[ "<< this->frontptr <<" ] = "<<this->buffer[this->frontptr]<<endl;
    cout<<"Rear  (enqueue at  ) : Buffer[ "<< this->rearptr <<" ]"<<endl;
    cout<<"Buffer Occupancy is "<< this->occupancy<<endl;
}

int main(){

    ringbuffer<int> rb(10);

    rb.enqueue(0);
    rb.enqueue(9,false);
    rb.enqueue(1);
    rb.enqueue(2);
    rb.enqueue(3);
    rb.enqueue(4);
    rb.enqueue(5);
    rb.enqueue(6);
    rb.enqueue(7);
    rb.enqueue(8);
    rb.printbuffer();
    cout<<"Front element is : "<<rb.front()<<endl;
    cout<<"Rear element is : "<<rb.rear()<<endl;
    if(rb.enqueue(10) == false) cout<<"Enqueue for 10 Failed !"<<endl;
    rb.dequeue();
    cout<<"Front element is : "<<rb.front()<<endl;
    cout<<"Rear element is : "<<rb.rear()<<endl;
    if(rb.enqueue(10) == true) cout<<"Enqueue for 10 succeeded !"<<endl;
    if(rb.enqueue(11) == false) cout<<"Enqueue for 11 failed !"<<endl;
    if(rb.enqueue(11) == true) cout<<"Enqueue for 11 succeeded !"<<endl;
    rb.dequeue();
    rb.printbuffer();
    cout<<endl;
    cout<<"Front element is : "<<rb.front()<<endl;
    cout<<"Rear element is : "<<rb.rear()<<endl;
    rb.dequeue();
    rb.dequeue(true);
    rb.dequeue();
    rb.dequeue(true);
    rb.dequeue();
    rb.dequeue(true);
    rb.dequeue();
    rb.dequeue(true);
    rb.dequeue();
    rb.printbuffer();

    return 0;
}
