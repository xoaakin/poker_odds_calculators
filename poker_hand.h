enum Suit {
  CLUBS,
  DIAMONDS,
  HEARTS,
  SPADES,
  NUM_SUITS
};

enum Rank {
  TWO,
  THREE,
  FOUR,
  FIVE,
  SIX,
  SEVEN,
  EIGHT,
  NINE,
  TEN,
  JACK,
  QUEEN,
  KING,
  ACE,
  NUM_CARDS_IN_SUIT
};

enum HandType {
  HIGH_CARD,
  ONE_PAIR,
  TWO_PAIRS,
  THREE_OF_A_KIND,
  STRAIGHT,
  FLUSH,
  FULL_HOUSE,
  FOUR_OF_A_KIND,
  STRAIGHT_FLUSH,
  ROYAL_FLUSH,
  NUM_HAND_TYPES
};

enum FlopType {
  DRY,
  WET,
  NUM_FLOP_TYPES
};

#define NUM_CARDS_IN_DECK (NUM_SUITS * NUM_CARDS_IN_SUIT)

#define suit_of(card) (card / NUM_CARDS_IN_SUIT)
#define rank_of(card) (card % NUM_CARDS_IN_SUIT)

#ifdef MAIN_MODULE
char suit_chars[] = "cdhs";
char rank_chars[] = "23456789TJQKA";

char *plain_hand_types[] = {
  "high card",
  "one pair",
  "two pair",
  "three of a kind",
  "straight",
  "flush",
  "full house",
  "four of a kind",
  "straight flush",
  "royal flush"
};
int plain_hand_type_lens[NUM_HAND_TYPES];
#else
extern char suit_chars[];
extern char rank_chars[];
extern char *plain_hand_types[];
extern int plain_hand_type_lens[];
#endif

#define NUM_CARDS_IN_HAND 5

#define POKER_3_2_PERMUTATIONS          3
#define POKER_4_2_PERMUTATIONS          6
#define POKER_6_5_PERMUTATIONS          6
#define POKER_5_3_PERMUTATIONS         10
#define POKER_7_5_PERMUTATIONS         21
#define POKER_33_2_PERMUTATIONS       528
#define POKER_37_2_PERMUTATIONS       666
#define POKER_41_2_PERMUTATIONS       820
#define POKER_43_2_PERMUTATIONS       903
#define POKER_45_2_PERMUTATIONS       990
#define POKER_46_2_PERMUTATIONS      1035
#define POKER_47_2_PERMUTATIONS      1081
#define POKER_52_2_PERMUTATIONS      1326
#define POKER_52_3_PERMUTATIONS     22100
#define POKER_45_4_PERMUTATIONS    148995
#define POKER_52_4_PERMUTATIONS    270725
#define POKER_36_5_PERMUTATIONS    376992
#define POKER_40_5_PERMUTATIONS    658008
#define POKER_44_5_PERMUTATIONS   1086008
#define POKER_46_5_PERMUTATIONS   1370754
#define POKER_48_5_PERMUTATIONS   1712304
#define POKER_52_5_PERMUTATIONS   2598960
#define POKER_52_7_PERMUTATIONS 133784560

#define NUM_HOLE_CARDS_IN_HOLDEM_HAND 2
#define NUM_HOLE_CARDS_IN_OMAHA_HAND 4
#define NUM_CARDS_IN_FLOP 3
#define NUM_CARDS_AFTER_FLOP 2
#define NUM_COMMUNITY_CARDS (NUM_CARDS_IN_FLOP + NUM_CARDS_AFTER_FLOP)
#define NUM_CARDS_IN_HOLDEM_POOL (NUM_HOLE_CARDS_IN_HOLDEM_HAND + NUM_CARDS_IN_FLOP + NUM_CARDS_AFTER_FLOP)
#define NUM_CARDS_IN_OMAHA_POOL (NUM_HOLE_CARDS_IN_OMAHA_HAND + NUM_CARDS_IN_FLOP + NUM_CARDS_AFTER_FLOP)
#define NUM_CARDS_AT_TURN (NUM_HOLE_CARDS_IN_HOLDEM_HAND + NUM_CARDS_IN_FLOP + 1)
#define NUM_HOLE_CARDS_IN_OMAHA_HAND 4
#define NUM_CARDS_AFTER_DEAL (NUM_CARDS_IN_FLOP + NUM_CARDS_AFTER_FLOP)
#define NUM_SELECTED_HOLE_CARDS_IN_OMAHA_HAND 2
#define NUM_SELECTED_COMMUNITY_CARDS_IN_OMAHA_HAND 3

