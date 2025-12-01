/* 
Filename: window.cc 
Author: Josh, Taim and Linh
Date: 2024-11-28
Last Edited: 2024-06-28

Description:
This file contains the interface of the Xwindow class, which provides a simple interface
*/

module;
#include <X11/Xlib.h>
export module xwindow;
import <iostream>;
import <string>;
import <vector>;

export class Xwindow {
  Display *d;
  Window w;
  int s;
  GC gc;
  std::vector<unsigned long> colours;
  Colormap cmap;

 public:
    /*
    Purpose: Constructor for Xwindow class. Initializes and displays a window of given width and height.
    @param: width - width of the window (default 500)
             height - height of the window (default 500)
    returns: Xwindow object
    */
    Xwindow(int width=500, int height=500);  // Constructor; displays the window.

    /*
    Purpose: Destructor for Xwindow class. Destroys the window and frees resources.
    @param: None
    returns: None
    */
    ~Xwindow(); // Destructor; destroys the window.

    /*
    Purpose: Delete copy constructor to prevent copying of Xwindow objects.
    @param: other - reference to another Xwindow object
    returns: None
    */
    Xwindow(const Xwindow&) = delete;

    /*
    Purpose: Delete copy assignment operator to prevent copying of Xwindow objects.
    @param: other - reference to another Xwindow object
    returns: reference to this Xwindow object
    */
    Xwindow &operator=(const Xwindow&) = delete;

    // Available colours.
    /*
    Purpose: Enumeration of available colours for drawing.
    @param: = White - white colour
        Black - black colour
        Red - red colour
        Green - green colour
        Blue - blue colour
        Cyan - cyan colour
        Yellow - yellow colour
        Magenta - magenta colour
        Orange - orange colour
        Brown - brown colour
    returns: None
    */
    enum {White=0, Black, Red, Green, Blue, Cyan, Yellow, Magenta, Orange, Brown};

    /*
    Purpose: Adds a custom color using RGB values (0-255 range)
    @param: r - red component (0-255)
            g - green component (0-255)
            b - blue component (0-255)
    returns: color index that can be used in fillRectangle
    */
    int addColor(int r, int g, int b);

    /*
    Purpose: Adds a custom color using hex string (e.g., "#FF5733")
    @param: hexColor - hex color string (e.g., "#RRGGBB")
    returns: color index that can be used in fillRectangle
    */
    int addColor(const std::string& hexColor);


    // Draws a rectangle
    /*
    Purpose: Draws a filled rectangle at specified position with given dimensions and colour.
    @param: x - x-coordinate of the top-left corner of the rectangle
        y - y-coordinate of the top-left corner of the rectangle
        width - width of the rectangle
            height - height of the rectangle
        colour - colour of the rectangle (default Black)
    returns: None
    */
    void fillRectangle(int x, int y, int width, int height, int colour=Black);

    // Draws a string
    /*
    Purpose: Draws a string at specified position in the window.
    @param: x - x-coordinate of the position to draw the string
        y - y-coordinate of the position to draw the string
            msg - the string message to be drawn
    returns: None
    */
    void drawString(int x, int y, std::string msg, int colour);

    /*
    Purpose: Flushes the output buffer, ensuring all drawing commands are executed.
    @param: None
    returns: None
    */
    void flush();
};
