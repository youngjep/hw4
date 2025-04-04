#ifndef AVLBST_H
#define AVLBST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <cstdint>
#include <algorithm>
#include "bst.h"

struct KeyError { };

/**
* A special kind of node for an AVL tree, which adds the balance as a data member, plus
* other additional helper functions. You do NOT need to implement any functionality or
* add additional data members or helper functions.
*/
template <typename Key, typename Value>
class AVLNode : public Node<Key, Value>
{
public:
    // Constructor/destructor.
    AVLNode(const Key& key, const Value& value, AVLNode<Key, Value>* parent);
    virtual ~AVLNode();

    // Getter/setter for the node's height.
    int8_t getBalance () const;
    void setBalance (int8_t balance);
    void updateBalance(int8_t diff);

    // Getters for parent, left, and right. These need to be redefined since they
    // return pointers to AVLNodes - not plain Nodes. See the Node class in bst.h
    // for more information.
    virtual AVLNode<Key, Value>* getParent() const override;
    virtual AVLNode<Key, Value>* getLeft() const override;
    virtual AVLNode<Key, Value>* getRight() const override;

protected:
    int8_t balance_;    // effectively a signed char
};

/*
  -------------------------------------------------
  Begin implementations for the AVLNode class.
  -------------------------------------------------
*/

/**
* An explicit constructor to initialize the elements by calling the base class constructor
*/
template<class Key, class Value>
AVLNode<Key, Value>::AVLNode(const Key& key, const Value& value, AVLNode<Key, Value> *parent) :
    Node<Key, Value>(key, value, parent), balance_(0)
{

}

/**
* A destructor which does nothing.
*/
template<class Key, class Value>
AVLNode<Key, Value>::~AVLNode()
{

}

/**
* A getter for the balance of a AVLNode.
*/
template<class Key, class Value>
int8_t AVLNode<Key, Value>::getBalance() const
{
    return balance_;
}

/**
* A setter for the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::setBalance(int8_t balance)
{
    balance_ = balance;
}

/**
* Adds diff to the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::updateBalance(int8_t diff)
{
    balance_ += diff;
}

/**
* An overridden function for getting the parent since a static_cast is necessary to make sure
* that our node is a AVLNode.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getParent() const
{
    return static_cast<AVLNode<Key, Value>*>(this->parent_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getLeft() const
{
    return static_cast<AVLNode<Key, Value>*>(this->left_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getRight() const
{
    return static_cast<AVLNode<Key, Value>*>(this->right_);
}

/*
  -----------------------------------------------
  End implementations for the AVLNode class.
  -----------------------------------------------
*/

template <class Key, class Value>
class AVLTree : public BinarySearchTree<Key, Value>
{
public:
    virtual void insert (const std::pair<const Key, Value> &new_item); // TODO
    virtual void remove(const Key& key);  // TODO
    virtual void showBalanceOfAll(); //DEBUG
protected:
    virtual void nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2);

    // Add helper functions here
    virtual void insertFix( AVLNode<Key,Value>* p, AVLNode<Key,Value>* n);
    virtual void removeFix( AVLNode<Key,Value>* n, int diff);
    //TODO
    //rotate left
    virtual void rotateLeft(AVLNode<Key,Value>* n);
    //rotate right
    virtual void rotateRight(AVLNode<Key,Value>* n);


};

/*
 * Recall: If key is already in the tree, you should 
 * overwrite the current value with the updated value.
 */
template<class Key, class Value>
void AVLTree<Key, Value>::insert (const std::pair<const Key, Value> &new_item)
{
    // TODO
    if (this->root_ == nullptr) 
    {
        this->root_ = new AVLNode<Key, Value>(new_item.first, new_item.second, nullptr);
        // this automatically set balance to 0
        return;
    }

    AVLNode<Key, Value> *temp = static_cast<AVLNode<Key, Value>*>(this->root_);
    AVLNode<Key, Value> *parent = nullptr;
    bool isLeft;

    while (temp != nullptr) 
    {
        parent = temp;

        if (new_item.first == temp->getKey())
        {
            temp->setValue(new_item.second); //found just replace
            return;
        }
        else if (new_item.first < temp->getKey()) 
        {
            temp = temp->getLeft();
            isLeft = true;
        }
        else 
        {
            temp = temp->getRight();
            isLeft = false;
        }
    }

    if (parent != nullptr) 
    {
        AVLNode<Key, Value> *node = new AVLNode<Key, Value>(new_item.first, new_item.second, parent);

        if (isLeft) // the new node needs to be inserted to the left.
        {
            parent->setLeft(node);
            parent->updateBalance(-1); // now heavier to the left
            // so if it was 1 -> it would be 0
        }
        else 
        {
            parent->setRight(node);
            parent->updateBalance(1);
            // so if it was -1, -> it would be 0
        }

        if (parent->getBalance() != 0)
        {
            insertFix(parent, node);
        }
    }
}

