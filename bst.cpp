#include <iostream>
#include <stack>
#include <vector>
#include <queue>

using namespace std;

enum SEARCHORDER{

    PRE,
    IN,
    POST
};

template <typename VAL_T>
struct node{

    node():val(0),lchild(nullptr),rchild(nullptr){}
    node(int val):val(val),lchild(nullptr),rchild(nullptr){}
    node *lchild;
    node *rchild;
    VAL_T val;
};

template <typename VAL_T>
class bst{
    public:
        bst():root(nullptr){}
        bst(VAL_T val):root(nullptr){}
	// Variables
	node<VAL_T>* root;
	// Methods
        bool push_rec(VAL_T val);
        bool push_itr(VAL_T val);
        bool insert_rec(node<VAL_T> **curr, node<VAL_T> *n);
        bool insert_itr(node<VAL_T> **curr, node<VAL_T>* n);
        void printbst_rec(bool inc, SEARCHORDER ORDER);
        void printbst_itr(SEARCHORDER ORDER);
        void printbst_bfs();
	void mirror();
        bool search(VAL_T val);
        int bstdepth();
	void deletenode(VAL_T val);
        bool lowestcommonancestor(VAL_T v1, VAL_T v2, node<VAL_T> *curr);
        bool lowestcommonancestor2(VAL_T v1, VAL_T v2, node<VAL_T> *curr, VAL_T&lca_node);
        bool ispresentinbst(VAL_T val, node<VAL_T>*curr);
        VAL_T kelement(int k, bool inc, node<VAL_T> *curr);
        VAL_T distancebtwnodes(VAL_T n1,VAL_T n2,node<VAL_T> *curr);
        VAL_T distancefromroot(VAL_T n1, node<VAL_T> *curr);
    private:
        void printpreorder_rec(node<VAL_T>*curr, bool inc);
        void printinorder_rec(node<VAL_T>*curr, bool inc);
        void printpostorder_rec(node<VAL_T>*curr, bool inc);
        void printpreorder_itr(node<VAL_T>*curr);
        void printinorder_itr(node<VAL_T>*curr);
        void printpostorder_itr(node<VAL_T>*curr);
	void mirrorbst(node<VAL_T>*curr);
        int depth(node<VAL_T>*curr);
        node<VAL_T> * deletenodek(VAL_T val, node<VAL_T> *curr);
};

template <typename VAL_T>
bool bst<VAL_T>::push_rec(VAL_T val){

    node<VAL_T>* n = new node<VAL_T>(val);
    return this->insert_rec(&this->root,n);
}

template <typename VAL_T>
bool bst<VAL_T>::insert_rec(node<VAL_T> **curr, node<VAL_T>* n){

    bool success = false;

    if(*curr == nullptr){
        *curr = n;
	return true;
    }

    if(n->val == (*curr)->val) return false;

    if(n->val < (*curr)->val)
	success = insert_rec(&(*curr)->lchild,n);
    else
	success = insert_rec(&(*curr)->rchild,n);
    return success;
}

template <typename VAL_T>
bool bst<VAL_T>::push_itr(VAL_T val){

    node<VAL_T>* n = new node<VAL_T>(val);
    return this->insert_itr(&this->root,n);
}

template <typename VAL_T>
bool bst<VAL_T>::insert_itr(node<VAL_T> **curr, node<VAL_T>* n){

    // TODO : Code can be made simple by just using a prev pointer
    // Save value of curr_backup in prev and then advance curr_backup
    // without any checks. While loop will terminate if curr_backup == nullptr
    // Now simply do prev = n

    node<VAL_T> *curr_backup = *curr;

    // Tree is empty. Directly insert at the root
    if(curr_backup == nullptr){
        *curr = n;
	return true;
    }

    while(curr_backup)
    {
        // new node value less than current node value ? Go left
        if(n->val < curr_backup->val){
           // Is left child present ?
	    if(curr_backup->lchild)
                // Left child present. Make it current and keep going down
                curr_backup = curr_backup->lchild;
	    else{
                // Left child absent. Make new node current node's left child
                curr_backup->lchild = n;
	        break;
	    }
	}
        // new node value greater than current node value ? Go Right
	else if(n->val > curr_backup->val){
           // Is right child present ?
	    if(curr_backup->rchild)
                // Right child present. Make it current and keep going down
                curr_backup = curr_backup->rchild;
	    else{
                // Right child absent. Make new node current node's Right child
                curr_backup->rchild = n;
	        break;
	    }
	}
	// New node value is already in the tree. NOT Allowed !
	else{
	    return false;
	}
    }
    return true;
}

