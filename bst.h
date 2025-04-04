#ifndef BST_H
#define BST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <utility>

/**
 * A templated class for a Node in a search tree.
 * The getters for parent/left/right are virtual so
 * that they can be overridden for future kinds of
 * search trees, such as Red Black trees, Splay trees,
 * and AVL trees.
 */
template <typename Key, typename Value>
class Node
{
public:
    Node(const Key& key, const Value& value, Node<Key, Value>* parent);
    virtual ~Node();

    const std::pair<const Key, Value>& getItem() const;
    std::pair<const Key, Value>& getItem();
    const Key& getKey() const;
    const Value& getValue() const;
    Value& getValue();

    virtual Node<Key, Value>* getParent() const;
    virtual Node<Key, Value>* getLeft() const;
    virtual Node<Key, Value>* getRight() const;

    void setParent(Node<Key, Value>* parent);
    void setLeft(Node<Key, Value>* left);
    void setRight(Node<Key, Value>* right);
    void setValue(const Value &value);

protected:
    std::pair<const Key, Value> item_;
    Node<Key, Value>* parent_;
    Node<Key, Value>* left_;
    Node<Key, Value>* right_;
};

/*
  -----------------------------------------
  Begin implementations for the Node class.
  -----------------------------------------
*/

/**
* Explicit constructor for a node.
*/
template<typename Key, typename Value>
Node<Key, Value>::Node(const Key& key, const Value& value, Node<Key, Value>* parent) :
    item_(key, value),
    parent_(parent),
    left_(NULL),
    right_(NULL)
{

}

/**
* Destructor, which does not need to do anything since the pointers inside of a node
* are only used as references to existing nodes. The nodes pointed to by parent/left/right
* are freed by the BinarySearchTree.
*/
template<typename Key, typename Value>
Node<Key, Value>::~Node()
{

}

/**
* A const getter for the item.
*/
template<typename Key, typename Value>
const std::pair<const Key, Value>& Node<Key, Value>::getItem() const
{
    return item_;
}

/**
* A non-const getter for the item.
*/
template<typename Key, typename Value>
std::pair<const Key, Value>& Node<Key, Value>::getItem()
{
    return item_;
}

/**
* A const getter for the key.
*/
template<typename Key, typename Value>
const Key& Node<Key, Value>::getKey() const
{
    return item_.first;
}

/**
* A const getter for the value.
*/
template<typename Key, typename Value>
const Value& Node<Key, Value>::getValue() const
{
    return item_.second;
}

/**
* A non-const getter for the value.
*/
template<typename Key, typename Value>
Value& Node<Key, Value>::getValue()
{
    return item_.second;
}

/**
* An implementation of the virtual function for retreiving the parent.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getParent() const
{
    return parent_;
}

/**
* An implementation of the virtual function for retreiving the left child.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getLeft() const
{
    return left_;
}

/**
* An implementation of the virtual function for retreiving the right child.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getRight() const
{
    return right_;
}

/**
* A setter for setting the parent of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setParent(Node<Key, Value>* parent)
{
    parent_ = parent;
}

/**
* A setter for setting the left child of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setLeft(Node<Key, Value>* left)
{
    left_ = left;
}

/**
* A setter for setting the right child of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setRight(Node<Key, Value>* right)
{
    right_ = right;
}

/**
* A setter for the value of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setValue(const Value& value)
{
    item_.second = value;
}

/*
  ---------------------------------------
  End implementations for the Node class.
  ---------------------------------------
*/

/**
* A templated unbalanced binary search tree.
*/
template <typename Key, typename Value>
class BinarySearchTree
{
public:
    BinarySearchTree(); //TODO
    virtual ~BinarySearchTree(); //TODO
    virtual void insert(const std::pair<const Key, Value>& keyValuePair); //TODO
    virtual void remove(const Key& key); //TODO
    void clear(); //TODO
    bool isBalanced() const; //TODO
    void print() const;
    bool empty() const;

    template<typename PPKey, typename PPValue>
    friend void prettyPrintBST(BinarySearchTree<PPKey, PPValue> & tree);
public:
    /**
    * An internal iterator class for traversing the contents of the BST.
    */
    class iterator  // TODO
    {
    public:
        iterator();

        std::pair<const Key,Value>& operator*() const;
        std::pair<const Key,Value>* operator->() const;

        bool operator==(const iterator& rhs) const;
        bool operator!=(const iterator& rhs) const;

