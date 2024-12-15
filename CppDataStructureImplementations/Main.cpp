#include "Utils/TreePrinter.h"
#include "Trees/BinaryTreeNode.h"
#include "Trees/AVLTree.h"
#include <iostream>
#include <random>

int getRandomInt(int min, int max) 
{
    static std::mt19937 rng{ std::random_device{}() };
    std::uniform_int_distribution<int> dist(min, max);
    return dist(rng);
}

int main() 
{
    std::locale::global(std::locale(""));

	AVLTree<BinaryTreeNode<int>> tree;

    for (int i = 0; i < 25; i++)
    {
		tree.insert(getRandomInt(0, 1000));
    }
    
    std::wcout << getTreeDisplay(tree.root());

    return 0;
}