#define MAX_STREET_MARKERS 6

#ifdef MAIN_MODULE
char *hand_type_abbrevs[] = {
  "hc",
  "1p",
  "2p",
  "3k",
  "st",
  "fl",
  "fh",
  "4k",
  "sf",
  "rf"
};
char *flop_type_abbrevs[] = {
  "dry",
  "wet"
};
int num_evaluations;
int num_unique_evaluations;
int num_comparisons;
int num_holdem_best_poker_hand_comparisons;
#else
extern char *hand_type_abbrevs[];
extern char *flop_type_abbrevs[];
extern int num_evaluations;
extern int num_unique_evaluations;
extern int num_comparisons;
extern int num_holdem_best_poker_hand_comparisons;
#endif

int get_rank_index(char rank_char,int *rank_index_ptr);
int get_suit_index(char suit_char,int *suit_index_ptr);

typedef struct {
  int cards[NUM_CARDS_IN_HAND];
} hand;

typedef struct {
  int cards[NUM_CARDS_AT_TURN];
} turn_hand;

typedef struct {
  int cards[NUM_CARDS_IN_HOLDEM_POOL];
} holdem_hand;

typedef struct {
  int cards[NUM_CARDS_IN_FLOP];
} flop;

struct hand_and_type {
  char cards[NUM_CARDS_IN_HAND];
  char hand_type;
  int hand_ix;
  int quick_ix;
};

struct outcomes {
  int wins;
  int wins_hand_counts[NUM_HAND_TYPES];
  int losses;
  int losses_hand_counts[NUM_HAND_TYPES];
  int ties;
  int ties_hand_counts[NUM_HAND_TYPES];
};

class PokerHand {
  public:

  // default constructor
  PokerHand();
  // copy constructor
  PokerHand(const PokerHand&);
  // assignment operator
  PokerHand& operator=(const PokerHand&);
  // destructor
  ~PokerHand();

  PokerHand(int card1,int card2,int card3,int card4, int card5);
  void NewCards(int card1,int card2,int card3,int card4, int card5);

  int GetRank(int card_ix);
  void Sort();
  HandType Evaluate();
  HandType EvaluateLow();
  HandType EvaluateQuick(struct hand_and_type *hands_and_types);
  int GetHandIx();
  int GetQuickIx();
  void UnEvaluate();
  bool Evaluated();
  bool RoyalFlush();
  bool StraightFlush();
  bool FourOfAKind();
  bool FullHouse();
  bool Flush();
  bool Straight();
  bool ThreeOfAKind();
  bool TwoPair();
  bool OnePair();

  char *GetHand();
  HandType GetHandType();

  int Compare(PokerHand& compare_hand,int in_holdem_best_poker_hand);
  int CompareLow(PokerHand& compare_hand,int in_holdem_best_poker_hand);
  int CompareQuick(PokerHand& compare_hand,int in_holdem_best_poker_hand,struct hand_and_type *hands_and_types);

  void print(ostream& out) const;
  void Verbose();
  void Terse();
  void Plain();
  void Fancy();
  int *GetCards();

  void SetDebugLevel(int debug_level);

  private:

  hand _card;
  hand _suit;
  hand _rank;
  hand _num_cards_with_same_rank;
  hand _order;

  bool _have_cards;
  bool _hand_sorted;
  bool _hand_evaluated;
  bool _verbose;
  bool _plain;

  HandType _hand_type;
  int _hand_ix;
  int _quick_ix;

  int _debug_level;
};

ostream& operator<<(ostream& out,const PokerHand& hand);

class HoldemPokerHand {
  public:

  // default constructor
  HoldemPokerHand();
  // copy constructor
  HoldemPokerHand(const HoldemPokerHand&);
  // assignment operator
  HoldemPokerHand& operator=(const HoldemPokerHand&);
  // destructor
  ~HoldemPokerHand();

  HoldemPokerHand(int card1,int card2,int card3,int card4,int card5,int card6,int card7);
  void NewCards(int card1,int card2,int card3,int card4,int card5,int card6,int card7);

