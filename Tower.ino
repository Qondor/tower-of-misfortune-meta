#include <Gamebuino-Meta.h>

// ver. 1.0 - 19.02.2022 //

// CONSTANTS //
float current_brick_position = 10;
float brick_speed = 0.2;
int value = 0;
int stripe_color = 160;
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
bool is_sorting_done = false;
bool keyboard_reset = true;
String hs_names[6] = {"CEZARY99PL", "BARTEK69", "JAKUB%", "-=MATI99=-", "GRUNIO", ""};
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
      for (int stripe_width = 0; stripe_width <= gb.display.width(); stripe_width++) {
        gb.display.setColor(stripe_color / 2, stripe_color, stripe_color / 2);
        stripe_color = stripe_color + 20;
        gb.display.fillRect(stripe_width, 0, 5, 64);
      }
      
      gb.display.setColor(255, 255, 255);

      gb.display.setCursor(gb.display.width() - 78, gb.display.height() - 60);
      gb.display.print("TOWER OF MISFORTUNE");
      
      gb.display.setCursor(gb.display.width() - 54, gb.display.height() - 45);
      gb.display.print("A: Start!");

      gb.display.setCursor(gb.display.width() - 54, gb.display.height() - 38);
      gb.display.print("B: Story/Help");

      gb.display.setCursor(gb.display.width() - 74, gb.display.height() - 31);
      gb.display.print("SELECT: Highscore");

      gb.display.setCursor(gb.display.width() - 75, gb.display.height() - 15);
      gb.display.print("(C) Vellichor Void");

      gb.display.setCursor(gb.display.width() - 80, gb.display.height() - 8);
      gb.display.print("Cezary Was|2020-2022");

      gb.waitForUpdate();
      if (gb.buttons.released(BUTTON_A)) {
        mode = 4; // GAMEPLAY // 
      }

      if (gb.buttons.released(BUTTON_B)) {
        mode = 1; // STORY //
      }

      if (gb.buttons.released(BUTTON_MENU)) {
        mode = 3; // HIGHSCORE //
      }
        break;

      // STORY //
      case 1:
        gb.display.clear();
        gb.display.setColor(255, 255, 255);
        gb.display.setCursor(30, 5);
        gb.display.print("STORY");
        gb.display.setCursor(5, 10);
        gb.display.print("Welcome to the    Tower of Misfortune.An ancient art of   stacking blocks. The legend says, that's whoever stacks 100 of them shall be     granted a wish. Anything they desire...");
        if (gb.buttons.released(BUTTON_B)) {
          mode = 2;
        }
        break;

      // HELP //
      case 2:
        gb.display.clear();
        gb.display.setCursor(30, 0);
        gb.display.print("HELP");
        gb.display.setCursor(5, 5);
        gb.display.print("Try to match the  previous block and  press A - closer thematch, the more     points you'll get.  Every pixel off will make your block    smaller.");
        gb.display.setCursor(0, 55);
        gb.display.print(" B-Start | A-Credits");
        if (gb.buttons.pressed(BUTTON_B)) {
          mode = 4;
        }
        if (gb.buttons.pressed(BUTTON_A)) {
          mode = 5;
        }
        break;

      // HIGHSCORE //
      case 3:
        gb.display.clear();
        gb.display.setCursor(25, 0);
        gb.display.print("HIGHSCORE");
        gb.display.setCursor(9, 8);
        gb.display.print(hs_names[0]); // CEZARY - 300
        gb.display.setCursor(49, 8);
        gb.display.print(" - ");
        gb.display.print(hs_points[0]);
        gb.display.setCursor(9, 14);
        gb.display.print(hs_names[1]); // BARTEK - 257
        gb.display.setCursor(49, 14);
        gb.display.print(" - ");
        gb.display.print(hs_points[1]);
        gb.display.setCursor(9, 20);
        gb.display.print(hs_names[2]); // JAKUB% - 256
        gb.display.setCursor(49, 20);
        gb.display.print(" - ");
        gb.display.print(hs_points[2]);
        gb.display.setCursor(9, 26);
        gb.display.print(hs_names[3]); // MATI99 - 128
        gb.display.setCursor(49, 26);
        gb.display.print(" - ");
        gb.display.print(hs_points[3]);
        gb.display.setCursor(9, 32);
        gb.display.print(hs_names[4]); // GRUNIO - 100
        gb.display.setCursor(49, 32);
        gb.display.print(" - ");
        gb.display.print(hs_points[4]);
        gb.display.setCursor(0, 41);

        keyboard_reset = true;

        if (coded_score != "") {
          gb.display.print("Enter the code on   Vellichor-Void.com/ /ToM to upload your  result: ");
        } else {
          gb.display.print("Press B to play the game!");
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
        GOtext = "";

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

            // If score is high enough to be put in the Highscore and keyboard wasn't called before... //
            if ((score >= (hs_points[4])) && keyboard_reset == true) {
              // ...ask for a name //
              gb.gui.keyboard("Enter your name!", player_name, 10);
              temp_score = String(score);
              // Encrypting the score. Nothing special. Do not reverse engineer. //
              coded_score = "";
              coded_score = (temp_score[0] - '0') * 2 + 10;
              coded_score += (temp_score[1] - '0') * 2 + 10;
              coded_score += (temp_score[2] - '0') * 2 + 10;
              coded_score += (temp_score[0] - '0') + (temp_score[1] - '0') + (temp_score[2] - '0') + 50;
              coded_score += random(6,10);
              is_sorting_done = false;
              for (int which_place = 4; is_sorting_done == false; which_place--) {
                         if (score >= hs_points[which_place]){
                            hs_names[which_place + 1] = hs_names[which_place];
                            hs_points[which_place + 1] = hs_points[which_place];
                            hs_names[which_place] = String(player_name);
                            hs_points[which_place] = score;
                                                                                                                   
                            if (which_place == 0 && score >= hs_points[0]){
                              is_sorting_done = true;
                              keyboard_reset = false;
                              }
                         }else if (score < hs_points[which_place]){
                            is_sorting_done = true;
                            keyboard_reset = false;
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

        // CREDITS & SPECIAL THANKS //
        case 5:
        gb.display.clear();
        gb.display.setCursor(30, 0);
        gb.display.print("CREDITS");
        gb.display.setCursor(5, 6);
        gb.display.print("Cezary Was - idea, code, screenplay");
        gb.display.setCursor(15, 20);
        gb.display.print("SPECIAL THANKS");
        gb.display.setCursor(5, 26);
        gb.display.print("Pawel \"KrzaQ\"      Zakrzewski - help   and mentoring (he   didn't approve any  part of this code)");
        gb.display.setCursor(15, 59);
        gb.display.print("B - Continue");
        if (gb.buttons.released(BUTTON_B)) {
          mode = 6;
        }
        break;

        // SPECIAL THANKS //
        case 6:
        gb.display.setCursor(15, 0);
        gb.display.print("SPECIAL THANKS");
        gb.display.setCursor(5, 6);
        gb.display.print("Bartek Lewandowski - testing and        encouragement");
        gb.display.setCursor(5, 30);
        gb.display.print("And all of my      friends, that made  my dream possible.");
        gb.display.setCursor(5, 51);
        gb.display.print("(C) Vellichor Void");
        gb.display.setCursor(22, 57);
        gb.display.print("2020-2022");
        if (gb.buttons.released(BUTTON_B)) {
          mode = 4;
        }
        break;
      }
  }
