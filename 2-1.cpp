//1、二叉树的基本操作算法实现
//(1) 利用二叉树字符串“A(B(D,E(H(J,K(L,M(,N))))),C(F,G(,I)))”创建二叉树的二叉链式存储结构；
//(2) 输出该二叉树；
//(3) 输出‘H’节点的左、右孩子结点值；
//(4) 输出该二叉树的结点个数、叶子结点个数、二叉树的度和高度。

// 2.	二叉树的各种遍历算法实现
// 实现上述二叉树的先序、中序和后序遍历的递归和非递归算法；

// 3.	线索二叉树的遍历
// 中序线索化上述二叉树并找出根结点的前驱和后继。
#include<bits/stdc++.h>
using namespace std;
int NodeNumber_=0,LeafNumber_=0,TreeHigh=0;
struct TreeNode {
    char val;
    TreeNode *left;
    TreeNode *right;
	bool rtag,ltag;
    TreeNode() {
      	 val='#'; left=NULL; right=NULL;
    }
};
struct Tree{
    TreeNode *Head;
	Tree(){
		  Head= new TreeNode();
	};
	void Init(string s) {
		TreeNode* tempNode, *&root=Head->left;
		stack<TreeNode*>st;
		int flag=0;
		cout<<root<<endl;
		for(int i=0;i<s.size();i++) {
			if (s[i] == '(') {
				flag = 1; 
				st.push(tempNode);
			}
			else if (s[i] == ',') {
				flag = 2;
			}
			else if (s[i] == ')') {
				st.pop();
			}
			else {
				tempNode = new TreeNode();
				tempNode->val = s[i];
				if (root==NULL){
					root = tempNode;
				}
				else {
					TreeNode*tempRoot = st.top();
					if (flag == 1)
						tempRoot->left = tempNode;
					else if (flag == 2)
						tempRoot->right = tempNode;
				}
			}
		}
	} 
 }*myTree;
 void ShowTree(TreeNode *root){
		if (root != NULL) {
		cout << root->val;
		if (root->left == NULL && root->right == NULL)return;
		cout << "(";
		ShowTree(root->left);
		if (root->right != NULL)cout << ",";
		ShowTree(root->right);
		cout << ")";
	}
 }	
void FindNode(TreeNode*root,char goal){
	TreeNode *tempNode=root;
	if(tempNode==NULL) return;
	if(tempNode->val==goal){
		cout<<"		该结点的左节点为： "<<tempNode->left->val<<endl;
		cout<<"		该结点的右节点为： "<<tempNode->right->val<<endl;
	}else{
		FindNode(tempNode->left,goal);
		FindNode(tempNode->right,goal);
	}
 }
 void NodeLeafNumber(TreeNode*root){
	TreeNode *tempNode=root;
	if(tempNode==NULL) {
		return;
	}
	if(tempNode!=NULL){
		NodeNumber_++;
		if(tempNode->left==NULL&&tempNode->right==NULL){
			LeafNumber_++;
		}
	}
	NodeLeafNumber(tempNode->left);
	NodeLeafNumber(tempNode->right);
 }
int GetBHigh(TreeNode*root){
	if(root==NULL||(root!=NULL&&root->left==NULL&&root->right==NULL))  return 0;
	TreeNode *tempNode=root;
	if(tempNode->left!=NULL&&tempNode->right!=NULL) return 2;
	if(tempNode->left==NULL&&tempNode->right!=NULL){
		 GetBHigh(tempNode->right);
	}
	if(tempNode->left==NULL&&tempNode->right!=NULL){
		 GetBHigh(tempNode->left);
	}
	return 1;
}
int GetTreeHigh(TreeNode* root) {
	if (root == NULL)return 0;
	return GetTreeHigh(root->left) > GetTreeHigh(root->right) ? GetTreeHigh(root->left) + 1 : GetTreeHigh(root->right) + 1;
}
void preorder(TreeNode*root){
	if (!root) return;
	cout<<root->val;
	preorder(root->left); 
	preorder(root->right); 
}
void inorder(TreeNode*root){
	if (!root) return;
	inorder(root->left); 
	cout<<root->val;
	inorder(root->right); 
}
void postorder(TreeNode*root){
	if (!root) return;
	postorder(root->left); 
	postorder(root->right); 
	cout<<root->val;
}
void _preorder(TreeNode*root){
	//vector<char>res;
	stack<TreeNode*>st;
    if (root != NULL) {
		while (root != NULL || !st.empty()) {
			if (root != NULL) {
				//res.push_back(root->val);
				cout<<root->val;
				st.push(root);
				root = root->left;
			}
			else {
				root = st.top();
				st.pop();
				root = root->right;
			}
		}
    }
	//for(auto i:res) cout<<i;
}
void _inorder(TreeNode*root){
	stack<TreeNode*>st; //vector<char>res;
	if (root != NULL) {
		while (root != NULL || !st.empty()) {
			if (root != NULL) {
				st.push(root);
				root = root->left;
			}
			else {
				root = st.top();
				st.pop();
				cout<<root->val;
				//res.push_back(root->val);
				root = root->right;
			}
		}//for(auto i:res)  cout<<i;
	}
}
void _postorder(TreeNode*root){
	vector<char>st;stack<TreeNode*>stk;
    TreeNode* tempNode = root, *lastNode = NULL;
	if (root != NULL) {
		while (tempNode != NULL) {
			stk.push(tempNode);
			tempNode = tempNode->left;
		}
		while (!stk.empty()) {
			tempNode = stk.top();
			stk.pop();
			if (tempNode->right == NULL || lastNode == tempNode->right) {
				//st.push_back(tempNode->val);
				cout<<tempNode->val;
				lastNode = tempNode;
			}
			else {
				stk.push(tempNode);
				tempNode = tempNode->right;
				while (tempNode) {
					stk.push(tempNode);
					tempNode = tempNode->left;
				}
			}
		}    
	}
	//for(auto i:st)  cout<<i; 
}
/*先找到最左边的节点，然后判断其右子树是否为线索，
如果是线索，那么就遍历后继结点，如果右子树是右孩子，
那么就进入到右孩子的最左边的节点，进行同样的判断，直到遍历完了整棵树为止。
*/
TreeNode* pre = NULL;
void ThreadBinaryTree(TreeNode* root) {
	if (root!=NULL) {
		ThreadBinaryTree(root->left);  //线索化左子树
		if (root->left == NULL) {
			root->left = pre;
			root->ltag = true;
		}
		//处理节点的后继
		if (pre != NULL && pre->right == NULL) {
			pre->right = root;
			pre->rtag = 1;
		}
		pre = root;
		ThreadBinaryTree(root->right);
	}
}

