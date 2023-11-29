#include <iostream>
#include <cmath>
#include <vector>

class Point {
public:
    double x, y;
    int q; // Координатная четверть: 0 - не определена, 1 - I, 2 - II, 3 - III, 4 - IV

    // Конструктор по умолчанию
    Point() : x(NULL), y(NULL), q(NULL) {}

    // Конструктор с параметрами
    Point(double x, double y) : x(x), y(y) {
        setQuadrant();
    }

private:
    // Функция для установки координатной четверти точки
    void setQuadrant() {
        if (x > 0 && y > 0) {
            q = 1;
        }
        else if (x < 0 && y > 0) {
            q = 2;
        }
        else if (x < 0 && y < 0) {
            q = 3;
        }
        else if (x > 0 && y < 0) {
            q = 4;
        }
        else {
            q = 0; // На оси или в начале координат
        }
    }
};

class Triangle {
public:
    Point A, B, C;
    double sideAB, sideBC, sideCA; // Стороны треугольника
    double perimeter = 0, area = 0; //Периметр и площадь фигуры
    Point intersectionPointM{ -1, -1 }; // Точки пересечения  
    Point intersectionPointN{ -1, -1 };

    Point intersectionPointM1{ -1, -1 }; // дополнительные Точки пересечения  
    Point intersectionPointN1{ -1, -1 };
    std::vector<Point> vertices;

    // Конструктор для инициализации вершин и вычисления сторон
    Triangle(Point A, Point B, Point C) : A(A), B(B), C(C) {
        calculateSides();

        if (isTriangle()) {
            
            if ((A.q == 2 && B.q == 2 && C.q == 2) ||
                (A.q == 3 && B.q == 3 && C.q == 3) || 
                (A.q == 4 && B.q == 4 && C.q == 4)) {
     
                std::cout << "Периметр фигуры = 0\nПлощадь фигуры = 0";
                return;
            }

            if ((A.q == 1 || A.q == 0) && (B.q == 1 || B.q == 0) && (C.q == 1 || C.q == 0)) {
                perimeter = calculatePerimeter(std::vector<Point>{A, B, C});
                area = calculateArea(std::vector<Point>{A, B, C});
                std::cout << "Периметр фигуры = " << perimeter << "\nПлощадь фигуры = " << area;
                return;
            }
            else {
                findIntersectionPoints(A, B);
                if (intersectionPointM.x == -1 || intersectionPointN.x == -1) {
                    findIntersectionPoints(B, C);
                    if (intersectionPointM.x == -1 || intersectionPointN.x == -1) {
                        findIntersectionPoints(C, A);
                    }
                }
                 //Добавляем точку (0, 0), если существует две точки пересечения
                if (intersectionPointM.x != -1 && intersectionPointN.x != -1) {
                    vertices.push_back(Point(0, 0));
                    vertices.push_back(intersectionPointN);
                    if (A.q == 1 || B.q == 1 || C.q == 1) {
                        if (A.q == 1) {
                            vertices.push_back(A);
                        }
                        if (B.q == 1) {
                            vertices.push_back(B);
                        }
                        if (C.q == 1) {
                            vertices.push_back(C);
                        }
                    }
                    vertices.push_back(intersectionPointM);
                }
                else {
                    if ((intersectionPointM.x != -1) && intersectionPointM1.x != -1) {
                        if ((intersectionPointM.x < 0 && intersectionPointM1.x > 0) ||
                            (intersectionPointM.x > 0 && intersectionPointM1.x < 0)) {
                            vertices.push_back(Point(0, 0));
                        }
                        else {
                            if (intersectionPointM.x < intersectionPointM1.x) {
                                vertices.push_back(intersectionPointM);
                            }
                            else {
                                vertices.push_back(intersectionPointM1);
                            }
                        }
                        if (A.q == 1 || B.q == 1 || C.q == 1) {
                            if (A.q == 1) {
                                vertices.push_back(A);
                            }
                            if (B.q == 1) {
                                vertices.push_back(B);
                            }
                            if (C.q == 1) {
                                vertices.push_back(C);
                            }
                        }
                        if (intersectionPointM.x > intersectionPointM1.x) {
                            vertices.push_back(intersectionPointM);
                        }
                        else {
                            vertices.push_back(intersectionPointM1);
                        }
                    }
                    else {
                        if ((intersectionPointN.x != -1) && intersectionPointN1.x != -1) {
                            if ((intersectionPointN.y < 0 && intersectionPointN1.y > 0) ||
                                (intersectionPointN.y > 0 && intersectionPointN1.y < 0)) {
                                vertices.push_back(Point(0, 0));
                            }
                            else {
                                if (intersectionPointN.y < intersectionPointN1.y) {
                                    vertices.push_back(intersectionPointN);
                                }
                                else {
                                    vertices.push_back(intersectionPointN1);
                                }
                            }
                            if (intersectionPointN.y > intersectionPointN1.y) {
                                vertices.push_back(intersectionPointN);
                            }
                            else {
                                vertices.push_back(intersectionPointN1);
                            }
                            if (A.q == 1 || B.q == 1 || C.q == 1) {
                                if (A.q == 1) {
                                    vertices.push_back(A);
                                }
                                if (B.q == 1) {
                                    vertices.push_back(B);
                                }
                                if (C.q == 1) {
                                    vertices.push_back(C);
                                }
                            }
                        }
                        else {
                            if (intersectionPointM.x != -1 && intersectionPointN.x == -1 && 
                                intersectionPointM1.x == -1 && intersectionPointN1.x == -1) {
                                vertices.push_back(Point(0, 0));
                                if (A.q == 1 || B.q == 1 || C.q == 1) {
                                    if (A.q == 1) {
                                        vertices.push_back(A);
                                    }
                                    if (B.q == 1) {
                                        vertices.push_back(B);
                                    }
                                    if (C.q == 1) {
                                        vertices.push_back(C);
                                    }
                                }
                                vertices.push_back(intersectionPointM);
                            }
                            else {
                                if (intersectionPointM.x == -1 && intersectionPointN.x != -1 &&
                                    intersectionPointM1.x == -1 && intersectionPointN1.x == -1) {
                                    vertices.push_back(Point(0, 0));
                                    vertices.push_back(intersectionPointN);
                                    if (A.q == 1 || B.q == 1 || C.q == 1) {
                                        if (A.q == 1) {
                                            vertices.push_back(A);
                                        }
                                        if (B.q == 1) {
                                            vertices.push_back(B);
                                        }
                                        if (C.q == 1) {
                                            vertices.push_back(C);
                                        }
                                    }
                                }
                            }
                        }
                    }
                }

                perimeter = calculatePerimeter(vertices);
                area = calculateArea(vertices);
                std::cout << "Периметр фигуры = " << perimeter << "\nПлощадь фигуры = " << area;

            }
        }
        else {
            std::cerr << "Треугольник не существует." << std::endl;
        }
    }

