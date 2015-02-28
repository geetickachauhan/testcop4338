#define INITIAL_CAPACITY 100

typedef struct {
	char* name;
	int id, vote1, vote2, vote3;
	float PPG, APG, RPG, SPG, MPG;
} Player;

typedef struct {
	int filled; //how filled it is
	int capacity; //total available slots
	Player *players; //array of Player
} List;

void initialize(List *list);

void append(List *list, Player t);

Player get(List *list, int index);

void set(List *list, int index, Player t);

void grow_list(List *list);

void free_list(List *list);

void B(List * list, char * choice);

void C(List * list);

void D(List * list);
