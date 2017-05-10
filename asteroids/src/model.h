/* Asteroids Model */
struct point {
    float x,y;
};
typedef struct point coordinate_t;
typedef struct point vector_t;

/* Some initial struct types*/
struct ship {
	  float heading;
    coordinate_t p;
    vector_t     v;
		int		 shield;
	  int shipScore;
};

/* initial structs for building linked lists */
typedef struct rock {
	  float heading;
    coordinate_t p;
	  vector_t     v;
	  float ttl;
    struct rock *next;
} rock_t;

typedef struct missile {
	  float heading;
    coordinate_t p;
	  vector_t     v;
	  float ttl;
    struct missile *next;
} missile_t;

void physics(void);
void fire();
void rotateLeft();
void rotateRight();
void shipFwd();
void shipBack();
void initialise_missiles();
void initialise_asteroids();
rock_t *allocate_rock_node(void);
missile_t *allocate_missile_node(void);
void free_rock_node(rock_t *n);
void free_missile_node(missile_t *n);