template<class Key, class Value>
void AVLTree<Key, Value>::insertFix(AVLNode<Key,Value>* p, AVLNode<Key,Value>* n)
{
    if (p == nullptr || p->getParent() == nullptr)
        return;

    AVLNode<Key, Value>* g = p->getParent();

    if (p == g->getLeft()) 
    {
        g->updateBalance(-1);

        switch (g->getBalance()) 
        {
            case 0:
                return;
            case -1:
                insertFix(g, p);
                break;
            case -2:
                if (n == p->getLeft())  
                //ZIGZIG LEFT LEFT
                {
                    rotateRight(g);
                    p->setBalance(0);
                    g->setBalance(0);
                }
                else // ZIG ZAG LEFT RIGHT
                {
                    rotateLeft(p);
                    rotateRight(g);
                    int b = n->getBalance();
                    if (b == -1) 
                    {
                        p->setBalance(0);
                        g->setBalance(1);
                    }
                    else if (b == 0) 
                    {
                        p->setBalance(0);
                        g->setBalance(0);
                    }
                    else 
                    { // b is 1
                        p->setBalance(-1);
                        g->setBalance(0);
                    }

                    n->setBalance(0);
                }
                break;
        }
    }
    else 
    {
        g->updateBalance(1); // flip for right child

        switch (g->getBalance()) 
        {
            case 0:
                return;
            case 1:
                insertFix(g, p);
                break;
            case 2:
                if (n == p->getRight()) 
                { //RIGHT RIGHT ZIG ZIG
                    rotateLeft(g);
                    p->setBalance(0);
                    g->setBalance(0);
                }
                else 
                { // RIGHT LEFT ZIG ZAG
                    rotateRight(p);
                    rotateLeft(g);
                    
                    int b = n->getBalance();
                    if (b == 1) 
                    {
                        p->setBalance(0);
                        g->setBalance(-1);
                    }
                    else if (b == 0) {
                        p->setBalance(0);
                        g->setBalance(0);
                    }
                    else 
                    {  // -1
                        p->setBalance(1);
                        g->setBalance(0);
                    }

                    n->setBalance(0);
                }
                break;
        }
    }
}


template<class Key, class Value>
void AVLTree<Key, Value>::rotateLeft(AVLNode<Key,Value>* n) 
{
    if (n == nullptr || n->getRight() == nullptr) return;

    //take a right child then make it parent (OK)
    //make the original parent the new left child (OK)

    AVLNode<Key, Value> *originalGrandparent = n->getParent();
    AVLNode<Key, Value> *newParent = n->getRight();
    AVLNode<Key, Value> *newParentOriginalLeft = n->getRight()->getLeft();

    n->setParent(newParent); // right child is now the parent
    newParent->setLeft(n);

    n->setRight(newParentOriginalLeft);
    if (newParentOriginalLeft != nullptr) newParentOriginalLeft->setParent(n);

    newParent->setParent(originalGrandparent);
    
    if (originalGrandparent != nullptr) 
    {
        if (originalGrandparent->getRight() == n) 
            originalGrandparent->setRight(newParent);
        else
            originalGrandparent->setLeft(newParent);
    }
    else 
    {
        this->root_ = newParent;
    }
}

template<class Key, class Value>
void AVLTree<Key, Value>::rotateRight(AVLNode<Key,Value>* n) 
{
    if (n == nullptr || n->getLeft() == nullptr) return;

    //take a left child then make it parent
    //make the original parent the new right child

    AVLNode<Key, Value> *originalGrandparent = n->getParent();
    AVLNode<Key, Value> *newParent = n->getLeft();
    AVLNode<Key, Value> *newParentOriginalRight = n->getLeft()->getRight();

    n->setParent(newParent);
    newParent->setRight(n);

    n->setLeft(newParentOriginalRight);
    if (newParentOriginalRight != nullptr) newParentOriginalRight->setParent(n);

    newParent->setParent(originalGrandparent);

    if (originalGrandparent != nullptr) 
    {
        if (originalGrandparent->getRight() == n) 
            originalGrandparent->setRight(newParent);
        else
            originalGrandparent->setLeft(newParent);
    }
    else 
    {
        this->root_ = newParent;
    }
}

