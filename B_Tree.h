#ifndef BTREE_H
#define BTREE_H

#include "Article.h"
#include "Node.h"

#include <vector>

typedef const char* filename_t;

class B_Tree
{
public:
	B_Tree(filename_t index_path, filename_t registry_path);
	bool contains(const char* key) const;
	void insert(const Article& article);
	void remove(const char* key);
private:
	Node root;
};

#endif

/*
 * Create(T)
 * x = Allocate-Node()
 * x.leaf = True
 * x.n = 0
 * Disk-Write(x)
 * T.root = x
 */

/* Deletion: to be continued... */
