#include <stdio.h>
#include <string.h>
#include <Windows.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>

#define GET_ARRAY_LEN(array,len){len = (sizeof(array) / sizeof(array[0]));}
#define rounds_Y_bias 10
#define rounds_user_X_bias 50

typedef enum
{
	rock = 0,
	scissors,
	paper
} General_Select;

typedef enum
{
	mini = 0,
	normal
} Character_Size;

typedef enum
{
	computer = 0,
	user,
	none
} Game_Player;

typedef enum
{
	result_OK = 0,
	result_Error
} General_Result;

void welcome_UI(char *option_choice);
void info_input(char **user_name_addr, int *game_times, int *name_length);
General_Select computer_select_get(int illegal_bias);
General_Select user_select_get(int *illegal_bias);
Game_Player rounds_UI(int *game_times);
Game_Player compare(General_Select computer_select, General_Select user_select);
void final_UI(Game_Player final_winner);
void printf_position(char *data, int init_X, int init_Y);
void printf_delta(char *data, int delta_X, int delta_Y);
void print_rock(Character_Size size, int bias_X, int bias_Y);
void print_scissors(Character_Size size, int bias_X, int bias_Y);
void print_paper(Character_Size size, int bias_X, int bias_Y);

int main()
{
	char *option_choice, c_pbase, **name_addr, *na_pbase;
	int *game_times, t_pbase, *name_len, nl_pbase, i = 2;
	Game_Player final_winner;
	option_choice = &c_pbase;
	game_times = &t_pbase;
	name_len = &nl_pbase;
	name_addr = &na_pbase;

	welcome_UI(option_choice);
	if (*option_choice == 'a')
	{
		info_input(name_addr, game_times, name_len);
		//for (int i = 0; i < *name_len; i++)
			//printf("%c", *(*name_addr + i));
		//system("pause");
		final_winner = rounds_UI(game_times);
		final_UI(final_winner);
	}

	return 0;
}

void welcome_UI(char *option_choice)
{
	General_Result user_result = result_Error;
	char user_choice[256] = { 0 };

	printf_position("Welcome to the EXCITING GAME!\n",13,0);
	print_rock(mini, -1, 0);
	print_scissors(mini, 19, 0);
	print_paper(mini, 35, 0);
	printf_delta("Please choose the option with serial number before it.\n",0,1);
	printf_delta("a. START!\n",19,1);
	printf_delta("b. EXIT.\n",19,1);

	while (user_result == result_Error)
	{
		printf_delta("Your choice is(a/b): ",0,1);
		gets(user_choice);
		rewind(stdin);

		if (strlen(user_choice) == 1)
		{
			switch (user_choice[0])
			{
			case 'a':
			case 'b':
				user_result = result_OK;
				break;
			default:
				user_result = result_Error;
			}
		}
		if (user_result == result_Error)
			printf("Your input is illegal, please try again!\n");
	}

	if (user_choice[0] == 'a')
	{
		printf("The game will start!\n");
	}
	else
		printf("The game will exit...\n");

	Sleep(1000);
	*option_choice = user_choice[0];
}

void info_input(char **user_name_addr, int *game_times, int *name_length)
{
	static char user_name[256] = { 0 }, user_times[256] = { 0 };
	int i = 0;
	General_Result name_result = result_Error, times_result = result_Error;
	*user_name_addr = user_name;

	system("cls");
	while (name_result == result_Error)
	{
		printf("Enter your name first, press \"ENTER\" to confirm:");
		gets(user_name);
		rewind(stdin);

		*name_length = strlen(user_name);
		if (strlen(user_name) != 0)
		{
			for (i = 0; i < strlen(user_name); i++)
			{
				if (user_name[i] != 32)
				{
					name_result = result_OK;
					break;
				}
			}
		}
		if (name_result == result_Error)
		{
			printf("The name cannot be space, please try again!\n");
			Sleep(1500);
			system("cls");
		}
	}

	system("cls");
	while (times_result == result_Error)
	{
		times_result = result_OK;
		printf("Enter the times you want to play(MUST BE A POSITIVE INTEGER!):");
		gets(user_times);
		rewind(stdin);

		if (strlen(user_times) != 0)
		{
			for (i = 0; i < strlen(user_times); i++)
			{
				if (!isdigit(user_times[i]))
				{
					times_result = result_Error;
					break;
				}
			}
		}
		if (times_result == result_Error)
		{
			printf("The times you input is illegal, please try again!\n");
			Sleep(1500);
			system("cls");
		}
	}
	*game_times = atoi(user_times);
}

