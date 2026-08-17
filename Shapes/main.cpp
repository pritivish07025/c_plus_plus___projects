#include <bits/stdc++.h>
using namespace std;

// ======================================================
// Abstract Base Class: Shape
// ======================================================
class Shape {
public:
    // Pure virtual functions
    virtual double area() const = 0;
    virtual double perimeter() const = 0;
    virtual void display() const = 0;

    // Virtual destructor
    virtual ~Shape() {}

    // Operator overloading to compare areas
    bool operator>(const Shape& other) const {
        return this->area() > other.area();
    }
};

// ======================================================
// Circle
// ======================================================
class Circle : public Shape {
private:
    double radius;

public:
    Circle(double r) : radius(r) {}

    double area() const override {
        return M_PI * radius * radius;
    }

    double perimeter() const override {
        return 2 * M_PI * radius;
    }

    void display() const override {
        cout << "Circle\n";
        cout << "Radius    = " << radius << "\n";
        cout << "Area      = " << area() << "\n";
        cout << "Perimeter = " << perimeter() << "\n";
    }
};

// ======================================================
// Rectangle
// ======================================================
class Rectangle : public Shape {
protected:
    double width;
    double height;

public:
    Rectangle(double w, double h)
        : width(w), height(h) {}

    double area() const override {
        return width * height;
    }

    double perimeter() const override {
        return 2 * (width + height);
    }

    void display() const override {
        cout << "Rectangle\n";
        cout << "Width     = " << width << "\n";
        cout << "Height    = " << height << "\n";
        cout << "Area      = " << area() << "\n";
        cout << "Perimeter = " << perimeter() << "\n";
    }
};

// ======================================================
// Square
// ======================================================
class Square : public Rectangle {
private:
    double side;

public:
    Square(double s)
        : Rectangle(s, s), side(s) {}

    void display() const override {
        cout << "Square\n";
        cout << "Side      = " << side << "\n";
        cout << "Area      = " << area() << "\n";
        cout << "Perimeter = " << perimeter() << "\n";
    }
};

// ======================================================
// Triangle
// ======================================================
class Triangle : public Shape {
private:
    double a, b, c;

public:
    Triangle(double x, double y, double z)
        : a(x), b(y), c(z) {}

    double perimeter() const override {
        return a + b + c;
    }

    double area() const override {
        double s = perimeter() / 2.0;

        // Heron's Formula
        return sqrt(s * (s - a) * (s - b) * (s - c));
    }

    void display() const override {
        cout << "Triangle\n";
        cout << "Sides     = " << a << ", "
             << b << ", " << c << "\n";
        cout << "Area      = " << area() << "\n";
        cout << "Perimeter = " << perimeter() << "\n";
    }
};

// ======================================================
// Ellipse
// ======================================================
class Ellipse : public Shape {
private:
    double a, b;

public:
    Ellipse(double x, double y)
        : a(x), b(y) {}

    double area() const override {
        return M_PI * a * b;
    }

    double perimeter() const override {
        // Ramanujan approximation
        return M_PI *
               (3 * (a + b) -
                sqrt((3 * a + b) * (a + 3 * b)));
    }

    void display() const override {
        cout << "Ellipse\n";
        cout << "Axes      = " << a << ", " << b << "\n";
        cout << "Area      = " << area() << "\n";
        cout << "Perimeter = " << perimeter() << "\n";
    }
};

// ======================================================
// Global Vector
// ======================================================
vector<Shape*> shapes;

// ======================================================
// Create Circle
// ======================================================
void createCircle() {
    double radius;

    cout << "\nEnter radius: ";
    cin >> radius;

    if (radius <= 0) {
        cout << "Radius must be greater than 0.\n";
        return;
    }

    shapes.push_back(new Circle(radius));

    cout << "Circle created successfully!\n";
}

// ======================================================
// Create Rectangle
// ======================================================
void createRectangle() {
    double width, height;

    cout << "\nEnter width and height: ";
    cin >> width >> height;

    if (width <= 0 || height <= 0) {
        cout << "Width and height must be greater than 0.\n";
        return;
    }

    shapes.push_back(new Rectangle(width, height));

    cout << "Rectangle created successfully!\n";
}

// ======================================================
// Create Square
// ======================================================
void createSquare() {
    double side;

    cout << "\nEnter side: ";
    cin >> side;

    if (side <= 0) {
        cout << "Side must be greater than 0.\n";
        return;
    }

    shapes.push_back(new Square(side));

    cout << "Square created successfully!\n";
}

