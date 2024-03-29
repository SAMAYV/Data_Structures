#include<bits/stdc++.h> 
using namespace std; 
   
class Node  
{  
    public: 
    int key;  
    Node *left;  
    Node *right;  
    int height;  
};  
  
int max(int a, int b);   
int height(Node *N)  
{  
    if (N == NULL)  
        return 0;  
    return N->height;  
}   
int max(int a, int b)  
{  
    return (a > b)? a : b;  
}  
  
Node* newNode(int key)  
{  
    Node* node = new Node(); 
    node->key = key;  
    node->left = NULL;  
    node->right = NULL;  
    node->height = 1;              
    return(node);  
}  
   
Node *rightRotate(Node *y)  
{  
    Node *x = y->left;  
    Node *T2 = x->right;  
    x->right = y;  
    y->left = T2;  
    y->height = max(height(y->left), 
                    height(y->right)) + 1;  
    x->height = max(height(x->left), 
                    height(x->right)) + 1;   
    return x;  
}  
   
Node *leftRotate(Node *x)  
{  
    Node *y = x->right;  
    Node *T2 = y->left;  
    y->left = x;  
    x->right = T2;   
    x->height = max(height(x->left),     
                    height(x->right)) + 1;  
    y->height = max(height(y->left),  
                    height(y->right)) + 1;  
    return y;  
}  
  
int getBalance(Node *N)  
{  
    if (N == NULL)  
        return 0;  
    return height(N->left) - height(N->right);  
}  
   
Node* insert(Node* node, int key)  
{  
    if (node == NULL)  
        return(newNode(key));  
  
    if (key < node->key)  
        node->left = insert(node->left, key);  
    else if (key > node->key)  
        node->right = insert(node->right, key);  
    else // Equal keys are not allowed in BST  
        return node;  
  
    node->height = 1 + max(height(node->left),  
                        height(node->right));  
  
    int balance = getBalance(node);  
  
    // Left Left Case  
    if (balance > 1 && key < node->left->key)  
        return rightRotate(node);  
    // Right Right Case  
    if (balance < -1 && key > node->right->key)  
        return leftRotate(node);  
    // Left Right Case  
    if (balance > 1 && key > node->left->key)  
    {  
        node->left = leftRotate(node->left);  
        return rightRotate(node);  
    }  
    // Right Left Case  
    if (balance < -1 && key < node->right->key)  
    {  
        node->right = rightRotate(node->right);  
        return leftRotate(node);  
    }  
    return node;  
}  
 
void inOrder(Node *root)  
{  
    if(root != NULL)  
    {  
        inOrder(root->left);
        cout << root->key << " ";    
        inOrder(root->right);  
    }  
}  
Node * minValueNode(Node* node)  
{  
    Node* current = node;  
    while (current->left != NULL)  
        current = current->left;  
    return current;  
}  

Node* deleteNode(Node* root, int key)  
{  
       
    if (root == NULL)  
        return root;   
    if ( key < root->key )  
        root->left = deleteNode(root->left, key);  
    else if( key > root->key )  
        root->right = deleteNode(root->right, key);  
    else
    {  
        if((root->left == NULL) || (root->right == NULL))  
        {  
            Node *temp = root->left ? root->left : root->right;  
            if (temp == NULL)  
            {  
                temp = root;  
                root = NULL;  
            }  
            else   
            *root = *temp; 
            free(temp);  
        }  
        else
        {  
            Node* temp = minValueNode(root->right);  
            root->key = temp->key;  
            root->right = deleteNode(root->right,temp->key);  
        }  
    }  
    if (root == NULL)  
    return root;  
  
    root->height = 1 + max(height(root->left),  
                           height(root->right));  
  
    int balance = getBalance(root);  
  
    // Left Left Case  
    if (balance > 1 &&  
        getBalance(root->left) >= 0)  
        return rightRotate(root);  
  
    // Left Right Case  
    if (balance > 1 &&  
        getBalance(root->left) < 0)  
    {  
        root->left = leftRotate(root->left);  
        return rightRotate(root);  
    }  
  
    // Right Right Case  
    if (balance < -1 &&  
        getBalance(root->right) <= 0)  
        return leftRotate(root);  
  
    // Right Left Case  
    if (balance < -1 &&  
        getBalance(root->right) > 0)  
    {  
        root->right = rightRotate(root->right);  
        return leftRotate(root);  
    }  
  
    return root;  
}    
int main()  
{  
    Node *root = NULL;
    char u;
    int ch;
      do
      {
        cout<<"Enter your preference: 1 for insert, 2 for delete, 3 for inoder traversal"<<endl;
        cin>>ch;
        int x,y;
        switch (ch)
        {
            case 1 : cin>>x; 
                    root = insert(root,x);
                    break;
            case 2 : cin>>y;
                    root = deleteNode(root,y);
                    break;
            case 3 : inOrder(root);
                    break;
            default : cout<<"Wrong case entered"<<endl;
                    break;
        }  
        cout<<"Do you want to continue?(Y/y for Yes and N/n for No"<<endl;
        cin>>u;
      } while(u=='Y' || u=='y');  
    return 0;  
}  