/*
 * There are 2 ways to traverse the BST:
 *
 * 1. Depth First Search (DFS): In this we first explore depth. i.e. 
 *    For each child we explore its entire subtree before visiting next child.
 *    Uses stack for implementation
 *
 *     a. Pre-order Traversal
 *     b. In-order Traversal
 *     c. Post-order Traversal
 *
 * 2. Breadth First Search (BFS): In this we explore breadth first. i.e. We explore
 *    all immediate childs first before going to subtrees of childs visited in order.
 *    Uses FIFO queue for implementation.
 *
 */

//
// BFS method
//
template<typename VAL_T>
void bst<VAL_T>::printbst_bfs(){

    // Visted is NOT useful in BST. Only in Graphs !
    // For normal graph, visited is vector or map
    queue<node<VAL_T>*> visited;
    queue<node<VAL_T>*> pending;

    node<VAL_T>* curr = this->root;

    if(curr == nullptr) return;
    pending.push(curr);

    cout<<"Starting BFS"<<endl;
    while(!pending.empty()){
        curr = pending.front();
	pending.pop();
	// For Graphs check if current node has been visited
	// If yes, then continue
	cout<<"Node is "<<curr->val<<endl;
	if(curr->lchild) pending.push(curr->lchild);
	if(curr->rchild) pending.push(curr->rchild);
	visited.push(curr);
    }
}

//
// DFS method
//
template <typename VAL_T>
void bst<VAL_T>::printbst_itr(SEARCHORDER ORDER){
    if(ORDER == PRE)
        printpreorder_itr(this->root);
    else if(ORDER == IN)
        printinorder_itr(this->root);
    else
        printpostorder_itr(this->root);
}

template <typename VAL_T>
void bst<VAL_T>::printinorder_itr(node<VAL_T> *curr){
    stack<node<VAL_T> *>  s;
    cout<<"Printing bst "<<endl;
    while(curr != nullptr || s.empty() == false){
        while(curr != nullptr){
	    s.push(curr);
	    curr = curr->lchild;
	}
	curr = s.top();
	s.pop();
	cout<<curr->val<<endl;
	curr = curr->rchild;
    }
}

template <typename VAL_T>
void bst<VAL_T>::printpreorder_itr(node<VAL_T> *curr){

    if(curr == nullptr) return;

    stack<node<VAL_T> *>  s;
    s.push(curr);
    while(s.empty() == false){
	curr= s.top();
	s.pop();
	cout<<curr->val<<endl;
	if(curr->rchild)
	    s.push(curr->rchild);
	if(curr->lchild)
	    s.push(curr->lchild);
    }
}

/*
Postorder iterative :

Following implementation uses 2 stacks. This is easiest.

This can also be done using single stack:

1.1 Create an empty stack
2.1 Do following while root is not NULL
    a) Push root's right child and then root to stack.
    b) Set root as root's left child.
2.2 Pop an item from stack and set it as root.
    a) If the popped item has a right child and the right child 
       is at top of stack, then remove the right child from stack,
       push the root back and set root as root's right child.
    b) Else print root's data and set root as NULL.
2.3 Repeat steps 2.1 and 2.2 while stack is not empty.

Source : https://www.geeksforgeeks.org/iterative-postorder-traversal-using-stack/#

*/

template <typename VAL_T>
void bst<VAL_T>::printpostorder_itr(node<VAL_T> *curr){

    if(curr == nullptr) return;

    stack<node<VAL_T> *>  prim_stk;
    stack<node<VAL_T> *>  sec_stk;
    node<VAL_T> * n; 

    prim_stk.push(curr);

    while(!prim_stk.empty()){
        n = prim_stk.top();
        prim_stk.pop();
	sec_stk.push(n);
	if(n->lchild) prim_stk.push(n->lchild);
	if(n->rchild) prim_stk.push(n->rchild);
    }

    while(!sec_stk.empty()){
        cout<<sec_stk.top()->val<<endl;
	sec_stk.pop();
    }
}

template <typename VAL_T>
void bst<VAL_T>::printbst_rec(bool inc, SEARCHORDER ORDER){
    if(ORDER == PRE)
        printpreorder_rec(this->root, inc);
    else if(ORDER == IN)
        printinorder_rec(this->root, inc);
    else
        printpostorder_rec(this->root, inc);
}

