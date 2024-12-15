#pragma once
#include <memory>

template <typename NodeType>
class AVLTree
{
	using NodePtrType = std::unique_ptr<NodeType>;
public:
	NodeType* root() { return m_root.get(); }

	void insert(const typename NodeType::KeyType& key)
	{
		_insert(m_root, key);
	}

private:

	void _insert(NodePtrType& currentNode, const typename NodeType::KeyType& key)
	{
		if (currentNode == nullptr)
		{
			currentNode = std::make_unique<NodeType>(key);
			return;
		}

		if (currentNode->data == key)
			return; // Duplicate

		if (key > currentNode->data)
		{
			_insert(currentNode->right, key);
		}
		else
		{
			_insert(currentNode->left, key);
		}

		updateHeight(currentNode.get());

		currentNode = rotate(std::move(currentNode), key, getBalance(currentNode.get()));
	}

	int getHeight(NodePtrType& node) const 
	{
		return node ? node->height : 0;
	}

	void updateHeight(NodeType* node) 
	{
		if (!node)
			return;

		node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));
	}

	int getBalance(NodeType* node) const 
	{
		if (!node)
			return 0;

		return getHeight(node->left) - getHeight(node->right);
	}

	NodePtrType rotateRight(NodePtrType node) 
	{
		NodePtrType newRoot = std::move(node->left);
		NodePtrType right = std::move(newRoot->right);

		newRoot->right = std::move(node);
		newRoot->right->left = std::move(right);

		updateHeight(newRoot->right.get());
		updateHeight(newRoot.get());

		return newRoot;
	}

	NodePtrType rotateLeft(NodePtrType node) 
	{
		NodePtrType newRoot = std::move(node->right);
		NodePtrType left = std::move(newRoot->left);

		newRoot->left = std::move(node);
		newRoot->left->right = std::move(left);

		updateHeight(newRoot->left.get());
		updateHeight(newRoot.get());

		return newRoot;
	}

	NodePtrType rotate(NodePtrType node, int key, int balance)
	{
		if (balance > 1 && key < node->left->data) 
		{
			return rotateRight(std::move(node));
		}

		if (balance > 1 && key > node->left->data) 
		{
			node->left = rotateLeft(std::move(node->left));
			return rotateRight(std::move(node));
		}

		if (balance < -1 && key > node->right->data) 
		{
			return rotateLeft(std::move(node));
		}

		if (balance < -1 && key < node->right->data) 
		{
			node->right = rotateRight(std::move(node->right));
			return rotateLeft(std::move(node));
		}

		return node;
	}

	NodePtrType m_root{ nullptr };
};