General_Select computer_select_get(int illegal_bias)
{
	int randnum = 0;
	General_Select computer_select;

	srand((unsigned int)time(NULL));
	randnum = rand() % 3;
	switch (randnum)
	{
	case 0:
		computer_select = rock;
		print_rock(normal, 0, illegal_bias + rounds_Y_bias);
		break;
	case 1:
		computer_select = scissors;
		print_scissors(normal, 0, illegal_bias + rounds_Y_bias);
		break;
	default:
		computer_select = paper;
		print_paper(normal, 0, illegal_bias + rounds_Y_bias);
	}

	return computer_select;
}

General_Select user_select_get(int *illegal_bias)
{
	char select_input[256] = { 0 };
	General_Result select_result = result_Error;
	General_Select user_select;

	printf("Please use a letter to choose what you want, the meanings are as follows:\n");
	printf("r: Rock \t\t s: Scissors \t\t p: Paper\n\n");

	while (select_result == result_Error)
	{
		printf("Computer choice is:");
		printf_delta("Your choice is(r/s/p): ", 30, 0);
		gets(select_input);
		rewind(stdin);

		if (strlen(select_input) == 1)
		{
			switch (select_input[0])
			{
			case 'r':
			case 's':
			case 'p':
				select_result = result_OK;
				break;
			default:
				select_result = result_Error;
			}
		}
		if (select_result == result_Error)
		{
			printf("Your input is illegal, please try again!\n\n");
			*illegal_bias += 2;
			Sleep(1000);
		}
	}

	switch(select_input[0])
	{
	case 'r':
		user_select = rock;
		print_rock(normal, rounds_user_X_bias, *illegal_bias + rounds_Y_bias);
		break;
	case 's':
		user_select = scissors;
		print_scissors(normal, rounds_user_X_bias, *illegal_bias + rounds_Y_bias);
		break;
	default:
		user_select = paper;
		print_paper(normal, rounds_user_X_bias, *illegal_bias + rounds_Y_bias);
	}

	return user_select;
}

Game_Player rounds_UI(int *game_times)
{
	int remain_games = *game_times, computer_win = 0, user_win = 0, *illegal_bias, ill_bias_pbase;
	General_Select computer_select, user_select;
	Game_Player current_winner, final_winner;

	illegal_bias = &ill_bias_pbase;
	for (remain_games = *game_times; remain_games > 0; remain_games--)
	{
		*illegal_bias = 0;
		system("cls");
		printf("You have %d times to play!\n", remain_games);
		printf("Score List:\n\n");
		printf("YOU: %d\n", user_win);
		printf("COMPUTER: %d\n\n", computer_win);

		user_select = user_select_get(illegal_bias);
		computer_select = computer_select_get(*illegal_bias);
		current_winner = compare(computer_select, user_select);
		if (current_winner == computer)
		{
			printf_delta("Computer win this time!\n", 0, 2);
			computer_win++;
		}
		else if (current_winner == user)
		{
			printf_delta("You win this time!\n", 0, 2);
			user_win++;
		}
		else
			printf_delta("Nobody win this time!\n", 0, 2);

		printf("\nPress \"Enter\" to continue game...");
		rewind(stdin);
		while (getchar() != '\n');
	}

	if (computer_win > user_win) final_winner = computer;
	else if (computer_win < user_win) final_winner = user;
	else final_winner = none;

	return final_winner;
}

Game_Player compare(General_Select computer_select, General_Select user_select)
{
	Game_Player current_winner;

	if (computer_select == user_select) current_winner = none;
	else
	{
		switch (computer_select)
		{
		case rock:
			if (user_select == rock) current_winner = none;
			if (user_select == scissors) current_winner = computer;
			if (user_select == paper) current_winner = user;
			break;
		case scissors:
			if (user_select == rock) current_winner = user;
			if (user_select == scissors) current_winner = none;
			if (user_select == paper) current_winner = computer;
			break;
		default:
			if (user_select == rock) current_winner = computer;
			if (user_select == scissors) current_winner = user;
			if (user_select == paper) current_winner = none;
		}
	}

	return current_winner;
}

void final_UI(Game_Player final_winner)
{
	system("cls");
	switch (final_winner)
	{
	case computer:
		printf("Sorry, you lose :(\n");
		break;
	case user:
		printf("Congratulations! You win :)\n");
		break;
	default:
		printf("Nobody win the game =_=\n");
	}
	Sleep(1500);
}

void printf_position(char *data, int init_X, int init_Y)
{
	HANDLE hd;
	COORD position;

	hd = GetStdHandle(STD_OUTPUT_HANDLE);
	position.X = init_X;
	position.Y = init_Y;

	SetConsoleCursorPosition(hd, position);
	printf("%s", data);
}

void printf_delta(char *data, int delta_X, int delta_Y)
{
	HANDLE hd;
	COORD position;
	CONSOLE_SCREEN_BUFFER_INFO console_buf;

	hd = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hd, &console_buf);
	position.X = console_buf.dwCursorPosition.X;
	position.Y = console_buf.dwCursorPosition.Y;
	position.X += delta_X;
	position.Y += delta_Y;
	
	SetConsoleCursorPosition(hd, position);
	printf("%s", data);
}

