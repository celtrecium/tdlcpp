/*
 * This file is part of Text Drawing Library C++ Wrapper.
 *
 * Text Drawing Library C++ Wrapper is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * Text Drawing Library C++ Wrapper is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Text Drawing Library C++ Wrapper. If not, see
 * <https://www.gnu.org/licenses/>.
 */

#include <cstddef>
#include <string>
#include <stdexcept>

extern "C" {
  #include <tdl.h>
  #include <u8string.h>
}

namespace TDL {
  class Point {
    friend class Line;
    friend class Rectangle;
    friend class Canvas;
    
  private:
    tdl_point_t point;
    
  public:
    Point(int x, int y);

    void setX(int x);
    void setY(int y);

    int getX();
    int getY();
  };
  
  class Size {
    friend class Canvas;
    friend class Rectangle;
    
  private:
    tdl_size_t size;

  public:
    Size(size_t width, size_t height);

    void setWidth(size_t width);
    void setHeight(size_t height);

    size_t getWidth();
    size_t getHeight();

  };

  class Line {
    friend class Canvas;
    
  private:
    tdl_line_t line;
    Point A;
    Point B;

  public:
    Line(Point a, Point b);

    void setPointA(Point a);
    void setPointB(Point b);

    Point getPointA();
    Point getPointB();
  };

  class Rectangle {
    friend class Canvas;

  private:
    tdl_rectangle_t rectangle;
    Point point;
    Size size;

  public:
    Rectangle(Point pt, Size sz);

    void setPoint(Point pt);
    void setSize(Size sz);

    Point getPoint();
    Size getSize();
  };
  
  enum class Attributes {
    NullAttribute = TDL_NO_ATTRIBUTES,
    Bold          = TDL_BOLD,
    Italic        = TDL_ITALIC,
    Underline     = TDL_UNDERLINE,
    CrossedOut    = TDL_CROSSED_OUT,
    Dim           = TDL_DIM
  };

  Attributes operator | (Attributes a1, Attributes a2);

  enum class Color {
    Black   = TDL_BLACK,
    Red     = TDL_RED,
    Green   = TDL_GREEN,
    Yellow  = TDL_YELLOW,
    Blue    = TDL_BLUE,
    Magenta = TDL_MAGENTA,
    Cyan    = TDL_CYAN,
    White   = TDL_WHITE,
    Grey    = TDL_GREY,
    BrightRed     = TDL_BRIGHT_RED,
    BrightGreen   = TDL_BRIGHT_GREEN,
    BrightYellow  = TDL_BRIGHT_YELLOW,
    BrightBlue    = TDL_BRIGHT_BLUE,
    BrightMagenta = TDL_BRIGHT_MAGENTA,
    BrightCyan    = TDL_BRIGHT_CYAN,
    BrightWhite   = TDL_BRIGHT_WHITE,
    Default       = TDL_DEFAULT_COLOR 
  };
  
  class PointColor {
    friend class Style;
    
  private:
    tdl_point_color_t pointColor;
    Color background;
    Color foreground;

  public:
    PointColor(Color bg, Color fg);

    void setBackground(Color bg);
    void setForeground(Color fg);

    Color getBackground();
    Color getForeground();
  };
  
  class Style {
    friend class Text;
    
  private:
    tdl_style_t style;
    PointColor pointColor;
    Attributes attributes;

  public:
    Style(PointColor ptColor, Attributes attr);

    void setPointColor(PointColor ptColor);
    void setAttributes(Attributes attr);

    PointColor getPointColor();
    Attributes getAttributes();
  };
  
  class Text {
    friend class Canvas;

  private:
    tdl_text_t text;
    std::string cppstring;
    Style style;

  public:

    Text(std::string str, Style st);
    Text(const Text &txt);
    
    void setString(std::string str);
    void setStyle(Style st);

    template<typename T>
    T getString();
    Style getStyle();

    void destroy();
    ~Text();
  };

  class Canvas {
  private:
    tdl_canvas_t *canvas;
    Point cursor;
    Size size;
    
  public:
    Canvas();

    void setCursorPosition(Point point);
    Point getCursorPosition();
    Size getCanvasSize();
    void print(const Text &text);
    void display();
    void clear();
    void drawLine(Line line, const Text &text);
    void drawRectangle(Rectangle rectangle, const Text &text);
    void drawFilledRectangle(Rectangle rectangle, const Text &text);
    
    void destroy();
    ~Canvas();
  };

  namespace Terminal {
    void clear();
    void setAlternateScreen(bool isEnabled);
    void setCursor(bool isEnabled);
  }
}
