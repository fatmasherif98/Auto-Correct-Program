#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 5000

typedef struct Node
{
    char data[100];
    struct Node* left;
    struct Node * right;

} Node;


Node *root = NULL;
Node *pre = NULL;
Node *succ = NULL;
Node *nodeArray[SIZE];
int n=0;

void find_p_s(Node* root1,char* a)
{
    // If root is null return
		if(!root1)return ;

		//Go left Until null
		find_p_s(root1->left, a);

		//if given string char*a greater than the current root
		if(root1 && strcasecmp(a,root1->data)>0)
    {
        pre = root1;
    }

		//if given string char*a smaller than the current root
    else if(root1&&strcasecmp(root1->data , a)>0)
    {
			if((!succ) || (succ) && strcasecmp((succ)->data, root1->data) >0)
          succ = root1;
    }
		//Go right util null
		find_p_s(root1->right, a);


}

Node* newNode(char temp[])
{
    Node *new_node = (Node*)malloc(sizeof(Node));
    strcpy(new_node->data, temp);
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

Node* insert(Node* root, char temp[])
{
  /*  if (root == NULL)
    {
        root = newNode(temp);
    }
    else if (strcasecmp(temp, root->data) < 0)
    {
        root->left = insert(root->left, temp);

    }
    else
    {
        root->right = insert(root->right, temp);

    }

    return root; */
    Node* nw;
    nw = newNode(temp);


    if(root == NULL)
         root = nw;
        else if(strcasecmp(temp, root->data) < 0)
        {

            if( !root->left)
                root->left = nw;
            else
                insert(root->left, temp);
        } else if(strcasecmp(temp, root->data) > 0){
               if( !root->right)
                root->right = nw;
               else
                insert(root->right, temp);
        }


    return root;
}

void Intraverse(Node *root)
{
    if (root == NULL)
    {
        return;
    }
    Intraverse(root->left);
    nodeArray[n] = root;
    //printf("%s\n",root->data);
    n++;
    Intraverse(root->right);
}
void inOrderTraverse(Node* node)
{

    if(node)
    {
        inOrderTraverse(node->left);
        inOrderTraverse(node->right);
    }
}
void ReadingFromFile(FILE* fptr)
{
    char temp[100];
    if( fptr )
    {
        while( !feof(fptr))
        {
            fscanf(fptr, "%s",temp );
            root = insert(root, temp);

        }
    }
    else
    {
        printf("Error in reading ");
    }
    fclose(fptr);

}

Node* BalanceBST(Node *array[], int start, int end)
{

    if( start > end)
        return NULL;
    int mid = (start + end)/2;
    Node *root = array[mid];
    root->left = BalanceBST(array,start,mid-1 );
    root->right = BalanceBST(array,mid+1, end);
    return root;


}
int height(Node* node)
{
    int leftHeight, rightHeight;
    if(node)
    {
        if(node->left)
            leftHeight = height(node->left);
        else
            leftHeight = 0;
        if(node->right)
            rightHeight = height(node->right);
        else
            rightHeight = 0;
        return 1+ (leftHeight >= rightHeight? leftHeight: rightHeight);
    }
    else return 0;

}

Node* search(Node* root, char temp[])
{
    if(root)
    {
        if( strcasecmp(temp, root->data) == 0)
            return root;
        else if( strcasecmp(temp, root->data) < 0)
            search(root->left, temp);
        else
            search(root->right, temp);
    }
    else
        return NULL;

}
Node* SearchIt(Node* root, char word[]) //finds closest node to the wrong word
{
    Node *temp;
    temp = root;
    while( root )
    {
        temp = root;
        if( strcasecmp(word, root->data) == 0)
            return root;
        else if( strcasecmp(word, root->data) < 0)
        {
            root = root->left;
        }
        else
        {
            root = root->right;
        }
    }
    return temp;
}


int main()
{
    FILE *fptr;
    fptr = fopen( "English Dictionary.txt", "r");
    ReadingFromFile(fptr);
    Intraverse(root);
    int heightt;
    heightt = height(root);
    printf("Height before balancing %d \n", heightt);
    root = BalanceBST(nodeArray,0,n-1);
    heightt = height(root);
    printf("Height after balancing %d \n", heightt);
    char sentence[500];
    gets(sentence);
    Node* currentNode;
    char *token;
    token = strtok(sentence," ");

    while(token != NULL)
    {
        currentNode = search(root, token);
        if( currentNode )
        {
          printf("[%s] is correct\n", currentNode->data);
        }
        else
        {
					succ=NULL;
					pre=NULL;
          printf("\n[%s] not found\n",token);
          currentNode = SearchIt(root, token);
          find_p_s(root, currentNode->data);

          printf("Suggestions for [%s] : [%s] [%s] [%s]\n",token,currentNode->data,pre->data,succ->data);

          }
        token = strtok(NULL," ");
    }



    return 0;
}
