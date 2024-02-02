#include "helloworld.h"

//global variables
//CONCEPT: 6 pointer
FILE* rec = NULL;
//CONCEPT: 7 array
char temp[BUFF8];
struct place* places = NULL;
int maxlen = 0;
Player player;

//utility functions
char* _flush_crlf()
{
  //CONCEPT: 8 for loop
  for(int i = 0; temp[i] != '\0'; i++)
  {
    //CONCEPT: 9 if statement
    if(temp[i] == '\r' || temp[i] == '\n')
    {
      temp[i] = '\0';
    }
  }
  return temp;
}
char* fgetl(FILE* fp)
{
  printf("%s", GRN);
  fgets(temp, BUFF8, fp);
  _flush_crlf();
  printf("%s", RST);
  return temp;
}
void opt()
{
  //CONCEPT: 10 while loop
  while(true)
  {
    fgetl(stdin);
    if(!strcasecmp(temp, "option"))
    {
      printf(
        "option - show avilable commands\n"
        "map - print out map and view available locations\n"
        "travel - travel to a place using coordinates\n"
        "game - show available minigames at this place\n"
        "player - print out player status\n"
        "back - cancel input\n"
        "continue - continue game\n"
      );
    }
    else if(!strcasecmp(temp, "map"))
    {
      print_place();
    }
    else if(!strcasecmp(temp, "travel"))
    {
      printf("%sWhere do you want to go?%s\n", MAG, RST);
      if(!strcasecmp(fgetl(stdin), "back"));
      else
      {
        int x = 0;
        int y = 0;
        sscanf(temp, "%d, %d", &x, &y);
        move_player(x, y);
      }
    }
    else if(!strcasecmp(temp, "game"))
    {
      if(player.place->npc == NULL)
      {
        printf("%sNobody is here yet.%s\n", RED, RST);
      }
      else
      {
        printf("%sDo you want to play %s with %s? (yes/no)%s\n", MAG, player.place->npc->game, player.place->npc->name, RST);
        if(!strcasecmp(fgetl(stdin), "yes"))
        {
          run_game(player.place->npc->game);
        }
      }
    }
    else if(!strcasecmp(temp, "player"))
    {
      print_player();
    }
    else if(!strcasecmp(temp, "continue"))
    {
      return;
    }
    else
    {
      printf("%sInvalid input, please try again:%s\n", RED, RST);
    }
  }
}

void init_game(int argc, char* argv[])
{
  //compiles auxiliary files
  printf("%s\n", BLK);
  system("make aux");
  printf("\033[3A%s", RST);
  //open score board
  rec = fopen("record.txt", "w+");
  //get player name
  setup_player(argc, argv);
  //initialize places
  places = (Place*)malloc(pow(MAPSIZE, 2) * sizeof(Place));
  init_place();
  import_place();

  return;
}

//story functions
void choose(Story* p)
{
  player.lock = true;
  printf("\n====\n");
  printf("%s", p->line);
  printf("====\n");
  if(p->choice1 == NULL && p->choice2 == NULL)
  {
    return;
  }
  printf("%sPlease enter your choice: ", MAG);

  while(true)
  {
    char c[BUFF1];
    fgetl(stdin);
    printf("%s", RST);
    if(strcasecmp(temp, "a") == 0 && p->choice1 != NULL)
    {
      choose(p->choice1);
      break;
    }
    else if(strcasecmp(temp, "b") == 0 && p->choice2 != NULL)
    {
      choose(p->choice2);
      break;
    }
    else
    {
      printf("%sInvalid input. Try again: ", RED);
    }
  }
  player.lock = false;
  return;
}
void link_story(Story* p, int n1, int n2, int n3)
{
  if(n2 != 0)
  {
    (p + n1 - 1)->choice1 = p + n2 - 1;
  }
  if(n3 != 0)
  {
    (p + n1 - 1)->choice2 = p + n3 - 1;
  }
  return;
}
void init_story(Story* p, int n, char* s)
{
  p->n = n;
  p->line = s;
  p->choice1 = NULL;
  p->choice2 = NULL;
  return;
}

//player functions
void print_player()
{
  printf(
    "  _\\/_     Name: %s\n"
    " | '.'|   Score: %d\n"
    " /    \\  Credit: %d\n"
    "  |  |    Place: %s\n",
    player.name, player.score, player.credit, player.place->name
  );

  return;
}
void setup_player(int argc, char* argv[])
{
  Player* p = &player;
  if(argc != 1)
  {
    p->name = strdup(argv[1]);
  }
  else
  {
    printf("%sWhat is your name?%s\n", MAG, RST);
    fgetl(stdin);
    p->name = strdup(temp);
  }
  p->place = NULL;
  p->lock = false;
  p->score = 0;
  p->credit = 100;
  printf("%sYour name is set to: %s%s\n", MAG, player.name, RST);
  return;
}

//npc functions
NPC* setup_npc(char* s, char* game, int x, int y)
{
  NPC* npc = (NPC*)malloc(sizeof(NPC));
  npc->name = s;
  npc->game = game;
  move_npc(npc, x, y);
  return npc;
}

