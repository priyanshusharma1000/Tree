// Online C++ compiler to run C++ program online
#include <iostream>
#include<bits/stdc++.h>
using namespace std;
class Node{
    public:
    int data;
    Node* left;
    Node* right;
    Node(int data){
        this->data=data;
        left=right=NULL;
    }
};
int height(Node* root){
    if(root==NULL)
    return 0;
    return max(height(root->left),height(root->right))+1;
}


int diameter(Node* root){
    if(root==NULL)
    return 0;

    int op1 = diameter(root->left);
    int op2 = diameter(root->right);
    int op3 = height(root->left)+height(root->right)+1;
    return max(op1,max(op2,op3));
}



pair<int,int>diameterfast(Node* root){
    if(root==NULL){
        pair<int,int>p = make_pair(0,0);
        return p;
    }

    pair<int,int>leftans = diameterfast(root->left);
    pair<int,int>rightans = diameterfast(root->right);

    int op1 = leftans.first;
    int op2 = rightans.first;
    int op3 = leftans.second+rightans.second+1;

    pair<int,int>ans;
    ans.first=max(op1,max(op2,op3));
    ans.second=max(leftans.second,rightans.second)+1;
    return ans;

}


void findtopview(Node*root,vector<int>&topview){
 map<int,int>mp;
 queue<pair<Node*,int>>q;
 q.push({root,0});
 mp[0]=root->data;
while(!q.empty()){
pair<Node*,int>p = q.front();
q.pop();
if(mp.find(p.second)==mp.end())
mp[p.second]=p.first->data;

if(p.first->left!=NULL)
q.push({p.first->left,p.second-1});

if(p.first->right!=NULL)
q.push({p.first->right,p.second+1});

}

for(auto i:mp){
    topview.push_back(i.second);
}
}

void findbottomview(Node*root,vector<int>&bottomview){
 map<int,int>mp;
 queue<pair<Node*,int>>q;
 q.push({root,0});
 mp[0]=root->data;
while(!q.empty()){
pair<Node*,int>p = q.front();
q.pop();
mp[p.second]=p.first->data;
if(p.first->left!=NULL)
q.push({p.first->left,p.second-1});

if(p.first->right!=NULL)
q.push({p.first->right,p.second+1});

}

for(auto i:mp){
    bottomview.push_back(i.second);
}
}

void findleftview(Node*root,vector<int>&leftview){
    queue<pair<Node*,int>>q;
    q.push({root,0});
    leftview.push_back(root->data);
    while(!q.empty()){
        pair<Node*,int>p = q.front();
        q.pop();
        if(leftview.size()==p.second)
        leftview.push_back(p.first->data);
        if(p.first->left!=NULL)
        q.push({p.first->left,p.second+1});

        if(p.first->right!=NULL)
        q.push({p.first->right,p.second+1});

    }
}

void findrightview(Node*root,vector<int>&rightview){
    queue<pair<Node*,int>>q;
    q.push({root,0});
    rightview.push_back(root->data);
    while(!q.empty()){
        pair<Node*,int>p = q.front();
        q.pop();
        if(rightview.size()==p.second)
        rightview.push_back(p.first->data);
        if(p.first->right!=NULL)
        q.push({p.first->right,p.second+1});
        if(p.first->left!=NULL)
        q.push({p.first->left,p.second+1});

        

    }
}
void findzigzagtraversal(Node* root,vector<int>&zigzag,bool lefttoright){
 queue<Node*>q;
 q.push(root);
 while(!q.empty()){
    int size = q.size();
    vector<int>p(size);
    for(int i=0;i<size;i++){
        Node* temp = q.front();
        q.pop();
        int index = lefttoright?i:size-i-1;
        p[index]= temp->data;
        if(temp->left)
        q.push(temp->left);
        if(temp->right)
        q.push(temp->right);
    }
    lefttoright=!lefttoright;
    for(auto i:p)
    zigzag.push_back(i);
 }

}
bool isidentical(Node* root1,Node* root2){
    if(root1==NULL && root2==NULL)
    return true;
    if(root1!=NULL && root2==NULL)
    return false;
    if(root1==NULL && root2!=NULL)
    return false;
    if(root1->data!=root2->data)
    return false;

    bool leftans = isidentical(root1->left,root2->left);
    bool rightans = isidentical(root1->right,root2->right);
    return leftans && rightans;
}

bool isHeightBalanced(Node* root){
    if(root==NULL)
    return true;

    bool leftans = isHeightBalanced(root->left);
    bool rightans = isHeightBalanced(root->right);
    bool op3 = abs(height(root->left)-height(root->right))<=1;
    return leftans && rightans && op3;  // O(n^2)
}

// optimized

pair<bool,int> isHeightBalancedfast(Node* root){
    if(root==NULL)
    {
        pair<bool,int>p = make_pair(true,0);
        return p;
    }

    pair<bool,int>leftans = isHeightBalancedfast(root->left);
    pair<bool,int>rightans = isHeightBalancedfast(root->right);

    pair<bool,int>ans;

    ans.first = leftans.first && rightans.first && (abs(leftans.second-rightans.second)<=1);
    ans.second = max(leftans.second,rightans.second)+1;
    return ans;


}

Node* buildtree(Node* root){
int data;

cin>>data;
if(data==-1)
return NULL;

root = new Node(data);
cout<<"enter the data to be put in the left of "<<data<<endl;
root->left=buildtree(root->left);

cout<<"enter the data to be put in the right of "<<data<<endl;
root->right=buildtree(root->right);

return root;
}
Node* findlca(Node* root,int n1,int n2){
    if(root==NULL)
    return NULL;

    if(root->data==n1 || root->data==n2)
    return root;

    Node* leftans = findlca(root->left,n1,n2);
    Node* rightans = findlca(root->right,n1,n2);

    if(leftans==NULL && rightans==NULL)
    return NULL;
    if(leftans!=NULL && rightans==NULL)
    return leftans;
    if(leftans==NULL && rightans!=NULL)
    return rightans;
    return root;
}