template <typename VAL_T>
void bst<VAL_T>::printinorder_rec(node<VAL_T>*curr, bool inc){
    if(curr != nullptr){
        (inc == true /* increasing */) ? printinorder_rec(curr->lchild, inc) : printinorder_rec(curr->rchild, inc);
	cout<<curr->val<<endl;
        (inc == true /* increasing */) ? printinorder_rec(curr->rchild, inc) : printinorder_rec(curr->lchild, inc);
    }
}

template <typename VAL_T>
void bst<VAL_T>::printpreorder_rec(node<VAL_T>*curr, bool inc){
    if(curr != nullptr){
	cout<<curr->val<<endl;
        (inc == true /* increasing */) ? printpreorder_rec(curr->lchild, inc) : printinorder_rec(curr->rchild, inc);
        (inc == true /* increasing */) ? printpreorder_rec(curr->rchild, inc) : printinorder_rec(curr->lchild, inc);
    }
}

template <typename VAL_T>
void bst<VAL_T>::printpostorder_rec(node<VAL_T>*curr, bool inc){
    if(curr != nullptr){
        (inc == true /* increasing */) ? printpostorder_rec(curr->lchild, inc) : printinorder_rec(curr->rchild, inc);
        (inc == true /* increasing */) ? printpostorder_rec(curr->rchild, inc) : printinorder_rec(curr->lchild, inc);
	cout<<curr->val<<endl;
    }
}


template <typename VAL_T>
void bst<VAL_T>::mirror(){
    mirrorbst(this->root);
}

template <typename VAL_T>
void bst<VAL_T>::mirrorbst(node<VAL_T>*curr){

    node<VAL_T> *n;

    if(!curr)
        return;

    mirrorbst(curr->lchild);
    mirrorbst(curr->rchild);
    n = curr->lchild;
    curr->lchild = curr->rchild;
    curr->rchild = n;
}


template <typename VAL_T>
bool bst<VAL_T>::search(VAL_T val){

    bool result = false;    

    node<VAL_T> *n = this->root;

    while(n){
        if(val == n->val){
	    result = true;
	    break;
	}
	else{
	    if(val>n->val)
	        n = n->rchild;
	    else
	        n = n->lchild;
	}
    }
    return result;
}

/*
 * Algo: Each node receive depth from both childs (left and right)
 *       Take max of two and send it up to your parent.
 */

template <typename VAL_T>
int bst<VAL_T>::bstdepth(){
    if(!this->root) return 0;
    return depth(this->root);
}

template <typename VAL_T>
int bst<VAL_T>::depth(node<VAL_T>*curr){

    int ld = 0;
    int rd = 0;

    if(curr){
        ld = depth(curr->lchild)+1;
        rd = depth(curr->rchild)+1;
    }
    return ((ld>rd)?ld:rd);
}

/*
template <typename VAL_T>
node<VAL_T>* bst<VAL_T>::minnode(node<VAL_T>*curr){

    if(!curr) return nullptr;

    while(curr->lchild){
        curr=curr->lchild;
    }
    return curr;
}

template <typename VAL_T>
node<VAL_T>* bst<VAL_T>::maxnode(node<VAL_T>*curr){

    if(!curr) return nullptr;

    while(curr->rchild){
        curr=curr->rchild;
    }
    return curr;
}

template <typename VAL_T>
node<VAL_T>* bst<VAL_T>::deletemin(node<VAL_T>*curr){

    if(!curr) return nullptr;

    if(!curr->left) return 
    curr->lchild = deletemin(curr->lchild);
    return curr;
}
*/

/* Deleting a nodes involves:
 * 1. Find the node to be deleted
 * 2. Now we have two choices - Either we replace
      node to be deleted with largest node in left
      subtree or with smallest node in right subtree.
      whichever route you take, accordingly check for the
      case when one child of the tree is NULL (lchild or rchild is null)
 * 3. Delete the min or max node 
 */

template<typename VAL_T>
void bst<VAL_T>::deletenode(VAL_T val){
    this->root = deletenodek(val, this->root);
}

