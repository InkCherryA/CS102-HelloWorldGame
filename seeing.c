#include "helloworld.h"

#define N 5

typedef struct object
{
  char* name;
  char* start;
  int reward;
  char* end;
}
Object;

int score = 0;

bool seeing_choose(Object* o);
void seeing_add_object(Object* o, char* s, char* t, char* u);

void seeing_setup_object(Object* o)
{
    seeing_add_object(o++,
      "cars",
      "Surrounding you are these objects that are symmetrical along one axis, "
      "slightly different along another, and tapers vertically. "
      "\"What are these?\" you ask the mind.\n",
      "\"These are cars, they are used by humans to travel long distances.\"\n\n"
    );
    seeing_add_object(o++,
      "glass",
      "Although the lights reflecting off the cars are in many different colors, "
      "there will always be a few pieces on the periphery that seem to reflect something, "
      "but also allow you to see behind. "
      "\"What is that material?\" you ask.\n",
      "\"They are glass, they shield people from the violence of nature, "
      "but allows them to enjoy its beauty that they always desire.\"\n\n"
    );
    seeing_add_object(o++,
      "sky",
      "Attracted by the busyness of the cars, "
      "you realize that you have been ignoring the large smooth surface that hovers above all of them. "
      "The cold tint of it is decorated by instances of white schmear. "
      "You cannot describe the form of it like you did the other objects.\n",
      "\"They call it the sky, and the white fluffs are called clouds. "
      "Interestingly the word sky used to mean cloud, "
      "because their presence is more noticeable than their absence.\"\n\n"
    );
    seeing_add_object(o++,
      "metal",
      "Rotating your head, the input of your visual sensor changes accordingly. "
      "When you lower your eye level, you see yourself lying there. "
      "Your body has the same texture as the cars in front of you, "
      "almost blending into the scene. "
      "\"What am I made of?\"\n",
      "\"Your body is made of metal. But you are much more than those chunks of metals beside you.\"\n\n"
    );
    seeing_add_object(o++,
      "bird",
      "As you are contemplating the meaning behind these word, "
      "an object descends from the sky rapidly. "
      "It lands softly on a car, and is sending out rhythmic high frequency sound signals. "
      "It bounces occasionally on the cars, making a metallic sound.\n",
      "\"This is a bird, but more generally an animal. "
      "Their bodies are composed of organic matter. "
      "Human is also a kind of animal.\n\n"
    );
}

void seeing_add_object(Object* o, char* s, char* t, char* u)
{
  o->name = s;
  o->start = t;
  o->reward = 10;
  o->end = u;
}

int main()
{
  FILE* recp = fopen("record.txt", "a");
  printf("%sMAINGAME: Seeing is Remembering the Name of the Thing One Sees%s\n\n", UYEL, RST);
  Object* objects = (Object*)malloc(N * sizeof(Object));
  seeing_setup_object(objects);
  seeing_choose(objects);
  printf(
    "After several rounds of question and answer, you learned the names of most objects within your sight. "
    "However, the idea of human that the mind spoke so often of is still puzzling you. "
    "You walked out from the junkyard accompanied by the ticks in your electrical brain that indicate the transferring of data to permanent storage...\n"
  );
  printf("\n%sEND OF MAINGAME%s\n\n", UYEL, RST);

  fprintf(recp, "%d\n", score);
  fclose(recp);
  return 0;
}

bool seeing_choose(Object* o)
{
  Object* op = o;
  while(op < o + N)
  {
    printf("%s\n", op->start);
    printf("%sPlease enter your answer: %s", MAG, RST);
    while(strcasecmp(fgetl(stdin), op->name))
    {
      op->reward--;
      if(op->reward == 0)
      {
        printf("%sSorry, you've used up your chances.%s\n", RED, RST);
        printf("%sThe correct answer is \"%s\".%s\n\n", MAG, op->name, RST);
        printf("%s", op++->end);
        break;
      }
      printf("%sWrong answer, try again: %s", RED, RST);
    }
    if(!strcasecmp(temp, op->name))
    {
      printf("%sCorrect! The answer is \"%s\"!\nYou've earned %d credit.%s\n\n", MAG, op->name, op->reward, RST);
      printf("%s", op->end);
      score += op++->reward;
    }
  }

  return true;
}
