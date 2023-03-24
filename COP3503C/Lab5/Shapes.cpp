#include "Shapes.h"
#include <iostream>
#include <string>

const float PI = 3.1459f;

// 2D shape
  // Display area of 2D shape
  void Shape2D::ShowArea() const {
    cout << "The area of the " << GetName2D() << " is: " << Area() << endl;
  }

  // Overloading > operator
  bool Shape2D::operator>(const Shape2D &rhs) const {
    return this->Area() > rhs.Area();
  }

  // Overloading < operator
  bool Shape2D::operator<(const Shape2D &rhs) const {
    return this->Area() < rhs.Area();
  }

  // Overloading == operator
  bool Shape2D::operator==(const Shape2D &rhs) const {
    return this->Area() == rhs.Area();
  }

// 3D shape
  // Displays the volume of 3D shape
  void Shape3D::ShowVolume() const {
    cout << "The volume of the " << GetName3D() << " is: " << Volume() << endl;
  }

  // Overloading > operator
  bool Shape3D::operator>(const Shape3D &rhs) const {
    return this->Volume() > rhs.Volume();
  }

  // Overloading < operator
  bool Shape3D::operator<(const Shape3D &rhs) const {
    return this->Volume() < rhs.Volume();
  }

  // Overloading == operator
  bool Shape3D::operator==(const Shape3D &rhs) const {
    return this->Volume() == rhs.Volume();
  }


// Square class definitions
  Square::Square() {
    side = 0;
  }

  Square::Square(float sideLength) {
    this->side = sideLength;
  }

  float Square::Area() const {
    return side * side;
  }

  string Square::GetName2D() const {
    return "Square";
  }

  void Square::Scale(float scaleFactor) {
    side *= scaleFactor;
  }

  void Square::Display() const {
    Shape2D::ShowArea();
    cout << "Length of the side: " << side << endl;
  }

// Triangle class definitions
  Triangle::Triangle() {
    base = 0;
    height = 0;
  }

  Triangle::Triangle(float base, float height) {
    this->base = base;
    this->height = height;
  }

  float Triangle::Area() const {
    return 0.5 * base * height;
  }

  string Triangle::GetName2D() const {
    return "Triangle";
  }

  void Triangle::Display() const {
    Shape2D::ShowArea();
    cout << "Base: " << base << endl;
    cout << "Height: " << height << endl;
  }

// Circle class definitions
  Circle::Circle() {
    radius = 0;
  }

  Circle::Circle(float radius) {
    this->radius = radius;
  }

  float Circle::Area() const {
    return PI * radius * radius;
  }

  string Circle::GetName2D() const {
    return "Circle";
  }

  void Circle::Scale(float scaleFactor) {
    radius *= scaleFactor;
  }

  void Circle::Display() const {
    Shape2D::ShowArea();
    cout << "Radius: " << radius << endl;
  }

// TriangularPyramid class definitions
  TriangularPyramid::TriangularPyramid() : Triangle() {
    height = 0;
    Triangle();
  }

  TriangularPyramid::TriangularPyramid(float height, float length, float baseHeight) : Triangle(length, baseHeight) {
    height = height;
  }

  float TriangularPyramid::Volume() const {
    return Triangle::Area() * height / 3;
  }

  string TriangularPyramid::GetName3D() const {
    return "TriangularPyramid";
  }

  void TriangularPyramid::Scale(float scaleFactor) {
    Triangle::Scale(scaleFactor);
    height *= scaleFactor;
  }

  void TriangularPyramid::Display() const {
    Shape3D::ShowVolume();
    cout << "The height is: " << height << end;
    Triangle::Display();
  }

// Cylindar class definitions
  Cylinder::Cylinder() {
    height = 0;
  }

  Cylinder::Cylinder(float height, float radius) : Circle(radius) {
    height = height;
  }

  float Cylinder::Volume() const {
    return Circle::Area() * height;
  }

  string Cylinder::GetName3D() const {
    return "Cylinder";
  }

  void Cylinder::Scale(float scaleFactor) {
    Circle::Scale(scaleFactor);
    height *= scaleFactor;
  }

  void Cylinder::Display() const {
    Shape3D::ShowVolume();
    cout << "The height is: " << height << endl;
    Circle::Display();
  }

// Sphere class definitions
  Sphere::Sphere() {
    radius = 0;
  }

  Sphere::Sphere(float radius) : Circle(radius) {
    radius = radius;
  }

  float Sphere::Volume() const {
    return 4 * PI * ((radius * radius * radius) / 3);
  }

  string Sphere::GetName3D() const {
    return "Sphere";
  }

  void Sphere::Scale(float scaleFactor) {
    radius *= scaleFactor;
  }

  void Sphere::Display() const {
    Shape3D::ShowVolume();
    Circle::Display();
  }