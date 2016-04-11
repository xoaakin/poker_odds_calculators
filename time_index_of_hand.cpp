#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
using namespace std;

#define MAIN_MODULE
#include "poker_hand.h"

static char usage[] =
"usage: time_old_index_of_hand (-debug) index_algorithm loop_count\n";

static int index_of_hand0(int *cards);
static int index_of_hand1(int *cards);
static int index_of_hand2(int *cards);

static int offsets[][NUM_CARDS_IN_DECK] = {
  {0,51,101,150,198,245,291,336,380,423,465,506,546,585,623,660,696,731,765,798,830,861,891,920,948,975,1001,1026,1050,1073,1095,1116,1136,1155,1173,1190,1206,1221,1235,1248,1260,1271,1281,1290,1298,1305,1311,1316,1320,1323,1325,1326}
};

int main(int argc,char **argv)
{
  int n;
  int curr_arg;
  bool bDebug;
  int index_algorithm;
  int loop_count;
  int cards[NUM_HOLE_CARDS_IN_HOLDEM_HAND];
  time_t start_sec;
  time_t stop_sec;
  int ix;

  if ((argc < 3) || (argc > 4)) {
    printf(usage);
    return 1;
  }

  bDebug = false;

  for (curr_arg = 1; curr_arg < argc; curr_arg++) {
    if (!strcmp(argv[curr_arg],"-debug"))
      bDebug = true;
    else
      break;
  }

  if (argc - curr_arg != 2) {
    printf(usage);
    return 1;
  }

  sscanf(argv[curr_arg],"%d",&index_algorithm);
  sscanf(argv[curr_arg+1],"%d",&loop_count);

  if (bDebug)
    loop_count = 1;

  if (!bDebug)
    time(&start_sec);

  for (n = 0; n < loop_count; n++) {
    for (cards[0] = 0; cards[0] < NUM_CARDS_IN_DECK - 1; cards[0]++) {
      for (cards[1] = cards[0] + 1; cards[1] < NUM_CARDS_IN_DECK; cards[1]++) {
        switch (index_algorithm) {
          case 0:
            ix = index_of_hand0(cards);
            break;
          case 1:
            ix = index_of_hand1(cards);
            break;
          case 2:
            ix = index_of_hand2(cards);
            break;
        }

        if (bDebug)
          printf("%d\n",ix);
      }
    }
  }

  if (!bDebug) {
    time(&stop_sec);

    printf("elapsed seconds: %d\n",stop_sec - start_sec);
  }

  return 0;
}

static int index_of_hand0(int *cards)
{
  int m;
  int n;
  int p;

  p = 0;

  for (m = 0; m < NUM_CARDS_IN_DECK - 1; m++) {
    for (n = m + 1; n < NUM_CARDS_IN_DECK; n++) {
      if (((m == cards[0]) && (n == cards[1])) ||
          ((m == cards[1]) && (n == cards[0]))) {
        return p;
      }

      p++;
    }
  }
}

static int index_of_hand1(int *cards)
{
  int n;
  int index;
  int num_other_cards;

  index = 0;
  num_other_cards = NUM_CARDS_IN_DECK - 1;

  for (n = 0; n < cards[0]; n++) {
    index += num_other_cards;
    num_other_cards--;
  }

  index += cards[1] - cards[0] - 1;

  return index;
}

static int index_of_hand2(int *cards)
{
  return offsets[0][cards[0]] + cards[1] - cards[0] - 1;
}