//Mert MUSLU


/*
    Note:
        I implemented this algorithm in GNU GCC Compiler.
*/


#include <stdio.h>
#include <stdlib.h>

// Creating a structure of AVL Tree
struct AVLT {
    int OccFreq;
    int height;
    int key;
    struct AVLT *left;
    struct AVLT *right;
    };

// Allocate a new node and assign NULL value for left and right child of Node with key inserted
struct AVLT* newAVL(int key) {
    struct AVLT* AVL = (struct AVLT*)malloc(sizeof(struct AVLT));
    AVL->key = key;
    AVL->height = 1;
    AVL->left = NULL;
    AVL->right = NULL;
    AVL->OccFreq = 1;
    return(AVL);
    };

// Basic PreOrder Struct
struct AVLT *PreOrderAVL(struct AVLT *a) {

    if(a == NULL)
        return;
    printf("%d ",a->key);
    PreOrderAVL(a->left);
    PreOrderAVL(a->right);
};

//Define Global Variables for output.
int CostOfAVL = 0;

/*          Write statements for single and double rotations
    1-) Single Rotation (Left/Left)
    2-) Single Rotation (Right/Right)
    3-) Double Rotation (Left/Right)
    4-) Double Rotation (Right/Left)
*/
struct AVLT *LeftLeft(struct AVLT *grand){
    /*           grand                             parent
                /                                 /    \                            "a" is still child of parent after rotation.
                parent                ->         a     grand                        RightC was child of parent, but after rotation, child of grand.
               /    \                                   /
              a    RightC                           RightC
    */
                struct AVLT *parent = grand->left;
                struct AVLT *RightC = parent->right;
                parent->right = grand;
                grand->left = RightC;

           if(height(grand->left) >= height(grand->right)) {
                grand->height = 1+height(grand->left);
           }
           else if (height(grand->right) > height(grand->left)) {
                grand->height = 1+height(grand->right);
           }
           if(height(parent->left) >= height(parent->right)) {
                parent->height = 1+height(parent->left);
           }
           else if (height(parent->right) > height(parent->left)) {
                parent->height = 1+height(parent->right);
           }
            return parent;
}
struct AVLT *RightRight(struct AVLT *grand) {
     /*           grand                                 parent
                  /   \                                 /    \                     *    "a","b","c" is still right child of parent after rotation.
                 a   parent                ->         grand    d                   **   LeftC was child of parent, but after rotation, child of grand.
                    /    \                           /   \                         ***  LeftC's value is not important, may have NULL value. Important case
                  LeftC   d                         a    LeftC                      is existing of left child.
                  /  \                                    /  \
                  b   c                                   b   c
        */
            struct AVLT *parent = grand->right;
            struct AVLT *LeftC = parent->left;
            parent->left = grand;
            grand->right = LeftC;

            if(height(grand->left) >= height(grand->right)) {
                grand->height = 1+height(grand->left);
           }
           else if (height(grand->right) > height(grand->left)) {
                grand->height = 1+height(grand->right);
           }
           if(height(parent->left) >= height(parent->right)) {
                parent->height = 1+height(parent->left);
           }
           else if (height(parent->right) > height(parent->left)) {
                parent->height = 1+height(parent->right);
           }
            return parent;
}
struct AVLT* LeftRight(struct AVLT *grand) {
     /*               grand                              Rchild
                    /      \                            /      \
              parent        d            ->         parent     grand
             /     \                                /   \      /   \
            a    Rchild                             a    b    c     d
                  /   \
                 b     c
    */
            grand->left = RightRight(grand->left);
            return LeftLeft(grand);
}
struct AVLT* RightLeft(struct AVLT *grand) {
    /*               grand                                 Lchild
                    /      \                               /    \
                    a    parent           ->           grand    parent
                          /    \                       /   \     /   \
                        Lchild  d                     a     b   c     d
                         /  \
                        b    c
    */
            grand->right = LeftLeft(grand->right);
            return RightRight(grand);
}


