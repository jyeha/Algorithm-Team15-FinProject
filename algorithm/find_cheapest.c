

Hotel * find_cheapest_hotel(Hotel * root)
{
	Hotel * cur = root;
	if (root != NULL && cur->left == NULL && cur->right == NULL) return root;
	if (cur->left == NULL) return successor(cur);
	else
	{
		while (cur->left != NULL)
		{
			cur = cur->left;
		}
		return cur;
	}
}

Hotel ** find_cheapest_route(sites * s, int size)
{
	Hotel ** cheapest = (Hotel**)malloc(sizeof(Hotel*) * size);

	for (int i = 0; i < size; i++)
	{
		cheapest[i] = find_cheapest_hotel((s[i])->hotel);
	}
	return cheapest;
}

int * find_cheapest_days(Hotel ** hotels,int size)
{
	int * arr = (int*)malloc(sizeof(int) * size);
	
	int INF = 987654321;
	
}
