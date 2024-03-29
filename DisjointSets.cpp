# include <bits/stdc++.h>
using namespace std;

class DisjointSet {
	int n;
    vector<int> parent, rank;

public:
    DisjointSet(int n) {
        this->n = n;
        parent.resize(n);
        rank.resize(n);

        for (int i = 0; i < n; i++) {
            parent[i] = i; // ith node is its own parent
            rank[i] = 0; // rank of every node initially is 0
        }
    }
    
    void unionByRank(int v, int u) {
        u = findParent(u);
        v = findParent(v);

        if (u == v) return; // u and v have the same parent

        if (rank[u] < rank[v])
            parent[u] = v; // if v has higher rank, then attach u to v
        else if (rank[v] < rank[u])
            parent[v] = u; // if u has higher rank, then attach v to u
        else {
            parent[v] = u; // if both of them have the same rank, then it doesn't matter to whom we are attching.		
            rank[u]++;     // increase the rank of the node to which the other node is attached by 1
	    }
    }

    int findParent(int u) {
        if (parent[u] == u)
            return u;
        return parent[u] = findParent(parent[u]); // path compression
    }   
};

class DisjointSetBySize {
    int n;
    vector<int> parent, size;

public: 
    DisjointSetBySize(int n) {
        this->n = n;
        parent.resize(n);
        size.resize(n);

        for (int i = 0; i < n; i++) {
            parent[i] = i;
            size[i] = 1;
        }
    }

    int findParent(int u) {
        if (parent[u] == u)
            return u;
        return parent[u] = findParent(parent[u]); // path compression
    }   

    void unionBySize(int u, int v) {
        int parentOfU = findParent(u);
        int parentOfV = findParent(v);

        if (parentOfU == parentOfV) return;

        if (size[parentOfU] > size[parentOfV]) {
            parent[parentOfV] = parentOfU;
            size[parentOfU] += size[parentOfV];
        } else {
            parent[parentOfU] = parentOfV;
            size[parentOfV] += size[parentOfU];
        }
    }
}

int main() {


    return 0;
}