void print_rock(Character_Size size, int bias_X, int bias_Y)
{
	int x_normal[] = { 5,7,9,11,4,6,8,10,12,2,3,4,6,8,10,12,2,4,6,8,10,12,2,4,5,6,7,8,9,10,11,12,2,12,2,12,2,3,4,5,6,7,8,9,10,11,12 };
	int y_normal[] = { 2,2,2, 2,3,3,3, 3, 3,4,4,4,4,4, 4, 4,5,5,5,5, 5, 5,6,6,6,6,6,6,6, 6, 6, 6,7, 7,8, 8,9,9,9,9,9,9,9,9, 9, 9, 9 };
	int x_mini[] = { 3,5,7,2,4,6,8,2,4,6,8,2,8,2,3,4,5,6,7,8 };
	int y_mini[] = { 2,2,2,3,3,3,3,4,4,4,4,5,5,6,6,6,6,6,6,6 };
	int pos_len;

	if (size == normal)
	{
		GET_ARRAY_LEN(x_normal, pos_len);
		for (int i = 0; i < pos_len; i++)
			printf_position("*", bias_X + x_normal[i] * 2.5, bias_Y + y_normal[i]);
		printf("\n");
	}
	else
	{
		GET_ARRAY_LEN(x_mini, pos_len);
		for (int i = 0; i < pos_len; i++)
			printf_position("*", bias_X + x_mini[i] * 2, bias_Y + y_mini[i]);
		printf("\n");
	}
}

void print_scissors(Character_Size size, int bias_X, int bias_Y)
{
	int x_normal[] = { 12,3,4,11,2,5,10,3,5,9,4,8,5,7,6,7,5, 8, 4, 9, 5, 3,10, 5, 2,11, 4, 3,12 };
	int y_normal[] = {  2,3,3, 3,4,4, 4,5,5,5,6,6,7,7,8,9,9,10,10,11,11,11,12,12,12,13,13,13,14 };
	int x_mini[] = {2,3,6,2,3,5,4,5,3,2,6,3,2};
	int y_mini[] = {2,2,2,3,3,3,4,5,5,5,6,6,6};
	int pos_len;

	if (size == normal)
	{
		GET_ARRAY_LEN(x_normal, pos_len);
		for (int i = 0; i < pos_len; i++)
			printf_position("*", bias_X + x_normal[i] * 2.5, bias_Y + y_normal[i]);
		printf("\n");
	}
	else
	{
		GET_ARRAY_LEN(x_mini, pos_len);
		for (int i = 0; i < pos_len; i++)
			printf_position("*", bias_X + x_mini[i] * 2, bias_Y + y_mini[i]);
		printf("\n");
	}
}

void print_paper(Character_Size size, int bias_X, int bias_Y)
{
	int x_normal[] = { 6,7,8,5,6,7,8,9,4,5,6,7,8,9,10,3,4,5,6,7,8,9,10,11,2,3,4,5,6,7,8,9,10,11,12,2,3,4,5,6,7,8,9,10,11,12,12,11,10,9,8,7,6,5,4,3,2,11,10,9,8,7,6,5,4,3,10, 9, 8, 7, 6, 5, 4, 9, 8, 7, 6, 5, 8, 7, 6 };
	int y_normal[] = { 2,2,2,3,3,3,3,3,4,4,4,4,4,4, 4,5,5,5,5,5,5,5, 5, 5,6,6,6,6,6,6,6,6, 6, 6, 6,7,7,7,7,7,7,7,7, 7, 7, 7, 8, 8, 8,8,8,8,8,8,8,8,8, 9, 9,9,9,9,9,9,9,9,10,10,10,10,10,10,10,11,11,11,11,11,12,12,12 };
	int x_mini[] = { 4,5,3,4,5,6,2,3,4,5,6,7,7,6,5,4,3,2,6,5,4,3,5,4 };
	int y_mini[] = { 2,2,3,3,3,3,4,4,4,4,4,4,5,5,5,5,5,5,6,6,6,6,7,7 };
	int pos_len;

	if (size == normal)
	{
		GET_ARRAY_LEN(x_normal, pos_len);
		for (int i = 0; i < pos_len; i++)
			printf_position("*", bias_X + x_normal[i] * 2, bias_Y + y_normal[i]);
		printf("\n");
	}
	else
	{
		GET_ARRAY_LEN(x_mini, pos_len);
		for (int i = 0; i < pos_len; i++)
			printf_position("*", bias_X + x_mini[i] * 2, bias_Y + y_mini[i]);
		printf("\n");
	}
}