//  a function that inserts a next number to AVL Tree
  int InsertAVL(struct AVLT *avlt, int a){

    //First Number is root
    if(avlt == NULL){
        CostOfAVL++;
        return newAVL(a);
    }

    //add 1 to CostOfAVL whether the condition is true or not.
    //Because, If "if" condition is true, successful search
    //If it is false, unsuccessful search



    //Insert to left
    if(avlt->key > a) {
        CostOfAVL++;
        avlt->left = InsertAVL(avlt->left,a);
    }
    //Insert to right
    else if(avlt->key < a) {
        CostOfAVL++;
        avlt->right = InsertAVL(avlt->right,a);
    }
    //blabla else
    else if(avlt->key == a){
        CostOfAVL++;
        avlt->OccFreq++;
    }

    if(height(avlt->left) >= height(avlt->right)) {
        avlt->height = 1 + height(avlt->left);
    }
    else if (height(avlt->right) > height(avlt->left)) {
        avlt->height = 1 + height(avlt->right);
    }

    // the height of the left subtree is 2 more than the height of the right subtree.
    // the height of the right subtree is 2 more than the height of the left subtree.

    // is the right child's key greater than the new inserted key,
    // if it is, goto RightLeft Rotation ; if it is not, goto RightRight Rotation.

    // is the left child's key greater than the new inserted key,
    // if it is, goto LeftLeft Rotation ; if it is not, goto LeftRight Rotation.

    //LeftLeft case, (1 time unit)
  if      (BalanceCondition(avlt) >= 2   &&   a < avlt->left->key) {
    CostOfAVL++;
    return LeftLeft(avlt);
  }
    //RightRight case, (1 time unit)
  else if (BalanceCondition(avlt) <= -2  &&   a > avlt->right->key) {
    CostOfAVL++;
    return RightRight(avlt);
  }
  //LeftRight case, (2 time units)
  else if (BalanceCondition(avlt) >= 2   &&   a > avlt->left->key) {
    CostOfAVL++;
    CostOfAVL++;
    return LeftRight(avlt);
  }
  //RightLeft case, (2 time units)
  else if (BalanceCondition(avlt) <= -2  &&   a < avlt->right->key) {
    CostOfAVL++;
    CostOfAVL++;
    return RightLeft(avlt);
  }
    return avlt;
}


// a function that checks the AVL Tree after inserting is violating the condition
// briefly, that function checks balance condition
int BalanceCondition(struct AVLT *cond) {
    if(cond == NULL) {
        return 0;
    }
    else if (cond  != NULL && cond->left == NULL) {
        return 0-height(cond->right);
    }
    else if (cond != NULL && cond->right == NULL) {
        return height(cond->left);
    }
    else {
    return (height(cond->left) - height(cond->right)); }
}
// Assign a height value for called Node
int height(struct AVLT* avltree) {
    if(avltree == NULL) {
        return 0;
    }
    else  {
        return avltree->height;
    }
}

// main function (Get input values from .txt files via File commands)
int main(int argc,char* argv[]){
    if(argc==1)
        printf("Error message!");


	if(argc >= 2) {

        struct AVLT *myAVL = NULL;
        struct AVLT *myAVL2 = NULL;

        FILE* File = fopen (argv[1], "r");

        int txtdata = 0;

        fscanf(File, "%d", &txtdata);
        while (!feof (File)){
        myAVL = InsertAVL(myAVL,txtdata);
        fscanf (File, "%d", &txtdata);
        }

    fclose (File);


        printf("Output1\n");
        printf("AVL tree:\n");
        PreOrderAVL(myAVL);
        printf("\nTotal cost: %d\n\n",CostOfAVL);
        return 0;
	}
}



/*
    /////////////////////////////////////////////////////////////////////////////
    *****************************************************************************
    -----------------------------------------------------------------------------
	        That main function get input manually. If you can't get input
            via command, you can also use this function.
    -----------------------------------------------------------------------------
    *****************************************************************************
    \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

*/


/*
int main(void){


	struct AVLT *myAVL = NULL;
    struct AVLT *myAVL2 = NULL;

    FILE* File = fopen ("input1.txt", "r");
    FILE* File2 = fopen ("input2.txt","r");

    int txtdata = 0;
    int txt2data = 0;

    fscanf(File, "%d", &txtdata);
    while (!feof (File)){
        myAVL = InsertAVL(myAVL,txtdata);
        fscanf (File, "%d", &txtdata);
    }
    fclose (File);


    printf("Output1\n");
    printf("AVL tree:\n");
    PreOrderAVL(myAVL);
    printf("\nTotal cost: %d\n\n",CostOfAVL);

    CostOfAVL = 0;

    fscanf(File2, "%d", &txt2data);
    while (!feof (File2)){
        myAVL2 = InsertAVL(myAVL2,txt2data);
        fscanf (File2, "%d", &txt2data);
    }
    fclose (File2);


    printf("\n\n\nOutput2\n");
    printf("AVL tree:\n");
    PreOrderAVL(myAVL2);
    printf("\nTotal cost: %d\n\n",CostOfAVL);


    return 0;
} */



