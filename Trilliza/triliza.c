#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void init_board(char board[][3]);

int input(int * row, int * col);

void print_board(char board[][3]);

void clear_stdin();

void clear_screen();

int is_valid_input(char in[5]);

int is_empty_cell(int i, int j, char board[][3]);

char somebody_wins(char board[][3]);

int is_draw(char board[][3]);

int save(char board[][3]);

int load(char board[][3], int * round);

int menu();

int main()
{
    int i, j;
    char board[3][3];

    init_board(board);

    int round = 1;
    int row, col;
    clear_screen();

    int choice = menu();
    
    if(choice == 2)
    {
        load(board, &round);
    }
    if (choice == 3)
    {
        exit(1);
    }
    clear_screen();
    print_board(board);

    do
    {
        printf("%s enter row and column: ", round%2 == 1 ? "Player X" : "Player O");
        do
        {
            int s = input(&row, &col);
            clear_screen();
            if(s == 1)
            {
                save(board);
                printf("Goodbye!\n");
                exit(1);
            }
            if(is_empty_cell(row - 1, col - 1, board) == -1) 
            {
                clear_screen();
                print_board(board);
                printf("Cell must not be  taken!\n");
                printf("%s enter row and column: ", round%2 == 1 ? "Player X" : "Player O");
                continue;
            }
        }
        while(is_empty_cell(row - 1, col - 1, board) == -1);

        if(round%2 == 1)
        {
            board[row - 1][col - 1] = 'X';
        }
        else
        {
            board[row - 1][col - 1] = 'O';
        }

        print_board(board);

        round++;
    }
    while(somebody_wins(board) == ' ' && is_draw(board) == -1);

    char w = somebody_wins(board);

    if(w != ' ')
    {
        print("Player %c wins!\n",w);
    }
    else
    {
        print("Draw!\n");
    }
    system('pause');
}

void init_board(char board[][3])
{
    int i, j;
    for(i = 0; i<3; j++)
    {
        for(j = 0; j < 3; j++)
        {
            board[i][j] = ' ';
        }
    }
}

void clear_stdin()
{
    fflush(stdin);
}

void clear_screen()
{
    system("cls");
}

int menu()
{
    print("1. Play\n2. Load\n3 .Exit\n:>");
    char choice;
    do
    {
        scanf("%c", &choice);
        if(choice != '1' && choice != '2' && choice !='3')
        {
            printf("Not valid input\n:>");
            clear_stdin();
        }
    } 
    while (choice != '1' && choice != '2' &&choice != '3');
     clear_stdin();
    return choice - '0';
    
}
int input(int * row, int * col)
{
    int res = 1;
		char in[5]="    ";
		while(1)
		{
            fgets(in, 5, stdin);
            clear_stdin();
            in[strcspn(in, "\n")] = 0;

			res = is_valid_input(in);
			if (res == 0)
			{
				printf("Input must be either 'save' or '[1-3][' '][1-3]'!\n:>");
				continue;
			}
			if(res == 1)
			{
				return 1;
			}
			if(res == 2)
			{
				*row = in[0] - '0';
				*col = in[2] - '0';
				return 0;
			}	
		}
}

int is_valid_input(char in[5])
{
	if(strcmp(in, "save") == 0)
	{
		return 1;
	}
	//Input is valid "[1-3] [1-3]"
	if((in[0] >= '1' && in[0] <= '3') && in[1] == ' ' && (in[2] >= '1' && in[2] <= '3') && in[3] == '\0')
	{
		return 2;
	}
	return 0;
}

void print_board(char board[][3])
{
    int i, j;
    printf("    1   2   3   \n");
    printf("  /-----------\\\n");//Starting divider
    for(i = 0; i < 3; i++)//For every line
    {
        printf("%d | ", i + 1);
        for(j = 0; j < 3; j++)//For every column
        {
            printf("%c | ", board[i][j]);//Print content then divider
        }
        if(i != 2)//For the first two loops
        {
            printf("\n  |-----------|\n");//Print middle divider
        }
    }
    printf("\n  \\-----------/\n");//When done print ending divider
}

int is_empty_cell(int i, int j, char board[3][3])
{
    if (board[i][j] != ' ') 
    {
        return -1;
    }
    else
    {
        return 1;
    }
}

char somebody_wins(char board[3][3])
{
    int i, j;

    for(i = 0; i < 3; i++) //Check each row
    {
        if(board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][2] != ' ')
        {
            return board[i][1];
        }
    }

    for(j = 0; j < 3; j++) //Check each column
    {
        if(board[0][j] == board[1][j] && board[1][j] == board[2][j] && board[2][j] != ' ')
        {
            return board[1][j];
        }
    }

    //Check main diagonal
    if(board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[2][2] != ' ')
    {
        return board[0][0];
    }

    if(board[2][0] == board[1][1] && board[1][1] == board[0][2] && board[0][2] != ' ')
    {
        return board[0][2];
    }

    return ' ';
}

int is_draw(char board[3][3])
{
    //We must count how many empty cells there are
    int empty = 0;
    int i, j;
    for(i = 0; i < 3; i++)
    {
        for(j = 0; j < 3; j++)
        {
            if(board[i][j] == ' ')
            {
                empty++;
            }
        }
    }

    if(somebody_wins(board) == ' ' && empty == 0)
    {
        return 1;
    }
    else
    {
        return -1;
    }
}

int save(char board[3][3])
{
    FILE * savefile;
    if ((savefile = fopen("data.sav", "w")) == NULL)
    {
        return -1;
    }

    int i, j;
    for(i = 0; i < 3; i++)
    {
        for(j = 0; j < 3; j++)
        {
            fprintf(savefile, "%c", board[i][j]);
        }
    }

    fclose(savefile);

    return 1;
}

int load(char board[3][3], int * round)
{
    FILE * savefile;

    if((savefile = fopen("data.sav", "r")) == NULL)
    {
        return -1;
    }

    int i = 0;
    int j = 0;

    int r = 1;

    char c;
    while((c = fgetc(savefile)) != EOF)//While we have not reached the end of file 
    {
        if(c != ' ')//If there is a symbol round counter is increased
        {
            r++;
        }
        board[i][j] = c;//Place character into board
        j++;//Count which column we are
        if(j == 3)
        {
            i++;
            j = 0;
        }
    }

    *round = r;//"Return" round

    fclose(savefile); 

    return 1;
}
