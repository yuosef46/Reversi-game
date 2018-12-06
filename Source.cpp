#include <iostream>
#include <algorithm>
#include <vector>
#include <limits>

#define TABLE_SIZE 6
using namespace std;
bool turn = true;
const int MAPPOINTCOUNT[TABLE_SIZE][TABLE_SIZE] =
{
	{90,-60,10,10,-60,90},
	{-60,-80,5,5,-80,-60},
	{10,5,1,1,5,10},
	{10,5,1,1,5,10},
	{-60,-80,5,5,-80,-60},
	{90,-60,10,10,-60,90}
};

struct children {
	int x;
	int y;
	int data;
	int alpha;
	int beta;
};

void build_game(char (*table)[TABLE_SIZE][TABLE_SIZE])
{
	for (size_t i = 0; i < TABLE_SIZE; i++)
		for (size_t j = 0; j < TABLE_SIZE; j++)
			(*table)[i][j] = '*';
	(*table)[TABLE_SIZE / 2 - 1][TABLE_SIZE / 2 - 1] = 'B';
	(*table)[TABLE_SIZE / 2 - 1][TABLE_SIZE / 2] = 'W';
	(*table)[TABLE_SIZE / 2][TABLE_SIZE / 2 - 1] = 'W';
	(*table)[TABLE_SIZE / 2][TABLE_SIZE / 2] = 'B';
}


void print_table(char(*table)[TABLE_SIZE][TABLE_SIZE])
{
	for (size_t i = 0; i < TABLE_SIZE; i++)
	{
		for (size_t j = 0; j < TABLE_SIZE; j++)
			cout << (*table)[i][j] << " ";
		cout << endl;
	}
}


void print_table1(char table[TABLE_SIZE][TABLE_SIZE])
{
	for (size_t i = 0; i < TABLE_SIZE; i++)
	{
		for (size_t j = 0; j < TABLE_SIZE; j++)
			cout << table[i][j] << " ";
		cout << endl;
	}
}


