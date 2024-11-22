#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>

bool isInsideCircle(double x, double y, double cx, double cy, double r) {
    return (x - cx) * (x - cx) + (y - cy) * (y - cy) <= r * r;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    double x1 = 1, y1 = 1, r1 = 1;
    double x2 = 1.5, y2 = 2, r2 = std::sqrt(5)/2;
    double x3 = 2, y3 = 1.5, r3 = std::sqrt(5)/2;

    double minX_big = std::min(std::min(x1 - r1, x2 - r2), x3 - r3);
    double maxX_big = std::max(std::max(x1 + r1, x2 + r2), x3 + r3);
    double minY_big = std::min(std::min(y1 - r1, y2 - r2), y3 - r3);
    double maxY_big = std::max(std::max(y1 + r1, y2 + r2), y3 + r3);

    double minX_small = std::max(std::max(x1 - r1, x2 - r2), x3 - r3);
    double maxX_small = std::min(std::min(x1 + r1, x2 + r2), x3 + r3);
    double minY_small = std::max(std::max(y1 - r1, y2 - r2), y3 - r3);
    double maxY_small = std::min(std::min(y1 + r1, y2 + r2), y3 + r3);

    double current_area;
    std::srand(58);


    for (int n = 100; n < 100000; n += 500) {
        int points_inside = 0;

        // для маленького
        for (int i = 0; i < n; i++) {
            double x = minX_small + (maxX_small - minX_small) * ((double) std::rand() / RAND_MAX);
            double y = minY_small + (maxY_small - minY_small) * ((double) std::rand() / RAND_MAX);

            // проверяем на наличие в сегменте
            if (isInsideCircle(x, y, x1, y1, r1) && isInsideCircle(x, y, x2, y2, r2) &&
                isInsideCircle(x, y, x3, y3, r3)) {
                ++points_inside;
            }
        }

        double area_rectangle = (maxX_small - minX_small) * (maxY_small - minY_small);
        current_area = area_rectangle * ((double)points_inside / n);

        std::cout << current_area << " ";

        // для большого

        points_inside = 0;
        for (int i = 0; i < n; i++) {
            double x = minX_big + (maxX_big - minX_big) * ((double) std::rand() / RAND_MAX);
            double y = minY_big + (maxY_big - minY_big) * ((double) std::rand() / RAND_MAX);

            // проверяем на наличие в сегменте
            if (isInsideCircle(x, y, x1, y1, r1) && isInsideCircle(x, y, x2, y2, r2) &&
                isInsideCircle(x, y, x3, y3, r3)) {
                ++points_inside;
            }
        }

        area_rectangle = (maxX_big - minX_big) * (maxY_big - minY_big);
        current_area = area_rectangle * ((double)points_inside / n);

        std::cout << current_area << "\n";
    }

    return 0;
}
