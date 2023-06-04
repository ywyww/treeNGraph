#include "Graph.h""

int depth;

void count_levels(Tree* root)
{
	if (root != nullptr)
	{
		if (root->parent != nullptr)
			root->level = root->parent->level + 1;

		if (depth < root->level)
			depth = root->level;

		count_levels(root->left);
		count_levels(root->right);
	}
}

void calculate_coords(Tree* node)
{
	if (node != nullptr)
	{
		if (node->parent != nullptr)
		{
			if (node->level == 2)
				node->x = node->x + node->state * (pow(2, depth - 1) / 2) * 40;
			else
				node->x = node->parent->x + node->state * (pow(2, depth - 1) / pow(2, node->level - 1)) * 40;
			node->y = node->parent->y + 80;
		}

		if (node->left != nullptr)
		{
			node->left->state = -1;
			calculate_coords(node->left);
		}

		if (node->right != nullptr)
		{
			node->right->state = 1;
			calculate_coords(node->right);
		}
	}
}

void draw_lines(Tree* node, RenderWindow& window)
{
	if (node != nullptr)
	{
		if (node->parent != nullptr)
		{
			vector<Vertex> line =
			{
				Vertex(Vector2f(node->parent->x + circleRadius, node->parent->y + circleRadius), Color::Red),
				Vertex(Vector2f(node->x + circleRadius, node->y + circleRadius), Color::Red)
			};
			window.draw(&line[0], line.size(), Lines);
		}

		if (node->left != nullptr)
			draw_lines(node->left, window);

		if (node->right != nullptr)
			draw_lines(node->right, window);
	}
}

void draw_nodes(Tree* node, RenderWindow& window)
{
	if (node != nullptr)
	{
		CircleShape circle(circleRadius);
		circle.setPosition(node->x, node->y);
		circle.setFillColor(Color::White);
		circle.setOutlineColor(Color::Red);
		circle.setOutlineThickness(3);

		Font font;
		font.loadFromFile("MorningBeach.ttf");

		stringstream txt;
		txt << node->data;
		Text text(txt.str(), font, 35);
		text.setPosition(node->x + circleRadius / 2, node->y + circleRadius / 2);
		text.setFillColor(Color::Red);

		window.draw(circle);
		window.draw(text);

		if (node->left != nullptr)
			draw_nodes(node->left, window);

		if (node->right != nullptr)
			draw_nodes(node->right, window);
	}
}

void draw(Tree* tree)
{
	RenderWindow MainWindow(VideoMode(1280, 720), "Tree");

	depth = 0;

	count_levels(tree);
	calculate_coords(tree);

	while (MainWindow.isOpen())
	{
		Event event;

		while (MainWindow.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				MainWindow.close();
				break;
			}
		}

		MainWindow.clear(Color::White);
		draw_lines(tree, MainWindow);
		draw_nodes(tree, MainWindow);
		MainWindow.display();
	}
}

int main()
{
	setlocale(LC_ALL, "RUS");

	Tree* tree = new Tree;

	tree->generate();
	cout << "right: ";
	tree->print_direct();
	cout << "\ncenter: ";
	tree->print_symmetrical();
	cout << "\nrever: ";
	tree->print_reverse();
	cout << "\ntree: " << endl;
	draw(tree);


	tree->minimum()->remove();
	cout << "after deleting min: " << endl;
	draw(tree);

	Tree* search_tree = tree->convert_into_search();
	cout << "to binary: " << endl;
	draw(search_tree);

	search_tree->minimum_search()->remove_search();
	cout << "after deleting min: " << endl;
	draw(search_tree);

	return 0;
}
