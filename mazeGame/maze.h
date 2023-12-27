//Define constants
const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 700;

const int STEP = 5;

const int SELECTOR_POSITION_X = 75;
const int SELECTOR_POSITION_Y = 88;
const int SELECTOR_STEP = 294;

#define MAX_COLS 50
#define MAX_ROWS 50
#define GREEN al_map_rgb(36, 255, 4)
#define BLACK al_map_rgb(0, 0, 0)
#define WHITE al_map_rgb(255, 255, 255)
#define PINK al_map_rgb(255, 0, 255)

/************DEFINE STRUCTURES****************/
//This structure is used for drawing and moving bitmaps
struct Image{
    ALLEGRO_BITMAP *bitmap;
    int x;
    int y;
};

//This structure is used for tracking the score, time and lives in the game
struct Data{
    Image tracker;
    char name[20];
    int time;
    int score;
    int bestTime;
    int highScore;
    int numberOfLives;
};

/*********************FUNCTION PROTOTYPES*********************/
//1. Functions that initializes Allegro
int initializeAllegro();
int checkSetup(ALLEGRO_DISPLAY *display, ALLEGRO_EVENT_QUEUE *event_queue, ALLEGRO_SAMPLE *sample,
               ALLEGRO_FONT *font, ALLEGRO_FONT *credits, ALLEGRO_TIMER *timer, ALLEGRO_SAMPLE *death,
               ALLEGRO_SAMPLE *objectPickup, ALLEGRO_SAMPLE *gameEnd, ALLEGRO_SAMPLE *win);
void registerEventQueue(ALLEGRO_EVENT_QUEUE *event_queue, ALLEGRO_DISPLAY *display, ALLEGRO_TIMER *timer);

//2. Functions that are used for title and start pages
int loadTitlePage(ALLEGRO_DISPLAY *display, Image &title);
void drawTitlePage(Image &title);
int loadCredits(ALLEGRO_FONT *font, ALLEGRO_EVENT_QUEUE *event_queue, Image title);
int loadInstructions(ALLEGRO_FONT *font, ALLEGRO_EVENT_QUEUE *event_queue);
int selectCharacter(ALLEGRO_DISPLAY *display, ALLEGRO_EVENT_QUEUE *event_queue, char name[20]);

//3. Functions that are used in making the maze map
int readMaze(int mazeMap[][50], int &row, int &column, int &entranceRow, int &entranceColumn, int &exitRow,
             int &exitColumn);
int generateMaze(ALLEGRO_DISPLAY *display, int mazeMap[][50], int &row, int &column);

//4. Functions that are used in making the game data tracker
int drawScoreTracker(Image &tracker, ALLEGRO_DISPLAY *display);
void displayTimeAndScore(ALLEGRO_FONT *font, Data &game);
int readHighScore(Data &game);
int saveHighScore(Data &game);

//5. Functions that makes the character function properly
int loadCharacter(ALLEGRO_DISPLAY *display, Image &character, char name[20]);
void drawCharacter(Image character);
int moveCharacter(ALLEGRO_DISPLAY *display, ALLEGRO_EVENT_QUEUE *event_queue, ALLEGRO_FONT *font,
                  ALLEGRO_TIMER *timer, ALLEGRO_SAMPLE *death, ALLEGRO_SAMPLE *object, Image &character,
                  Data &game, int mazeMap[][50], int &row, int &column, int &entranceRow, int &entranceColumn,
                  int &exitRow, int &exitColumn, ALLEGRO_SAMPLE *sample);
int checkCollision(ALLEGRO_SAMPLE *object, ALLEGRO_SAMPLE *death, Image &character, Data &game, int mazeMap[][50],
                   int &row, int &column, int &entranceRow, int &entranceColumn, int movement);

//6. Functions that checks whether the user has won or lost
int checkWin(ALLEGRO_DISPLAY *display, ALLEGRO_TIMER *timer, Image character, int mazeMap[][50], int row,
             int column, int exitRow, int exitColumn, ALLEGRO_SAMPLE *sample);
int winInput(ALLEGRO_DISPLAY *display, ALLEGRO_EVENT_QUEUE *event_queue);
int loseInput(ALLEGRO_DISPLAY *display, ALLEGRO_EVENT_QUEUE *event_queue);

//7. Other functions for various uses
int continueToGame(ALLEGRO_DISPLAY *display, ALLEGRO_EVENT_QUEUE *event_queue, ALLEGRO_FONT *font, Image title);
void reDraw(ALLEGRO_DISPLAY *display, ALLEGRO_FONT *font, int mazeMap[][50], int &row, int &column,
            Image &character, Data &game);
int moveMonster(int mazeMap[][50], int &row, int &column);
int replay(ALLEGRO_DISPLAY *display, ALLEGRO_EVENT_QUEUE *event_queue, ALLEGRO_FONT *font,
           ALLEGRO_TIMER *timer, ALLEGRO_SAMPLE *sample, ALLEGRO_SAMPLE *death, ALLEGRO_SAMPLE *gameEnd,
           ALLEGRO_SAMPLE *object, ALLEGRO_SAMPLE *win, Image &character, Data &game, int mazeMap[][50],
           int &row, int &column, int &entranceRow, int &entranceColumn, int &exitRow, int &exitColumn,
           int &a, int &b, int &c);
int resetCharacter(ALLEGRO_SAMPLE *death, Image &character, int row, int column, int entranceRow, int entranceColumn);