    // Функция для проверки существования треугольника
    bool isTriangle() const {
        return ((A.x != B.x || A.y != B.y) && (B.x != C.x || B.y != C.y) && (C.x != A.x || C.y != A.y) && 
            (sideAB + sideBC > sideCA) && (sideBC + sideCA > sideAB) && (sideCA + sideAB > sideBC));
    }

    // Функция для вычисления сторон треугольника
    void calculateSides() {
        sideAB = distance(A, B);
        sideBC = distance(B, C);
        sideCA = distance(C, A);
    }

    bool isInsideTriangle(const Point& P, const Point& A, const Point& B) {
        // Сортируем координаты вершин по возрастанию
        double minX = std::min({ A.x, B.x});
        double minY = std::min({ A.y, B.y});
        double maxX = std::max({ A.x, B.x});
        double maxY = std::max({ A.y, B.y});

        // Проверяем, лежит ли точка внутри треугольника
        return P.x >= minX && P.x <= maxX && P.y >= minY && P.y <= maxY && (P.x > 0 || P.y > 0);
    }

    void findIntersectionPoints(Point A, Point B) {
         // Точки пересечения с осями координат
        double x_oy, y_oy;
        double x_ox, y_ox;

        // Прямая с осями
        if (B.x - A.x != 0) {
            x_oy = 0;
            y_oy = A.y + (B.y - A.y) / (B.x - A.x) * (-A.x);

            x_ox = B.x + (A.x - B.x) / (A.y - B.y) * (-B.y);
            y_ox = 0;

            /*else {
                x_oy = A.x;
                y_oy = 0;
                if (isInsideTriangle(Point(x_oy, y_oy), A, B)) {
                    intersectionPointN = Point(x_oy, y_oy);
                }
            }*/

            // Проверка, лежит ли точка внутри треугольника
            bool ox, oy;
            ox = isInsideTriangle(Point(x_ox, y_ox), A, B);
            oy = isInsideTriangle(Point(x_oy, y_oy), A, B);
            if (ox || oy) {
                if (intersectionPointM.x == -1) {
                    intersectionPointM = ox ? Point(x_ox, y_ox) : Point(-1, -1);
                }
                if (intersectionPointN.x == -1) {
                    intersectionPointN = oy ? Point(x_oy, y_oy) : Point(-1, -1);
                }
                if (ox && (intersectionPointM.x != x_ox || intersectionPointM.y != y_ox)) {
                    intersectionPointM1 = ox ? Point(x_ox, y_ox) : Point(-1, -1);
                }
                if (oy && (intersectionPointN.x != x_oy || intersectionPointN.y != y_oy)) {
                    intersectionPointN1 = oy ? Point(x_oy, y_oy) : Point(-1, -1);
                }
            }
        }
        else {
            x_ox = A.x;
            y_ox = 0;
            if (isInsideTriangle(Point(x_ox, y_ox), A, B)) {
                (intersectionPointM.x == -1) ?
                    intersectionPointM = Point(x_ox, y_ox) : 
                    intersectionPointM1 = Point(x_ox, y_ox);
            }
        }
    }

private:
    // Функция для вычисления расстояния между двумя точками
    double distance(Point p1, Point p2) const {
        return sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2));
    }
    
    // Функция для вычисления периметра фигуры
    double calculatePerimeter(const std::vector<Point>& vertices) {
        double perimeter = 0;

        // Проверяем количество вершин
        if (vertices.size() < 3) {
            std::cerr << "Фигура должна иметь как минимум три вершины." << std::endl;
            return 0;
        }

        for (size_t i = 0; i < vertices.size() - 1; ++i) {
            perimeter += distance(vertices[i], vertices[i + 1]);
        }

        // Замыкаем фигуру, добавляя расстояние между последней и первой вершиной
        perimeter += distance(vertices.back(), vertices.front());

        return perimeter;
    }

    // Функция для вычисления площади фигуры
    double calculateArea(const std::vector<Point>& vertices) {
        // Проверяем количество вершин
        if (vertices.size() < 3) {
            std::cerr << "Многоугольник должен иметь как минимум три вершины." << std::endl;
            return 0;
        }

        double area = 0;

        for (size_t i = 0; i < vertices.size(); ++i) {
            size_t nextIndex = (i + 1) % vertices.size();
            area += (vertices[i].x * vertices[nextIndex].y) - (vertices[nextIndex].x * vertices[i].y);
        }

        area *= 0.5;
        return std::abs(area);
    }
};

int main() {
    setlocale(LC_ALL, "Russian");

    double x1, y1, x2, y2, x3, y3;

    std::cin >> x1 >> y1;
    std::cin >> x2 >> y2;
    std::cin >> x3 >> y3;

    Point A(x1, y1), B(x2, y2), C(x3, y3);

    Triangle triangle(A, B, C);

    return 0;

    //1     -2 2 4 -1 1 -4
    //2     12 7 1 -4 -1.2 0.4
    //3     1 1 2 1 1.5 2
    //4     2 0 0 2 2 2
    //5     2 4 5 4 -1 -2       1 4 4 4 -2 -2
    //6     1.5 4 5 4 -2 -3   
    //7     3 4 7 -4 -1 -4      -1 3 1 2 -1 1
    //8     -2 3 4 0 -2 -3    
    //9     1 3 5 1 1 -1
    //10    0 4 2 1 -2 1
    //11    4 7 2 1 -2 1
    //12    1 2 1 -2 0 -2
    //13    -2 3 -1 1 -3 1      -4 -1 -2 -3 -4 -3       1 -1 4 -1 1 -3     
    //14    1 1 2 2 3 3
}
