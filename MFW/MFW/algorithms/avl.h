#pragma once
/*
算法：AVL 高度平衡的二叉搜索树
AVL树的性质：
左子树和右子树的高度之差的绝对值不超过1
树中的每个左子树和右子树都是AVL树
每个节点都有一个平衡因子(balance factor--bf),任一节点的平衡因子是-1,0,1之一
(每个节点的平衡因子bf 等于右子树的高度减去左子树的高度 )

*/
#include <iostream>
#include <cmath>
#include <stack>
#include <algorithm>
#include <string>

namespace MFWAlg {

	template <typename T>
	class AVL {
	public:
		AVL();
		T root() const;//根节点
		unsigned height() const;//获取树高度
		unsigned size() const;//获取树的大小
		bool isEmpty() const;//判断是否为空
		bool contains(const T &x) const;
		void insert(const T &x);
		void erase(const T &x);
		void toGraphViz(std::ostream &stream, std::string name) const;
	public:
		//树节点
		struct Node {
			Node *left, *right;
			T value;
			unsigned height;
			Node(const T &x) : left(0), right(0), value(x), height(1) {}
			bool contains(const T &x) const {
				if (value == x) return true;
				else if (x < value && left != 0) return left->contains(x);
				else if (right != 0) return right->contains(x);
				else return false;
			}
			Node *insert(const T &x) {
				if (x <= value) {
					if (left == 0) left = new Node(x);
					else left = left->insert(x);
				}
				else {
					if (right == 0) right = new Node(x);
					else right = right->insert(x);
				}

				return update();
			}
			Node *erase(const T &x, bool &found) {
				if (value == x) {
					found = true;
					if (left == 0 && right == 0) {
						delete this;
						return 0;
					}
					else if (left == 0) {
						Node *aux = right;
						*this = *right;
						delete aux;
					}
					else if (right == 0) {
						Node *aux = left;
						*this = *left;
						delete aux;
					}
					else {
						// Tracing path to rightmost leaf of the left subtree
						std::stack<Node*> trace;

						Node *current = left;
						while (current != 0) {
							trace.push(current);
							current = current->right;
						}

						current = trace.top();
						value = current->value;
						Node *lsubtree = current->left;
						delete current;
						trace.pop();

						if (trace.empty()) { left = lsubtree; }
						else {
							trace.top()->right = lsubtree;
							trace.pop();
							while (!trace.empty()) {
								current = trace.top();
								current->right = current->right->update();
								trace.pop();
							}
						}
					}
					return update();
				}
				else if (x < value) {
					if (left != 0) {
						left = left->erase(x, found);
						return update();
					}
					else return this;
				}
				else {
					if (right != 0) {
						right = right->erase(x, found);
						return update();
					}
					else return this;
				}
			}
			Node *update() {
				updateHeight();

				if (getBF(this) >= 2) {
					if (getBF(left) <= -1) LR();
					return LL();
				}
				else if (getBF(this) <= -2) {
					if (getBF(right) >= 1) RL();
					return RR();
				}
				else return this;
			}
			void updateHeight() { height = std::max(getHeight(left), getHeight(right)) + 1; }
			void LR() {
				Node *lrcopy = left->right;
				left->right = lrcopy->left;
				lrcopy->left = left;
				left = lrcopy;
				left->left->updateHeight();
				left->updateHeight();
				updateHeight();
			}
			void RL() {
				Node *rlcopy = right->left;
				right->left = rlcopy->right;
				rlcopy->right = right;
				right = rlcopy;
				right->right->updateHeight();
				right->updateHeight();
				updateHeight();
			}
			Node *LL() {
				Node *lcopy = left;
				left = left->right;
				lcopy->right = this;
				lcopy->left->updateHeight();
				lcopy->right->updateHeight();
				lcopy->updateHeight();
				return lcopy;
			}
			Node *RR() {
				Node *rcopy = right;
				right = right->left;
				rcopy->left = this;
				rcopy->left->updateHeight();
				rcopy->right->updateHeight();
				rcopy->updateHeight();
				return rcopy;
			}
			static int getBF(const Node *t) {
				return getHeight(t->left) - getHeight(t->right);
			}
			static int getHeight(const Node *t) {
				return t == 0 ? 0 : t->height;
			}
			void toGraphViz(std::ostream &stream) const {
				stream << value << ";" << std::endl;
				if (left != 0) {
					stream << left->value << ";" << std::endl;
					stream << value << "->" << left->value << ";" << std::endl;
					left->toGraphViz(stream);
				}
				if (right != 0) {
					stream << right->value << ";" << std::endl;
					stream << value << "->" << right->value << ";" << std::endl;
					right->toGraphViz(stream);
				}
			}
		};
		Node *tree;
		unsigned numNodes;
	};
}      // namespace MFWAlg


