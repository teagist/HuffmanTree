//****************************************************************************
//	Header File for Huffman Tree Class
//	Programmed by: Houston Brown
//	Last Compiled Date: 11/21/2022
//****************************************************************************

#ifndef _HuffmanTree_H
#define _HuffmanTree_H

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <string>
#include <cmath>
#include "BinaryHeap.h"
using namespace std;



class HuffmanTree
{
public:
    HuffmanTree(): root(NULL){};                 

    void FillTree(BinaryHeap& minHeap);

    void PrintTree() const;
    void PrintCodes(int code[], int top) 
			    { return PrintCodesHelper(root, code, top); };

    HuffmanTree(const HuffmanTree& myTree);
    ~HuffmanTree();
    HuffmanTree& operator=(const HuffmanTree& rightTree);

private:
    HNode* root;

    // Printing in Level Order Helper Methods
    int TreeHeight(HNode* subtree) const;
    void PrintLevel(int height) const;
    void DispLevel(HNode* subtree, int level, int displace) const;
    
    void PrintCodesHelper(HNode*& subtree, int arr[], int top);

    void CopyHelper(HNode*& root, HNode* myRoot);
    void DestroyHelper(HNode*& Tree);
};

#endif
