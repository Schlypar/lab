#include "Sequence/ArraySequence.h"
#include "Tree/BinaryHeap.h"
#include "Tree/BinaryTree.h"
#include "Tree/MultiBinaryTree.h"
#include "Tree/OrderedSet.h"
#include "Tuple.h"
#include "functional/Algorithms.h"
#include <ADT.h>

LogPriority Logger::priority = TracePriority;

template <typename T1, typename T2>
using TreePtr = SharedPtr<Tree<T1, T2>>;

template <typename T1, typename T2>
using ConstTreePtr = SharedPtr<const Tree<T1, T2>>;

template <typename T1, typename T2>
using BinTreePtr = SharedPtr<BinaryTree<T1, T2>>;

template <typename T1, typename T2>
using BinHeapPtr = SharedPtr<BinaryHeap<T1, T2>>;

template <typename T>
using BinSearchPtr = SharedPtr<BinarySearchTree<T>>;

template <typename T1, typename T2>
using MultiBinTreePtr = SharedPtr<MultiBinaryTree<T1, T2>>;

template <typename T1>
using SetPtr = SharedPtr<OrderedSet<T1>>;

int main()
{
	Logger::setPriority(ErrorPriority);

	BinTreePtr<int, Pair<int, String>> tree = new BinaryTree<int, Pair<int, String>>({ 25, "root" },
		[](const Pair<int, String>& pair) -> int { return pair.GetLeft(); });

	tree->Add({ 20, "left" })->Add({ 30, "right" });

	print(tree, '\n');

	return 0;
}