        iterator& operator++();

    protected:
        friend class BinarySearchTree<Key, Value>;
        iterator(Node<Key,Value>* ptr);
        Node<Key, Value> *current_;
    };

public:
    iterator begin() const;
    iterator end() const;
    iterator find(const Key& key) const;
    Value& operator[](const Key& key);
    Value const & operator[](const Key& key) const;

protected:
    // Mandatory helper functions
    Node<Key, Value>* internalFind(const Key& k) const; // TODO
    Node<Key, Value> *getSmallestNode() const;  // TODO
    static Node<Key, Value>* predecessor(Node<Key, Value>* current); // TODO
    // Note:  static means these functions don't have a "this" pointer
    //        and instead just use the input argument.

    // Provided helper functions
    virtual void printRoot (Node<Key, Value> *r) const;
    virtual void nodeSwap( Node<Key,Value>* n1, Node<Key,Value>* n2) ;

    // Add helper functions here

    int checkBalanced(Node<Key, Value>* n) const;
    void clearHelper(Node<Key, Value>* current);

    Node<Key, Value> *findMinInternal(Node<Key, Value>* root) const;
    

protected:
    Node<Key, Value>* root_;
    // You should not need other data members
};

/*
--------------------------------------------------------------
Begin implementations for the BinarySearchTree::iterator class.
---------------------------------------------------------------
*/

/**
* Explicit constructor that initializes an iterator with a given node pointer.
*
* You will need to implement the unfinished functions of the iterator class.
* Note: You do NOT need to check whether the iterator is about to dereference a NULL pointer
* in operator*() or operator->() of the iterator. Just let it fault.
* It is up to the user to ensure the iterator is not equal to the end() iterator.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::iterator::iterator(Node<Key,Value> *ptr)
{
    // TODO DONE
    current_ = ptr;
}

/**
* A default constructor that initializes the iterator to NULL.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::iterator::iterator() 
{
    // TODO DONE
    current_ = NULL;
}

/**
* Provides access to the item.
*/
template<class Key, class Value>
std::pair<const Key,Value> &
BinarySearchTree<Key, Value>::iterator::operator*() const
{
    return current_->getItem();
}

/**
* Provides access to the address of the item.
*/
template<class Key, class Value>
std::pair<const Key,Value> *
BinarySearchTree<Key, Value>::iterator::operator->() const
{
    return &(current_->getItem());
}

/**
* Checks if 'this' iterator's internals have the same value
* as 'rhs'
*/
template<class Key, class Value>
bool
BinarySearchTree<Key, Value>::iterator::operator==(
    const BinarySearchTree<Key, Value>::iterator& rhs) const
{
    // TODO DONE
    return current_ == rhs.current_;
}

/**
* Checks if 'this' iterator's internals have a different value
* as 'rhs'
*/
template<class Key, class Value>
bool
BinarySearchTree<Key, Value>::iterator::operator!=(
    const BinarySearchTree<Key, Value>::iterator& rhs) const
{
    // TODO DONE
    return current_ != rhs.current_;
}


/**
* Advances the iterator's location using an in-order sequencing
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator&
BinarySearchTree<Key, Value>::iterator::operator++()
{
    // TODO DONE
    if (current_ == NULL) return *this;

    if (current_->getRight() == NULL)
    {
        Node<Key, Value> *temp = current_->getParent();

        while (temp != NULL)
        {
            if (current_ == temp->getLeft()) break;

            current_ = current_->getParent();
            temp = current_->getParent();
        }

        current_ = temp;
    }
    else
    {
        current_ = current_->getRight();

        while (current_ != NULL &&  current_->getLeft() != NULL) {
            current_ = current_->getLeft();
        }
    }

    return *this; // or should i do without start
}


/*
-------------------------------------------------------------
End implementations for the BinarySearchTree::iterator class.
-------------------------------------------------------------
*/

/*
-----------------------------------------------------
Begin implementations for the BinarySearchTree class.
-----------------------------------------------------
*/

