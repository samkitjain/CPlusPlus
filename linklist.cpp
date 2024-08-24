#include<iostream>

using namespace std;

template <class T>
struct ListNode{

    // Init Constructor with initializer list
    ListNode():val(0),next(nullptr){}
    ListNode(T v):val(v),next(nullptr){}
    ListNode(T v, ListNode *n):val(v),next(n){}
    // Destructor

    // Members
    T val;
    ListNode<T> *next;
};

template <class T>
class LinkList{

    public:
        //// constructor
        LinkList():head(nullptr),tail(nullptr),size(0){};

	//// Members

	//  Methods
	
	// Insert node at end of the list
	void insert(T n);
	// Remove node from begining
	T  pop();
	T middle();
        void deleteat(int i);
        ListNode<T>* nodeat(int i);
        int swapnodesat(int i, int j);
        void insertat(int i, T data);
        void reverse();
        void printlist();

    private:
        // Insert new element @ head
	ListNode<T> * head;
        // Pop element from tail
	ListNode<T> * tail;
	
	int size;

};

template <class T>
void LinkList<T>::insert(T n){

    ListNode<T> *node = new ListNode<T>(n);

    if(head==nullptr){
        head=node;
	tail=head;
    }
    else{
        head->next = node;
	head = head->next;
    }

    this->size++;
}

template <class T>
T LinkList<T>::pop(){

    ListNode<T> *node;
    T val = 0 ; 
    if(tail==nullptr)
        return -1;
    else{
        node = tail;
	tail = tail->next;
    }
    val = node->val;
    delete node;
    this->size--;
    return val;
}

template <class T>
T LinkList<T>::middle(){
    ListNode<T> *middle = this->tail;
    ListNode<T> *runner = this->tail;

    if(runner == nullptr) return -1;

    while(runner->next){
        runner = runner->next;
	runner = runner->next;
	if(runner == nullptr) break;
        middle = middle->next;
    }
    return middle->val;
}


template <class T>
   void LinkList<T>::deleteat(int i){

   // index is larger than list size
   if(i==0 && i>this->size) return;

   int count = i;
   ListNode<T> *curr = this->tail;
   ListNode<T> *prev = nullptr;

   while(--count){
      prev=curr; 
      curr=curr->next;
   }
  
   if(prev)
       prev->next = curr->next;
   else
       this->tail = this->tail->next;
   
   cout<<"Deleted : "<<curr->val<<endl;
}


template <class T>
void LinkList<T>::insertat(int i, T data){

    if(i==0 || i > this->size) return;
    
    ListNode<T> *prev = nullptr;
    ListNode<T> *curr = this->tail;
    int counter = i;

    ListNode<T> *node = new ListNode<T>(data);

    while(--counter){
        prev = curr;
	curr = curr->next;
    }

    if(prev == nullptr){ // Inserting at tail
        node->next = curr ;
	this->tail = node;
    }
    else{
        prev->next = node;
	node->next = curr;
    }
    this->size++;

    return;
}

template <class T>
ListNode<T>* LinkList<T>::nodeat(int i){
   
    int count = i;
    if(count == 0 || count > this->size) return nullptr;

    ListNode<T> *nodeat = this->tail;
    while(--count)
        nodeat = nodeat->next;
    return nodeat;
}


//
// Assume i > j (j is a younger node than i in the link list)
//
// Algo (First change past and then change future):
// Step 1 : Swap previ->next and prevj->next
// Step 2 : Swap curri->next and currj->next
//
template <class T>
int LinkList<T>::swapnodesat(int i, int j){
   
    if( i == 0 || j == 0 || i > this->size || j > this->size || this->size < 2) return 1;

    //
    // TODO Swap i and j if j > i
    // For now we are assuming that j is younger than i in the link list
    //

    ListNode<T> *previ = LinkList<T>::nodeat(i-1);
    ListNode<T> *curri = LinkList<T>::nodeat(i);
    ListNode<T> *prevj = LinkList<T>::nodeat(j-1);
    ListNode<T> *currj = LinkList<T>::nodeat(j);
    ListNode<T> *tmp = nullptr;

     //
     // Step 1 :  Swap prev->next pointers
     //

     // This is to address corner case when we are swapping head element
     if(curri->next == nullptr){
         // update head
	 cout<<"swapnodesat: Updating head"<<endl;
         this->head = currj;
     }

     if(prevj != nullptr){
         tmp = previ->next;
         previ->next = prevj->next;
         prevj->next = tmp;
     }
     // This is to address corner case when we are swapping tail element
     else{
	 cout<<"swapnodesat: Updating tail"<<endl;
         previ->next = currj;
	 // Update tail
	 this->tail = curri;
     }

     //
     // Step 2 :  Swap curr->next pointers
     //
     tmp = curri->next;
     curri->next = currj->next;
     currj->next = tmp;

    return 0;
}

template <class T>
void LinkList<T>::reverse(){
    ListNode<T> *prev = nullptr;
    ListNode<T> *curr = this->tail;
    ListNode<T> *tmp  = nullptr;


    while(curr){
        tmp = curr->next;
        curr->next = prev;
        prev = curr;
        curr = tmp;
    }
    // Swap tail and head poitners
    tmp = this->tail;
    this->tail = this->head;
    this->head = tmp;
}

template <class T>
void LinkList<T>::printlist(){

	int count = 1;
	ListNode<T> *node = this->tail;

	while(node){
		cout<<"Node at list index "<<count<<" is "<<node->val<<endl;
		count++;
		node=node->next;
	}
}


int main(){

 LinkList<int> list;
 list.insert(1);
 list.insert(2);
 list.insert(3);
 list.insert(4);
 list.insert(5);
 list.insertat(4, 100);

 cout<<"Val of node at 2 is : "<< list.nodeat(2)->val << endl;
 cout<<"Val of node at 4 is : "<< list.nodeat(4)->val << endl;
 cout<<"Val of node at 1 is : "<< list.nodeat(1)->val << endl;
 
 cout<<"Midde is "<<list.middle()<<endl;

 cout<<"Swap test region start"<<endl<<endl;
 cout<<"Order before swap"<<endl;
 cout<<"Val of node at 1 is : "<< list.nodeat(1)->val << endl;
 cout<<"Val of node at 2 is : "<< list.nodeat(2)->val << endl;
 cout<<"Val of node at 3 is : "<< list.nodeat(3)->val << endl;
 cout<<"Val of node at 4 is : "<< list.nodeat(4)->val << endl;
 cout<<"Val of node at 5 is : "<< list.nodeat(5)->val << endl;
 cout<<"Val of node at 6 is : "<< list.nodeat(6)->val << endl;
 list.swapnodesat(3,2);
 cout<<"Order after swap"<<endl;
 cout<<"Val of node at 1 is : "<< list.nodeat(1)->val << endl;
 cout<<"Val of node at 2 is : "<< list.nodeat(2)->val << endl;
 cout<<"Val of node at 3 is : "<< list.nodeat(3)->val << endl;
 cout<<"Val of node at 4 is : "<< list.nodeat(4)->val << endl;
 cout<<"Val of node at 5 is : "<< list.nodeat(5)->val << endl;
 cout<<"Swap test region end"<<endl<<endl;

 list.deleteat(4);

 cout<<"List before reverse:"<<endl;
 list.printlist();
 list.reverse();
 cout<<"List after reverse:"<<endl;
 list.printlist();

 cout<<list.pop()<<endl;
 cout<<list.pop()<<endl;
 cout<<list.pop()<<endl;

return 0 ;
}