//
// Following is recurssive deletek.
//
// Iterative deletek is avaialble here : https://www.geeksforgeeks.org/binary-search-tree-set-3-iterative-delete/
// 
template<typename VAL_T>
node<VAL_T>* bst<VAL_T>::deletenodek(VAL_T val, node<VAL_T> *curr){
    
    if(curr){
        if(val < curr->val){
            curr->lchild = deletenodek(val,curr->lchild);
	}
	else if(val > curr->val){
            curr->rchild = deletenodek(val,curr->rchild);
	}
	else{ // Target node found ! Start removal process
	      // 4 case: either child present, both absent, both present

              // Left child absent. This also covers case even right is null
	      if(!curr->lchild){
	          // delete current and return left->right
		  node<VAL_T>* n = curr->rchild;
		  delete(curr);
		  return n; 
	      }
	          
              // Right child absent
	      if(!curr->rchild){
	          // delete current and return left->right
		  node<VAL_T>* n = curr->lchild;
		  delete(curr);
		  return n; 
	      }

	      // Both children are present : we chose to replace
	      // curr with the largest node in the left subtree.
	      // We can  also replace it with smallest node in right
	      // subtree. In this e.g. we chose largest node in left subtree
	      
	      // Step 1 : Select node to replace curr node from left subtree
	      node<VAL_T>* n = curr;
	      n = n->lchild; // Go to left subtree
	      // Now find largest node in left subtree (i.e. rightmost node)
	      while(n->rchild)
	          n = n->rchild;
              
	      // Copy value from target node to curr node
	      curr->val = n->val;
	      
	      // Step 2 : delete target node in the left subtree
              curr->lchild = deletenodek(n->val,curr->lchild);

	      return curr;
	}
    }
    return curr;
}

template<typename VAL_T>
bool bst<VAL_T>::lowestcommonancestor(VAL_T v1, VAL_T v2, node<VAL_T> *curr){

    node<VAL_T> *n = curr;
    VAL_T n1,n2;
    bool found = false;
    vector<VAL_T> s1,s2;

    while(n){

        //cout<<"Pushing "<<n->val<<" in stack s1"<<endl;
	s1.push_back(n->val);

        if(v1 < n->val){
	   n = n->lchild;
	}
	else if(v1 > n->val){
	   n = n->rchild;
	}
	else{
	   found = true;
	   break;
	}
    }

    if(found == false){
        cout<<"Node1 [val: "<<v1<<" ] doesn't exist in BST. Ancestor doesn't exist !"<<endl;
	return 0;
    }

    n = curr;
    found = false;

    while(n){
        //cout<<"Pushing "<<n->val<<" in stack s2"<<endl;
	s2.push_back(n->val);

        if(v2 < n->val){
	   n = n->lchild;
	}
	else if(v2 > n->val){
	   n = n->rchild;
	}
	else{
	   found = true;
	   break;
	}
    }
    
    if(found == false){
        cout<<"Node2 [val: "<<v2<<" ] doesn't exist in BST. Ancestor doesn't exist !"<<endl;
	return 0;
    }

    int lca = 0;
    int count = (s1.size() > s2.size()) ? s2.size() : s1.size();
    bool mismatch = false;

    for(lca = 0; lca < count; lca++){
        if(s1[lca] != s2[lca]){
	    mismatch = true;
	    break;
	}
    }
    cout<<"LCA is "<<s1[lca-1]<<endl;

    return 1;
}

template<typename VAL_T>
bool bst<VAL_T>::ispresentinbst(VAL_T val, node<VAL_T>*curr){

    while(curr){
        if(val > curr->val)
	    curr = curr->rchild;
        else if(val < curr->val)
	    curr = curr->lchild;
	else{ // Node found !
	    return true;
	}
    }
    return false;
}


template<typename VAL_T>
bool bst<VAL_T>::lowestcommonancestor2(VAL_T v1, VAL_T v2, node<VAL_T> *curr, VAL_T&lca_node){

    if(!curr) return false;

    if(!this->ispresentinbst(v1,curr)){
        cout<<"Node1 [val: "<<v1<<" ] doesn't exist in BST. Ancestor doesn't exist !"<<endl;
	return false;
    }
    if(!this->ispresentinbst(v2,curr)){
        cout<<"Node2 [val: "<<v2<<" ] doesn't exist in BST. Ancestor doesn't exist !"<<endl;
	return false;
    }

    VAL_T lca = 0;
    while(curr){

        if((v1 >= curr->val && v2 <= curr->val) || (v2 >= curr->val && v1 <= curr->val)){
            break;
	}
	else if(v1 < curr->val && v2 < curr->val){
	    curr=curr->lchild;
	}
	else if(v1 > curr->val && v2 > curr->val){
	    curr=curr->rchild;
	}

    }
    cout<<"LCA is "<<curr->val<<endl;
    lca_node = curr->val;
    return true;
}

