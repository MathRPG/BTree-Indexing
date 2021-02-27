#include "B_Tree.h"

#include <fstream>

B_Tree::B_Tree(filename_t index_path, filename_t registry_path)
{
	std::fstream file(index_path, std::fstream::out);
	file.close();
	file.open(registry_path, std::fstream::out);
	file.close();
}

bool B_Tree::contains(const char* key) const
{
	return root.contains(key);
}

void B_Tree::insert(const Article& article)
{
	root.insert(article);
}

void B_Tree::remove(const char* const key)
{
	root.remove(key);
}
