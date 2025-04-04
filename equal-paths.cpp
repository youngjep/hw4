#ifndef RECCHECK
//if you want to add any #includes like <iostream> you must do them here (before the next endif)

#endif

#include "equal-paths.h"

//#include <algorithm>
using namespace std;


// You may add any prototypes of helper functions here

int getHeight(Node* root) {

    if (root == nullptr) return 0;

    int leftH = getHeight(root->left);
    int rightH = getHeight(root->right);

    if (leftH > rightH) return leftH + 1;
    else return rightH + 1;
    //return std::max(leftH, rightH) + 1;
}

bool equalPaths(Node * root)
{
    // Add your code below
    if (root == nullptr) return true;

    bool isValidL = equalPaths(root->left);
    bool isValidR = equalPaths(root->right);

    if (root->left != nullptr && root->right != nullptr)
    {
        int leftH = getHeight(root->left);
        int rightH = getHeight(root->right);

        return leftH == rightH;
    }

    return isValidL && isValidR;
}

