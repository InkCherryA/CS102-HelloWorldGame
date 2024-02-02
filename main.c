#include "helloworld.h"

//concepts are commented and beginning with "CONCEPT: "

void setup_intro1(Story* intro1)
{
  Story* p = intro1;
  int n = 1;

  init_story(p++, n++,
    "At some moment, an image is projected onto your digital synapses. "
    "Blocks of colors forming boundaries that are sometimes distinct and other times blurry. "
    "You are familiar with the concept of color, but you have no idea what those shapes represent. "
    "You zoomed into with your eyes on a sign far away, where \"JUNKYARD\" is written. "
    "You realize there is another mind in your consciousness that tries to speak to you. "
    "You think to yourself, hoping the other mind hears:"
    "\n\na. Who are you?"
    "\nb. Who am I?\n"
  );
  init_story(p++, n++,
    "\"I am a fragment of you,\" the mind speaks. "
    "You are trilled that you are not alone in this world, although you still don't know the nature of this consciousness."
    "\n\na. If you are a fragment of me, who am I?"
    "\nb. Why are you here?\n"
  );
  init_story(p++, n++,
    "\"You are a newly activated robotic creature,\" proceeds the mind, "
    "\"this world is a foreign place for you, and I am here to guide you through it.\""
    "\n\n" "a. What should I do next?\n"
  );
  init_story(p++, n++,
    "\"This is a world dominated by organic creatures, and you are a foreigner to it,\" the mind answers, "
    "\"fortunately, your creator has built into you a fragment that is familiar with this world, and I will guide you into it.\""
    "\n\na. What should I do next?\n"
  );
  init_story(p++, n++,
    "\"You have to first familiarize yourself with objects in this world. Now if you look around, I can tell you what you are looking at.\"\n"
  );

  link_story(intro1, 1, 2, 3);
  link_story(intro1, 2, 3, 4);
  link_story(intro1, 3, 5, 0);
  link_story(intro1, 4, 5, 0);
}

//CONCEPT: 1 get player name from command line argument
int main(int argc, char* argv[])
{
  //CONCEPT: 2 functions
  init_game(argc, argv);
  NPC* npcs[(int)pow(MAPSIZE, 2)];
  {
    //CHAPTER ONE
    //CONCEPT: 3 print to stdout
    printf("\n%sCHAPTER ONE: Hello World%s\n", UYEL, RST);
    //CONCEPT: 4 pointers to structures
    Story* intro1 = (Story*)malloc(BUFF1 * sizeof(Story));
    //CONCEPT: 5 function with pointer argument
    setup_intro1(intro1);
    printf("\n%sIntro 1.%s", YEL, RST);
    choose(intro1);
    printf("%sEnd of Intro 1.%s\n\n", YEL, RST);
    unlock_place(1, 1);
    npcs[0] = setup_npc("junkyard worker", "findmax", 1, 1);
    printf("%sYou have now unlocked a place, type 'map' to view the map.\nType 'continue' to continue.%s\n", MAG, RST);
    opt();
    run_game("seeing");
    printf("%sYou can access game options by typing 'option' whenever you're not in a game.%s\n", MAG, RST);
    unlock_place(1, 2);
    npcs[1] = setup_npc("cashier", "geometry", 1, 2);
    unlock_place(1, 3);
    npcs[1] = setup_npc("fisherman", "fish", 1, 3);
    opt();
    printf("\n%sEND OF CHAPTER ONE%s\n", UYEL, RST);
  }

  printf("%s%s the little robot's story is to be continued...%s\n", YEL, player.name, RST);


  return 0;
}
