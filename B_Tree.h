#ifndef B_TREE_INDEXING_B_TREE_H
#define B_TREE_INDEXING_B_TREE_H

#include <vector>
#include "Article.h"

typedef const char* filename_t;

class B_Tree
{
public:
	B_Tree(filename_t index_path, filename_t registry_path);
	bool contains(const char* key);
	void insert(Article& article);
private:
	std::vector<Article> all_articles;
};

#endif //B_TREE_INDEXING_B_TREE_H
