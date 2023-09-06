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

#include "tdlcpp.hpp"
#include <tdl/tdl_char.h>
#include <tdl/tdl_shapes.h>
#include <u8string.h>

// Class Point

TDL::Point::Point(int x, int y) : point(tdl_point(x, y)) {}

void TDL::Point::setX(int x) { this->point.x = x; }
void TDL::Point::setY(int y) { this->point.y = y; }

int TDL::Point::getX() { return this->point.x; }
int TDL::Point::getY() { return this->point.y; }

// Class Size

TDL::Size::Size(size_t width, size_t height) : size(tdl_size(width, height)) {}

void TDL::Size::setWidth(size_t width) { this->size.width = width; }
void TDL::Size::setHeight(size_t height) { this->size.height = height; }

size_t TDL::Size::getWidth() { return this->size.width; }
size_t TDL::Size::getHeight() { return this->size.height; }

// Class Line

TDL::Line::Line(Point a, Point b)
    : line(tdl_line(a.point, b.point)), A(a), B(b) {}

void TDL::Line::setPointA(Point a) {
  this->line.a = a.point;
  this->A = a;
}

void TDL::Line::setPointB(Point b) {
  this->line.b = b.point;
  this->B = b;
}

TDL::Point TDL::Line::getPointA() { return this->A; }
TDL::Point TDL::Line::getPointB() { return this->B; }

// Class Rectangle

TDL::Rectangle::Rectangle(Point pt, Size sz)
    : rectangle(tdl_rectangle(pt.point, sz.size)), point(pt), size(sz) {}

void TDL::Rectangle::setPoint(Point pt) {
  this->rectangle.point = pt.point;
  this->point = pt;
}
void TDL::Rectangle::setSize(Size sz) {
  this->rectangle.size = sz.size;
  this->size = sz;
}

TDL::Point TDL::Rectangle::getPoint() { return this->point; }
TDL::Size TDL::Rectangle::getSize() { return this->size; }
  
// Class PointColor

TDL::PointColor::PointColor(Color bg, Color fg)
  : pointColor(tdl_point_color(static_cast<tdl_color_t>(bg), static_cast<tdl_color_t>(fg))) {}

void TDL::PointColor::setBackground(Color bg) {
  this->pointColor.bg = static_cast<tdl_color_t>(bg);
  this->background = bg;
}

void TDL::PointColor::setForeground(Color fg) {
  this->pointColor.fg = static_cast<tdl_color_t>(fg);
  this->foreground = fg;
}

TDL::Color TDL::PointColor::getBackground() { return this->background; }
TDL::Color TDL::PointColor::getForeground() { return this->foreground; }

// Class Style

TDL::Style::Style(PointColor ptColor, Attributes attr)
    : style(tdl_style(ptColor.pointColor, static_cast<tdl_attributes_t>(attr))),
      pointColor(ptColor), attributes(attr) {}

void TDL::Style::setPointColor(PointColor ptColor) {
  this->style.color = ptColor.pointColor;
  this->pointColor = ptColor;
}

void TDL::Style::setAttributes(Attributes attr) {
  this->style.attributes = static_cast<tdl_attributes_t>(attr);
  this->attributes = attr;
}

TDL::PointColor TDL::Style::getPointColor() { return pointColor; }

TDL::Attributes TDL::operator | (TDL::Attributes a1, TDL::Attributes a2) {
  return static_cast<TDL::Attributes>(static_cast<tdl_attributes_t>(a1) | static_cast<tdl_attributes_t>(a2));
}

TDL::Attributes TDL::Style::getAttributes() { return this->attributes; }

// Class Text

TDL::Text::Text(std::string str, Style st)
    : text(tdl_text(u8string(const_cast<cstr>(str.c_str())), st.style)),
      cppstring(str), style(st) {}


TDL::Text::Text(const Text &txt)
    : text(tdl_text(u8string(const_cast<cstr>(txt.cppstring.c_str())),
                    txt.text.style)),
      cppstring(txt.cppstring), style(txt.style) {}

void TDL::Text::setString(std::string str) {
  this->cppstring = str;

  if (!u8string_set(&this->text.string, const_cast<cstr>(str.c_str())))
    throw std::invalid_argument("Failed to set a new string value");
}

void TDL::Text::setStyle(Style st) {
  this->text.style = st.style;
  this->style = st;
}

template<>
std::string TDL::Text::getString<std::string>() { return this->cppstring; }

template<>
u8string_t TDL::Text::getString<u8string_t>() { return this->text.string; }
TDL::Style TDL::Text::getStyle() { return this->style; }

void TDL::Text::destroy() {
  if (!tdl_text_free (this->text))
    throw std::runtime_error("An error occurred while releasing memory of string");
}

TDL::Text::~Text() { destroy(); }

// Class Canvas

TDL::Canvas::Canvas(): canvas(tdl_canvas()), cursor(0, 0), size(0, 0) {
  this->size = Size(this->canvas->size.width, this->canvas->size.height);
}

void TDL::Canvas::setCursorPosition(Point point) {
  this->cursor = point;
  if(!tdl_set_cursor_pos(this->canvas, point.point))
    throw std::runtime_error("Failed to set the canvas cursor position");
}

TDL::Point TDL::Canvas::getCursorPosition() { return this->cursor; }
TDL::Size TDL::Canvas::getCanvasSize() { return this->size; }

void TDL::Canvas::print(const Text &text) {
  if (text.text.string.string == NULL)
    throw std::invalid_argument("The text is NULL");
  
  if(!tdl_print(this->canvas, text.text))
    throw std::runtime_error("Failed to print the text on the canvas");

  this->cursor = TDL::Point(this->canvas->cursor.x, this->canvas->cursor.y);
}

void TDL::Canvas::display() {
  if(!tdl_display(this->canvas))
    throw std::runtime_error("Failed to display the canvas on the terminal");
}

void TDL::Canvas::clear() {
  if(!tdl_clear(this->canvas))
    throw std::runtime_error("Failed to clear the canvas");
}

void TDL::Canvas::drawLine(Line line, const Text &text) {
  if(!tdl_draw_line(this->canvas, tdl_char(text.text.string.string[0], text.text.style), line.line))
    throw std::runtime_error("Failed to draw the line on the canvas");
}

void TDL::Canvas::drawRectangle(Rectangle rectangle, const Text &text) {
  if(!tdl_draw_rectangle(this->canvas, tdl_char(text.text.string.string[0], text.text.style), rectangle.rectangle))
    throw std::runtime_error("Failed to draw the rectangle on the canvas");
}

void TDL::Canvas::drawFilledRectangle(Rectangle rectangle, const Text &text) {
  if(!tdl_draw_filled_rectangle(this->canvas,
      tdl_char(text.text.string.string[0], text.text.style), rectangle.rectangle))
    throw std::runtime_error("Failed to draw the rectangle on the canvas");
}

void TDL::Canvas::destroy() {
  if(!tdl_destroy_canvas(this->canvas))
    throw std::runtime_error("Failed to destroy the canvas");
}

TDL::Canvas::~Canvas() { destroy(); }

// Namespace Terminal

void TDL::Terminal::clear() { tdl_terminal_clear(); }
void TDL::Terminal::setAlternateScreen(bool isEnabled) { tdl_terminal_set_alternate_screen(isEnabled); }
void TDL::Terminal::setCursor(bool isEnabled) { tdl_terminal_set_cursor(isEnabled); }
