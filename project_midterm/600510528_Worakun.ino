#include "LiquidCrystal_I2C.h"
#include <Wire.h>

const int POT = 0;
const int ROW = 2; // row of LCD screen
const int COL = 4; // col of game in LCD screen
int val = 0;       // value of pot use to control paddle

LiquidCrystal_I2C lcd(0x3F, 16, 2);

const int WIDTH = COL * 5;  // number of pixel in width map
const int HEIGHT = ROW * 8; // number of pixel in height map

byte _map[HEIGHT][WIDTH]; // representative of map (game logic)
byte data[ROW][COL][8];   // represent real data in LCD
byte load[10][8];         // loading animation

// Paddle information
int bar_y = HEIGHT - 4; // position row's pixel in map of paddle
int bar_x = 7;          // position col's pixel in map of paddle
int h_bar = 1;          // size of paddle's height (unit of pixel)
int w_bar = 6;          // size of paddle's width (unit of pixel)

// ball information
int ball_y = HEIGHT / 2 - 1; // position row in map of ball
int ball_x = 9;              // position col in map of ball
int h_ball = 2;              // size height of ball (unit of pixel)
int w_ball = 2;              // size width of ball (unit of pixel)

float ball_dx = 1;    // speed of ball belong to x-axis (col)
float ball_dy = -1;   // speed of ball belong to y-axis (row)
float speed_up = 0.1; // epsilon value to increasing speed

// score
long score = 0;
long max_score = 0;
long up_score = long(2500);

// state game
bool game_over = false;

// serve state
int ss = 0;

// text information
char emp[] = "                ";

void setup() {
  lcd.init();
  start_game();
}

void loop() {
  if (!game_over) {
    update_map();
    setting_map();
    render();
  } else {
    reset_game();
  }
  delay(16.66666); // 60 FPS, (1000/60) millisec.
}

void light_effect() {
  for (int i = 0; i < 3; ++i) {
    lcd.backlight();
    delay(80);

    lcd.noBacklight();
    delay(80);
  }

  for (int i = 0; i < 2; ++i) {
    lcd.backlight();
    delay(200);

    lcd.noBacklight();
    delay(200);
  }

  delay(500);
  lcd.backlight();
}

// assign position pixel in (row, col)
void p(int row, int col, int val) {
  if (row < 0 || col < 0 || row >= HEIGHT || col >= WIDTH)
    return;
  _map[row][col] = val;
}

// function display text on the screen
void show_text(char *a) { lcd.print(a); }

void clear_screen() {
  lcd.setCursor(0, 0);
  show_text(emp);

  lcd.setCursor(0, 1);
  show_text(emp);

  lcd.setCursor(0, 0);
}

void start_game() {
  light_effect();

  // animation show each character
  lcd.setCursor(0, 0);
  char mes1[] = "   Welcome to...";
  int len_mes1 = sizeof(mes1) / sizeof(mes1[0]);
  for (int i = 0; i < len_mes1; ++i) {
    lcd.setCursor(i, 0);

    char print_char[5];
    sprintf(print_char, "%c", mes1[i]);
    show_text(print_char);

    if (i < len_mes1 - 4)
      delay(80);
    else
      delay(800);
  }
  show_text(mes1);

  // show normal text and traditional effect game
  delay(1000);
  lcd.setCursor(0, 1);
  char mes2[] = "The Pong Game!!!";
  show_text(mes2);

  delay(500);
  light_effect();

  // make the feeling of loading starter game
  delay(3000);
  clear_screen();

  // animation show loading start page
  delay(1000);
  lcd.setCursor(0, 0);
  lcd.print(">");
  delay(100);

  // show three dot animation
  for (int i = 0; i < 3; i++) {
    lcd.setCursor(i + 1, 0);

    char print_char[5];
    sprintf(print_char, "%c", mes1[16 - 3 + i]);
    show_text(print_char);

    delay(100);
  }

  // show interface for waiting user
  clear_screen();
  lcd.print(">> START GAME <<");
  lcd.setCursor(0, 1);
  lcd.print("<- MOVE (pot) ->");

  // Control to start game
  int old = map(analogRead(POT), 0, 1023, 0, COL * 5 - 1);
  while (true) {
    val = map(analogRead(POT), 0, 1023, 0, COL * 5 - 1);
    if (abs(old - val) >= 5)
      break;
  }

  // show loading game and credit
  clear_screen();
  int loading = 0;
  for (int i = 0; i < 6; ++i) {
    for (int j = 0; j < 8; ++j) {
      load[i][j] = loading;
    }
    loading |= 1 << (4 - i);
    lcd.createChar(i, load[i]);
  }
  for (int i = 0; i < 16; ++i) {
    lcd.setCursor(0, 0);

    if (i == 1) {
      lcd.print("   Loading...   ");
    } else if (i == 3) {
      show_text(emp);
    } else if (i == 4) {
      lcd.print("  presented by  ");
    } else if (i == 7) {
      show_text(emp);
    } else if (i == 9) {
      lcd.print("Chimeng Inc. CMU");
    } else if (i == 13) {
      show_text(emp);
    } else if (i == 15) {
      lcd.print("   game start   ");
    }

    for (int j = 0; j < 6; ++j) {
      lcd.setCursor(i, 1);
      lcd.write(j);
      delay(100);
    }

    if (i == 1) {
      delay(100);
    } else if (i == 8) {
      delay(200);
    } else if (i == 12) {
      delay(2000);
    } else if (i == 15) {
      delay(1500);
    }
  }

  clear_screen();
}