//place functions
bool unlock_place(int x, int y)
{
  Place* p = _get_place(x, y);
  _get_place(x, y);
  if(p == NULL)
  {
    return false;
  }
  p->lock = false;
  printf("%s%s is unlocked.%s\n", MAG, p->name, RST);
  return true;
}
bool setup_place(int x, int y, char* s)
{
  Place* p = _get_place(x, y);
  if(p == NULL)
  {
    return false;
  }
  if(p->name != NULL)
  {
    printf("%sPlace already exist.%s\n", RED, RST);
    return false;
  }
  p->name = strdup(s);
  p->x = x;
  p->y = y;
  return true;
}
void import_place()
{
  FILE* fp = fopen("place.txt", "r");

  for(int i = 1; i <= MAPSIZE; i++)
  {
    for(int j = 1; j <= MAPSIZE; j++)
    {
      setup_place(i, j, fgetl(fp));
      if(strlen(temp) > maxlen)
      {
        maxlen = strlen(temp) + 1;
      }
    }
  }
  fclose(fp);
  return;
}
Place* _get_place(int x, int y)
{
  if(x < 1 || x > MAPSIZE || y < 1 || y > MAPSIZE)
  {
    printf("%sPlace out of range.%s\n", RED, RST);
    return NULL;
  }
  Place* p = places;
  p += (x - 1) * MAPSIZE + y - 1;
  return p;
}
void init_place()
{
  Place* p = places;
  for(int i = 0; i < MAPSIZE; i++)
  {
    for(int j = 0; j < MAPSIZE; j++)
    {
      p->name = NULL;
      p->lock = true;
      p->x = j;
      p->y = i;
      p->visit = 0;
      p->npc = NULL;
      // for(int k = 0; k < BUFF2; k++)
      // {
      //   p->npc[k] = NULL;
      // }
      p++;
    }
  }
  player.place = places;
  return;
}
void print_place()
{
  for(int i = 0; i < (int)log10((double)MAPSIZE) + 2; i++)
  {
    printf(" ");
  }
  Place* p = places;
  for(int i = 1; i <= MAPSIZE; i++)
  {
    for(int k = 0; k < maxlen - (int)log10((double)i); k++)
    {
      printf(" ");
    }
    printf("%d", i);
  }
  printf("\n");
  for(int i = 0; i < MAPSIZE; i++)
  {
    for(int i = 0; i < (int)log10((double)MAPSIZE) + 2; i++)
    {
      printf(" ");
    }
    for(int j = 0; j < MAPSIZE; j++)
    {
      printf("+");
      for(int k = 0; k < maxlen; k++)
      {
        printf("-");
      }
    }
    printf("+\n");

    for(int k = 0; k < 1 + (int)log10((double)MAPSIZE) - (int)log10((double)(i+1)); k++)
    {
      printf(" ");
      printf("%d", i + 1);
    }

    for(int j = 0; j < MAPSIZE; j++)
    {
      printf("|");
      if(p->lock)
      {
        for(int k = 0; k < maxlen - 1; k++)
        {
          printf(" ");
        }
        printf("?");
      }
      // else if(p->name == NULL)
      // {
      //   for(int k = 0; k < maxlen - 6; k++)
      //   {
      //     printf(" ");
      //   }
      //   printf("(null)");
      // }
      else if(p == player.place)
      {
        for(int k = 0; k < maxlen - strlen(p->name) - 1; k++)
        {
          printf(" ");
        }
        printf("*%s", p->name);
      }
      else
      {
        for(int k = 0; k < maxlen - strlen(p->name); k++)
        {
          printf(" ");
        }
        printf("%s", p->name);
      }
      p++;
    }
    printf("|\n");
  }
  for(int i = 0; i < (int)log10((double)MAPSIZE) + 2; i++)
  {
    printf(" ");
  }
  for(int j = 0; j < MAPSIZE; j++)
  {
    printf("+");
    for(int k = 0; k < maxlen; k++)
    {
      printf("-");
    }
  }
  printf("+\n");
  return;
}
bool move_npc(NPC* npc, int x, int y)
{
  Place* p = _get_place(x, y);
  if(npc->place == p)
  {
    printf("%sNPC is already here.%s\n", RED, RST);
    return false;
  }
  npc->place = p;
  for(int i = 0; i < BUFF2; i++)
  {
    if(p->npc == NULL)
    {
      p->npc = npc;
      npc->place = p;
      printf("%s%s is in %s now.%s\n", MAG, npc->name, p->name, RST);
      return true;
    }
    // if(p->npc[i] == NULL)
    // {
    //   p->npc[i] = npc;
    //   npc->place = p;
    //   printf("%s is in %s now\n", npc->name, p->name);
    //   return true;
    // }
  }
  printf("%sThis place is full.%s\n", RED, RST);
  return false;
}
bool move_player(int x, int y)
{
  Place* original = player.place;
  Place* new = _get_place(x, y);
  if(new == NULL)
  {
    return false;
  }
  else if(original == new)
  {
    printf("%sYou are already here%s\n", RED, RST);
    return false;
  }
  else if(new->lock)
  {
    printf("%sYou have not unlocked this place yet.%s\n", RED, RST);
    return false;
  }
  int diff = abs(x - original->x) + abs(y - original->y);
  int price = diff * 50 / (new->visit + 1);
  if(player.credit < price)
  {
    printf("%sYou need %d credit to travel here%s\n", RED, price, RST);
    return false;
  }
  player.place = new;
  player.credit -= price;
  new->visit++;
  printf("%sYou are now in %s.\nRemaining credit: %d%s\n", MAG, player.place->name, player.credit, RST);
  return true;
}

//minigame Functions
void run_game(char* s)
{
  printf("%s\n", BLK);
  sprintf(temp, "make %s", s);
  printf("\033[2A\n");
  system(temp);
  printf("%s", RST);
  sprintf(temp, "./%s.exe", s);
  system(temp);
  sprintf(temp, "rm %s.exe", s);
  system(temp);
  int n = atoi(fgetl(rec));
  player.score += n;
  player.credit += n;
  printf("%s\n", RST);
  return;
}
