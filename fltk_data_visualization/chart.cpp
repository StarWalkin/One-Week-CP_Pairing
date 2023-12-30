#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Draw.H>
#include <FL/fl_draw.H>
#include <string>

// 三组数据，每组数据有三个指标
double dataA[3] = {0.8, 0.885177, 0.488208};
double dataB[3] = {0.801887, 0.887265, 0.487059};
double dataC[3] = {0.812362, 0.814159, 0.495924};

// 柱状图颜色
Fl_Color colors[3] = {FL_RED, FL_GREEN, FL_BLUE};

// 图例
const char* legends[3] = {"Success Rate", "Net Success Rate", "Nice Matching Rate"};

class BarChart : public Fl_Widget {
public:
   BarChart(int x, int y, int w, int h, const char* label = 0)
           : Fl_Widget(x, y, w, h, label) {}

   void draw() override {
       // 画坐标轴
       fl_color(FL_BLACK);
       fl_line(x(), y() + h(), x() + w(), y() + h()); // x轴
       fl_line(x(), y(), x(), y() + h());             // y轴

       // 画y轴刻度
       fl_color(FL_BLACK);
       fl_line(x(), y() + h(), x() - 5, y() + h()); // 刻度0
       fl_line(x(), y(), x() - 5, y());             // 刻度1

       // 标注0和1
       fl_draw("0", x() - 20, y() + h() + 5);
       fl_draw("1", x() - 20, y() - 15);

       // 画刻度和柱形图
       for (int i = 0; i < 3; ++i) {
           for (int j = 0; j < 3; ++j) {
               // 刻度
               fl_color(FL_BLACK);
               fl_line(x() + 30 + i * 160 + j * 40, y() + h(), x() + 30 + i * 160 + j * 40, y() + h() + 5);

               // 柱形图
               fl_color(colors[j]);
               int barWidth = 30;
               int barHeight = static_cast<int>(h() * getData(i, j));
               fl_rectf(x() + 20 + i * 160 + j * 40, y() + h() - barHeight, barWidth, barHeight);
           }

           // 画 "exp" 标签
           fl_color(FL_BLACK);
           fl_draw(("exp" + std::to_string(i + 1)).c_str(), x() + 20 + i * 160 + 40, y() + h() + 15);
       }

       // 画图例
       for (int i = 0; i < 3; ++i) {
           fl_draw(legends[i], x() + w() - 120, y() + 20 + i * 20);
           fl_color(colors[i]);
           fl_rectf(x() + w() - 140, y() + 15 + i * 20, 10, 10);
       }
   }

private:
   double getData(int group, int index) {
       if (group == 0) return dataA[index];
       else if (group == 1) return dataB[index];
       else return dataC[index];
   }
};

int main() {
   Fl_Window window(800, 400, "different participants distribution");

   BarChart barChart(50, 50, 700, 300);

   window.end();
   window.show();

   return Fl::run();
}
