#include <iostream>

#include "Article.h"
#include "BTree.h"

enum MENU_OPERATION
{
	SAVE_EXIT = 0, INSERTION, DELETION, LOOKUP
};

void show_menu()
{
	std::cout <<
			  "\nSelecione a operacao desejada:\n\n"
			  "0 - Salvar registro e sair\n"
			  "1 - Inserir (ou editar) registro\n"
			  "2 - Apagar registro por DOI\n"
			  "3 - Busca de registro por DOI\n\n";
}

std::string get_str(const std::string& prompt)
{
	std::cout << prompt;
	std::string str;
	std::cin >> str;
	return str;
}

unsigned get_unsigned(const char* const prompt)
{
	std::cout << prompt;
	unsigned input;
	std::cin >> input;
	return input;
}

Article get_article()
{
	std::string doi = get_str("DOI: ");
	std::string title = get_str("Titulo: ");
	std::string author = get_str("Autor: ");
	unsigned year = get_unsigned("Ano: ");
	return Article(doi, title, author, year);
}

int main()
{
	std::cout << "Bem-vindo\n";

	const std::string& filename = get_str("Nome do arquivo: ");
	std::fstream file(filename, std::fstream::in);
	BTree registry = BTree(file);
	file.close();

	while (true)
	{
		show_menu();

		switch (get_unsigned("Operacao: "))
		{
		case SAVE_EXIT:
		{
			std::fstream ifile(filename, std::fstream::out);
			registry.dump(ifile);
			ifile.close();
			return EXIT_SUCCESS;
		}
		case INSERTION:
		{
			registry.insert(get_article());
			break;
		}
		case DELETION:
		{
			registry.remove(get_str("DOI para remocao: "));
			break;
		}
		case LOOKUP:
		{
			const Article* fetched = registry.fetch(get_str("DOI para busca: "));
			if (fetched == nullptr)
			{
				std::cout << "DOI nao encontrado no registro\n";
				break;
			}
			std::cout << *fetched;
			break;
		}
		default:
			std::cout << "Opcao invalida; Tente novamente...\n";
		}
	}
}