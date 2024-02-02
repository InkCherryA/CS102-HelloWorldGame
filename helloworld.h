//INCLUDE LIBRARY
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include <time.h>

//DEFINE BUFFER SIZE
#define BUFF1 5
#define BUFF2 10
#define BUFF3 50
#define BUFF4 100
#define BUFF5 500
#define BUFF6 1000
#define BUFF7 5000
#define BUFF8 10000

//DEFINE CONSTANT
#define MAPSIZE 3

//struct definitions
typedef struct player
{
  char* name;
  struct place* place;
  bool lock;
  int score;
  int credit;
}
Player;
typedef struct place
{
  char* name;
  bool lock;
  int x;
  int y;
  int visit;
  struct nonplayer* npc;
}
Place;
typedef struct nonplayer
{
  char* name;
  char* game;
  struct place* place;
}
NPC;
typedef struct story
{
  int n;
  char* line;
  struct story* choice1;
  struct story* choice2;
}
Story;

//global variables
extern FILE* rec;
extern char temp[];
extern struct place* places;
extern int maxlen;
extern Player player;

//utility functions
char* _flush_crlf();
char* fgetl(FILE* fp);
void opt();
void init_game(int argc, char* argv[]);

//story functions
void choose(Story* p);
void link_story(Story* p, int n1, int n2, int n3);
void init_story(Story* p, int n, char* s);
void setup_intro1(Story* intro1);

//player functions
void print_player();
void setup_player(int argc, char* argv[]);

//npc functions
NPC* setup_npc(char* s, char* game, int x, int y);

//place functions
bool unlock_place(int x, int y);
bool setup_place(int x, int y, char* s);
void import_place();
Place* _get_place(int x, int y);
void get_loca(Place* p, int* x, int* y);
void init_place();
void print_place();
bool move_npc(NPC* npc, int x, int y);
bool move_player(int x, int y);

//minigame Functions
void run_game(char* s);

//DEFINE TEXT STYLE
//Regular text
#define BLK "\e[0;30m"
#define RED "\e[0;31m"
#define GRN "\e[0;32m"
#define YEL "\e[0;33m"
#define BLU "\e[0;34m"
#define MAG "\e[0;35m"
#define CYN "\e[0;36m"
#define WHT "\e[0;37m"
//Regular bold text
#define BBLK "\e[1;30m"
#define BRED "\e[1;31m"
#define BGRN "\e[1;32m"
#define BYEL "\e[1;33m"
#define BBLU "\e[1;34m"
#define BMAG "\e[1;35m"
#define BCYN "\e[1;36m"
#define BWHT "\e[1;37m"
//Regular underline text
#define UBLK "\e[4;30m"
#define URED "\e[4;31m"
#define UGRN "\e[4;32m"
#define UYEL "\e[4;33m"
#define UBLU "\e[4;34m"
#define UMAG "\e[4;35m"
#define UCYN "\e[4;36m"
#define UWHT "\e[4;37m"
//Regular background
#define BLKB "\e[40m"
#define REDB "\e[41m"
#define GRNB "\e[42m"
#define YELB "\e[43m"
#define BLUB "\e[44m"
#define MAGB "\e[45m"
#define CYNB "\e[46m"
#define WHTB "\e[47m"
//High intensty background
#define BLKHB "\e[0;100m"
#define REDHB "\e[0;101m"
#define GRNHB "\e[0;102m"
#define YELHB "\e[0;103m"
#define BLUHB "\e[0;104m"
#define MAGHB "\e[0;105m"
#define CYNHB "\e[0;106m"
#define WHTHB "\e[0;107m"
//High intensty text
#define HBLK "\e[0;90m"
#define HRED "\e[0;91m"
#define HGRN "\e[0;92m"
#define HYEL "\e[0;93m"
#define HBLU "\e[0;94m"
#define HMAG "\e[0;95m"
#define HCYN "\e[0;96m"
#define HWHT "\e[0;97m"
//Bold high intensity text
#define BHBLK "\e[1;90m"
#define BHRED "\e[1;91m"
#define BHGRN "\e[1;92m"
#define BHYEL "\e[1;93m"
#define BHBLU "\e[1;94m"
#define BHMAG "\e[1;95m"
#define BHCYN "\e[1;96m"
#define BHWHT "\e[1;97m"
//Reset
#define RST "\e[0m"
