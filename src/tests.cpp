#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "BTree.h"
#include "Article.h"

TEST_SUITE("BTree")
{
	TEST_CASE("Empty tree")
	{
		SUBCASE("contains returns false")
		{
			BTree empty_tree = BTree();
			CHECK_UNARY_FALSE(empty_tree.contains("Whatever key"));
		}
	}

	TEST_CASE("Insertion")
	{
		SUBCASE("1 key: search returns true only for inserted key")
		{
			BTree tree = BTree();
			const char* key = "DOI";
			tree.insert(Article(key, "Title", "Author", 2000));
			CHECK(tree.contains(key));
			CHECK_UNARY_FALSE(tree.contains("Other_DOI"));
		}

		SUBCASE("2 keys")
		{
			BTree tree = BTree();
		}
	}
}