void right_location_and_change(char(*table)[TABLE_SIZE][TABLE_SIZE], int x, int y, char player)
{
	bool positiong_ever = false;
	turn = true;
	if ((*table)[x][y] == 'W' || (*table)[x][y] == 'B')
	{
		cout << " <<<<taken place>>>>\n";
		turn = false;
		return;
	}
	for (int i = 0; i < TABLE_SIZE; i++)
	{
		for (int j = 0; j < TABLE_SIZE; j++)
		{
			bool position = false;
			int flag = 0;
			// if the postion is on the same row and far away one col or more from the selected
							// for all of the col in between should be oppsite clr and nt empty 
			if (x - i == 0 && (*table)[i][j] == player)
			{
				if (y - j < 0)
				{
					flag = (y - j) * -1;
					for (int w = 1; w < flag; w++)
					{
						if ((*table)[i][j - w] != player && (*table)[i][j - w] != '*')
							position = true;
						else
						{
							position = false;
							break;
						}
					}
					if (position == true )
					{
						for (int w = 1; w < flag + 1; w++)
							(*table)[i][j - w] = player;
						position = false;
						positiong_ever = true;
					}
				}
				else
				{
					flag = y - j;
					for (int w = 1; w < flag; w++)
					{
						if ((*table)[i][j + w] != player && (*table)[i][j + w] != '*')
							position = true;
						else
						{
							position = false;
							break;
						}
					}
					if (position == true )
					{
						for (int w = 1; w < flag + 1; w++)
							(*table)[i][j + w] = player;
						position = false;
						positiong_ever = true;
					}
				}
			}
			// if the postion is on the same col and far away one row or more from the selected
			// for all of the row in between should be oppsite clr and nt empty
			else if (y - j == 0 && (*table)[i][j] == player)
			{
				//cout << "enteredd\n";
				//cout << x << " " << i << " " << x - i << endl;
				if (x - i < 0)
				{
					//cout << "enteredd\n";
					flag = (x - i) * -1;
					for (int w = 1; w < flag; w++)
					{
						if ((*table)[i - w][j] != player && (*table)[i - w][j] != '*')
							position = true;
						else
						{
							position = false;
							break;
						}
					}
					if (position == true )
					{
						for (int w = 1; w < flag + 1; w++)
							(*table)[i - w][j] = player;
						position = false;
						positiong_ever = true;
					}
				}
				else
				{
					flag = x - i;
					for (int w = 1; w < flag; w++)
					{
						if ((*table)[i + w][j] != player && (*table)[i + w][j] != '*')
							position = true;
						else
						{
							position = false;
							break;
						}
					}
					if (position == true )
					{
						for (int w = 1; w < flag + 1; w++)
							(*table)[i + w][j] = player;
						position = false;
						positiong_ever = true;
					}
				}
			}
			// if the slcted position diagonal
			// because this area need to check the four direction so we need four situations 
			else if ((x - i == y - j || x - i == (y - j) * -1 ) && (*table)[i][j] == player)
			{
				if (x - i < 0)
					flag = (x - i) * -1;
				else
					flag = x - i;
				if (y - j > 0)
				{
					if (x - i > 0)
					{
						for (int w = 1; w < flag; w++)
						{
							if ((*table)[i + w][j + w] != player && (*table)[i + w][j + w] != '*')
								position = true;
							else
							{
								position = false;
								break;
							}
						}
						if (position == true )
						{
							for (int w = 1; w < flag + 1; w++)
								(*table)[i + w][j + w] = player;
							position = false;
							positiong_ever = true;
						}
					}
					else
					{
						for (int w = 1; w < flag; w++)
						{
							if ((*table)[i - w][j + w] != player && (*table)[i - w][j + w] != '*')
								position = true;
							else
							{
								position = false;
								break;
							}
						}
						if (position == true)
						{
							for (int w = 1; w < flag + 1; w++)
								(*table)[i - w][j + w] = player;
							position = false;
							positiong_ever = true;
						}
					}
				}
				else if (y - j < 0)
				{
					if (x - i > 0)
					{
						for (int w = 1; w < flag; w++)
						{
							if ((*table)[i + w][j - w] != player && (*table)[i + w][j - w] != '*')
								position = true;
							else
							{
								position = false;
								break;
							}
						}
						if (position == true)
						{
							for (int w = 1; w < flag + 1; w++)
								(*table)[i + w][j - w] = player;
							position = false;
							positiong_ever = true;
						}
					}
					else
					{
						for (int w = 1; w < flag; w++)
						{
							if ((*table)[i - w][j - w] != player && (*table)[i - w][j - w] != '*')
								position = true;
							else
							{
								position = false;
								break;
							}
						}
						if (position == true)
						{
							for (int w = 1; w < flag + 1; w++)
								(*table)[i - w][j - w] = player;
							position = false;
							positiong_ever = true;
						}
					}
				}
			}
		}
	}
	if (positiong_ever == false)
	{
		cout << "<<<<<Wrong location. try another place>>>>>\n";
		turn = false;
	}
}


