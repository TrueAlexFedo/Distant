#include <iostream>
#include <string>
using namespace std;
class BTree
{
public:
	int elem;
	BTree* head;
	BTree* left;
	BTree* right;
	string Line;

	//конструктор дерева
	BTree(const int n, BTree* parent) {
		elem = n;
		head = parent;
	}
	BTree() {

	}
	BTree(string str) {
		Line = str;
	}
	//функция заполнения элемента или добавления веток рекурсией
	void add(const int n)
	{
		if (n > elem) {
			if (right == nullptr) {
				right = new BTree(n, this);
			}
			else right->add(n);
		}

		else {
			if (left == nullptr) {
				left = new BTree(n, this);
			}
			else left->add(n);
		}
	}
	//поиск ветки по элементу
	BTree* search(BTree* item, int n)
	{
		if (item == nullptr) std::cout << "Search Error";
		else if (item == nullptr && item->elem == n) return item;
		else if (item != nullptr && item->elem > n) return search(item->left, n);
		else if (item != nullptr && item->elem < n) return search(item->right, n);
		
	}
	BTree* Search(int n)
	{
		return search(this, n);
	}
	//Поиск вершины по элементу
	void SEARCH(int v) {
		Line = "";
		convertion2(search(this, v));
		std::cout << Line << std::endl;

	}
	//перевод числа в строку
	string convertion(int elem)
	{
		string line;
		if (elem > 9)
		{
			line += char(elem / 10 + 48);
			line += char(elem % 10 + 48);
		}
		else line += char(elem + 48);
		return line;
	}

	//Перевод дерева в строку
	void convertion2(BTree* tree)
	{
		Line += convertion(tree->elem);
		if (tree->left != nullptr || tree->right != nullptr) {
			Line += "(";

			if (tree->left != nullptr) convertion2(tree->left);
			Line += ",";

			if (tree->right != nullptr) convertion2(tree->right);
			Line += ")";
		}
	}

	void print() {
		convertion2(this);
		cout << endl;
	}
	//удаление элементов
	void remove(int elem)
	{
		BTree* item = this->Search(elem);
		if (item == nullptr) return;
		BTree* Tree1 = nullptr;
		//удаление корня
		if (this == item) {
			if (item->left != nullptr) {
				Tree1 = item->left;
				while (Tree1->right != nullptr) Tree1 = Tree1->right;
			}

			else if (item->right != nullptr) {
				Tree1 = item->right;
				while (Tree1->left != nullptr) Tree1 = Tree1->left;
			}

			int el = Tree1->elem;
			remove(el);
			item->elem = el;
		}
		//удаление элемента ветки
		else if (item->right == nullptr && item->left == nullptr && item->head != nullptr) {
			if (item->head->right == item) item->head->right = nullptr;
			else item->head->left = nullptr;
		}
		// удаление узла с левой веткой
		else if (item->left != nullptr && item->right == nullptr && item->head != nullptr){
			item->left->head = item->head;
			if (item == item->head->left) *item->head->left = *item->left;
			else if (item == item->head->right) *item->head->right = *item->left;
		}
		// удаление узла с правой веткой
		else if (item->left == nullptr && item->right != nullptr && item->head != nullptr){
			item->right->head = item->head;
			if (item == item->head->left) *item->head->left = *item->right;
			else if (item == item->head->right) *item->head->right = *item->right;
		}
		//удаление узла с двумя ветками
		else if (item->right != nullptr && item->right != nullptr && item->head != nullptr) {
			Tree1 = item->right;
			if (Tree1->left != nullptr) {

				while (Tree1->left != nullptr) Tree1 = Tree1->left;

				if (Tree1->right != nullptr) {
					Tree1->right->head = Tree1->head;
					Tree1->head->left = Tree1->right;
				}
				else Tree1->head->left = nullptr;

				item->left->head = Tree1;
				Tree1->left = item->left;
				if (item->head->right == item) {
					Tree1->head = item->head->right;
					item->head->left = Tree1;
				}
				else {
					Tree1->head = item->head->left;
					item->head->left = Tree1;
				}
				Tree1->right = item->right;
				item->right->head = Tree1;
			}

			else {
				item->left->head = Tree1;
				Tree1->left = item->left;
				Tree1->head = item->head;
				if (item->head->left == item)item->head->left = Tree1;
				else item->head->right = Tree1;
			}
			
		}
	}

	bool isDigit(const char elem)
	{
		return (elem >= '0' && elem <= '9') ? true : false;
	}
	//перевод строки в дерево
	BTree str_to_tree(string str) {
		BTree result;
		int k;
		if (isDigit(str[0]) && isDigit(str[1])) {
			int el = (str[0]-48) * 10 + str[1] -48;
			result.elem = el;
			k = 2;
		}
		else if (isDigit(str[0]) && !isDigit(str[1])) {
			int el = str[0] - 48;
			result.elem = el;
			k = 1;
		}

		for (int i = k; i < str.size() - 1;) {
			if (isDigit(str[i]) && isDigit(str[i + 1])) {
				int elem = (str[i] - 48) * 10 + str[i + 1] - 48;
				result.add(elem);
				i += 2;
			}
			else if (isDigit(str[i]) && !isDigit(str[i + 1])) {
				int elem = str[i] - 48;
				result.add(elem);
				i++;
			}
			else i++;
		}
		return result;
	}
};

void main()
{
	std::string str = "8(3(1,6(4,7)),10(,14(13,)))";
	BTree tree;
	tree = tree.str_to_tree(str);
	BTree newTree = tree;
	newTree.print();
	for (auto& value : newTree.Line)
	{
		std::cout << value;
	}
	cout << endl;
	cout << "Choose command: 1) add element, 2) remove element, 3)show tree by element, 4) show node of elem, 5) show help" << endl;
	int n = -1;
	while (n != 0)
	{
		cin >> n;
		switch (n)
		{
		case 1:
		{
			int value;
			std::cout << "Enter element to add:";
			std::cin >> value;
			newTree.add(value);
			newTree.print();


			for (auto& value : newTree.Line)
			{
				std::cout << value;
			}
			newTree.Line = "";
			cout << endl;
			break;

		}
		case 2:
		{
			int value;
			std::cout << "Enter element to remove:";
			std::cin >> value;
			newTree.remove(value);
			newTree.print();

			for (auto& value : newTree.Line)
			{
				std::cout << value;
			}
			newTree.Line = "";
			cout << endl;
			break;
		}
		case 3:
		{
			newTree.print();
			for (auto& value : newTree.Line)
			{
				std::cout << value;
			}
			newTree.Line = "";
			cout << endl;
			break;
		}
		case 4:
		{
			int value;
			std::cout << "Enter element to search:";
			std::cin >> value;
			newTree.SEARCH(value);
			break;
		}
		case 5: {
			std::cout << "Choose command: 1) add element, 2) remove element, 3)show tree by element, 4) show node of elem, 5) show help" << endl;
			break;
		}
		default:
		{
			newTree.print();
			for (auto& value : newTree.Line)
			{
				std::cout << value;
			}
			newTree.Line = "";
			cout << endl;
			break;
		}
		}

	}

}