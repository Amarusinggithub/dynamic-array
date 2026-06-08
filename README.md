# C Collections

A from scratch implementation of common data structures in C, built as a learning project to understand manual memory management, pointers, and how fundamental data structures work under the hood. No third-party libraries just the C standard library.

---

## Disclaimer

All code within the src and include folders are hand written by the author not AI. The code written in these folders are completed by the authors research. Through utilizing the official docs, books, forums, youtube and blogs. AI was only use help guide the author in identifying bugs and logical errors and extending their understanding of the different concepts covered. This is detailed in the [AGENTS.md](AGENTS.md).

Here is a list of other files that were extended by AI, but not fully completed by AI:

- .clang-tidy
- .clang-format
- CMakeLists.txt

Here is a list of files that were Completely AI Generated:

- README.md (excluding this section)
- AGENTS.MD

---

## Table of Contents

- [C Collections](#c-collections)
  - [Disclaimer](#disclaimer)
  - [Table of Contents](#table-of-contents)
  - [Overview](#overview)
  - [Data Structures](#data-structures)
    - [Dynamic Array](#dynamic-array)
    - [Linked List](#linked-list)
    - [Stack](#stack)
    - [Queue](#queue)
    - [Circular Buffer / Ring Buffer](#circular-buffer--ring-buffer)
    - [Deque](#deque)
    - [Min / Max Heap](#min--max-heap)
    - [Binary Search Tree](#binary-search-tree)
    - [AVL Tree](#avl-tree)
    - [Trie](#trie)
    - [Hash Map](#hash-map)
    - [Hash Set](#hash-set)
    - [Graph — Adjacency List](#graph--adjacency-list)
    - [Graph — Adjacency Matrix](#graph--adjacency-matrix)
    - [B-Tree](#b-tree)
    - [B+ Tree](#b-tree-1)
    - [Bloom Filter](#bloom-filter)
    - [HyperLogLog](#hyperloglog)
    - [Skip List](#skip-list)
  - [Build \& Execute](#build--execute)
    - [CMake — Windows (PowerShell)](#cmake--windows-powershell)
    - [CMake — WSL / Linux](#cmake--wsl--linux)
    - [Choosing a build type](#choosing-a-build-type)

---

## Overview

Each data structure lives in its own header/source pair under `include/` and `src/`. The project grows one structure at a time — each one is fully implemented and tested before moving to the next.

**Core C concepts practised across this project:**

- Heap allocation with `malloc`, `calloc`, and `realloc`
- Generic storage using `void*` and `element_size`
- Manual pointer arithmetic with `(char*)` casting
- Value copying with `memcpy` and `memmove`
- Linked node structures and pointer chaining
- Recursive and iterative tree traversal
- Hashing and collision resolution
- Struct design for encapsulating state

---

## Data Structures

### Dynamic Array

**Files:** `include/dynarr.h` · `src/dynarr.c`

A resizable array that stores any data type via `void*`. Doubles in capacity automatically when full.

```c
typedef struct {
    size_t length;       // number of elements currently stored
    size_t capacity;     // max elements before realloc
    size_t element_size; // size of each element in bytes
    void  *items;        // pointer to the data on the heap
} Array;
```

| Function                       | Description                                                       |
| ------------------------------ | ----------------------------------------------------------------- |
| `append(arr, value)`           | Add an element to the end, doubling capacity if full              |
| `remove_item(arr, value)`      | Remove all occurrences of a value                                 |
| `remove_at(arr, index)`        | Remove the element at a given index                               |
| `get(arr, index)`              | Return a pointer to the element at an index, with bounds checking |
| `set(arr, index, value)`       | Overwrite an element at an index                                  |
| `contains(arr, value)`         | Return 1 if value exists, 0 if not                                |
| `insert_at(arr, index, value)` | Insert at a position, shifting everything after it right          |
| `reverse(arr)`                 | Reverse the array in place                                        |
| `index_of(arr, value)`         | Return the index of the first match, -1 if not found              |
| `sort(arr, cmp)`               | Sort using a comparator function pointer                          |
| `map(arr, fn)`                 | Apply a function to every element in place                        |
| `filter(arr, fn)`              | Return a new array with only elements where fn returns true       |
| `shrink_to_fit(arr)`           | Realloc capacity down to match length, reclaiming unused memory   |

**Status:** complete

---

### Linked List

**Files:** `include/llist.h` · `src/llist.c`

A singly linked list where each node holds a value and a pointer to the next node. No contiguous memory — each node is individually heap-allocated.

```c
typedef struct Node {
    void        *data;
    struct Node *next;
} Node;

typedef struct {
    Node  *head;
    size_t length;
    size_t element_size;
} LinkedList;
```

| Function                           | Description                              |
| ---------------------------------- | ---------------------------------------- |
| `ll_append(list, value)`           | Add a node to the end                    |
| `ll_prepend(list, value)`          | Add a node to the front                  |
| `ll_remove(list, value)`           | Remove the first node matching value     |
| `ll_get(list, index)`              | Return a pointer to the data at an index |
| `ll_insert_at(list, index, value)` | Insert a node at a given position        |
| `ll_contains(list, value)`         | Return 1 if value exists, 0 if not       |
| `ll_reverse(list)`                 | Reverse the list in place                |
| `ll_length(list)`                  | Return the number of nodes               |
| `ll_free(list)`                    | Free all nodes and reset the list        |

**Status:** in progress

---

### Stack

**Files:** `include/stack.h` · `src/stack.c`

A LIFO (last-in, first-out) structure. Push onto the top, pop from the top. Can be backed by a dynamic array or linked list.

| Function                   | Description                              |
| -------------------------- | ---------------------------------------- |
| `stack_push(stack, value)` | Add an element to the top                |
| `stack_pop(stack)`         | Remove and return the element at the top |
| `stack_peek(stack)`        | View the top element without removing it |
| `stack_is_empty(stack)`    | Return true if the stack has no elements |
| `stack_size(stack)`        | Return the number of elements            |
| `stack_free(stack)`        | Free all memory                          |

**Status:** planned

---

### Queue

**Files:** `include/queue.h` · `src/queue.c`

A FIFO (first-in, first-out) structure. Enqueue at the back, dequeue from the front. Backed by a singly linked list so both operations are O(1) with no shifting.

```c
typedef struct {
    Node  *head;         // front of the queue — next to dequeue
    Node  *tail;         // back of the queue — where new items go
    size_t length;
    size_t element_size;
} Queue;
```

| Function                       | Description                                       |
| ------------------------------ | ------------------------------------------------- |
| `queue_enqueue(queue, value)`  | Add an element to the back                        |
| `queue_dequeue(queue)`         | Remove and return the element at the front        |
| `queue_peek(queue)`            | View the front element without removing it        |
| `queue_is_empty(queue)`        | Return true if the queue has no elements          |
| `queue_size(queue)`            | Return the number of elements                     |
| `queue_contains(queue, value)` | Return 1 if value exists, 0 if not                |
| `queue_clear(queue)`           | Remove all elements, freeing each node            |
| `queue_free(queue)`            | Free all memory including the queue struct itself |

**Status:** planned

---

### Circular Buffer / Ring Buffer

**Files:** `include/cbuf.h` · `src/cbuf.c`

A fixed-size FIFO queue backed by a flat array. Instead of shifting elements, two indices (`head` and `tail`) chase each other around the array in a loop — no allocation after init. Commonly used in operating systems, device drivers, and network I/O buffers.

```c
typedef struct {
    void  *buffer;       // flat array holding the elements
    size_t head;         // index of the next element to read
    size_t tail;         // index of the next slot to write
    size_t length;       // number of elements currently stored
    size_t cap;          // maximum number of elements (fixed at creation)
    size_t element_size;
} CircBuf;
```

| Function                      | Description                                                       |
| ----------------------------- | ----------------------------------------------------------------- |
| `cbuf_create(cap, elem_size)` | Allocate a new circular buffer with a fixed capacity              |
| `cbuf_push(cbuf, value)`      | Write an element at `tail`; return an error if the buffer is full |
| `cbuf_pop(cbuf, out)`         | Read and remove the element at `head`; return an error if empty   |
| `cbuf_peek(cbuf, out)`        | Read the element at `head` without removing it                    |
| `cbuf_is_full(cbuf)`          | Return 1 if `length == cap`                                       |
| `cbuf_is_empty(cbuf)`         | Return 1 if no elements are stored                                |
| `cbuf_size(cbuf)`             | Return the number of elements currently stored                    |
| `cbuf_clear(cbuf)`            | Reset `head`, `tail`, and `length` to 0 without freeing memory    |
| `cbuf_free(cbuf)`             | Free the buffer array and the struct itself                       |

**Status:** planned

---

### Deque

**Files:** `include/deque.h` · `src/deque.c`

A double-ended queue. Elements can be pushed and popped from both the front and the back in O(1). Generalises both stack and queue.

```c
typedef struct DequeNode {
    void             *data;
    struct DequeNode *prev;
    struct DequeNode *next;
} DequeNode;

typedef struct {
    DequeNode *head;
    DequeNode *tail;
    size_t     length;
    size_t     element_size;
} Deque;
```

| Function                         | Description                                       |
| -------------------------------- | ------------------------------------------------- |
| `deque_push_front(deque, value)` | Add an element to the front                       |
| `deque_push_back(deque, value)`  | Add an element to the back                        |
| `deque_pop_front(deque)`         | Remove and return the element at the front        |
| `deque_pop_back(deque)`          | Remove and return the element at the back         |
| `deque_peek_front(deque)`        | View the front element without removing it        |
| `deque_peek_back(deque)`         | View the back element without removing it         |
| `deque_is_empty(deque)`          | Return 1 if no elements are stored                |
| `deque_size(deque)`              | Return the number of elements                     |
| `deque_clear(deque)`             | Remove all elements, freeing each node            |
| `deque_free(deque)`              | Free all memory including the Deque struct itself |

**Status:** planned

---

### Min / Max Heap

**Files:** `include/heap.h` · `src/heap.c`

A complete binary tree stored in a flat array (no node pointers). The smallest (min-heap) or largest (max-heap) element is always at index 0. The foundation of priority queues and heap sort.

```c
typedef struct {
    void  *data;         // flat array storing the heap elements
    size_t length;       // number of elements currently stored
    size_t cap;          // max elements before realloc
    size_t element_size;
    int  (*cmp)(const void *, const void *); // comparator — defines min or max behaviour
} Heap;
```

| Function                           | Description                                                          |
| ---------------------------------- | -------------------------------------------------------------------- |
| `heap_create(cap, elem_size, cmp)` | Allocate a new heap; pass a comparator to choose min or max behavior |
| `heap_push(heap, value)`           | Insert an element and sift it up to restore the heap property        |
| `heap_pop(heap)`                   | Remove and return the root (min or max), sift the replacement down   |
| `heap_peek(heap)`                  | Return a pointer to the root element without removing it             |
| `heap_is_empty(heap)`              | Return 1 if no elements are stored                                   |
| `heap_size(heap)`                  | Return the number of elements                                        |
| `heap_clear(heap)`                 | Remove all elements without freeing the underlying array             |
| `heap_free(heap)`                  | Free the data array and the Heap struct itself                       |

**Status:** planned

---

### Binary Search Tree

**Files:** `include/bst.h` · `src/bst.c`

A node-based tree where every left child is smaller than its parent and every right child is larger. Supports recursive insertion, search, deletion, and in-order/pre-order/post-order traversal.

```c
typedef struct BSTNode {
    void           *data;
    struct BSTNode *left;
    struct BSTNode *right;
} BSTNode;

typedef struct {
    BSTNode *root;
    size_t   length;
    size_t   element_size;
    int    (*cmp)(const void *, const void *);
} BST;
```

| Function                    | Description                                                 |
| --------------------------- | ----------------------------------------------------------- |
| `bst_insert(tree, value)`   | Insert a value, maintaining the BST property                |
| `bst_search(tree, value)`   | Return a pointer to the matching node's data, or NULL       |
| `bst_remove(tree, value)`   | Remove a value; handle leaf, one-child, and two-child cases |
| `bst_contains(tree, value)` | Return 1 if the value exists, 0 otherwise                   |
| `bst_min(tree)`             | Return a pointer to the smallest element                    |
| `bst_max(tree)`             | Return a pointer to the largest element                     |
| `bst_inorder(tree, fn)`     | Call `fn` on each node in sorted order (left, root, right)  |
| `bst_preorder(tree, fn)`    | Call `fn` on each node in pre-order (root, left, right)     |
| `bst_postorder(tree, fn)`   | Call `fn` on each node in post-order (left, right, root)    |
| `bst_height(tree)`          | Return the height of the tree                               |
| `bst_free(tree)`            | Free all nodes and the BST struct itself                    |

**Status:** planned

---

### AVL Tree

**Files:** `include/avl.h` · `src/avl.c`

A self-balancing BST. After every insert or delete the tree checks its balance factor and performs rotations to keep height at O(log n), guaranteeing fast lookups even in worst-case input sequences.

```c
typedef struct AVLNode {
    void           *data;
    struct AVLNode *left;
    struct AVLNode *right;
    int             height;  // cached height used to compute balance factor
} AVLNode;

typedef struct {
    AVLNode *root;
    size_t   length;
    size_t   element_size;
    int    (*cmp)(const void *, const void *);
} AVL;
```

| Function                    | Description                                                |
| --------------------------- | ---------------------------------------------------------- |
| `avl_insert(tree, value)`   | Insert a value and rebalance with rotations if needed      |
| `avl_remove(tree, value)`   | Remove a value and rebalance the affected path             |
| `avl_search(tree, value)`   | Return a pointer to the matching node's data, or NULL      |
| `avl_contains(tree, value)` | Return 1 if the value exists, 0 otherwise                  |
| `avl_min(tree)`             | Return a pointer to the smallest element                   |
| `avl_max(tree)`             | Return a pointer to the largest element                    |
| `avl_height(tree)`          | Return the height of the tree                              |
| `avl_inorder(tree, fn)`     | Call `fn` on each node in sorted order (left, root, right) |
| `avl_free(tree)`            | Free all nodes and the AVL struct itself                   |

**Status:** planned

---

### Trie

**Files:** `include/trie.h` · `src/trie.c`

A prefix tree where each node represents one character. Ideal for autocomplete, spell-check, and dictionary lookups. Insertion and search run in O(k) where k is the length of the key.

```c
#define TRIE_ALPHA 26

typedef struct TrieNode {
    struct TrieNode *children[TRIE_ALPHA];
    int              is_end;   // 1 if this node marks the end of a word
} TrieNode;

typedef struct {
    TrieNode *root;
    size_t    word_count;
} Trie;
```

| Function                         | Description                                                |
| -------------------------------- | ---------------------------------------------------------- |
| `trie_insert(trie, word)`        | Insert a string, creating nodes for each character         |
| `trie_search(trie, word)`        | Return 1 if the exact word exists, 0 otherwise             |
| `trie_starts_with(trie, prefix)` | Return 1 if any stored word begins with the given prefix   |
| `trie_remove(trie, word)`        | Remove a word, cleaning up nodes that are no longer needed |
| `trie_count(trie)`               | Return the number of words stored                          |
| `trie_free(trie)`                | Free all nodes and the Trie struct itself                  |

**Status:** planned

---

### Hash Map

**Files:** `include/hashmap.h` · `src/hashmap.c`

A key-value store backed by a hash table. A hash function maps string keys to bucket indices; collisions are handled via chaining (a linked list per bucket). Average O(1) get/set.

```c
typedef struct {
    size_t  size;     // number of key-value pairs currently stored
    size_t  cap;      // number of buckets in the table
    void  **buckets;  // array of bucket chain heads
} Map;
```

| Function                   | Description                                                                     |
| -------------------------- | ------------------------------------------------------------------------------- |
| `map_create(cap)`          | Allocate and initialise a new Map with `cap` buckets                            |
| `map_put(map, key, value)` | Insert a key-value pair, or overwrite the value if the key already exists       |
| `map_get(map, key)`        | Return a pointer to the value for a key, NULL if not found                      |
| `map_remove(map, key)`     | Remove the entry for a key; return NOT_FOUND if the key doesn't exist           |
| `map_contains(map, key)`   | Return 1 if the key exists in the map, 0 otherwise                              |
| `map_size(map)`            | Return the number of key-value pairs stored                                     |
| `map_is_empty(map)`        | Return 1 if no entries are stored                                               |
| `map_resize(map, new_cap)` | Rehash all entries into a new bucket array (triggered when load factor is high) |
| `map_clear(map)`           | Remove all entries, freeing each bucket chain                                   |
| `map_free(map)`            | Free all memory including the Map struct itself                                 |

**Status:** in progress

---

### Hash Set

**Files:** `include/hashset.h` · `src/hashset.c`

A hash map without values — just keys. O(1) average insert, delete, and membership test.

```c
typedef struct {
    size_t  size;     // number of keys currently stored
    size_t  cap;      // number of buckets in the table
    void  **buckets;  // array of bucket chain heads
} Set;
```

| Function                   | Description                                           |
| -------------------------- | ----------------------------------------------------- |
| `set_create(cap)`          | Allocate and initialise a new Set with `cap` buckets  |
| `set_add(set, key)`        | Insert a key; do nothing if it already exists         |
| `set_contains(set, key)`   | Return 1 if the key is present, 0 otherwise           |
| `set_remove(set, key)`     | Remove a key; return NOT_FOUND if absent              |
| `set_size(set)`            | Return the number of keys stored                      |
| `set_is_empty(set)`        | Return 1 if no keys are stored                        |
| `set_resize(set, new_cap)` | Rehash all keys into a new bucket array               |
| `set_union(a, b)`          | Return a new Set containing all keys from both sets   |
| `set_intersection(a, b)`   | Return a new Set with only keys present in both sets  |
| `set_difference(a, b)`     | Return a new Set with keys in `a` that are not in `b` |
| `set_clear(set)`           | Remove all keys, freeing each bucket chain            |
| `set_free(set)`            | Free all memory including the Set struct itself       |

**Status:** planned

---

### Graph — Adjacency List

**Files:** `include/graph_list.h` · `src/graph_list.c`

A graph where each vertex stores a list of its neighbours. Memory-efficient for sparse graphs. Supports BFS and DFS traversal.

```c
typedef struct AdjNode {
    int              vertex;
    struct AdjNode  *next;
} AdjNode;

typedef struct {
    int       num_vertices;
    AdjNode **lists;    // array of adjacency list heads, one per vertex
    int       directed; // 1 = directed, 0 = undirected
} GraphList;
```

| Function                                    | Description                                                     |
| ------------------------------------------- | --------------------------------------------------------------- |
| `graph_list_create(num_vertices, directed)` | Allocate a graph with the given number of vertices              |
| `graph_list_add_edge(graph, src, dst)`      | Add an edge from src to dst (both directions if undirected)     |
| `graph_list_remove_edge(graph, src, dst)`   | Remove an edge between src and dst                              |
| `graph_list_has_edge(graph, src, dst)`      | Return 1 if the edge exists, 0 otherwise                        |
| `graph_list_bfs(graph, start, fn)`          | Breadth-first traversal from start, calling `fn` on each vertex |
| `graph_list_dfs(graph, start, fn)`          | Depth-first traversal from start, calling `fn` on each vertex   |
| `graph_list_print(graph)`                   | Print all adjacency lists for debugging                         |
| `graph_list_free(graph)`                    | Free all adjacency list nodes and the struct                    |

**Status:** planned

---

### Graph — Adjacency Matrix

**Files:** `include/graph_matrix.h` · `src/graph_matrix.c`

A graph represented as a 2D array where `matrix[i][j] = 1` means an edge exists between vertex i and j. Fast edge lookups at the cost of O(V²) memory. Better suited for dense graphs.

```c
typedef struct {
    int **matrix;       // 2D array — matrix[i][j] = 1 means edge i -> j
    int   num_vertices;
    int   directed;     // 1 = directed, 0 = undirected
} GraphMatrix;
```

| Function                                      | Description                                                     |
| --------------------------------------------- | --------------------------------------------------------------- |
| `graph_matrix_create(num_vertices, directed)` | Allocate a V x V matrix initialized to 0                        |
| `graph_matrix_add_edge(graph, src, dst)`      | Set the edge cell to 1 (both directions if undirected)          |
| `graph_matrix_remove_edge(graph, src, dst)`   | Set the edge cell(s) back to 0                                  |
| `graph_matrix_has_edge(graph, src, dst)`      | Return 1 if the edge exists, 0 otherwise                        |
| `graph_matrix_bfs(graph, start, fn)`          | Breadth-first traversal from start, calling `fn` on each vertex |
| `graph_matrix_dfs(graph, start, fn)`          | Depth-first traversal from start, calling `fn` on each vertex   |
| `graph_matrix_print(graph)`                   | Print the matrix for debugging                                  |
| `graph_matrix_free(graph)`                    | Free the 2D array and the struct                                |

**Status:** planned

---

### B-Tree

**Files:** `include/btree.h` · `src/btree.c`

A self-balancing search tree where each node can hold many keys and have many children. Designed for systems where data lives on disk — a single node read can eliminate many branches at once, keeping the tree very short. Used in databases (SQLite, PostgreSQL) and file systems (NTFS, ext4). Each node holds up to `m-1` keys and up to `m` children, and all leaves sit at the same depth.

```c
#define BTREE_T 3  // minimum degree: each non-root node has at least T-1 keys

typedef struct BTreeNode {
    int              num_keys;
    int              is_leaf;
    void            *keys[2 * BTREE_T - 1];
    struct BTreeNode *children[2 * BTREE_T];
} BTreeNode;

typedef struct {
    BTreeNode *root;
    int        t;            // minimum degree
    size_t     element_size;
    int      (*cmp)(const void *, const void *);
} BTree;
```

| Function                          | Description                                            |
| --------------------------------- | ------------------------------------------------------ |
| `btree_create(t, elem_size, cmp)` | Allocate a new B-Tree with minimum degree `t`          |
| `btree_insert(tree, key)`         | Insert a key, splitting full nodes as needed           |
| `btree_search(tree, key)`         | Return a pointer to the matching key, or NULL          |
| `btree_remove(tree, key)`         | Remove a key, merging or redistributing keys as needed |
| `btree_contains(tree, key)`       | Return 1 if the key exists, 0 otherwise                |
| `btree_traverse(tree, fn)`        | In-order traversal calling `fn` on each key            |
| `btree_height(tree)`              | Return the height of the tree                          |
| `btree_free(tree)`                | Free all nodes and the BTree struct itself             |

**Status:** planned

---

### B+ Tree

**Files:** `include/bplustree.h` · `src/bplustree.c`

A variant of the B-Tree where only leaf nodes store actual data — internal nodes hold keys purely for navigation. All leaf nodes are linked together in a list, making range queries fast. This is what most real-world databases use under the hood.

```c
typedef struct BPlusNode {
    int               num_keys;
    int               is_leaf;
    void             *keys[2 * BTREE_T - 1];
    struct BPlusNode *children[2 * BTREE_T]; // leaf: last pointer links to next leaf
    void             *values[2 * BTREE_T - 1]; // only populated in leaf nodes
} BPlusNode;

typedef struct {
    BPlusNode *root;
    BPlusNode *leftmost_leaf; // head of the leaf linked list for range scans
    int        t;
    size_t     element_size;
    int      (*cmp)(const void *, const void *);
} BPlusTree;
```

| Function                           | Description                                                  |
| ---------------------------------- | ------------------------------------------------------------ |
| `bplus_create(t, elem_size, cmp)`  | Allocate a new B+ Tree with minimum degree `t`               |
| `bplus_insert(tree, key, value)`   | Insert a key-value pair, splitting nodes as needed           |
| `bplus_search(tree, key)`          | Return a pointer to the value for a key, or NULL             |
| `bplus_remove(tree, key)`          | Remove a key-value pair, merging or redistributing as needed |
| `bplus_contains(tree, key)`        | Return 1 if the key exists, 0 otherwise                      |
| `bplus_range(tree, low, high, fn)` | Call `fn` on every entry where low <= key <= high            |
| `bplus_traverse(tree, fn)`         | Walk the leaf level left to right calling `fn` on each entry |
| `bplus_free(tree)`                 | Free all nodes and the BPlusTree struct itself               |

**Status:** planned

---

### Bloom Filter

**Files:** `include/bloom.h` · `src/bloom.c`

A probabilistic data structure that answers "have I seen this before?" using a bit array and multiple hash functions. Inserting an item sets several bits; checking an item tests those same bits. If any bit is 0 the item is definitely absent; if all are 1 it is probably present. False positives are possible but false negatives are not. Uses a tiny amount of memory compared to a hash set — the trade-off is the small chance of being wrong.

```c
typedef struct {
    uint8_t *bits;        // flat bit array
    size_t   bit_count;   // total number of bits in the array
    size_t   hash_count;  // number of independent hash functions to apply
    size_t   item_count;  // number of items inserted (used to estimate FPR)
} BloomFilter;
```

| Function                              | Description                                                        |
| ------------------------------------- | ------------------------------------------------------------------ |
| `bloom_create(bit_count, hash_count)` | Allocate a Bloom Filter with a given bit array size and hash count |
| `bloom_add(filter, key)`              | Hash the key with each function and set the corresponding bits     |
| `bloom_contains(filter, key)`         | Return 1 if all bits for key are set (probably present), 0 if not  |
| `bloom_estimated_fpr(filter)`         | Estimate the current false-positive rate based on fill level       |
| `bloom_clear(filter)`                 | Zero out the bit array and reset item_count to 0                   |
| `bloom_free(filter)`                  | Free the bit array and the BloomFilter struct itself               |

**Status:** planned

---

### HyperLogLog

**Files:** `include/hll.h` · `src/hll.c`

A probabilistic data structure that estimates how many unique items have been seen (cardinality) using a tiny fixed amount of memory — typically a few kilobytes regardless of how many items you process. It works by hashing each item and tracking the maximum number of leading zeros seen across buckets; statistically, more unique items produce longer runs of zeros. The estimate can be off by roughly 1-2% but uses orders of magnitude less memory than storing every unique item. Used in Redis (`PFADD`/`PFCOUNT`), BigQuery, and stream analytics pipelines.

```c
typedef struct {
    uint8_t *registers;  // array of M registers, each storing a max leading-zero count
    size_t   m;          // number of registers (must be a power of 2)
    double   alpha;      // bias-correction constant derived from m
} HyperLogLog;
```

| Function                | Description                                                                 |
| ----------------------- | --------------------------------------------------------------------------- |
| `hll_create(precision)` | Allocate a HLL where m = 2^precision registers (precision typically 4-16)   |
| `hll_add(hll, key)`     | Hash key, pick a register from leading bits, update with leading-zero count |
| `hll_count(hll)`        | Return the estimated cardinality using the harmonic mean formula            |
| `hll_merge(dst, src)`   | Merge src into dst by taking the element-wise max of each register          |
| `hll_clear(hll)`        | Zero all registers                                                          |
| `hll_free(hll)`         | Free the register array and the HyperLogLog struct itself                   |

**Status:** planned

### Skip List

**Files:** `include/skiplist.h` · `src/skiplist.c`

A probabilistic data structure built from multiple layers of linked lists. The bottom layer is a standard sorted linked list; each layer above it is a "fast lane" that skips over roughly half the nodes of the layer below. Search, insert, and delete all run in O(log n) expected time by dropping down to slower lanes only when needed. Provides the same asymptotic guarantees as a balanced BST without complex rotations — balance is maintained probabilistically by a coin flip on each insert.

```c
#define SKIPLIST_MAX_LEVEL 16

typedef struct SkipNode {
    void            *data;
    struct SkipNode *forward[]; // flexible array — one pointer per level this node occupies
} SkipNode;

typedef struct {
    SkipNode *head;        // sentinel node with SKIPLIST_MAX_LEVEL forward pointers
    int       level;       // highest level currently in use
    size_t    length;
    size_t    element_size;
    int     (*cmp)(const void *, const void *);
} SkipList;
```

| Function                      | Description                                                        |
| ----------------------------- | ------------------------------------------------------------------ |
| `skip_create(elem_size, cmp)` | Allocate a new Skip List with a sentinel head node                 |
| `skip_insert(list, value)`    | Insert a value, randomly choosing how many levels it occupies      |
| `skip_search(list, value)`    | Return a pointer to the matching element, or NULL                  |
| `skip_remove(list, value)`    | Remove the element, updating all forward pointers that bypassed it |
| `skip_contains(list, value)`  | Return 1 if value exists, 0 otherwise                              |
| `skip_min(list)`              | Return a pointer to the smallest element (first node on level 0)   |
| `skip_max(list)`              | Return a pointer to the largest element (last node on level 0)     |
| `skip_size(list)`             | Return the number of elements                                      |
| `skip_free(list)`             | Free all nodes and the SkipList struct itself                      |

**Status:** planned

---

## Build & Execute

### CMake — Windows (PowerShell)

```powershell
cmake -B build -S .
cmake --build build
.\build\Debug\c_collections.exe
```

### CMake — WSL / Linux

```sh
cmake -B build -S . -DCMAKE_C_COMPILER=gcc
cmake --build build
./build/c_collections
```

### Choosing a build type

The default build type is `Debug`. To switch, pass `-DCMAKE_BUILD_TYPE` when configuring:

```sh
# Debug (default) — includes debug symbols and sanitizers
cmake -DCMAKE_BUILD_TYPE=Debug -B build

# Release — optimized, no sanitizers
cmake -DCMAKE_BUILD_TYPE=Release -B build
```

If you have already configured the build directory and want to switch types, delete the `build/` folder first or pass the flag explicitly to override the cached value.