bool theEnd(char table[TABLE_SIZE][TABLE_SIZE], char player)
{
	int white = 0;
	int black = 0;
	int empty = 0;
	for (int i = 0; i < TABLE_SIZE; i++)
	{
		for (int j = 0; j < TABLE_SIZE; j++)
		{
			if (table[i][j] == 'W')
				white ++;
			else if (table[i][j] == 'B')
				black ++;
			else
				empty ++;
		}
	}
	if (black == 0 || white == 0 || empty == 0)
		return true;
	for (int i = 0; i < TABLE_SIZE; i++)
	{
		for (int j = 0; j < TABLE_SIZE; j++)
		{
			if (table[i][j] == '*')
			{
				for (int z = 0; z < TABLE_SIZE; z++)
				{
					for (int w = 0; w < TABLE_SIZE; w++)
					{
						bool position = false;
						int flag = 0;
						// if the postion is on the same row and far away one col or more from the selected
										// for all of the col in between should be oppsite clr and nt empty 
						if (z - i == 0 && table[z][w] == player)
						{
							if (w - j < 0)
							{
								flag = (w - j) * -1;
								for (int w = 1; w < flag; w++)
								{
									if (table[i][j - w] != player && table[i][j - w] != '*')
										position = true;
									else
									{
										position = false;
										break;
									}
								}
								if (position == true)
									return false;
							}
							else
							{
								flag = w - j;
								for (int w = 1; w < flag; w++)
								{
									if (table[i][j + w] != player && table[i][j + w] != '*')
										position = true;
									else
									{
										position = false;
										break;
									}
								}
								if (position == true)
									return false;
							}
						}
						else if (w - j == 0 && table[z][w] == player)
						{
							if (z - i < 0)
							{
								flag = (z - i) * -1;
								for (int w = 1; w < flag; w++)
								{
									if (table[i - w][j] != player && table[i - w][j] != '*')
										position = true;
									else
									{
										position = false;
										break;
									}
								}
								if (position == true)
									return false;
							}
							else
							{
								flag = z - i;
								for (int w = 1; w < flag; w++)
								{
									if (table[i + w][j] != player && table[i + w][j] != '*')
										position = true;
									else
									{
										position = false;
										break;
									}
								}
								if (position == true)
									return false;
							}
						}
						else if ((z - i == w - j || z - i == (w - j) * -1) && table[z][w] == player)
						{
							if (z - i < 0)
								flag = z - i * -1;
							else
								flag = z - i;
							if (w - j > 0)
							{
								if (z - i > 0)
								{
									for (int w = 1; w < flag; w++)
									{
										if (table[i + w][j + w] != player && table[i + w][j + w] != '*')
											position = true;
										else
										{
											position = false;
											break;
										}
									}
									if (position == true)
										return false;
								}
								else
								{
									for (int w = 1; w < flag; w++)
									{
										if (table[i - w][j + w] != player && table[i - w][j + w] != '*')
											position = true;
										else
										{
											position = false;
											break;
										}
									}
									if (position == true)
										return false;
								}
							}
							else if (w - j < 0)
							{
								if (z - i > 0)
								{
									for (int w = 1; w < flag; w++)
									{
										if (table[i + w][j - w] != player && table[i + w][j - w] != '*')
											position = true;
										else
										{
											position = false;
											break;
										}
									}
									if (position == true)
										return false;
								}
								else
								{
									for (int w = 1; w < flag; w++)
									{
										if (table[i - w][j - w] != player && table[i - w][j - w] != '*')
											position = true;
										else
										{
											position = false;
											break;
										}
									}
									if (position == true)
										return false;
								}
							}
						}
					}
				}
			}
			else
				continue;
		}
	}
	return true;
}


int result(char table[TABLE_SIZE][TABLE_SIZE],char player, vector<int> movment)
{
	int max = 0;
	for (int i = 0; i < movment.size() / 2; i++)
	{
		max += MAPPOINTCOUNT[movment[i * 2]][movment[i * 2 + 1]];
	}

	return max;
}


