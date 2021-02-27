#ifndef BTREE_H
#define BTREE_H

#include "Article.h"

#include <vector>

typedef const char* filename_t;

class B_Tree
{
public:
	B_Tree(filename_t index_path, filename_t registry_path);
	bool contains(const char* key);
	void insert(Article& article);
	void remove_key(const char* key);
private:
	std::vector<Article> all_articles;
};

#endif