// Kth element : 
//
// inc : True (K-Smallest)
//
// Implement inorder search and after hitting leftmost element,
// increment a counter (starting at 10 everytime you visit a new node. 
// When counter value is k, you have k'th smallest element.
//
//
//
// inc : False (K-Largest)
//
// Implement inorder search and after hitting rightmost element,
// increment a counter (starting at 10 everytime you visit a new node. 
// When counter value is k, you have k'th largest element.
//
template<typename VAL_T>
VAL_T bst<VAL_T>::kelement(int k, bool inc, node<VAL_T> *curr){

    stack<node<VAL_T>*> s;
    int kcounter = 0;

    while(!s.empty() || curr){
        while(curr){
	    s.push(curr);
	    curr = (inc) ? curr->lchild : curr->rchild;
	}
	curr = s.top();
	s.pop();
	if(++kcounter == k){
	    cout<<"K "<<((inc)?" smallest ":" largest ")<<"element is "<<curr->val<<endl;
	    return curr->val;
	}
	curr = (inc) ? curr->rchild : curr->lchild;
    }
    cout<<"K "<<((inc)?" smallest ":" largest ")<<"doesn't exist in the bst"<<endl;
    return -1;
}

//
//
// Distance between 2 nodes (n1,n2) in BST:
//
// dist(n1,n2) = (dist(root,n1) + dist(root,n2))  - 2 * dist(root,LCA(n1,n2))
//
//
// Assumes node is present in BST
//
template<typename VAL_T>
VAL_T bst<VAL_T>::distancefromroot(VAL_T n1, node<VAL_T> *curr){

    int hops = 0;
    while(curr){
        if(n1<curr->val)
	    curr = curr->lchild;
        else if(n1>curr->val)
	    curr = curr->rchild;
	else // Equal
	    return hops;
	hops++;
    }
    cerr<<"Node not found"<<endl;
    throw exception();
    return -1;
}

template<typename VAL_T>
VAL_T bst<VAL_T>::distancebtwnodes(VAL_T n1,VAL_T n2,node<VAL_T> *curr){
    int dist_n1_root = distancefromroot(n1,curr);
    int dist_n2_root = distancefromroot(n2,curr);
    int lca_node = 0;
    this->lowestcommonancestor2(n1,n2,curr,lca_node);
    int dist_lca_root = distancefromroot(lca_node,curr);
    int distancebtwn1n2 = (dist_n1_root + dist_n2_root ) - (2*dist_lca_root);
    cout<<"Distance between n1 ("<<n1<<") and n2 ("<<n2<<") is : "<<distancebtwn1n2<<endl;
    return distancebtwn1n2;
}


int main(void){
    
//    bst<int> t;
//    t.push_rec(4);
//    t.push_rec(6);
//    t.push_rec(3);
//    t.push_rec(7);
//    t.push_rec(2);
//    t.push_rec(5);
//    t.push_rec(1);
//    t.printbst_rec(true/* Increasing order -> True else False*/, PRE);

    bst<int> t;
    t.push_itr(4);
    t.push_itr(6);
    t.push_itr(3);
    t.push_itr(7);
    t.push_itr(2);
    t.push_itr(5);
    t.push_itr(1);
//    t.printbst_rec(true/* Increasing order -> True else False*/, PRE);
//    t.printbst_itr(POST);

    cout<<"------INTR--------------"<<endl;
    t.printbst_itr(POST);
    cout<<"-----------------------"<<endl;
    cout<<"------REC--------------"<<endl;
    t.printbst_rec(true,POST);
    cout<<"-----------------------"<<endl;

    t.mirror();
    t.printbst_itr(POST);
    t.mirror();

    cout<<"-----------------------"<<endl;
    cout<<t.search(8)<<endl;

    cout<<"BST depth is "<<t.bstdepth()<<endl;
    cout<<"-----------------------"<<endl;
    t.deletenode(1);
    t.printbst_itr(POST);
    cout<<"-----------------------"<<endl;
    t.push_itr(1);
    t.printbst_itr(POST);
    t.lowestcommonancestor(1,1,t.root);
    cout<<"-----------------------"<<endl;
    int lca_node;
    t.lowestcommonancestor2(5,7,t.root,lca_node);
    t.printbst_itr(IN);
    cout<<"-----------------------"<<endl;
    cout<<"lca_node "<<lca_node<<endl;
    cout<<"-----------------------"<<endl;
    // K-Smallest
    t.kelement(1,true,t.root);
    // K-Largest
    t.kelement(1,false,t.root);
    // Distance between 2 nodes
    t.distancebtwnodes(1,5,t.root);
    t.distancebtwnodes(5,7,t.root);
    t.distancebtwnodes(1,2,t.root);
    t.distancebtwnodes(4,4,t.root);
    t.distancebtwnodes(1,1,t.root);
    
    t.printbst_bfs();
    
    return 0;
}