vector<int> avalMove(char table[TABLE_SIZE][TABLE_SIZE], char player)
{
	vector<int> movement;
	for (int i = 0; i < TABLE_SIZE; i++)
	{
		for (int j = 0; j < TABLE_SIZE; j++)
		{
			/*for (int zz = 0; zz < movement.size() / 2; zz++)
				cout << movement[zz] << movement[zz + 1] << endl;
			cout << i << " " << j << endl;*/
			if (table[i][j] == '*')
			{
				for (int z = 0; z < TABLE_SIZE; z++)
				{
					for (int w = 0; w < TABLE_SIZE; w++)
					{
						bool position = false;
						int flag = 0;
						// if the postion is on the same row and far away one col or more from the selected
										// for all of the col in between should be oppsite clr and nt empty 
						if (z - i == 0 && table[z][w] == player)
						{
							if (w - j < 0)
							{
								flag = (w - j) * -1;
								for (int q = 1; q < flag; q++)
								{
									if (table[i][j - q] != player && table[i][j - q] != '*')
										position = true;
									else
									{
										position = false;
										break;
									}
								}
								if (position == true)
								{
									movement.push_back(i);
									movement.push_back(j);
								}
							}
							else
							{
								flag = w - j;
								for (int q = 1; q < flag; q++)
								{
									if (table[i][j + q] != player && table[i][j + q] != '*')
										position = true;
									else
									{
										position = false;
										break;
									}
								}
								if (position == true)
								{
									movement.push_back(i);
									movement.push_back(j);
								}
							}
						}
						else if (w - j == 0 && table[z][w] == player)
						{
							if (z - i < 0)
							{
								flag = (z - i) * -1;
								for (int q = 1; q < flag; q++)
								{
									if (table[i - q][j] != player && table[i - q][j] != '*')
										position = true;
									else
									{
										position = false;
										break;
									}
								}
								if (position == true)
								{
									movement.push_back(i);
									movement.push_back(j);
								}
							}
							else
							{
								flag = z - i;
								for (int q = 1; q < flag; q++)
								{
									if (table[i + q][j] != player && table[i + q][j] != '*')
										position = true;
									else
									{
										position = false;
										break;
									}
								}
								if (position == true)
								{
									movement.push_back(i);
									movement.push_back(j);
								}
							}
						}
						else if ((z - i == w - j || z - i == (w - j) * -1) && table[z][w] == player)
						{
							if (z - i < 0)
								flag = (z - i) * -1;
							else
								flag = z - i;
							if (w - j > 0)
							{
								if (z - i > 0)
								{
									for (int q = 1; q < flag; q++)
									{
										if (table[i + q][j + q] != player && table[i +q][j + q] != '*')
											position = true;
										else
										{
											position = false;
											break;
										}
									}
									if (position == true)
									{
										movement.push_back(i);
										movement.push_back(j);
									}
								}
								else
								{
									for (int q = 1; q < flag; q++)
									{
										if (table[i - q][j + q] != player && table[i - q][j + q] != '*')
											position = true;
										else
										{
											position = false;
											break;
										}
									}
									if (position == true)
									{
										movement.push_back(i);
										movement.push_back(j);
									}
								}
							}
							else if (w - j < 0)
							{
								if (z - i > 0)
								{
									for (int q = 1; q < flag; q++)
									{
										if (table[i + q][j - q] != player && table[i + q][j - q] != '*')
											position = true;
										else
										{
											position = false;
											break;
										}
									}
									if (position == true)
									{
										movement.push_back(i);
										movement.push_back(j);
									}
								}
								else
								{
									for (int q = 1; q < flag; q++)
									{
										if (table[i - q][j - q] != player && table[i - q][j - q] != '*')
											position = true;
										else
										{
											position = false;
											break;
										}
									}
									if (position == true)
									{
										movement.push_back(i);
										movement.push_back(j);
									}
								}
							}
						}
					}
				}
			}
			else
				continue;
		}
	}
	return movement;
}


