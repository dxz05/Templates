#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template<typename T> using indexed_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

// find_by_order(k) - iterator to the k-th element (0-indexation)
// order_of_key(k) - number of elements strictly less than k (also, the position of k if set contained k)
// multiset --> use pairs
