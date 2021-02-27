#ifndef ARTICLE_H
#define ARTICLE_H

#include <fstream>

static const int MAX_DOI_LEN = 64;
static const int MAX_TITLE_LEN = 64;
static const int MAX_AUTHOR_LEN = 64;

static const int EQUAL_STRINGS = 0;
class Article
{
public:
	Article();
	Article(const char* doi, const char* name, const char* author, unsigned year) noexcept;

	[[nodiscard]] size_t infile_size() const;

	bool has_primary_key(const char* other_doi) const;
	bool is_identical(Article& other) const;
	bool operator==(Article& other) const;

	void write(std::fstream& out) const;
	friend std::fstream& operator<<(std::fstream& out, Article& article);

	void read(std::fstream& in);
	friend void operator>>(std::fstream& in, Article& article);

private:
	char doi[MAX_DOI_LEN]{};
	char title[MAX_TITLE_LEN]{};
	char author[MAX_AUTHOR_LEN]{};
	unsigned year = 0;
};

#endif