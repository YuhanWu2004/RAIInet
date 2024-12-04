#ifndef __WINDOW_H__
#define __WINDOW_H__

#include <X11/Xlib.h>
#include <iostream>
#include <string>

class Xwindow {
  Display *d;
  Window w;
  int s, width, height;
  GC gc;

  // Array size adjusted to match the number of colors
  static constexpr int NumColors = 10; // Total number of colors in the enum
  unsigned long colours[NumColors];    // Array to store allocated colors

 public:
  Xwindow(int width = 500, int height = 500);  // Constructor; displays the window
  ~Xwindow();                                  // Destructor; destroys the window

  // Available colors as an enumeration for clarity and usability
  enum Color { 
      White = 0, Black, Red, Green, Blue, 
      Yellow, Magenta, Cyan, Orange, Purple 
  };

  int getWidth() const;
  int getHeight() const;

  // Draws a rectangle with a specified color
  void fillRectangle(int x, int y, int width, int height, int colour = Black);

  // Draws a string at the specified position
  void drawString(int x, int y, std::string msg);
};

#endif
