#ifndef B_TREE_INDEXING_ARTICLE_H
#define B_TREE_INDEXING_ARTICLE_H

#include <string>

static const int FIELD_MAX_STR_LEN = 64;

class Article
{
public:
	Article();
	Article(const char* doi, const std::string& name, const std::string& author, unsigned year);

	static size_t size();
	bool compare_key(const char* other_doi);

	void write(std::fstream& out);
	friend std::fstream& operator<<(std::fstream& out, Article& article);

	void read(std::fstream& in);
	friend void operator>>(std::fstream& in, Article& article);

private:
	char doi[FIELD_MAX_STR_LEN]{};
};

#endif //B_TREE_INDEXING_ARTICLE_H
