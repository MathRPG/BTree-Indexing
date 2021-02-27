#ifndef NODE_H
#define NODE_H

#include "Article.h"

#include <array>

static const int NODE_DEGREE = 4;
static const int NODE_CAPACITY = NODE_DEGREE - 1;

class Node
{
public:
	bool contains(const char* key) const;
	void insert(const Article& article);
	void remove(const char* key);
	~Node();
private:
	unsigned n = 0;
	std::array<Article, NODE_CAPACITY> keys{};
	std::array<Node*, NODE_DEGREE> children{};
};

#endif
