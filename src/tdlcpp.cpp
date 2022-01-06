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
#include <tdl/tdl_style.h>
#include <tdl/tdl_terminal.h>

// Class Point

void TDL::Point::setX(int x) { this->point.x = x; }
void TDL::Point::setY(int y) { this->point.y = y; }

int TDL::Point::getX() { return this->point.x; }
int TDL::Point::getY() { return this->point.y; }

// Class Size

void TDL::Size::setWidth(size_t width) { this->size.width = width; }
void TDL::Size::setHeight(size_t height) { this->size.height = height; }

size_t TDL::Size::getWidth() { return this->size.width; }
size_t TDL::Size::getHeight() { return this->size.height; }

// Class Line

void TDL::Line::setPointA(Point a) { this->line.a = a.point; }
void TDL::Line::setPointB(Point b) { this->line.b = b.point; }

TDL::Point TDL::Line::getPointA() { return Point(this->line.a.x, this->line.a.y); }
TDL::Point TDL::Line::getPointB() { return Point(this->line.b.x, this->line.b.y); }

// Class Rectangle

void TDL::Rectangle::setPoint(Point point) { this->rectangle.point = point.point; }
void TDL::Rectangle::setSize(Size size) { this->rectangle.size = size.size; }

TDL::Point TDL::Rectangle::getPoint() { return Point(this->rectangle.point.x, this->rectangle.point.y); }
TDL::Size TDL::Rectangle::getSize() { return Size(this->rectangle.size.width, this->rectangle.size.height); }
  
// Class PointColor

void TDL::PointColor::setBackground(Color bg) { this->pointColor.bg = static_cast<tdl_color_t>(bg); }
void TDL::PointColor::setForeground(Color fg) { this->pointColor.fg = static_cast<tdl_color_t>(fg); }

TDL::Color TDL::PointColor::getBackground() { return static_cast<Color>(this->pointColor.bg); }
TDL::Color TDL::PointColor::getForeground() { return static_cast<Color>(this->pointColor.fg); }

// Class Style

void TDL::Style::setPointColor(PointColor pointColor) { this->style.color = pointColor.pointColor; }
void TDL::Style::setAttributes(Attributes attributes) {
  this->style.attributes = static_cast<tdl_attributes_t>(attributes);
}

TDL::PointColor TDL::Style::getPointColor() {
  return PointColor(static_cast<Color>(this->style.color.bg), static_cast<Color>(this->style.color.fg));
}


TDL::Attributes TDL::operator | (TDL::Attributes a1, TDL::Attributes a2) {
  return static_cast<TDL::Attributes>(static_cast<tdl_attributes_t>(a1) | static_cast<tdl_attributes_t>(a2));
}


TDL::Attributes TDL::Style::getAttributes() { return static_cast<Attributes>(this->style.attributes); }

// Class Text

bool TDL::Text::setString(std::string str) {
  this->cppstring = str;
  
  return u8string_set(&this->text.string, (char*)str.c_str());
}
void TDL::Text::setStyle(Style style) { this->text.style = style.style; };

template<>
std::string TDL::Text::getString<std::string>() {
  return this->cppstring;
}

template<>
u8string_t TDL::Text::getString<u8string_t>() {
  return this->text.string;
}

TDL::Style TDL::Text::getStyle() {
  return Style(PointColor(static_cast<Color>(this->text.style.color.bg), static_cast<Color>(this->text.style.color.fg)),
               static_cast<Attributes>(this->text.style.attributes));
}

bool TDL::Text::destroy() { return tdl_text_free (this->text); }
TDL::Text::~Text() { destroy(); }

// Class Canvas

bool TDL::Canvas::setCursorPosition(Point point) { return tdl_set_cursor_pos(this->canvas, point.point); }
bool TDL::Canvas::print(Text text) { return tdl_print(this->canvas, text.text); }
bool TDL::Canvas::display() { return tdl_display(this->canvas); }
bool TDL::Canvas::clear() { return tdl_clear(this->canvas); }
bool TDL::Canvas::drawLine(Line line, Text text) { return tdl_draw_line(this->canvas, text.text, line.line); }

bool TDL::Canvas::drawRectangle(Rectangle rectangle, Text text) {
  return tdl_draw_rectangle(this->canvas, text.text, rectangle.rectangle);
}

bool TDL::Canvas::drawFilledRectangle(Rectangle rectangle, Text text) {
  return tdl_draw_filled_rectangle(this->canvas, text.text, rectangle.rectangle);
}

bool TDL::Canvas::destroy() { return tdl_destroy_canvas(this->canvas); }
TDL::Canvas::~Canvas() { destroy(); }

// Namespace Terminal

void TDL::Terminal::clear() { tdl_terminal_clear(); }
void TDL::Terminal::setAlternateScreen(bool isEnabled) { tdl_terminal_set_alternate_screen(isEnabled); }
void TDL::Terminal::setCursor(bool isEnabled) { tdl_terminal_set_cursor(isEnabled); }
