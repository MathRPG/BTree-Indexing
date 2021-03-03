#ifndef B_TREE_INDEXING_ARTICLE_H
#define B_TREE_INDEXING_ARTICLE_H

#include <string>

class Article
{
public:
	Article(std::string doi, std::string title, std::string author, unsigned year);
	Article(Article const &original);
	bool has_key(const std::string& key) const;
private:
	std::string doi;
	std::string title;
	std::string author;
	unsigned year{};
};

#endif //B_TREE_INDEXING_ARTICLE_H
