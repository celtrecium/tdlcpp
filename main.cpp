#include <tdlcpp>
#include <iostream>

int main() {
  TDL::Terminal::setAlternateScreen(true);
  TDL::Terminal::setCursor(false);

  TDL::Canvas canv = TDL::Canvas();
  
  canv.setCursorPosition(TDL::Point(20, 5));
  canv.print(TDL::Text("Hello world!",
                       TDL::Style(TDL::PointColor(TDL::Color::Red, TDL::Color::BrightWhite),
                                  TDL::Attributes::Bold | TDL::Attributes::Italic)));

  canv.display();

  std::cin.get();
  
  TDL::Terminal::setAlternateScreen(false);
  TDL::Terminal::setCursor(true);
  
  return 0;
}
