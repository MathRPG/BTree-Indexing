#ifndef B_TREE_INDEXING_ARTICLE_H
#define B_TREE_INDEXING_ARTICLE_H

#include <string>

class Article
{
	friend class BTree;
	friend class Node;
public:
	Article(std::string doi, std::string title, std::string author, unsigned year);
	Article(Article const &original);
	bool operator==(const Article& other);
private:
	std::string doi;
	std::string title;
	std::string author;
	unsigned year;
};

#endif //B_TREE_INDEXING_ARTICLE_H