// ======================================================
// Create Triangle
// ======================================================
void createTriangle() {
    double a, b, c;

    cout << "\nEnter sides a, b and c: ";
    cin >> a >> b >> c;

    if (a <= 0 || b <= 0 || c <= 0) {
        cout << "All sides must be greater than 0.\n";
        return;
    }

    // Triangle inequality theorem
    if (a + b <= c ||
        a + c <= b ||
        b + c <= a) {
        cout << "Invalid triangle sides!\n";
        cout << "Sum of any two sides must be greater than the third side.\n";
        return;
    }

    shapes.push_back(new Triangle(a, b, c));

    cout << "Triangle created successfully!\n";
}

// ======================================================
// Create Ellipse
// ======================================================
void createEllipse() {
    double a, b;

    cout << "\nEnter semi-major axis and semi-minor axis: ";
    cin >> a >> b;

    if (a <= 0 || b <= 0) {
        cout << "Axes must be greater than 0.\n";
        return;
    }

    shapes.push_back(new Ellipse(a, b));

    cout << "Ellipse created successfully!\n";
}

// ======================================================
// Display All Shapes
// ======================================================
void displayAllShapes() {

    if (shapes.empty()) {
        cout << "\nNo shapes created yet.\n";
        return;
    }

    cout << "\n========================================\n";
    cout << "          ALL CREATED SHAPES\n";
    cout << "========================================\n";

    for (size_t i = 0; i < shapes.size(); i++) {

        cout << "\nShape #" << i + 1 << "\n";
        cout << "----------------------------------------\n";

        shapes[i]->display();
    }

    cout << "\n========================================\n";
}

// ======================================================
// Compare Two Shapes
// ======================================================
void compareShapes() {

    if (shapes.size() < 2) {
        cout << "\nNeed at least 2 shapes to compare.\n";
        return;
    }

    int i, j;

    cout << "\nEnter first shape index: ";
    cin >> i;

    cout << "Enter second shape index: ";
    cin >> j;

    if (i < 1 || j < 1 ||
        i > static_cast<int>(shapes.size()) ||
        j > static_cast<int>(shapes.size())) {

        cout << "Invalid shape indices.\n";
        return;
    }

    Shape* shape1 = shapes[i - 1];
    Shape* shape2 = shapes[j - 1];

    cout << "\n----------------------------------------\n";
    cout << "Comparison Result\n";
    cout << "----------------------------------------\n";

    cout << "Shape #" << i
         << " Area = " << shape1->area() << "\n";

    cout << "Shape #" << j
         << " Area = " << shape2->area() << "\n";

    if (*shape1 > *shape2) {

        cout << "\nShape #" << i
             << " has a larger area.\n";

    }
    else if (*shape2 > *shape1) {

        cout << "\nShape #" << j
             << " has a larger area.\n";

    }
    else {

        cout << "\nBoth shapes have equal area.\n";
    }
}

// ======================================================
// Delete All Shapes
// ======================================================
void cleanup() {

    for (Shape* shape : shapes) {
        delete shape;
    }

    shapes.clear();
}

// ======================================================
// Shape Dashboard
// ======================================================
void shapeDashboard() {

    int choice;

    while (true) {

        cout << "\n\n";
        cout << "========================================\n";
        cout << "         SHAPE CALCULATOR\n";
        cout << "========================================\n";

        cout << "1. Create Circle\n";
        cout << "2. Create Rectangle\n";
        cout << "3. Create Square\n";
        cout << "4. Create Triangle\n";
        cout << "5. Create Ellipse\n";
        cout << "6. Display All Shapes\n";
        cout << "7. Compare Two Shapes\n";
        cout << "8. Exit\n";

        cout << "========================================\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {

            case 1:
                createCircle();
                break;

            case 2:
                createRectangle();
                break;

            case 3:
                createSquare();
                break;

            case 4:
                createTriangle();
                break;

            case 5:
                createEllipse();
                break;

            case 6:
                displayAllShapes();
                break;

            case 7:
                compareShapes();
                break;

            case 8:
                cout << "\nExiting Shape Calculator...\n";
                return;

            default:
                cout << "\nInvalid choice! Please try again.\n";
        }
    }
}

// ======================================================
// Main Function
// ======================================================
int main() {

    cout << "========================================\n";
    cout << "       OOP SHAPE CALCULATOR\n";
    cout << "========================================\n";

    shapeDashboard();

    // Free dynamically allocated memory
    cleanup();

    return 0;
}