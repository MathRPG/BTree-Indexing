#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "Article.h"

TEST_SUITE("Article")
{
	static const char* const some_doi = "Doi";
	static const char* const some_name = "Name";
	static const char* const some_author = "Author";
	static const unsigned some_year = 2000u;
	Article some_article(some_doi, some_name, some_author, some_year);

	static const char* const other_doi = "Other-Doi";
	static const char* other_name = "Other-Name";
	static const char* other_author = "Other-Author";
	static const unsigned other_year = 2001u;

	TEST_CASE("should indicate if it has certain primary key")
	{
		CHECK(some_article.has_primary_key(some_doi));
		CHECK_FALSE(some_article.has_primary_key(other_doi));
	}

	TEST_CASE("should compare if it is identical to other articles")
	{
		SUBCASE("returns false if DOIs are different")
		{
			Article some_article_different_doi(other_doi, some_name, some_author, some_year);
			CHECK_FALSE(some_article.is_identical(some_article_different_doi));
		}

		SUBCASE("returns false if Names are different")
		{
			Article some_article_different_name(some_doi, other_name, some_author, some_year);
			CHECK_FALSE(some_article.is_identical(some_article_different_name));
		}

		SUBCASE("returns false if Authors are different")
		{
			Article some_article_different_author(some_doi, some_name, other_author, some_year);
			CHECK_FALSE(some_article.is_identical(some_article_different_author));
		}

		SUBCASE("returns false if Years are different")
		{
			Article some_article_different_year(some_doi, some_name, some_author, other_year);
			CHECK_FALSE(some_article.is_identical(some_article_different_year));
		}

		SUBCASE("returns true if articles are identical")
		{
			Article some_article_identical(some_doi, some_name, some_author, some_year);
			CHECK(some_article.is_identical(some_article_identical));
		}
	}

	TEST_CASE("should write to file its writing writing_size")
	{
		std::fstream file("testfile.txt", std::fstream::in | std::fstream::out);
		file << some_article;
		CHECK(file.tellg() == some_article.writing_size());
	}
}
