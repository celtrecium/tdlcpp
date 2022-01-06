#include <tdlcpp>
#include <iostream>
#include <chrono>
#include <thread>

int main() {
  TDL::Terminal::setAlternateScreen(true);
  TDL::Terminal::setCursor(false);

  // Initialize canvas and text
  TDL::Canvas canv = TDL::Canvas();
  TDL::Text hello = TDL::Text("Hello world!", TDL::Style(TDL::PointColor(TDL::Color::Red, TDL::Color::BrightWhite),
                                                         TDL::Attributes::Bold | TDL::Attributes::Italic));

  // Initialize point in the middle of the terminal width
  TDL::Point point =
    TDL::Point(static_cast<int>(((canv.getCanvasSize().getWidth()) - hello.getString<std::string>().length()) / 2), 0);

  for (size_t i = 0; i < canv.getCanvasSize().getHeight() - 1; ++i) {
    canv.clear();

    point.setY(static_cast<int>(i));
    canv.setCursorPosition(point);
    canv.print(hello);

    canv.display();

    std::this_thread::sleep_for(std::chrono::microseconds(50000));
  }

  
  TDL::Terminal::setAlternateScreen(false);
  TDL::Terminal::setCursor(true);
  
  return 0;
}
