#include "helloworld.h"

#define FISHNUM 12

struct fishy
{
  char* name;
  int n;
};

int score = 0;
struct fishy fish[FISHNUM];
struct fishy** board;
int size = 0;
struct fishy** max = NULL;
char* answer;

void fish_print()
{
  for(int i = 0; i < pow(size, 2); i++)
  {
    int j = rand() % 12;
    board[i] = &fish[j];
    printf("%12s", board[i]->name);
    fish[j].n++;
    if((i + 1) % size == 0)
    {
      printf("\n");
    }
  }
}

void fish_reset()
{
  for(int i = 0; i < FISHNUM; i++)
  {
    fish[i].n = 0;
    max[i] = NULL;
  }
}

void fish_max()
{
  answer[0] = '\0';
  char* ptr = answer;
  int maxn = 0;
  for(int i = 0; i < FISHNUM; i++)
  {
    if(fish[i].n > maxn)
    {
      maxn = fish[i].n;
    }
  }
  for(int i = 0; i < pow(size, 2); i++)
  {
    if(board[i]->n == maxn)
    {
      int j = 0;
      for(; max[j] != NULL; j++)
      {
        if(board[i] == max[j])
        {
          break;
        }
      }
      if(max[j] == NULL)
      {
        max[j] = board[i];
      }
    }
  }
  for(int i = 0; max [i] != NULL; i++)
  {
    sprintf(ptr + strlen(answer), "%s ", max[i]->name);
  }
  sprintf(ptr + strlen(answer), "%d\0", maxn);
}

void fish_init()
{
  srand((unsigned)time(NULL));
  FILE* fp = fopen("fish.txt", "r");
  for(int i = 0; i < FISHNUM; i++)
  {
    fish[i].name = strdup(fgetl(fp));
  }
  max = (struct fishy**)malloc(FISHNUM * sizeof(struct fishy*));
  answer = (char*)malloc(BUFF4 * sizeof(char));
  board = (struct fishy**)malloc(pow(size, 2) * sizeof(struct fishy*));
  return;
}

int main()
{
  FILE* recp = fopen("record.txt", "a");
  printf("%sMINIGAME: A Fishy World%s\n\n", UYEL, RST);
  printf(
    "\"It's a nice day to fish out there, \"the fisherman says to himself while dragging a netful of fish onto onto the deck. "
    "Suddenly, A tuna jumped out of net. With your precise calculations, it fell right into your hands. "
    "\"Nice reflexes, and great calculation,\" remarked the fishman, \"would you like to help me count these fish also? I can cook you tuna afterwards,\" "
    "says the fisherman with a kind smile on his face.\n\n"
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

  fish_init();

  printf("%sRULE: Please find the most common type of fish followed by their number. If there are more than one, sort by appearance in the board. Separate with space.%s\n", MAG, RST);

  while(true)
  {
    fish_reset();
    fish_print();
    fish_max();
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
}
