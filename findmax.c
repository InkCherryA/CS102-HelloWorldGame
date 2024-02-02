#include "helloworld.h"

int score = 0;
int* board = NULL;
int size = 0;
int* max;
char* answer;

void findmax_print_board()
{
  for(int i = 0; i < pow(size, 2); i++)
  {
    printf("%5.d", board[i]);
    if((i + 1) % size == 0)
    {
      printf("\n");
    }
  }
}

void findmax_reset()
{
  for(int i = 0; i < pow(size, 2); i++)
  {
    board[i] = rand() % 200;
  }
  for(int i = 0; i < size; i++)
  {
    max[i] = 0;
  }
}

void findmax_max()
{
  answer[0] = '\0';
  char* ptr = answer;
  for(int i = 0; i < size; i++)
  {
    for(int j = 0; j < pow(size, 2); j++)
    {
      if(board[j] > max[i] && (i == 0 || (i != 0 && board[j] < max[i - 1])))
      {
        max[i] = board[j];
      }
    }
  }
  for(int i = 0; i < size; i++)
  {
    sprintf(ptr + strlen(answer), "%d ", max[i]);
  }
  answer[strlen(answer)-1] = '\0';
}

int main()
{
  srand((unsigned)time(NULL));
  FILE* recp = fopen("record.txt", "a");
  printf("%sMINIGAME: Things Fall Apart%s\n\n", UYEL, RST);
  printf(
    "\"Hi little fella over there, \"the junkyard worker called. "
    "You look over to him and see a notebook in his hands. "
    "\"I have written down the weight of the scraps in here. Would you be kind enough to help me find the best ones to sell for today?\"\n\n"
    "While nodding your head, you approached him and looked down at his notebook.\n\n"
  );

  printf("%sPlease choose difficulty level:\na. easy    b. medium    c.hard\n%s", MAG, RST);
  while(true)
  {
    if(!strcasecmp(fgetl(stdin), "a"))
    {
      size = 3;
      break;
    }
    else if(!strcasecmp(temp, "b"))
    {
      size = 5;
      break;
    }
    else if(!strcasecmp(temp, "c"))
    {
      size = 7;
      break;
    }
    else if(!strcasecmp(temp, "quit"))
    {
      return 0;
    }
    else
    {
      printf("%sInvalid input.%s\n", RED, RST);
    }
  }

  board = (int*)malloc(pow(size, 2) * sizeof(int));
  max = (int*)malloc(size * sizeof(int));
  answer = (char*)malloc(BUFF4 * sizeof(char));
  printf("%sRULE: please sort the first %d largest number in descending order separated by space.%s\n", MAG, size, RST);

  while(true)
  {
    findmax_reset();
    findmax_print_board();
    findmax_max();
    if(!strcasecmp(fgetl(stdin), answer))
    {
      printf("%sCorrect, you've earned %d credits%s\n", MAG, size, RST);
      score += size;
    }
    else
    {
      printf("%sThe correct answer is: \n%s%s\n", RED, answer, RST);
      break;
    }
  }

  printf("\n%sEND OF MINIGAME%s\n\n", UYEL, RST);
  fprintf(recp, "%d\n", score);
  fclose(recp);
  return 0;
}
