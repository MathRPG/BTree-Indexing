#ifndef B_TREE_INDEXING_ARTICLE_H
#define B_TREE_INDEXING_ARTICLE_H

#include <string>
#include <fstream>

class Article
{
	friend class BTree;
	friend class Node;
public:
	Article(std::string doi, std::string title, std::string author, unsigned year);
	Article(Article const &original);
	explicit Article(std::fstream& f);
	bool operator==(const Article& other) const;
	friend void operator<<(std::fstream& out, const Article& article);
private:
	std::string doi;
	std::string title;
	std::string author;
	unsigned year;
	bool is_removed = false;
};

#endif //B_TREE_INDEXING_ARTICLE_H
