#pragma once

#include <vector>

class LCA
{
    public:
        LCA(std::vector< std::pair<int,int> > edges);
        int lcaQuery(int a, int b);

    private:
        int getMaxLog();
        void initDP();
        void dfs(int currentNode, int currentParent);
        std::vector< std::vector<int> > adjList, binaryLiftDp;
        std::vector<int> parent, nodeHeight;
        std::vector<bool> visited;
        int _numberOfNodes, _maxLog;
};


