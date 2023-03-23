using namespace std;

// base class
class Shape {
  public:
    virtual void Scale(float scaleFactor) = 0;
    virtual void Display() const = 0;

    // destructor
    virtual ~Shape() {}
};

// derived class
class Shape2D : virtual public Shape {
  public:
    virtual float Area() const = 0;
    void ShowArea() const;
    virtual string GetName2D() const = 0;

    // operator overloading
    bool operator>(const Shape2D &rhs) const;
    bool operator<(const Shape2D &rhs) const;
    bool operator==(const Shape2D &rhs) const;

    // destructor
    virtual ~Shape2D() {}
};

// derived class
class Shape3D : virtual public Shape {
  public:
    virtual float Volumne() const = 0;
    void ShowVolumne() const;
    virtual string GetName3D() const = 0;

    // operator overloading
    bool operator>(const Shape3D &rhs) const;
    bool operator<(const Shape3D &rhs) const;
    bool operator==(const Shape3D &rhs) const;

    // destructor
    virtual ~Shape3D() {}
};

// derived from derived classes
class Square : public Shape2D {
  public:
    Square();
    Square(float sideLength);

    // four functions required by abstract base class Shape2D
    float Area() const;
    string GetName2D() const;
    void Scale(float scaleFactor);
    void Display() const;

    ~Square() {}
};