void update_map() {
  val = map(analogRead(POT), 0, 1023, 0, COL * 5 - 1);

  // clear tap of bar
  for (int i = 0; i < HEIGHT; ++i) {
    for (int j = 0; j < WIDTH; ++j) {
      p(i, j, 0);
    }
  }

  // bound limit of bar's x position
  bar_x = val;
  if (bar_x > WIDTH - w_bar - 1)
    bar_x = WIDTH - w_bar - 1;
  if (bar_x <= 0)
    bar_x = 1;

  // draw bar
  for (int i = bar_y; i < bar_y + h_bar; ++i) {
    for (int j = bar_x; j < bar_x + w_bar; ++j) {
      p(i, j, 1);
    }
  }

  // update position of ball
  ball_y = ball_y + ball_dy;
  ball_x = ball_x + ball_dx;

  // check collision of ball
  if (ball_y <= 0) {
    ball_dy = -ball_dy;
  } else if (bar_x <= ball_x + w_ball && ball_x <= bar_x + w_bar &&
             bar_y <= ball_y + h_ball && ball_y <= bar_y + h_bar) {
    // AABB collision detection
    ball_dy = -ball_dy;
    score += up_score;

    // increasing speed of ball
    ball_dy = -(abs(ball_dy) + speed_up);

    if (ball_dx < 0) {
      ball_dx -= speed_up;
    } else {
      ball_dx += speed_up;
    }

    // avoid double collsion
    ball_y = bar_y - 1;

  } else if (ball_y >= HEIGHT) {
    game_over = true;
  }

  if (ball_x <= 0 || ball_x + w_ball >= WIDTH) {
    ball_dx = -ball_dx;
  }

  // draw ball on map
  for (int i = ball_y; i < ball_y + h_ball; ++i) {
    for (int j = ball_x; j < ball_x + w_ball; ++j) {
      p(i, j, 1);
    }
  }

  // draw bound of game's map
  for (int i = 0; i < HEIGHT; ++i) {
    for (int j = 0; j < WIDTH; ++j) {
      if (i == 0 || j == 0 || j == WIDTH - 1) {
        p(i, j, 1);
      }
    }
  }

  // bounding score
  if (score > 99999) {
    score = long(99999);
  }
}

void setting_map() {
  for (int i = 0; i < HEIGHT; i += 8) {
    for (int j = 0; j < WIDTH; j += 5) {
      for (int r = i; r < i + 8; ++r) {
        byte _bit = 0;
        for (int c = j; c < j + 5; ++c)
          _bit = (_bit << 1) | _map[r][c];
        data[i / 8][j / 5][r - i] = _bit;
      }
    }
  }

  for (int i = 0; i < ROW; ++i) {
    for (int j = 0; j < COL; ++j) {
      lcd.createChar(i * COL + j, data[i][j]);
    }
  }
}

void render() {
  lcd.setCursor(5, 0);
  char mes[] = "Score:";
  show_text(mes);

  lcd.setCursor(11, 0);
  char point[10];
  sprintf(point, "%05ld", score);
  show_text(point);

  if (max_score != 0) {
    lcd.setCursor(5, 1);
    char max_stat[100];
    sprintf(max_stat, "  Max:%5ld", max_score);
    show_text(max_stat);
  }

  for (int i = 0; i < ROW; ++i) {
    lcd.setCursor(0, i);
    for (int j = 0; j < COL; ++j) {
      lcd.write(i * COL + j);
    }
  }
}

void reset_game() {
  lcd.setCursor(5, 1);
  char mes[] = "Game Over! ";
  show_text(mes);

  light_effect();

  delay(3000);
  int count_down = 3;
  while (count_down--) {
    lcd.setCursor(5, 1);
    char txt[16];
    sprintf(txt, "Restart...%d", count_down + 1);
    show_text(txt);
    delay(1000);
  }
  lcd.setCursor(5, 1);
  show_text(emp);

  game_over = false;

  ball_y = HEIGHT / 2;
  ball_x = 8;

  ball_dx = 1;
  ball_dy = -1;

  bar_x = 7;

  if (score > max_score) {
    max_score = score;
  }
  score = 0;

  update_map();
  setting_map();
  render();

  ss = val % 4;
  if (ss & 1)
    ball_dx = -ball_dx;
  if (ss >> 1)
    ball_dy = -ball_dy;

  int old = val;
  while (true) {
    val = map(analogRead(POT), 0, 1023, 0, COL * 5 - 1);
    if (abs(val - old) >= 3)
      break;
    delay(10);
  }
}
