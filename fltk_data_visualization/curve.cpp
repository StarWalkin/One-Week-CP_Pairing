#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/fl_draw.H>

const int numPoints = 50;

double data[numPoints] = {0.663209, 0.663209, 0.663209, 0.663383, 0.663383, 0.663563, 0.663563, 0.663563, 0.663563, 0.664568, 0.664568, 0.664568, 0.664568, 0.664568, 0.664568, 0.664568, 0.664568, 0.66516, 0.66516, 0.66516, 0.66516, 0.66516, 0.66516, 0.666164, 0.666164, 0.666164, 0.666164, 0.666164, 0.666164, 0.666164, 0.666164, 0.666164, 0.666164, 0.666164, 0.666164, 0.666577, 0.667582, 0.667582, 0.667582, 0.667582, 0.667582, 0.667582, 0.667582, 0.667582, 0.667582, 0.667582, 0.667582, 0.667582, 0.667582, 0.667582, };

class MyWindow : public Fl_Window {
public:
    MyWindow(int width, int height, const char* title) : Fl_Window(width, height, title) {
        this->label(title);  // 设置窗口标题
    }

    void draw() override {
        Fl_Window::draw();

        fl_color(FL_BLACK);
        fl_line_style(FL_SOLID);

        // 绘制 Y 轴
        fl_line(50, 50, 50, h() - 50);

        // 绘制 X 轴
        fl_line(50, h() - 50, w() - 50, h() - 50);

        fl_color(FL_RED);
        fl_line_style(FL_SOLID);

        double yScale = (h() - 100) / 0.06;  // 计算y轴的缩放比例
        double yShift = 50 - 0.64 * yScale;  // 计算y轴的偏移量
        for (int i = 0; i < numPoints - 1; ++i) {
            int x1 = 50 + i * (w() - 100) / (numPoints - 1);
            int y1 = h() - 50 - (data[i] * yScale + yShift);
            int x2 = 50 + (i + 1) * (w() - 100) / (numPoints - 1);
            int y2 = h() - 50 - (data[i + 1] * yScale + yShift);

            fl_line(x1, y1, x2, y2);
        }

        // 在 X 轴和 Y 轴上标注信息
        fl_color(FL_BLACK);
        fl_font(FL_HELVETICA, 12);
        fl_draw("Generation", w() / 2 - 40, h() - 20);  // 标注 X 轴
        fl_draw("Score", 15, h() / 2);                  // 标注 Y 轴

        // 标注 X 轴上限
        fl_draw("50", w() - 60, h() - 35);
        // 标注 Y 轴上限和下限
        fl_draw("0.64", 35, h() - 60);
        fl_draw("0.7", 35, 50);
    }
};

int main() {
    MyWindow window(600, 400, "Scores during evolution");
    window.show();
    return Fl::run();
}
