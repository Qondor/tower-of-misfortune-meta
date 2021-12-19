#include <Gamebuino-Meta.h>
#include <utility>
#include <cstdlib>

// ver. beta 1.3

// CONSTANTS //
float current_brick_position = 10;
float brick_speed = 0.2;
int value = 0;
int b = 160;
byte mode = 0;
int brick_x = 70;
int score = 0;
int brick_y = 44;
int past_brick_x[16] = {75};
int past_brick_position[16] = {10};
int past_brick_y[16] = {44};
int past_brick_pos = 0;
int random_red[16] = {55};
int random_green[16] = {55};
int random_blue[16] = {255};
char player_name[13];
String GOtext = "";
String coded_score = "";
String temp_score = "";
bool done = false;
String hs_names[6] = {"CEZARY - ", "BARTEK - ", "JAKUB% - ", "MATI99 - ", "GRUNIO - ", ""};
int hs_points[6] = {300, 257, 256, 128, 100, 0};

void setup() {
  gb.begin();
  gb.pickRandomSeed();
}

void past_bricks() {
  for (int i = 0; i < past_brick_pos; i++) {
    gb.display.fillRect(past_brick_x[i], past_brick_position[i], 5, past_brick_y[i]);
  }
}

void loop() {
  while (!gb.update());
  gb.display.clear();
  gb.lights.clear();

  switch (mode) {
    // TITLE SCREEN //
    case 0:
      gb.display.clear();
      gb.display.setCursor(gb.display.width() - 10, 0);
      for (int a = 0; a <= gb.display.width(); a = a + 7) {
        gb.display.setColor(b / 2, b, b / 2);
        b = b + 20;
        gb.display.fillRect(a, 0, 5, 64);
      }
      
      gb.display.setColor(255, 255, 255); // Height -64 width-80

      gb.display.setCursor(gb.display.width() - 78, gb.display.height() - 60);
      gb.display.print("TOWER OF MISFORTUNE");
      
      gb.display.setCursor(gb.display.width() - 54, gb.display.height() - 45);
      gb.display.print("A: Start!");

      gb.display.setCursor(gb.display.width() - 54, gb.display.height() - 38);
      gb.display.print("B: Help");

      gb.display.setCursor(gb.display.width() - 74, gb.display.height() - 31);
      gb.display.print("SELECT: Highscore");

      gb.display.setCursor(gb.display.width() - 78, gb.display.height() - 15);
      gb.display.print("(C) Vellichor Games");

      gb.display.setCursor(gb.display.width() - 72, gb.display.height() - 8);
      gb.display.print("Cezary Was | 2022");

      gb.waitForUpdate();
      if (gb.buttons.released(BUTTON_A)) {
        mode = 4;
      }

      if (gb.buttons.released(BUTTON_B)) {
        mode = 1;
      }

      if (gb.buttons.released(BUTTON_MENU)) {
        mode = 3;
      }
        break;

      // STORY //
      case 1:
        gb.display.clear();
        gb.display.setColor(255, 255, 255);
        gb.display.setCursor(30, 5);
        gb.display.print("STORY");
        gb.display.setCursor(5, 10);
        gb.display.print("Welcome to the    Tower of Misfortune.An ancient art of   stacking blocks. The legend says, that's whoever stacks 100 of them shall be     granted a wish. Anything they desire..."); // Okay, thats look like shit. Needs to be repaired.
        // gb.display.print("Press B to continue");
        //gb.waitForUpdate();
        if (gb.buttons.released(BUTTON_B)) {
          mode = 2;
        }
        break;

      // HELP //
      case 2:
        gb.display.clear();
        gb.display.setCursor(30, 5);
        gb.display.print("HELP");
        gb.display.setCursor(5, 10);
        gb.display.print("Try to match the  previous block and  press A - the better the match, the more points you'll get. Every pixel off will make your block    smaller.");
        gb.display.setCursor(5, 58);
        gb.display.print("Press B to start!");
        //gb.waitForUpdate();
        if (gb.buttons.pressed(BUTTON_B)) {
          mode = 4;
        }
        break;

      // HIGHSCORE //
      case 3:
        gb.display.clear();
        gb.display.setCursor(25, 0);
        gb.display.print("HIGHSCORE");
        gb.display.setCursor(5, 8);
        gb.display.print(hs_names[0]); // CEZARY - 300");
        gb.display.print(hs_points[0]);
        gb.display.setCursor(5, 14);
        gb.display.print(hs_names[1]); // BARTEK - 257");
        gb.display.print(hs_points[1]);
        gb.display.setCursor(5, 20);
        gb.display.print(hs_names[2]); // JAKUB% - 256");
        gb.display.print(hs_points[2]);
        gb.display.setCursor(5, 26);
        gb.display.print(hs_names[3]); // MATI99 - 128");
        gb.display.print(hs_points[3]);
        gb.display.setCursor(5, 32);
        gb.display.print(hs_names[4]); // GRUNIO - 100");
        gb.display.print(hs_points[4]);
        gb.display.setCursor(0, 41);

        if (coded_score != "") {
          gb.display.print("Enter the code on   Vellichor-Void.com/ /ToM to upload your  result: ");
        } else {
          gb.display.print("Play the game first!");
        }
        gb.display.print(coded_score);
        if (gb.buttons.pressed(BUTTON_B)) {
          mode = 4;
        }
        break;

      // GAMEPLAY //
      case 4:
        // Score //
        gb.display.setCursor(30, 5);
        gb.display.print("SCORE: ");
        gb.display.print(score);

        // Game Over text //
        gb.display.setCursor(gb.display.width() - 75, gb.display.height() - 8);
        gb.display.print(GOtext);

        // Brick Y movement //
        if (current_brick_position + brick_y > gb.display.height()) {
          brick_speed *= -1;
          gb.lights.fill(BLUE);
        } else if (current_brick_position < 1) {
          brick_speed *= -1;
          gb.lights.fill(RED);
        }

        // Guiding lines //
        gb.display.setColor(248, 250, 255);
        gb.display.fillRect(0, 10, 80, 1);
        gb.display.fillRect(0, 53, 80, 1);

        current_brick_position = current_brick_position + brick_speed;

        // Starting block //
        for (int i = 0; i <= past_brick_pos; i++) {
          gb.display.setColor(random_red[i], random_green[i], random_blue[i]);
          gb.display.fillRect(past_brick_x[i], past_brick_position[i], 5, past_brick_y[i]);
        }

        // Playable block //
        gb.display.setColor(99, 97, 0);
        gb.display.fillRect(brick_x, current_brick_position, 5, brick_y);

        if (gb.buttons.released(BUTTON_A)) {
          gb.sound.playOK();
          if (current_brick_position == past_brick_position[past_brick_pos]) {
            score += brick_y;
            past_brick_y[past_brick_pos + 1] = brick_y;
            past_brick_x[past_brick_pos + 1] = brick_x;
            past_brick_position[past_brick_pos + 1] = current_brick_position;
            brick_x -= 5;
            past_brick_pos++;
            gb.lights.fill(GREEN);
            // new_line();
          } else if ((current_brick_position + brick_y) < past_brick_position[past_brick_pos]) {
            brick_speed = 0;
            gb.lights.fill(RED);
          } else if (current_brick_position > (past_brick_position[past_brick_pos] + past_brick_y[past_brick_pos])) {
            brick_speed = 0;
            gb.lights.fill(YELLOW);
          } else if (current_brick_position < past_brick_position[past_brick_pos]) {
            gb.lights.fill(GREEN);
            score += (current_brick_position + brick_y) - past_brick_position[past_brick_pos];
            brick_y = (current_brick_position + brick_y) - past_brick_position[past_brick_pos];
            past_brick_y[past_brick_pos + 1] = brick_y;
            past_brick_x[past_brick_pos + 1] = brick_x;
            past_brick_position[past_brick_pos + 1] = past_brick_position[past_brick_pos];
            brick_x -= 5;
            past_brick_pos++;
            // new_line();
          } else if (current_brick_position > past_brick_position[past_brick_pos]) {
            score += (past_brick_position[past_brick_pos] + past_brick_y[past_brick_pos]) - current_brick_position + 1;
            brick_y = (past_brick_position[past_brick_pos] + past_brick_y[past_brick_pos]) - current_brick_position + 1;
            past_brick_y[past_brick_pos + 1] = brick_y;
            past_brick_x[past_brick_pos + 1] = brick_x;
            past_brick_position[past_brick_pos + 1] = current_brick_position;
            brick_x -= 5;
            past_brick_pos++;
            gb.lights.fill(GREEN);
          }
          
          if (brick_speed == 0) {
            GOtext = "SELECT: Highscore!";

            // If score is high enough to be put in the Highscore //
            if (score >= (hs_points[4])) {
              // Ask for a name //
              gb.gui.keyboard("Enter your name!", player_name);
              srand(time(0));
              temp_score = String(score);
              coded_score = "";
              coded_score = (temp_score[0] - '0') * 2 + 10;
              coded_score += (temp_score[1] - '0') * 2 + 10;
              coded_score += (temp_score[2] - '0') * 2 + 10;
              coded_score += (temp_score[0] - '0') + (temp_score[1] - '0') + (temp_score[2] - '0') + 50;
              coded_score += random(5,9);
              done = false;
              for (int which_place = 4; done == false; which_place--) {
                         if (score >= hs_points[which_place]){
                            hs_names[which_place + 1] = hs_names[which_place];
                            hs_points[which_place + 1] = hs_points[which_place];
                            hs_names[which_place] = String(player_name) += String(" - ");
                            hs_points[which_place] = score;
                                                                                                                   
                            if (which_place == 0 && score >= hs_points[0]){
                              done = true;
                              }
                         }else if (score < hs_points[which_place]){
                            done = true;
                         }
              }
            }
          }
          brick_speed *= 1.4;
          random_red[past_brick_pos] = random(50, 200);
          random_green[past_brick_pos] = random(50, 200);
          random_blue[past_brick_pos] = random(50, 200);
        }
        if (gb.buttons.pressed(BUTTON_MENU)) {
          mode = 3;
          brick_x = 70;
          score = 0;
          brick_y = 44;
          brick_speed = 0.2;
          current_brick_position = 10;
          past_brick_pos = 0;
          for (int x = 1; x >= 16; x++) {
            past_brick_x[x] = 0;
            past_brick_position[x] = 0;
            past_brick_y[x] = 0;
          }
        }
        break;
      }
  }