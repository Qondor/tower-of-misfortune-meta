#include <Gamebuino-Meta.h>

// Constants

void setup() {
  gb.begin();
    
    int b = 160;
    gb.display.setCursor(gb.display.width() - 10, 0);
    for(int a = 0; a <= gb.display.width(); a = a + 7){
      gb.display.setColor(b/2, b, b/2);
      b = b + 20;
      gb.display.fillRect(a, 0, 5, 64);
    }

    gb.display.setColor(255, 255, 255);

    // print the screen height

    // gb.display.print("Screen height:");
    // gb.display.println(gb.display.height()); 64

    // print the screen width
    // gb.display.print("Screen width:");
    // gb.display.println(gb.display.width()); 80
  
    gb.display.setCursor(gb.display.width() - 78, gb.display.height() - 40);
    gb.display.print("TOWER OF MISFORTUNE");

    gb.display.setCursor(gb.display.width() - 54, gb.display.height() - 20);
    gb.display.print("A: help");

    gb.display.setCursor(gb.display.width() - 54, gb.display.height() - 10);
    gb.display.print("B: start!");

    
    if (gb.buttons.pressed(BUTTON_A)) {
    gb.display.setColor(0, 0, 0);
    gb.display.fillRect(0, 0, gb.display.width(), gb.display.height());
    }
    // gb.display.fillRect(0, 0, gb.display.width(), gb.display.height());

    // gb.display.print("Press B to start!");
}

void loop() {
  while(!gb.update());

  // INPUTS //



  // LOGIC //


  // DRAW //

}