/*
 * Recall: The writeup specifies that if a node has 2 children you
 * should swap with the predecessor and then remove.
 */
template<class Key, class Value>
void AVLTree<Key, Value>::remove(const Key& key)
{
    // TODO
    AVLNode<Key, Value> *n = static_cast<AVLNode<Key, Value>*>(this->root_);

    while (n != nullptr) 
    {
        if (key == n->getKey()) 
            break; // found!
        else if (key < n->getKey())
            n = n->getLeft();
        else n = n->getRight();
    }

    if (n == nullptr) return; //failed to find one.

    //std::cout << "removing node: " << n->getKey() << std::endl;

    int diff = 0;

    if (n->getLeft() != nullptr && n->getRight() != nullptr) //case with 2 children
    {
        AVLNode<Key, Value>* replacement = static_cast<AVLNode<Key, Value>*>(this->predecessor(n));

        nodeSwap(replacement, n);
    }
    // now the node is going to be have only one child or none

    AVLNode<Key, Value> *p = n->getParent();

    if (p != nullptr) 
    {
        if (p->getLeft() == n) // the node to be deleted is on the left
        {
            diff = 1;
            //std::cout << "the node to be deleted is on the left!" << std::endl;
        }
        else if (p->getRight() == n) // the node to be deleted is on the right
        {
            diff = -1;
            //std::cout << "the node to be deleted is on the right!" << std::endl;
        }
        else 
        {
            std::cout << "n is not a child of p!" << std::endl;
        }
    }

    // now n is the node to be deleted.
    // as we swapped with pred if had two children, the n has either one child or none.

    if (n->getLeft() != nullptr) // do the stiching
    {
        // left
        if (p == nullptr) 
        {
            this->root_ = n->getLeft();
            this->root_->setParent(nullptr);
        }
        else 
        {
            if (diff == 1) // n is a left child
            {
                p->setLeft(n->getLeft());
                n->getLeft()->setParent(p);
            }
            else if (diff == -1) // n is a right child
            {
                p->setRight(n->getLeft());
                n->getLeft()->setParent(p);
            }
            else std::cout << "UNEXPECTED BEHAVIOUR" << std::endl;
        }
    }
    else if (n->getRight() != nullptr) 
    {
        // left
        if (p == nullptr) 
        {
            this->root_ = n->getRight();
            this->root_->setParent(nullptr);
        }
        else 
        {
            if (diff == 1) // n is a left child
            {
                p->setLeft(n->getRight());
                n->getRight()->setParent(p);
            }
            else if (diff == -1) // n is a right child
            {
                p->setRight(n->getRight());
                n->getRight()->setParent(p);
            }
            else std::cout << "UNEXPECTED BEHAVIOUR" << std::endl;
        }
    }
    else // no children of n
    {
        if (p == nullptr) 
        {
            this->root_ = nullptr;
        }
        else 
        {
            if (diff == 1) // n is a left child
            {
                //std::cout << "yup it's right" << std::endl;
                p->setLeft(nullptr);
            }
            else if (diff == -1) 
            {
                //std::cout << "yup it's left" << std::endl;
                p->setRight(nullptr);
            }
            else std::cout << "UNEXPECTED BEHAVIOUR" << std::endl;
            
        }
    }

    delete n;


    if (p != nullptr) 
    {
        //p->updateBalance(diff);

        //std::cout << "balance of P: " << static_cast<int>(p->getBalance()) << std::endl;
        //std::cout << "p is " << static_cast<int>(p->getKey()) << std::endl;

        //TODO here if?

        //if (p->getBalance > 1 && p->getBalance > 1)

        removeFix(p, diff);
        showBalanceOfAll(); //DEBUG

    }
}