  PokerHand& BestPokerHand();
  PokerHand& BestPokerHandQuick(struct hand_and_type *hands_and_types);

  void print(ostream& out) const;

  void SetDebugLevel(int debug_level);

  private:

  holdem_hand _card;
  PokerHand _best_poker_hand;

  int _have_cards;

  int _debug_level;
};

ostream& operator<<(ostream& out,const HoldemPokerHand& board_hand);

class HoldemTurnHand {
  public:

  // default constructor
  HoldemTurnHand();
  // copy constructor
  HoldemTurnHand(const HoldemTurnHand&);
  // assignment operator
  HoldemTurnHand& operator=(const HoldemTurnHand&);
  // destructor
  ~HoldemTurnHand();

  HoldemTurnHand(int card1,int card2,int card3,int card4,int card5,int card6);
  void NewCards(int card1,int card2,int card3,int card4,int card5,int card6);

  PokerHand& BestPokerHand();

  void print(ostream& out) const;

  void SetDebugLevel(int debug_level);

  private:

  turn_hand _card;
  PokerHand _best_poker_hand;

  int _have_cards;

  int _debug_level;
};

ostream& operator<<(ostream& out,const HoldemTurnHand& board_hand);

class Flop {
  public:

  // default constructor
  Flop();
  // copy constructor
  Flop(const Flop&);
  // assignment operator
  Flop& operator=(const Flop&);
  // destructor
  ~Flop();

  Flop(int card1,int card2,int card3);
  void NewCards(int card1,int card2,int card3);

  int GetCard(int card_ix);
  int GetRank(int card_ix);
  void Sort();
  FlopType Evaluate();
  int Evaluated();
  int Flush();
  int Straight();
  int PairOrBetter();

  FlopType GetFlopType();

  void print(ostream& out) const;
  void Verbose();
  void Terse();
  void Plain();
  void Fancy();

  void SetDebugLevel(int debug_level);

  private:

  flop _card;
  flop _suit;
  flop _rank;
  flop _num_cards_with_same_rank;
  flop _order;

  bool _have_cards;
  bool _flop_sorted;
  bool _flop_evaluated;
  bool _verbose;
  bool _plain;

  FlopType _flop_type;

  int _debug_level;
};

ostream& operator<<(ostream& out,const Flop& hand);

class OmahaPokerHand {
  public:

  // default constructor
  OmahaPokerHand();
  // copy constructor
  OmahaPokerHand(const OmahaPokerHand&);
  // assignment operator
  OmahaPokerHand& operator=(const OmahaPokerHand&);
  // destructor
  ~OmahaPokerHand();

  OmahaPokerHand(int card1,int card2,int card3,int card4,int card5,int card6,int card7,int card8,int card9);
  void NewCards(int card1,int card2,int card3,int card4,int card5,int card6,int card7,int card8,int card9);

  PokerHand& BestPokerHand();
  PokerHand& BestLowPokerHand();

  void print(ostream& out) const;

  void SetDebugLevel(int debug_level);

  private:

  hand _card;
  PokerHand _best_poker_hand;

  int _have_cards;

  int _debug_level;
};

ostream& operator<<(ostream& out,const OmahaPokerHand& board_hand);

void get_permutation_instance_two(
  int set_size,
  int *m,int *n,
  int instance_ix
);

void get_permutation_instance_three(
  int set_size,
  int *m,int *n,int *o,
  int instance_ix
);

void get_permutation_instance_four(
  int set_size,
  int *m,int *n,int *o,int *p,
  int instance_ix
);

void get_permutation_instance_five(
  int set_size,
  int *m,int *n,int *o,int *p,int *q,
  int instance_ix
);

void get_permutation_instance_seven(
  int set_size,
  int *m,int *n,int *o,int *p,int *q,int *r,int *s,
  int instance_ix
);

int card_value_from_card_string(char *card_string,int *card_value);
int card_string_from_card_value(int card_value,char *card_string);

HandType get_hand_type(char *hand_type_str);

bool four_to_a_flush(int *cards);

void init_plain_hand_type_lens();

int read_hands_and_types(
  char *hands_and_types_filename,
  struct hand_and_type **hands_and_types
);

int compare_key(const void *elem1,const void *elem2);

int find_hand(
  hand *in_hand,
  struct hand_and_type *hands_and_types,
  bool bBsearch,
  struct hand_and_type **out_hand
);
