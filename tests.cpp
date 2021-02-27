#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <filesystem>
#include "doctest.h"
#include "Article.h"
#include "B_Tree.h"

TEST_SUITE("Article")
{
	const char* const some_doi = "Some_DOI";
	const char* const some_title = "Some_Title";
	const char* const some_author = "Some_Author";
	const unsigned int some_year = 2000u;

	Article an_article(some_doi, some_title, some_author, some_year);

	const char* const other_doi = "Other_DOI";

	TEST_CASE("should use DOI as primary key")
	{
		CHECK(an_article.has_primary_key(some_doi));
		CHECK_FALSE(an_article.has_primary_key(other_doi));
	}

	TEST_CASE("should be comparable with other articles")
	{
		SUBCASE("they are not equal if their DOIs are different")
		{
			Article an_article_with_different_doi(other_doi, some_title, some_author, some_year);
			CHECK_UNARY_FALSE(an_article == an_article_with_different_doi);
		}

		SUBCASE("they are not equal if their Titles are different")
		{
			Article an_article_with_different_title(some_doi, "Other_Title", some_author, some_year);
			CHECK_UNARY_FALSE(an_article == an_article_with_different_title);
		}

		SUBCASE("they are not equal if their Authors are different")
		{
			Article an_article_with_different_author(some_doi, some_title, "Other_Author", some_year);
			CHECK_UNARY_FALSE(an_article == an_article_with_different_author);
		}

		SUBCASE("they are not equal if their Years are different")
		{
			Article an_article_with_different_year(some_doi, some_title, some_author, 1999u);
			CHECK_UNARY_FALSE(an_article == an_article_with_different_year);
		}

		SUBCASE("they are equal if none of their fields are different")
		{
			Article an_identical_article(some_doi, some_title, some_author, some_year);
			CHECK_UNARY(an_article == an_identical_article);
		}
	}

	TEST_CASE("should be writable to and readable from a file")
	{
		std::fstream file("testfile.txt", std::fstream::in | std::fstream::out);
		file << an_article;

		file.seekp(0);
		Article read_article;
		file >> read_article;

		SUBCASE("writes to file infile_size bytes")
		{
			CHECK(file.tellg() == an_article.infile_size());
		}

		SUBCASE("reads from file infile_size bytes")
		{
			CHECK(file.tellp() == an_article.infile_size());
		}

		SUBCASE("writes to file data that can be read and interpreted back")
		{
			CHECK_UNARY(an_article == read_article);
		}

		file.close();
	}
}

TEST_SUITE("B-Tree")
{
	TEST_CASE("Is able to initialize B-tree")
	{
		B_Tree tree("index.txt", "registry.txt");
	}

	TEST_CASE("should create index and registry files if they don't exist")
	{
		const char* nonexistent_index_filepath = "this_index_file_doesn't_exist.txt";
		const char* nonexistent_registry_filepath = "this_registry_file_doesn't_exist.txt";

		remove(nonexistent_index_filepath);
		remove(nonexistent_registry_filepath);

		B_Tree tree(nonexistent_index_filepath, nonexistent_registry_filepath);

		CHECK(std::filesystem::exists(nonexistent_index_filepath));
		CHECK(std::filesystem::exists(nonexistent_registry_filepath));

		remove(nonexistent_index_filepath);
		remove(nonexistent_registry_filepath);
	}

//	TEST_CASE("should only close file when tree object is destructed")
}
