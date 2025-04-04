#include <iostream>
#include <map>
#include "bst.h"
#include "avlbst.h"

using namespace std;


int main(int argc, char *argv[])
{

    AVLTree<int, double> bst;
	bst.insert(std::make_pair(43, 1.0));
	bst.insert(std::make_pair(-109, 1.0));
	bst.insert(std::make_pair(107, 1.0));
	bst.insert(std::make_pair(-140, 1.0));
	bst.insert(std::make_pair(14, 1.0));
    bst.insert(std::make_pair(51, 1.0));
	bst.insert(std::make_pair(122, 1.0));
	bst.insert(std::make_pair(16, 1.0));
	bst.insert(std::make_pair(48, 1.0));
	bst.insert(std::make_pair(86, 1.0));
	bst.insert(std::make_pair(135, 1.0));
	bst.insert(std::make_pair(83, 1.0));
	bst.insert(std::make_pair(88, 1.0));

    bst.showBalanceOfAll();

    bst.print();
    bst.remove(-140);

    std::cout << "here balance is fucked: " << std::endl;
    bst.print();
    /*
	bst.remove(-109);
    std::cout << "Before any removals, tree is: " << std::endl;
    bst.print();
	bst.remove(48);
	bst.print();*/

    /*
    // Binary Search Tree tests
    BinarySearchTree<char,int> bt;
    bt.insert(std::make_pair('a',1));
    bt.insert(std::make_pair('b',2));
    
    cout << "Binary Search Tree contents:" << endl;
    for(BinarySearchTree<char,int>::iterator it = bt.begin(); it != bt.end(); ++it) {
        cout << it->first << " " << it->second << endl;
    }
    if(bt.find('b') != bt.end()) {
        cout << "Found b" << endl;
    }
    else {
        cout << "Did not find b" << endl;
    }
    cout << "Erasing b" << endl;
    bt.remove('b');

    // AVL Tree Tests
    AVLTree<char,int> at;
    at.insert(std::make_pair('a',1));
    at.insert(std::make_pair('b',2));

    cout << "\nAVLTree contents:" << endl;
    for(AVLTree<char,int>::iterator it = at.begin(); it != at.end(); ++it) {
        cout << it->first << " " << it->second << endl;
    }
    if(at.find('b') != at.end()) {
        cout << "Found b" << endl;
    }
    else {
        cout << "Did not find b" << endl;
    }
    cout << "Erasing b" << endl;
    at.remove('b');
    */
    return 0;
}
