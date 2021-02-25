#ifndef B_TREE_INDEXING_ARTICLE_H
#define B_TREE_INDEXING_ARTICLE_H

static const int FIELD_MAX_STR_LEN = 64;
#include <string>
class Article
{
public:
	Article(const char* doi, std::string name, std::string author, unsigned year);
	bool compare_key(const std::string& other_doi);
	void write(std::fstream& out);
private:
	char doi[FIELD_MAX_STR_LEN]{};
};

#endif //B_TREE_INDEXING_ARTICLE_H
