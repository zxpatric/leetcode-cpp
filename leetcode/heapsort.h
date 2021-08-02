//
// Created by ZhouP on 3/5/2019.
//

#ifndef CPPSANDBOX_HEAPSORT_H
#define CPPSANDBOX_HEAPSORT_H

#include "../include/datastructure.h"
#include <bitset>

typedef TreeNode HeapNode;
typedef std::vector<HeapNode*> HNodes;


class Solution_LinkedList {
    void sortToRoot(HeapNode *root, int index) {
        HNodes nodes;
        nodes.push_back(root);
        std::bitset<31> bs = index;
        int i;
        for (i = bs.size() - 1; i >= 0; --i) {
            if (bs.test(i))
                break;
        }

        HeapNode *top = root;
        for (int j = i - 1; j >= 0; --j) {
            if (bs.test(j)) {
                //right
                nodes.push_back(top->rightP);
                top = top->rightP;
            } else {
                //left
                nodes.push_back(top->leftP);
                top = top->leftP;
            }
        }

        top = nodes.back();
        nodes.pop_back();
        do {
            HeapNode *parent = nodes.back();
            nodes.pop_back();
            int vp = parent->value;
            if (top->value > vp) {
                //swap values
                parent->value = top->value;
                top->value = vp;

                //top pointing to parent now
                top = parent;
            } else {
                break;
            }
        } while (!nodes.empty());
    }

    void insertUnder(int v, HeapNode *root) {
        if (root == NULL) {
            root = new HeapNode(v);
            return;
        }

        std::queue<TreeNode *> treenodes;
        treenodes.push(root);

        int i = 1;
        TreeNode *aNode = NULL;

        while (!treenodes.empty()) {
            // find the first empty spot and insert the element there
            aNode = treenodes.front();
            treenodes.pop();
            ++i;
            if (aNode->leftP == NULL) {
                aNode->leftP = new TreeNode(v);
                sortToRoot(root, i);
                break;
            } else
                treenodes.push(aNode->leftP);

            ++i;
            if (aNode->rightP == NULL) {
                aNode->rightP = new TreeNode(v);
                sortToRoot(root, i);
                break;
            } else
                treenodes.push(aNode->rightP);
        }
    }

    void insertUnder_unbalanced(int v, HeapNode *root) {

        int vroot = root->value;
        if (v > vroot) {
            root->value = v;
            v = vroot;
        }

        if (root->leftP == NULL) {
            root->leftP = new HeapNode(v);
        } else if (root->rightP == NULL) {
            root->rightP = new HeapNode(v);
        } else {
            insertUnder(v, root->leftP);
        }
    }

    HeapNode *buildMaxHeap(const std::vector<int> &values) {
        HeapNode *root = new HeapNode(values.front());
        for (int i = 1; i < values.size(); ++i) {
            insertUnder(values[i], root);
//        int v = values[i];
//        if (v<=root->value)
//        {
//// insert v somewhere under root
//            insertUnder (v, root);
//        }
//        else
//        {
//            HeapNode* new_root = new HeapNode(v);
//            new_root->leftP = root;
//            root = new_root;
//        }
        }

        return root;
    }

#define DoHeapify(nodeP)   extractRoot(nodeP);

    bool extractRoot(HeapNode *&root) {
        if (root->leftP != NULL) {
            if (root->rightP == NULL) {
                root->value = root->leftP->value;
                DoHeapify(root->leftP)
            } else {
                if (root->rightP->value > root->leftP->value) {
                    root->value = root->rightP->value;
                    DoHeapify(root->rightP)
                } else {
                    root->value = root->leftP->value;
                    DoHeapify(root->leftP)
                }
            }
        } else {
            if (root->rightP == NULL) {
                delete root;
                root = NULL;
                return false;
            } else {
                if (root->rightP->value) {
                    root->value = root->rightP->value;removeDuplicateLetters
                    DoHeapify(root->rightP)
                }
            }
        }
    }

