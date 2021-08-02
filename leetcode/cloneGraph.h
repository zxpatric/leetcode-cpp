//
// Created by ZhouP on 3/12/2019.
//

#ifndef CPPSANDBOX_CLONEGRAPH_H
#define CPPSANDBOX_CLONEGRAPH_H

#include "../include/datastructure.h"

GraphNode* cloneGraph_BFS (GraphNode* aNode)
{
    HSTwoGNodes hs_nodes;

    QGNodes queue_nodes;
    queue_nodes.push(aNode);
    GraphNode* new_aNode = new GraphNode(aNode->val);
    hs_nodes.emplace(aNode, new_aNode);

    GraphNode* aNode_counter(NULL);

    while (!queue_nodes.empty())
    {
        aNode = queue_nodes.front();
        queue_nodes.pop();
        aNode_counter = hs_nodes.find(aNode)->second;

        for (GraphNode* gNode : aNode->neighbors)
        {
            auto iter = hs_nodes.find(gNode);
            if (iter != hs_nodes.end())
            {
                aNode_counter->addNeighbor(1,iter->second);
            }
            else
            {
                GraphNode* new_gNode = new GraphNode(gNode->val);
                hs_nodes.emplace(gNode, new_gNode);
                queue_nodes.push(gNode);
                aNode_counter->addNeighbor(1, new_gNode);
            }
        }
    }

    return new_aNode;
}

GraphNode* cloneGraph_DFS (GraphNode* aNode)
{
    HSTwoGNodes hs_nodes;

    SGNodes stack_nodes;
    stack_nodes.push(aNode);
    GraphNode* new_aNode = new GraphNode(aNode->val);
    hs_nodes.emplace(aNode, new_aNode);

    GraphNode* aNode_counter(NULL);

    while (!stack_nodes.empty())
    {
        aNode = stack_nodes.top();
        stack_nodes.pop();
        aNode_counter = hs_nodes.find(aNode)->second;

        for (GraphNode* gNode : aNode->neighbors)
        {
            auto iter = hs_nodes.find(gNode);
            if (iter == hs_nodes.end())
            {
                GraphNode* new_gNode = new GraphNode(gNode->val);
                hs_nodes.emplace(gNode, new_gNode);
                aNode_counter->addNeighbor(1, new_gNode);
                stack_nodes.push(gNode);
            }
            else
            {
                aNode_counter->addNeighbor(1,iter->second);
            }
        }
    }

    return new_aNode;
}

GraphNode* cloneGraph(GraphNode* gNode)
{
//    return cloneGraph_DFS (gNode);
    return cloneGraph_BFS(gNode);
}

void test_cloneGraph()
{
    // create a random graph
    GraphNode* root = constructTestGraph();

    // print the original graph
    printGraph (root);

    // copy the graph
    GraphNode* newGNode = cloneGraph(root);
    printGraph (newGNode);
    freeGraph(newGNode);
    // print the copied graph
    freeGraph(root);

}

#endif //CPPSANDBOX_CLONEGRAPH_H
