#include "B_Tree.h"
#include <fstream>

B_Tree::B_Tree(filename_t index_path, filename_t registry_path)
{
	std::fstream file(index_path, std::fstream::out);
	file.close();
	file.open(registry_path, std::fstream::out);
	file.close();
}