    void cleanupHeap(HeapNode *root) {
        if (root == NULL)
            return;

        cleanupHeap(root->leftP);
        root->leftP = NULL;
        cleanupHeap(root->rightP);
        root->rightP = NULL;
        delete root;
    }

public:
    void heap_sort(const std::vector<int> &values, std::vector<int> &result) {

        if (values.size() < 2) {
            result = values;
            return;
        }

        // build the max heap
        HeapNode *root = buildMaxHeap(values);
        printTree(root);

        // extract the head, heapify the heap until the root is a leaf
        do {
            int v = root->value;
            result.push_back(v);
            extractRoot(root);
        } while (root != NULL);

        // clean heap
//    cleanupHeap(root_for_delete);
    }
};

class Solution_Vector {


    void heapify (std::vector<int> &values, int index)
    {
        int left = index*2+1;
        int right = index*2+2;

//        int value = values[index];
//        if (left<values.size() && right<values.size())
//        {
//            int left_value = values[left];
//            int right_value = values[right];
//
//            if (left_value < right_value)
//            {
//                if (value < right_value)
//                {
//                    values[index] = right_value;
//                    values[right] = value;
//                    heapify(values, right);
//                }
//            }
//            else
//            {
//                if (value < left_value)
//                {
//                    values[index] = left_value;
//                    values[left] = value;
//                    heapify(values, left);
//                }
//            }
//
//        }
//        else if (left<values.size())
//        {
//            int left_value = values[left];
//            if (value < left_value)
//            {
//                values[index] = left_value;
//                values[left] = value;
//                heapify(values, left);
//            }
//        }
//        else
//        {
//        }

        int largest_index = index;

        if (left<values.size() && values[left]>values[largest_index])
            largest_index = left;
        if (right<values.size() && values[right]>values[largest_index])
            largest_index = right;

        if (largest_index != index)
        {
            std::iter_swap(values.begin()+index, values.begin()+largest_index);
            heapify(values, largest_index);
        }
    }

    void buildMaxHeap (Ints& values)
    {
        int n = values.size();
        for (int i = n / 2 - 1; i >= 0; i--)
            heapify(values, i);
    }

    int extractRoot(std::vector<int> &values)
    {
        int value = values.front();
        values.front() = values.back();
        values.pop_back();

        heapify (values, 0);

        return value;
    }

public:
    void heap_sort(const std::vector<int> &values, std::vector<int> &result) {

        if (values.size() < 2) {
            result = values;
            return;
        }

        // build the max heap
//        printVector<std::remove_reference<decltype(values)>::type::value_type>(values);
        std::vector<int> raws = values;
        buildMaxHeap(raws);
        printVector<decltype(raws)::value_type>(raws);

        // extract the head, heapify the heap until the root is a leaf
        do {
            result.push_back(extractRoot(raws));
        } while (!raws.empty());

//        printVector<std::remove_reference<decltype(result)>::type::value_type>(result);
    }
};

class Solution_Array
{
void heapify(int arr[], int n, int i)
{
    int largest = i; // Initialize largest as root
    int l = 2*i + 1; // left = 2*i + 1
    int r = 2*i + 2; // right = 2*i + 2

    // If left child is larger than root
    if (l < n && arr[l] > arr[largest])
        largest = l;

    // If right child is larger than largest so far
    if (r < n && arr[r] > arr[largest])
        largest = r;

    // If largest is not root
    if (largest != i)
    {
        swap(arr[i], arr[largest]);

        // Recursively heapify the affected sub-tree
        heapify(arr, n, largest);
    }
}

void swap (int &i0, int &i1)
{
    int s = i0;
    i0 = i1;
    i1 = s;
}

public:
// main function to do heap sort
void heapSort(int arr[], int n)
{
    // Build heap (rearrange array)
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    // One by one extract an element from heap
    for (int i=n-1; i>=0; i--)
    {
        // Move current root to end
        swap(arr[0], arr[i]);

        // call max heapify on the reduced heap
        heapify(arr, i, 0);
    }
}
};

void test_heapsort()
{
    Ints input = {0, 6, 7, 7, 2, 7, 5, 9};
    Ints output;
    printVector<decltype(input)::value_type >(input);
//    Solution_LinkedList s;
//    s.heap_sort(input, output);
//    Solution_Array s;
//    s.heapSort(&input.front(),input.size());
//    printVector<decltype(input)::value_type >(input);
    Solution_Vector s;
    s.heap_sort(input, output);
    printVector<decltype(output)::value_type >(output);
}

#endif //CPPSANDBOX_HEAPSORT_H