/**
* Default constructor for a BinarySearchTree, which sets the root to NULL.
*
* Your destructor will probably just call the clear function. The constructor should take constant time.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::BinarySearchTree() 
{
    // TODO DONE
    root_ = NULL;
}

template<typename Key, typename Value>
BinarySearchTree<Key, Value>::~BinarySearchTree()
{
    // TODO DONE
    clear();
}

/**
 * Returns true if tree is empty
*/
template<class Key, class Value>
bool BinarySearchTree<Key, Value>::empty() const
{
    return root_ == NULL;
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::print() const
{
    printRoot(root_);
    std::cout << "\n";
}

/**
* Returns an iterator to the "smallest" item in the tree
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::begin() const
{
    BinarySearchTree<Key, Value>::iterator begin(getSmallestNode());
    return begin;
}

/**
* Returns an iterator whose value means INVALID
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::end() const
{
    BinarySearchTree<Key, Value>::iterator end(NULL);
    return end;
}

/**
* Returns an iterator to the item with the given key, k
* or the end iterator if k does not exist in the tree
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::find(const Key & k) const
{
    Node<Key, Value> *curr = internalFind(k);
    BinarySearchTree<Key, Value>::iterator it(curr);
    return it;
}

/**
 * @precondition The key exists in the map
 * Returns the value associated with the key
 */
template<class Key, class Value>
Value& BinarySearchTree<Key, Value>::operator[](const Key& key)
{
    Node<Key, Value> *curr = internalFind(key);
    if(curr == NULL) throw std::out_of_range("Invalid key");
    return curr->getValue();
}
template<class Key, class Value>
Value const & BinarySearchTree<Key, Value>::operator[](const Key& key) const
{
    Node<Key, Value> *curr = internalFind(key);
    if(curr == NULL) throw std::out_of_range("Invalid key");
    return curr->getValue();
}

/**
* An insert method to insert into a Binary Search Tree.
* The tree will not remain balanced when inserting.
* Recall: If key is already in the tree, you should 
* overwrite the current value with the updated value.
*
* There is no guarantee the tree is balanced before or after the insertion.
* If key is already in the tree, you should overwrite.
* Runtime is O(h).
*/
template<class Key, class Value>
void BinarySearchTree<Key, Value>::insert(const std::pair<const Key, Value> &keyValuePair)
{
    // TODO DONE
    if (root_ == NULL) {
        root_ = new Node<Key, Value>(keyValuePair.first, keyValuePair.second, nullptr);
        return;
    }

    /*Node<Key, Value> *f = internalFind(keyValuePair.first);
    if (f != NULL) {
        f->setValue(keyValuePair.second);
        return;
    }*/

    Node<Key, Value> *temp = root_;
    Node<Key, Value> *parent = nullptr;
    bool left;

    while (temp != NULL)
    {
        parent = temp;
        if (keyValuePair.first == temp->getKey()) {
            temp->setValue(keyValuePair.second);
            return;
        }
        else if (keyValuePair.first < temp->getKey()) {
            temp = temp->getLeft();
            left = true;
        }
        else
        {
            temp = temp->getRight();
            left = false;
        }
    }

    if (parent != nullptr) {
        if (left)
            parent->setLeft(new Node<Key, Value>(keyValuePair.first, keyValuePair.second, parent));
        else
        {
            parent->setRight(new Node<Key, Value>(keyValuePair.first, keyValuePair.second, parent));

            //std::cout << "add to the right" << std::endl;
        }
    }

}


/**
* A remove method to remove a specific key from a Binary Search Tree.
* Recall: The writeup specifies that if a node has 2 children you
* should swap with the predecessor and then remove.

* There is no guarantee the tree is balanced before or after the removal.
* If the key is not already in the tree, this function will do nothing.
* If the node to be removed has two children, swap with its predecessor (not its successor) in the BST removal algorithm.
* If the node to be removed has exactly one child, you can promote the child.
* You may NOT just swap key,value pairs.
* You must swap the actual nodes by changing pointers,
* but we have given you a helper function to do this in the BST class: swapNode(). Runtime of removal should be O(h).
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::remove(const Key& key)
{
    // TODO DONE

    Node<Key, Value> *curr = internalFind(key);

    if (curr != NULL)
    {
        if (curr->getLeft() != NULL && curr->getRight() != NULL) // 2 children
        {
            Node<Key, Value>* replacement = predecessor(curr);

            //std::cout << replacement->getItem().second << std::endl;
            
            nodeSwap(replacement, curr);

            if (curr->getParent() != nullptr) 
            {
                if (curr->getLeft() != nullptr) // it will be always to the left as thats how predecessor works
                {
                    if (curr->getParent()->getLeft() == curr) //curr is left child
                    {
                        curr->getParent()->setLeft(curr->getLeft());
                        curr->getLeft()->setParent(curr->getParent());
                    }
                    else if (curr->getParent()->getRight() == curr) // curr is right child
                    {
                        curr->getParent()->setRight(curr->getLeft());
                        curr->getLeft()->setParent(curr->getParent());
                    }
                }
                else 
                {
                    if (curr->getParent()->getLeft() == curr) curr->getParent()->setLeft(nullptr);
                    else if (curr->getParent()->getRight() == curr) curr->getParent()->setRight(nullptr);
                }
            }

            //std::cout << "node swapped root is " << root_->getKey() << std::endl;

            
        }
        else if (curr->getLeft() != NULL) // curr only has left Child to promote
        {
            if (curr->getParent() == NULL)
            {
                root_ = curr->getLeft();
                curr->getLeft()->setParent(nullptr);
            }
            else
            {
                if (curr->getParent()->getRight() == curr) { // is curr a right child?
                    curr->getParent()->setRight(curr->getLeft());
                }
                else if (curr->getParent()->getLeft() == curr) { // or left
                    curr->getParent()->setLeft(curr->getLeft());
                }

                curr->getLeft()->setParent(curr->getParent());
            }
        }
        else if (curr->getRight() != NULL) // curr only has right child to promote
        {
            if (curr->getParent() == NULL)
            {
                //std::cout << " curr: " << curr->getKey() << std::endl;
                //std::cout << " root: " << root_->getKey() << std::endl;
                root_ = curr->getRight();
                curr->getRight()->setParent(nullptr);
            }
            else
            {
                if (curr->getParent()->getRight() == curr) { // is curr a right child?
                    curr->getParent()->setRight(curr->getRight());
                }
                else if (curr->getParent()->getLeft() == curr) { // or left
                    curr->getParent()->setLeft(curr->getRight());
                }

                curr->getRight()->setParent(curr->getParent());
            }
        }
        else {
            if (curr->getParent() == nullptr) {
                root_ = nullptr;
            }
            else if (curr == curr->getParent()->getLeft()) {
                curr->getParent()->setLeft(NULL);
            } else {
                curr->getParent()->setRight(NULL);
            }
        }
        
        delete curr;
    }
}



template<class Key, class Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::predecessor(Node<Key, Value>* current)
{
    // TODO DONE
    if (current == NULL) return NULL;

    if (current->getLeft() != NULL) {

        Node<Key, Value>* temp = current->getLeft();
        while (temp->getRight() != nullptr) {
            temp = temp->getRight();
        }

        return temp;
    }
    else 
    {
        Node<Key, Value>* temp = current;
        Node<Key, Value>* parent = temp->getParent();
        while (temp != nullptr && parent != nullptr && temp == parent->getLeft()) {
            temp = parent;
            parent = temp->getParent();
        }
        return parent;
    }
    
    return NULL;
}

template<class Key, class Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::findMinInternal(Node<Key, Value>* root) const
{
    if (root == nullptr) return nullptr;

    Node<Key, Value> *min = root;

    while (min->getLeft() != NULL)
    {
        min = min->getLeft();
    }

    return min;
}

/**
* A method to remove all contents of the tree and
* reset the values in the tree for use again.
*
* Deletes all nodes inside the tree, resetting it to the empty tree. Runtime is O(n).
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::clear()
{
    clearHelper(root_);
    root_ = nullptr;
}

//TODO clear recursively

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::clearHelper(Node<Key, Value>* current) 
{
    if (current == nullptr) return;

    if (current->getLeft() != nullptr) clearHelper(current->getLeft());
    if (current->getRight() != nullptr) clearHelper(current->getRight());
    delete current;
}

/**
* A helper function to find the smallest node in the tree.
*
* Returns a pointer to the node with the smallest key.
* This function is used by the iterator.
* Runtime is O(h).
*/
template<typename Key, typename Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::getSmallestNode() const
{
    // TODO DONE
    if (root_ == NULL) return NULL;

    Node<Key, Value> *min = root_;

    while (min->getLeft() != NULL)
    {
        min = min->getLeft();
    }

    return min;
}

/**
* Helper function to find a node with given key, k and
* return a pointer to it or NULL if no item with that key
* exists
*
* Returns a pointer to the node with the specified key. Runtime is O(h).
*/
template<typename Key, typename Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::internalFind(const Key& key) const
{
    // TODO DONE
    Node<Key, Value> *curr = root_;

    while (curr != NULL)
    {
        if (curr->getKey() == key) {
            //std::cout << "found: " << curr->getItem().second << std::endl;
            return curr;
        }
        else if (key < curr->getKey()) curr = curr->getLeft();
        else if (key > curr->getKey()) curr = curr->getRight();
    }

    //std::cout << "found failed" << std::endl;
    return NULL;
}

/**
 * Return true iff the BST is balanced.
 *
 * Returns true if the BST is an AVL Tree
 * (that is, for every node, the height of its left subtree is within 1 of the height of its right subtree).
 * It is okay if your algorithm is not particularly efficient, as long as it is not O(n^2).
 * This function may help you debug your AVL Tree in the next part of this problem,
 * but it is mainly given as practice of writing recursive tree traversal algorithms.
 * Think about how a pre- or post-order traversal can help.
 */
template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::isBalanced() const
{
    return checkBalanced(root_) != -1;
}
template<typename Key, typename Value>
int BinarySearchTree<Key, Value>::checkBalanced(Node<Key, Value>* n) const
{
    if (n == nullptr) return 0;

    int leftBalance = checkBalanced(n->getLeft());
    int rightBalance = checkBalanced(n->getRight());

    if (leftBalance == -1 || rightBalance == -1) return -1;

    if (std::abs(rightBalance - leftBalance) > 1) return -1;

    return std::max(leftBalance, rightBalance) + 1;
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::nodeSwap( Node<Key,Value>* n1, Node<Key,Value>* n2)
{
    if((n1 == n2) || (n1 == NULL) || (n2 == NULL) ) {
        return;
    }
    Node<Key, Value>* n1p = n1->getParent();
    Node<Key, Value>* n1r = n1->getRight();
    Node<Key, Value>* n1lt = n1->getLeft();
    bool n1isLeft = false;
    if(n1p != NULL && (n1 == n1p->getLeft())) n1isLeft = true;
    Node<Key, Value>* n2p = n2->getParent();
    Node<Key, Value>* n2r = n2->getRight();
    Node<Key, Value>* n2lt = n2->getLeft();
    bool n2isLeft = false;
    if(n2p != NULL && (n2 == n2p->getLeft())) n2isLeft = true;


    Node<Key, Value>* temp;
    temp = n1->getParent();
    n1->setParent(n2->getParent());
    n2->setParent(temp);

    temp = n1->getLeft();
    n1->setLeft(n2->getLeft());
    n2->setLeft(temp);

    temp = n1->getRight();
    n1->setRight(n2->getRight());
    n2->setRight(temp);

    if( (n1r != NULL && n1r == n2) ) {
        n2->setRight(n1);
        n1->setParent(n2);
    }
    else if( n2r != NULL && n2r == n1) {
        n1->setRight(n2);
        n2->setParent(n1);

    }
    else if( n1lt != NULL && n1lt == n2) {
        n2->setLeft(n1);
        n1->setParent(n2);

    }
    else if( n2lt != NULL && n2lt == n1) {
        n1->setLeft(n2);
        n2->setParent(n1);

    }


    if(n1p != NULL && n1p != n2) {
        if(n1isLeft) n1p->setLeft(n2);
        else n1p->setRight(n2);
    }
    if(n1r != NULL && n1r != n2) {
        n1r->setParent(n2);
    }
    if(n1lt != NULL && n1lt != n2) {
        n1lt->setParent(n2);
    }

    if(n2p != NULL && n2p != n1) {
        if(n2isLeft) n2p->setLeft(n1);
        else n2p->setRight(n1);
    }
    if(n2r != NULL && n2r != n1) {
        n2r->setParent(n1);
    }
    if(n2lt != NULL && n2lt != n1) {
        n2lt->setParent(n1);
    }

    if(this->root_ == n1) {
        this->root_ = n2;
    }
    else if(this->root_ == n2) {
        this->root_ = n1;
    }

}

/**
 * Lastly, we are providing you with a print function,
   BinarySearchTree::printRoot().
   Just call it with a node to start printing at, e.g:
   this->printRoot(this->root_) // or any other node pointer

   It will print up to 5 levels of the tree rooted at the passed node,
   in ASCII graphics format.
   We hope it will make debugging easier!
  */

// include print function (in its own file because it's fairly long)
#include "print_bst.h"

/*
---------------------------------------------------
End implementations for the BinarySearchTree class.
---------------------------------------------------
*/

#endif
