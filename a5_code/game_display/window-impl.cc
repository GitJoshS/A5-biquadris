/* 
Filename: window-impl.cc 
Author: Josh, Taim and Linh
Date: 2024-11-28
Last Edited: 2024-06-28

Description:
This file contains the implementation of the Xwindow class, which provides a simple interface
*/

module;
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <unistd.h>
module xwindow;
import <iostream>;
import <cstdlib>;
import <string>;
import <sstream>;
import <iomanip>;

using namespace std;

Xwindow::Xwindow(int width, int height) {

  d = XOpenDisplay(NULL);
  if (d == NULL) {
    cerr << "Cannot open display" << endl;
    exit(1);
  }
  s = DefaultScreen(d);
  w = XCreateSimpleWindow(d, RootWindow(d, s), 10, 10, width, height, 1,
                          BlackPixel(d, s), WhitePixel(d, s));
  XSelectInput(d, w, ExposureMask | KeyPressMask);
  XMapRaised(d, w);

  // Pixmap pix = XCreatePixmap(d,w,width,
  //       height,DefaultDepth(d,DefaultScreen(d)));
  gc = XCreateGC(d, w, 0,(XGCValues *)0);

  cmap = DefaultColormap(d, DefaultScreen(d));

  // Set up colours.
  XColor xcolour;
  char color_vals[10][10]={"white", "black", "red", "green", "blue", "cyan", "yellow", "magenta", "orange", "brown"};

  // colours.reserve(10);
  for(int i=0; i < 10; ++i) {
      XParseColor(d,cmap,color_vals[i],&xcolour);
      XAllocColor(d,cmap,&xcolour);
      colours.push_back(xcolour.pixel);
  }

  XSetForeground(d,gc,colours[White]);

  // Make window non-resizeable.
  XSizeHints hints;
  hints.flags = (USPosition | PSize | PMinSize | PMaxSize );
  hints.height = hints.base_height = hints.min_height = hints.max_height = height;
  hints.width = hints.base_width = hints.min_width = hints.max_width = width;
  XSetNormalHints(d, w, &hints);

}

Xwindow::~Xwindow() {
  // Free allocated colors
  for (unsigned long color : colours) {
    XFreeColors(d, cmap, &color, 1, 0);
  }
  XFreeGC(d, gc);
  XCloseDisplay(d);
}

int Xwindow::addColor(int r, int g, int b) {
  // X11 uses 16-bit color values (0-65535), so scale from 0-255
  XColor xcolour;
  xcolour.red = r * 257;    // 257 = 65535/255
  xcolour.green = g * 257;
  xcolour.blue = b * 257;
  xcolour.flags = DoRed | DoGreen | DoBlue;

  if (XAllocColor(d, cmap, &xcolour)) {
    colours.push_back(xcolour.pixel);
    return colours.size() - 1;
  } else {
    cerr << "Failed to allocate color RGB(" << r << "," << g << "," << b << ")" << endl;
    return Black; // Return black as fallback
  }
}


int Xwindow::addColor(const string& hexColor) {
  // Parse hex color string (e.g., "#FF5733" or "FF5733")
  string hex = hexColor;
  if (hex[0] == '#') {
    hex = hex.substr(1);
  }

  if (hex.length() != 6) {
    cerr << "Invalid hex color format: " << hexColor << endl;
    return Black;
  }

  // Convert hex to RGB
  int r, g, b;
  stringstream ss;
  ss << std::hex << hex.substr(0, 2);
  ss >> r;
  ss.clear();
  ss << std::hex << hex.substr(2, 2);
  ss >> g;
  ss.clear();
  ss << std::hex << hex.substr(4, 2);
  ss >> b;

  return addColor(r, g, b);
}

void Xwindow::fillRectangle(int x, int y, int width, int height, int colour) {
  if (colour >= 0 && colour < static_cast<int>(colours.size())) {
    XSetForeground(d, gc, colours[colour]);
    XFillRectangle(d, w, gc, x, y, width, height);
    XSetForeground(d, gc, colours[Black]);
  } else {
    cerr << "Invalid color index: " << colour << endl;
  }
}

void Xwindow::drawString(int x, int y, string msg, int colour) {
  if (colour >= 0 && colour < static_cast<int>(colours.size())) {
    XSetForeground(d, gc, colours[colour]);
    XDrawString(d, w, gc, x, y, msg.c_str(), msg.length());
    XSetForeground(d, gc, colours[Black]);
  } else {
    cerr << "Invalid color index: " << colour << endl;
  }
}


void Xwindow::flush() {
  XFlush(d);
}