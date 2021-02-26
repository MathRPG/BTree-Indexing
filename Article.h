#ifndef B_TREE_INDEXING_ARTICLE_H
#define B_TREE_INDEXING_ARTICLE_H

#include <string>

static const int MAX_DOI_LEN = 64;
static const int MAX_NAME_LEN = 64;
static const int MAX_AUTHOR_LEN = 64;

static const int EQUAL_STRINGS = 0;
class Article
{
public:
	Article();
	Article(const char* doi, const char* name, const char* author, unsigned year);

	size_t infile_size();
	bool has_primary_key(const char* other_doi);
	bool is_identical(Article& other);

	void write(std::fstream& out);
	friend std::fstream& operator<<(std::fstream& out, Article& article);

	void read(std::fstream& in);
	friend void operator>>(std::fstream& in, Article& article);

private:
	char doi[MAX_DOI_LEN]{};
	char name[MAX_NAME_LEN]{};
	char author[MAX_AUTHOR_LEN]{};
	unsigned year = 0;
};

#endif //B_TREE_INDEXING_ARTICLE_H
