#include "Node.h"

Node::Node()
= default;

Node::~Node()
{
	for (int i = 0; i < item_count; ++i)
		delete items[i];

	if (is_leaf)
		return;

	for (int i = 0; i < item_count + 1; ++i)
		delete children[i];
}

bool Node::contains(const std::string& key)
{
	// TODO: Make search return pointer
	int i = 1;

	while (i <= item_count and key > items[i - 1]->doi)
		i = i + 1;

	if (i <= item_count and key == items[i - 1]->doi)
		return true;

	if (is_leaf)
		return false;

	return children[i - 1]->contains(key);
}

void Node::insert_non_full(const Article& article)
{
//	items[item_count++] = new Article(article);

	int i = (int) item_count;
	std::string k = article.doi;

	if (is_leaf)
	{
		while (i >= 1 && k < items[i - 1]->doi)
		{
			// TODO: do we need to free any of this stuff?
			items[i + 1 - 1] = items[i - 1];
			i--;
		}

		items[i + 1 - 1] = new Article(article);
		item_count++;
	}
	else
	{
		while (i >= 1 and k < items[i - 1]->doi)
			i = i - 1;
		i = i + 1;
		if (children[i - 1]->item_count == (2 * 2) - 1)
		{
			split_child(i);
			if (k > items[i - 1]->doi)
				i = i + 1;
		}
		children[i - 1]->insert_non_full(article);
	}
}

void Node::split_child(unsigned int i) // it do be one more tho
{
	Node* z = new Node();
	Node* y = children[i - 1];

	z->is_leaf = y->is_leaf;
	z->item_count = NODE_T - 1;

	for (int j = 1; j <= NODE_T - 1; ++j) // TODO: maybe t-1?
		z->items[j - 1] = y->items[j + NODE_T - 1];

	if (!y->is_leaf)
		for (int j = 1; j <= NODE_T; ++j)
			z->children[j - 1] = y->children[j + NODE_T - 1];

	y->item_count = NODE_T - 1;

	for (unsigned j = item_count + 1; j >= i + 1; --j)
		children[j + 1 - 1] = children[j - 1]; // Don't judge me

	children[i + 1 - 1] = z; // Again, don't judge me

	for (unsigned j = item_count; j >= i; --j)
		items[j + 1 - 1] = items[j - 1]; // FOR THE LAST TIME, DON'T JUDGE ME

	items[i - 1] = y->items[NODE_T - 1];
	item_count++;
}
