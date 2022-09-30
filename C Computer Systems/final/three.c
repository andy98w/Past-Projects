#include "final.h"

#include <stdio.h>
int findDepth(int d, int v, BinaryTree *tree){
        if(tree==NULL)
		return -1;
        if(tree->val == v)
                return d;
        int depth = findDepth(d+1,v,tree->left);
	if(depth!=-1){
		return depth;
	}
	depth = findDepth(d+1,v,tree->right);
	return depth;
}
int depth_of_value(int value, BinaryTree *tree) {
	if(tree==NULL)
		return -1;
	  int depth = 0;
	  return findDepth(depth,value,tree);
}
//
//                   NULL NULL
//     NULL NULL NULL  42
//         3         15
//            14