// in this function we did not pass by address, we only pass a copy
children minimax(char table[TABLE_SIZE][TABLE_SIZE], int depth, int alpha, int beta, bool maxOrMin, char player)
{
	children eval ;
	eval.alpha = alpha;
	eval.beta = beta;
	children maxEval;
	maxEval.data = numeric_limits<int>::min();
	children minEval;
	minEval.data = numeric_limits<int>::max();
	vector<int> movement = avalMove(table, player);
	/*print_table1(table);
	for (int x = 0; x < (movement.size()/2); x++)
	{
		cout << movement[x * 2] << " " << movement[(x * 2) + 1] << endl;
	}*/
	if (depth == 0 || theEnd(table, player))
	{
		eval.data = result(table, 'W', movement);
		return eval;
	}
	if (maxOrMin)
	{
		for (int x = 0; x < (movement.size() / 2); x++)
		{
			char child[TABLE_SIZE][TABLE_SIZE];
			for (int i = 0; i < TABLE_SIZE; i++)
				for (int j = 0; j < TABLE_SIZE; j++)
					child[i][j] = table[i][j];
			char(*p_child)[TABLE_SIZE][TABLE_SIZE] = &child;
			right_location_and_change(p_child, movement[x * 2], movement[(x * 2) + 1], player);
			eval = minimax(child, depth - 1, eval.alpha, eval.beta, false, 'B');
			if (maxEval.data < eval.data)
			{
				maxEval = eval;
				maxEval.x = movement[x * 2];
				maxEval.y = movement[(x * 2) + 1];
			}
			if (maxEval.alpha < eval.data)
				maxEval.alpha = eval.data;
			if (maxEval.beta <= maxEval.alpha)
				break;
		}
		return maxEval;
	}
	else
	{
		for (int x = 0; x < (movement.size() / 2); x++)
		{
			char child[TABLE_SIZE][TABLE_SIZE];
			for (int i = 0; i < TABLE_SIZE; i++)
				for (int j = 0; j < TABLE_SIZE; j++)
					child[i][j] = table[i][j];
			char(*p_child)[TABLE_SIZE][TABLE_SIZE] = &child;
			right_location_and_change(p_child, movement[x * 2], movement[(x * 2) + 1], player);
			eval = minimax(child, depth - 1, eval.alpha, eval.beta, true, 'W');
			if (eval.data < minEval.data)
			{
				minEval = eval;
				minEval.x = movement[x * 2];
				minEval.y = movement[(x * 2) + 1];
			}
			if ( minEval.beta < eval.data)
				minEval.beta = eval.data;
			if (minEval.beta <= minEval.alpha)
				break;
		}
		return minEval;
	}
}

void theWinner(char table[TABLE_SIZE][TABLE_SIZE])
{
	int black = 0;
	int white = 0;
	for (int i = 0; i < TABLE_SIZE; i++)
	{
		for (int j = 0; j < TABLE_SIZE; j++)
		{
			if (table[i][j] == 'B')
				black++;
			else if (table[i][j] == 'W')
				white++;

		}
	}
	if (white == black)
		cout << "***** TIE *****\n";
	else if (white > black)
		cout << "**** YOU LOST ****\n";
	else
		cout << "**** YOU WON ****\n";
}

int main()
{
	int i = 0, j = 0;
	children child;
	char table[TABLE_SIZE][TABLE_SIZE];
	char(*p_table)[TABLE_SIZE][TABLE_SIZE] = &table;
	int alpha = numeric_limits<int>::min();
	int beta = numeric_limits<int>::max();
	cout << "Welcome to reversi game\n";
	build_game(p_table);
	print_table(p_table);
	cout << "________________________________\n";
	cout << "Enter the X's and Y's for your movment (0 - 5) : \n";
	cout << "NOTE: your input should have one of your stone in the same\n";
		cout << "horizontal, vertical or diagonal\n";
	while (theEnd(table, 'B') == false && cin >> i >> j)
	{
		system("CLS");
		right_location_and_change(p_table, i, j, 'B');
		print_table(p_table);
		cout << "_________________________________________\n";
		if (!turn)
			continue;
		if (theEnd(table, 'W'))
			break;
		child = minimax(table, 3, alpha, beta, false, 'W');
		right_location_and_change(p_table, child.x, child.y, 'W');
		print_table(p_table);
		cout << "________________________________\n";
		cout << "Enter the X's and Y's for your movment (0 - 5) : \n";
	}
	cout << " the game is over !!!!\n";
	theWinner(table);
	system("pause");
	return 0;
}