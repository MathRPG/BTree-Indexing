#include <cstring>
#include <fstream>
#include "Article.h"

Article::Article(const char* doi, std::string name, std::string author, unsigned int year)
{
	strncpy(this->doi, doi, FIELD_MAX_STR_LEN);
}
bool Article::compare_key(const std::string& other_doi)
{
	return doi == other_doi;
}
void Article::write(std::fstream& out)
{
	out.write(this->doi, FIELD_MAX_STR_LEN);
}
