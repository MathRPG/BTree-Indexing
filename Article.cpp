#include "Article.h"

#include <cstring>
#include <fstream>

Article::Article() = default;

Article::Article(const char* doi, const char* name, const char* author, unsigned int year) noexcept
{
	strncpy(this->doi, doi, MAX_DOI_LEN);
	strncpy(this->title, name, MAX_TITLE_LEN);
	strncpy(this->author, author, MAX_AUTHOR_LEN);
	this->year = year;
}

size_t Article::infile_size()
{
	return MAX_DOI_LEN + MAX_TITLE_LEN + MAX_AUTHOR_LEN + INFILE_YEAR_SIZE;
}

bool Article::has_primary_key(const char* other_doi) const
{
	return strncmp(doi, other_doi, MAX_DOI_LEN) == EQUAL_STRINGS;
}

bool Article::is_identical(Article& other) const
{
	if (!has_primary_key(other.doi))
		return false;
	if (strncmp(title, other.title, MAX_TITLE_LEN) != EQUAL_STRINGS)
		return false;
	if (strncmp(author, other.author, MAX_AUTHOR_LEN) != EQUAL_STRINGS)
		return false;
	if (year != other.year)
		return false;
	return true;
}

void Article::write(std::fstream& out) const
{
	out.write(doi, MAX_DOI_LEN);
	out.write(title, MAX_TITLE_LEN);
	out.write(author, MAX_AUTHOR_LEN);
	out.write(reinterpret_cast<const char*> (&year), INFILE_YEAR_SIZE);
}

std::fstream& operator<<(std::fstream& out, Article& article)
{
	article.write(out);
	return out;
}

void Article::read(std::fstream& in)
{
	in.read(doi, MAX_DOI_LEN);
	in.read(title, MAX_TITLE_LEN);
	in.read(author, MAX_AUTHOR_LEN);
	in.read(reinterpret_cast<char*> (&year), INFILE_YEAR_SIZE);
}

void operator>>(std::fstream& in, Article& article)
{
	article.read(in);
}

bool Article::operator==(Article& other) const
{
	return is_identical(other);
}