TreeNode* FirstInNode(TreeNode *root){
	if(root==NULL) return NULL;
	while(!root->ltag){
		root=root->left;
	}
	return root;
}
TreeNode* preTreeNode(TreeNode* q) {
	TreeNode* cur= q;
	if (cur->ltag) {
		cur = cur->left;
	//	return cur;
	}
	else{
		cur = cur->left;//进入左子树
		while (!cur->rtag) {
			cur = cur->right;
		}//找到左子树的最右边结点	
	}
	return cur;
}
/*如果LTag=1，直接找到前驱，如果LTag=0，
则走到该结点左子树的最右边的结点，即为要寻找的结点的前驱。*/
TreeNode* rearTreeNode(TreeNode* q) {
	TreeNode* cur = q;
	if (cur->rtag) {
		cur = cur->right;
	//	return cur;
	}
	else {
		//进入到*cur的右子树
		cur = cur->right;
		while (!cur->ltag) {
			cur = cur->left;
		}	
	}
	return cur;
}
/*如果RTag=1，直接找到后继，如果RTag=0，
则走到该结点右子树的最左边的结点，即为要寻找的结点的后继。*/

int main(){
	myTree=new Tree();
	string s="A(B(D,E(H(J,K(L,M(,N))))),C(F,G(,I)))"; 	
	myTree->Init(s);
	// string a="A(B)";
	// string c="A";
	// string d="";
	cout<<"输出该二叉树： ";
	ShowTree(myTree->Head->left);
	// cout<<endl<<"查找H的左右结点："<<endl;
	// FindNode(myTree->Head->left,'H');
	// NodeLeafNumber(myTree->Head->left);
	// cout<<"树中结点的个数是： "<<NodeNumber_<<endl;
	// cout<<"树中叶子的个数是： "<<LeafNumber_<<endl;
	// cout<<"树的度数是： "<<GetBHigh(myTree->Head->left);
	// GetTreeHigh(myTree->Head->left);
	// cout<<endl<<"树的高度是： "<<GetTreeHigh(myTree->Head->left)<<endl;
	// cout<<endl<<"输出该树的递归前序遍历： ";
	// preorder(myTree->Head->left);
	cout<<endl<<"输出该树的递归中序遍历： ";
	inorder(myTree->Head->left);
	// cout<<endl<<"输出该树的递归后序遍历： ";
	// postorder(myTree->Head->left);
	// cout<<endl<<"输出该树的非递归前序遍历： ";
	// _preorder(myTree->Head->left);
	// cout<<endl<<"输出该树的非递归中序遍历： ";
	// _inorder(myTree->Head->left);
	// cout<<endl<<"输出该树的非递归后序遍历： ";
	// _postorder(myTree->Head->left);
	cout<<endl<<"中序线索化二叉树"<<endl;
	ThreadBinaryTree(myTree->Head);
	TreeNode* FirstNode=FirstInNode(myTree->Head->left);
	TreeNode* preNode=preTreeNode(FirstNode);
	TreeNode* rearNode=rearTreeNode(FirstNode);
	cout<<"中序线索化遇到的第一个节点是"<<FirstNode->val<<endl;
	cout<<"前驱："<<preNode->val<<" "<<"后继："<<rearNode->val<<endl;
	return 0;
	// cout<<"前驱："<<"E"<<" "<<"后继："<<"F"<<endl;
	
}
