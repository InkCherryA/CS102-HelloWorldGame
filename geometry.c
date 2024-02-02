#include "helloworld.h"

struct frustum
{
  int topr;
  int botr;
  int h;
  int volume;
};

int score = 0;
struct frustum geo;
int shape = 0;
int max = 20;

void geometry_reset()
{
  geo.topr = rand() % 10 + 1;
  geo.botr = rand() % 10 + 1;
  geo.h = rand() % 20 + 1;
  if(shape == 5)
  {
    geo.volume = 3 * pow(geo.botr, 2) * geo.h;
  }
  else if(shape == 7)
  {
    geo.volume = pow(geo.botr, 2) * geo.h;
  }
  else if(shape == 10)
  {
    geo.volume = (pow(geo.botr, 2) + pow(geo.topr, 2) + geo.topr * geo.botr) * geo.h;
  }
}

void geometry_print()
{
  if(shape == 5)
  {
    printf(
      "Cylinder\n"
      "Radius: %d\n"
      "Height: %d\n"
      "Volume: πhr^2\n",
      geo.botr, geo.h
    );
  }
  else if(shape == 7)
  {
    printf(
      "Cone\n"
      "Radius: %d\n"
      "Height: %d\n"
      "Volume: 1/3 x πhr^2\n",
      geo.botr, geo.h
    );
  }
  else if(shape == 10)
  {
    printf(
      "Frustum\n"
      "Radius 1: %d\n"
      "Radius 2: %d\n"
      "Height: %d\n"
      "Volume: 1/3 x πh(r^2 + R^2 + rR)\n",
      geo.botr, geo.topr, geo.h
    );
  }
}


int main()
{
  srand((unsigned)time(NULL));
  FILE* recp = fopen("record.txt", "a");
  printf("%sMINIGAME: The Duckness of the Thing%s\n\n", UYEL, RST);
  printf(
    "You approached the counter with a can of tuna. "
    "\"That'll be $8.99.\" The cashier says. "
    "You tilted your head, not knowing what the number means. "
    "\"Do you not have money on you?\" The cashier asks. "
    "You both stood in silence for seconds with only the shutter sound of your blinking. "
    "\"Well, it's fine, we're closing soon, so if you could just help me sort these cans out,\" the cashier says finally.\n\n"
  );

  printf("%sPlease choose difficulty level:\na. easy    b. medium    c.hard\n%s", MAG, RST);
  while(true)
  {
    if(!strcasecmp(fgetl(stdin), "a"))
    {
      shape = 5;
      break;
    }
    else if(!strcasecmp(temp, "b"))
    {
      shape = 7;
      break;
    }
    else if(!strcasecmp(temp, "c"))
    {
      shape = 10;
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

  printf("%sRULE: Calculate the volume of the geometry. Use π = 3.%s\n", MAG, RST);
  while(true)
  {
    geometry_reset();
    geometry_print();
    if(atoi(fgetl(stdin)) == geo.volume)
    {
      printf("%sCorrect, you've earned %d credits%s\n", MAG, shape, RST);
      score += shape;
    }
    else
    {
      printf("%sThe correct answer is: %d%s\n", RED, geo.volume, RST);
      break;
    }
  }

  printf("\n%sEND OF MINIGAME%s\n\n", UYEL, RST);
  fprintf(recp, "%d\n", score);
  fclose(recp);
}
