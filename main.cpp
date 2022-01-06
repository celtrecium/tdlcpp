#include <tdlcpp>
#include <iostream>

int main() {
  TDL::Canvas canv = TDL::Canvas();
  
  canv.setCursorPosition(TDL::Point(20, 5));
  canv.print(TDL::Text("Hello world!",
                       TDL::Style(TDL::PointColor(TDL::Color::Red, TDL::Color::BrightWhite), TDL::Attributes::Bold)));

  canv.display();

  std::cout << "\033[m\n\n"; // This is a temporary measure
  
  return 0;
}
