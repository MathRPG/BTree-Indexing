#ifndef ARTICLE_H
#define ARTICLE_H

#include <fstream>

static const int MAX_DOI_LEN = 64;
static const int MAX_TITLE_LEN = 64;
static const int MAX_AUTHOR_LEN = 64;

typedef unsigned int year_type;
static const size_t INFILE_YEAR_SIZE = sizeof(typeof(year_type));

static const int EQUAL_STRINGS = 0;

class Article
{
public:
	Article();
	Article(const char* doi, const char* name, const char* author, year_type year) noexcept;

	[[nodiscard]] static size_t infile_size();

	bool has_primary_key(const char* other_doi) const;
	[[nodiscard]] bool is_identical(const Article& other) const;
	bool operator==(Article& other) const;

	void write(std::fstream& out) const;
	friend std::fstream& operator<<(std::fstream& out, Article& article);

	void read(std::fstream& in);
	friend void operator>>(std::fstream& in, Article& article);

	static bool compare_article(const Article& first, const Article& second);

private:
	char doi[MAX_DOI_LEN]{};
	char title[MAX_TITLE_LEN]{};
	char author[MAX_AUTHOR_LEN]{};
	year_type year = 0;
};

#endif