template<class Key, class Value>
void AVLTree<Key, Value>::removeFix( AVLNode<Key,Value>* n, int diff)
{
    // TODO
    if (n == nullptr) return;


    //std::cout << "balance Before: " << static_cast<int>(n->getBalance()) << std::endl;
    //std::cout << "Diff to add is " << diff << std::endl;

    n->updateBalance(diff);
    //std::cout << "node balance after: " << static_cast<int>(n->getBalance()) << std::endl;

    AVLNode<Key, Value> *p = n->getParent(); 
    int ndiff;

    if (p != nullptr) 
    {
        if (n == p->getLeft()) 
            ndiff = 1;
        else ndiff = -1;
    }

    //std::cout << "balance after: " << static_cast<int>(n->getBalance()) << std::endl;
    
    //std::cout << "n is " << n->getKey() << std::endl;

    if (n->getBalance() <= -2) // its left heavy 
    {
        AVLNode<Key, Value> *c = n->getLeft(); 

        if (c->getBalance() == -1) //zig zig LEFT LEFT
        {
            std::cout << "LL" << std::endl;
            rotateRight(n);
            n->setBalance(0);
            c->setBalance(0);
            removeFix(p, ndiff);
        }
        else if (c->getBalance() == 0) 
        {
            //std::cout << "LL" << std::endl;
            rotateRight(n);
            n->setBalance(-1);
            c->setBalance(1); //DONE
        }
        else if (c->getBalance() == 1) // LEFT RIGHT
        {

            //std::cout << "LR" << std::endl;
            AVLNode<Key, Value> *g = c->getRight(); //taller child of n

            rotateLeft(c);
            rotateRight(n);

            if (g->getBalance() == 1) 
            {
                n->setBalance(0);
                c->setBalance(-1);
            }
            else if (g->getBalance() == 0) 
            {
                n->setBalance(0);
                c->setBalance(0);
            }
            else // -1
            {
                n->setBalance(1);
                c->setBalance(0);
            }

            g->setBalance(0);
            removeFix(p, ndiff);
        }
    }
    else if (n->getBalance() == -1) 
    {
        n->setBalance(-1); //DONE
    }
    else if (n->getBalance() == 1) 
    {
        n->setBalance(1); //DONE
    }
    else if (n->getBalance() == 0)
    {
        n->setBalance(0);
        removeFix(p, ndiff);
    }
    else if (n->getBalance() >= 2) // it's right heavy 
    {
        AVLNode<Key, Value> *c = n->getRight();
        
        //std::cout << "balance of c: " << static_cast<int>(c->getBalance()) << std::endl;

        if (c->getBalance() == 1) //zig zig RIGHT RIGHT
        {

            //std::cout << "RR" << std::endl;

            rotateLeft(n);
            n->setBalance(0);
            c->setBalance(0);

            //showBalanceOfAll(); //TEMP DEBUG
            //this->print();

            removeFix(p, ndiff);

        }
        else if (c->getBalance() == 0)  
        {
            //std::cout << "RR" << std::endl;

            rotateLeft(n);
            n->setBalance(1);
            c->setBalance(-1); //DONE
        }
        else if (c->getBalance() == -1)
        {
            //this->print();
            //showBalanceOfAll();

            // BEFORE 43 got changed, lets check the status
            //std::cout << "RL" << std::endl;

            AVLNode<Key, Value> *g = c->getLeft(); //taller child of n

            rotateRight(c);
            rotateLeft(n);

            // LETS QUICKY CHECK WHAT N , G, C are
            /*
            std::cout << "N " << n->getKey() << std::endl;
            std::cout << "G " << g->getKey() << std::endl;
            std::cout << "C " << c->getKey() << std::endl;
            */
            if (g->getBalance() == 1) 
            {
                n->setBalance(-1); //ok so this is wrong
                c->setBalance(0);

                //std::cout << "N " << n->getKey() << std::endl;
            }
            else if (g->getBalance() == 0) 
            {
                n->setBalance(0);
                c->setBalance(0);
            }
            else if (g->getBalance() == -1) 
            {
                n->setBalance(0);
                c->setBalance(1);
            }

            g->setBalance(0);
            removeFix(p, ndiff);
        }
    }
}

template<class Key, class Value>
void AVLTree<Key, Value>::nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2)
{
    BinarySearchTree<Key, Value>::nodeSwap(n1, n2);
    int8_t tempB = n1->getBalance();
    n1->setBalance(n2->getBalance());
    n2->setBalance(tempB);
}

template<class Key, class Value>
void AVLTree<Key, Value>::showBalanceOfAll() 
{
    int i = 1;
    for (typename AVLTree<Key, Value>::iterator it = this->begin(); it != this->end(); ++it) 
    {
        // Find the node corresponding to the key
        Node<Key, Value>* baseNode = this->internalFind(it->first);
        AVLNode<Key, Value>* avlNode = dynamic_cast<AVLNode<Key, Value>*>(baseNode);
        if (avlNode != nullptr) 
        {
            std::cout << " [" << i << "] -> " << static_cast<int>(avlNode->getBalance());
        }
        i++;
    }
    std::cout << std::endl;
}


#endif