void printtree(Node* root){
    queue<Node*>q;
    q.push(root);
    q.push(NULL);
    
    while(!q.empty()){
        Node* temp = q.front();
         q.pop();
        if(temp==NULL){
            cout<<endl<<endl;
            if(q.size()>0)
            q.push(NULL);
        }
        else{
            cout<<temp->data<<"  ";
            if(temp->left)
            q.push(temp->left);
            if(temp->right)
            q.push(temp->right);
        }
    }
}


void findinorder(Node* root,vector<int>&inorder){
    if(root==NULL)
    return;
    findinorder(root->left,inorder);
    inorder.push_back(root->data);
    findinorder(root->right,inorder);
    
}


void createmapping(vector<int>inorder,unordered_map<int,int>&NodeToindex){
    for(int i=0;i<inorder.size();i++){
        NodeToindex[inorder[i]]=i;
    }
}


void findpreorder(Node* root,vector<int>&preorder){
    if(root==NULL)
    return;
    preorder.push_back(root->data);
    findpreorder(root->left,preorder);
    findpreorder(root->right,preorder);
    
}


Node* solve(vector<int>inorder,vector<int>preorder,int inorderstart,int inorderend,int& preorderindex,int n,unordered_map<int,int>&NodeToindex){
    if(inorderstart>inorderend || preorderindex>=n)
    return NULL;
    
    int element = preorder[preorderindex++];
    Node* root = new Node(element);
    int pos = NodeToindex[element];
    
    root->left=solve(inorder,preorder,inorderstart,pos-1,preorderindex,n,NodeToindex);
    root->right=solve(inorder,preorder,pos+1,inorderend,preorderindex,n,NodeToindex);
     
     return root;
}

int main() {
    Node* root;
    cout<<"enter data"<<endl;
    root = buildtree(root);
    printtree(root);
    vector<int>inorder;
    vector<int>preorder;
    findinorder(root,inorder);
    findpreorder(root,preorder);
    
    cout<<"inorder of tree is"<<endl;
    for(auto i:inorder)
    cout<<i<<" ";
    
    cout<<endl;
    
    cout<<"preorder of tree is"<<endl;
    for(auto i:preorder)
    cout<<i<<" ";
    cout<<endl<<endl;
    
    
    
    unordered_map<int,int>NodeToindex;
    createmapping(inorder,NodeToindex);
    int n = inorder.size();
    
    int inorderstart = 0;
    int inorderend = n-1;
    int preorderindex =0;
    
    Node* ans = solve(inorder,preorder,inorderstart,inorderend,preorderindex,n,NodeToindex);
    cout<<endl<<endl;
    
    printtree(ans);
    cout<<endl<<endl;
    
    cout<<endl<<"height of binary tree is "<<endl<<height(root);
    cout<<endl<<endl<<"diameter of binary tree is "<<diameter(root)<<endl;

    cout<<endl<<endl<<"diameter of binary tree using diameterfast function "<<diameterfast(root).first<<endl;


    vector<int>topview;
    findtopview(root,topview);

    cout<<endl<<endl<<"topview of binary tree is "<<endl;
    for(auto i:topview)
    cout<<i<<" ";


    vector<int>bottomview;
    findbottomview(root,bottomview);

    cout<<endl<<endl<<"bottomview of binary tree is "<<endl;
    for(auto i:bottomview)
    cout<<i<<" ";
   
   vector<int>leftview;
   findleftview(root,leftview);
   cout<<endl<<endl<<"leftview of binary tree is "<<endl;
   for(auto i:leftview)
   cout<<i<<" ";



   vector<int>rightview;
   findrightview(root,rightview);
   cout<<endl<<endl<<"rightview of binary tree is "<<endl;
   for(auto i:rightview)
   cout<<i<<" ";


  cout<<endl<<endl;
  cout<<"Now check your tree is height balanced or not is isheightbalanced function"<<endl;
  if(isHeightBalanced(root))
  cout<<"Tree Is Height Balanced"<<endl;
  else
  cout<<"Tree Is Not Height Balanced"<<endl;

  cout<<"Now check your tree is height balanced or not is isheightbalancedfast function"<<endl;
  if(isHeightBalancedfast(root).first)
  cout<<"Tree Is Height Balanced"<<endl;
  else
  cout<<"Tree Is Not Height Balanced"<<endl;


  cout<<"Now zigzag traversal"<<endl;
  vector<int>zigzag;
  findzigzagtraversal(root,zigzag,true);
  for(auto i:zigzag)
  cout<<i<<" ";

cout<<endl<<"Now we want to learn the concept of identical trees whether two trees are identical, so build a tree you want to check with root tree"<<endl;
cout<<"ENTER THE DATA"<<endl;
Node* Newtree = buildtree(Newtree);

if(isidentical(root,Newtree))
cout<<"Both Tree Are Identical"<<endl;
else
cout<<"Both Tree Are Not Identical"<<endl;

cout<<"we learn the concept of lowest common ancestor"<<endl;
cout<<"ENTER THE TWO NODE WHOSE YOU WANT TO FIND LOWEST COMMON ANCESTOR"<<endl;
int data1,data2;
cin>>data1>>data2;
Node* lca = findlca(root,data1,data2);
if(lca==NULL)
cout<<"data no present in tree"<<endl;
else
cout<<"lowest common ancestor of these two nodes is ->"<<lca->data;
cout<<endl;
return 0;
}