#include <cstring>
#include <ostream>
#include "Article.h"

Article::Article(const char* doi, std::string name, std::string author, unsigned int year)
{
	strncpy(this->doi, doi, FIELD_MAX_STR_LEN);
}
bool Article::compare_key(const std::string& other_doi)
{
	return doi == other_doi;
}
void Article::dump(std::ostream f)
{
//	f.write(this->doi, FIELD_MAX_STR_LEN);
}
