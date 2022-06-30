# include <bits/stdc++.h>

using namespace std;

// Segment Tree template for segment sum
template <class T>
class SegmentTree {
    int size;
    vector<T> tree;

    void build(int idx, int tl, int tr, const vector<T> &arr) {
        if (tl == tr) {
            tree[idx] = arr[tl];
            return;
        }

        int mid = (tl + tr) >> 1;
        build(2 * idx + 1, tl, mid, arr);
        build(2 * idx + 2, mid + 1, tr, arr);
        tree[idx] = merge(tree[2 * idx + 1], tree[2 * idx + 2]);        
    }

    void update(int idx, int tl, int tr, const int pos, const T newVal) {
        if (tl == tr) {
            tree[idx] = newVal;
            return;
        } 

        int mid = (tl + tr) >> 1;
        if (pos <= mid) update(2 * idx + 1, tl, mid, pos, newVal);
        else update(2 * idx + 2, mid + 1, tr, pos, newVal);

        tree[idx] = merge(tree[2 * idx + 1], tree[2 * idx + 2]);
    }

    T query(int idx, int tl, int tr, const int l, const int r) {
        // in case of no operlap
        // tl, tr, l, r or l, r, tl, tr
        if (tl > r || tr < l) {
            return 0;
        }

        // in case of complete overlap
        if (l <= tl && r >= tr) {
            return tree[idx];
        }

        // in case of partial overlap, recur for the left and right sub-tree
        int mid = (tl + tr) >> 1;
        return merge(query(2 * idx + 1, tl, mid, l, r), query(2 * idx + 2, mid + 1, tr, l, r));
    }

    /**
     * @brief specify how you want to merge two elements
     * 
     * @param a -> the first element
     * @param b -> the second element
     */
    T merge(T a, T b) {
        return a + b;
    }

public:
    SegmentTree(int n) {
        size = n;
        tree.resize(4 * n);
    }

    void build(const vector<T> &arr) {
        build(0, 0, size - 1, arr);
    }

    void update(int pos, int newVal) {
        update(0, 0, size - 1, pos, newVal);
    }

    T query(int l, int r) {
        return query(0, 0, size - 1, l, r);
    }
};

// Segment Tree with lazy propagation template for segment sum
template<class T>
class SegmentTreeLP {
    int size;
    vector<T> seg, lazy;

    void pushChanges(int idx, int tl, int tr) {
        if(lazy[idx] != 0) {
			seg[idx] += (tr - tl + 1) * lazy[idx]; 

			// propogate the lazy update downwards
			// for the remaining nodes to get updated 
            // if this node is not a leaf node
			if(tl != tr) {
				lazy[2 * idx + 1] += lazy[idx]; 
				lazy[2 * idx + 2] += lazy[idx]; 
			}

            // there are no updates pending for this node now
			lazy[idx] = 0; 
		}
    }

    void build(int idx, int tl, int tr, const vector<T> &arr) {
        if (tl == tr) {
            seg[idx] = arr[tl];
            return;
        }

        int mid = (tl + tr) >> 1;
        build(2 * idx + 1, tl, mid, arr);
        build(2 * idx + 2, mid + 1, tr, arr);

        seg[idx] = merge(seg[2 * idx + 1], seg[2 * idx + 2]);
    }

    void rangeUpdate(int idx, int tl, int tr, const int l, const int r, const T val) {
        // the first thing to do is update the the pending changes
        // and propagate them downwards
        pushChanges(idx, tl, tr);

        // in case of no overlap,
        // we don't need to do anything
        // tl, tr, l, r or l, r, tl, tr
        if (tr < l || tl > r) {
            return;
        }

        // in case of complete overlap
        if (tl >= l && tr <= r) {
            // update the current node
            // this node is responsible for the values of (tr - tl + 1) nodes
            seg[idx] += (tr - tl + 1) * val;

            // lazily propagate the change downwards if this node is not a leaf node
            if (tl != tr) {
                lazy[2 * idx + 1] += val;
                lazy[2 * idx + 2] += val;
            }

            return;
        }

        // in case of partial overlap
        // recurr for the left and right sub-tree
        int mid = (tl + tr) >> 1;
        rangeUpdate(2 * idx + 1, tl, mid, l, r, val);
        rangeUpdate(2 * idx + 2, mid + 1, tr, l, r, val);
        seg[idx] = merge(seg[2 * idx + 1], seg[2 * idx + 2]);
    }

    T query(int idx, int tl, int tr, const int l, const int r) {
        // if any updates are remaining, do them first
        pushChanges(idx, tl, tr);

        // in case of no overlap, return 0
        if (tl > r || tr < l) {
            return 0;
        }

        // in case of complete overlap
        if (tl >= l && tr <= r) {
            return seg[idx];
        }

        // in case of partial overlap
        int mid = (tl + tr) >> 1;
        T left = query(2 * idx + 1, tl, mid, l, r);
        T right = query(2 * idx + 2, mid + 1, tr, l, r);
        return merge(left, right);
    }  
    
    /**
     * @brief specify how you want to merge two elements
     * 
     * @param a -> the first element
     * @param b -> the second element
     */
    T merge(T a, T b) {
        return a + b;
    }

public:
    SegmentTreeLP(int n) {
        size = n;
        seg.resize(4 * n);
        lazy.resize(4 * n);
    }

    void build(const vector<T> &arr) {
        build(0, 0, size - 1, arr);
    }

    void rangeUpdate(int l, int r, int newVal) {
        rangeUpdate(0, 0, size - 1, l, r, newVal);
    }

    T query(int l, int r) {
        return query(0, 0, size - 1, l, r);
    }
};


int main() {
    vector<int> arr = {1, 2, 3, 4, 5};
    int n = 5;
    SegmentTreeLP<int> sgt(n);
    sgt.build(arr);
    sgt.rangeUpdate(2, 4, 1);
    sgt.rangeUpdate(1, 4, 1);
    sgt.rangeUpdate(1, 3, 1);
    cout << sgt.query(0, 0) << endl;
    cout << sgt.query(1, 1) << endl;
    cout << sgt.query(2, 2) << endl;
    cout << sgt.query(3, 3) << endl;
    cout << sgt.query(4, 4) << endl;
    return 0;
} 