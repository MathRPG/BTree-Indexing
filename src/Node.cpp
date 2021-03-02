#include "Node.h"

Node::Node()
= default;

Node::~Node()
{
	if (values[0] != nullptr)
		delete values[0];
}

bool Node::contains(const char* key)
{
	if (values[0] == nullptr)
		return false;

	return values[0] -> has_key(key);
}
void Node::insert(const Article& article)
{
	values[0] = new Article(article);
}
