#define BOOL bool

struct CComplex
{
  double re, im;

  CComplex();
  CComplex(double x);
  CComplex(int x);
  CComplex(double x, double y);

  CComplex Sqrt();
  CComplex Conj();
  CComplex Inv();
  void Set(double x, double y);
  double Abs();
  double Arg();
  double Re();
  double Im();
  char *ToString(char *s);

  // operator redefinition
  // Addition
  CComplex operator+(const CComplex &z);
  CComplex operator+(double z);
  CComplex operator+(int z);
  friend CComplex operator+(int x, const CComplex &y);
  friend CComplex operator+(double x, const CComplex &y);
  friend CComplex operator+(const CComplex &x, const CComplex &y);
  void operator+=(const CComplex &z);
  void operator+=(double z);
  void operator+=(int z);

  // Subtraction
  CComplex operator-();
  CComplex operator-(const CComplex &z);
  CComplex operator-(double z);
  CComplex operator-(int z);
  friend CComplex operator-(int x, const CComplex &y);
  friend CComplex operator-(double x, const CComplex &y);
  friend CComplex operator-(const CComplex &x, const CComplex &y);
  friend CComplex operator-(const CComplex &x);
  void operator-=(const CComplex &z);
  void operator-=(double z);
  void operator-=(int z);

  // Multiplication
  CComplex operator*(const CComplex &z);
  CComplex operator*(double z);
  CComplex operator*(int z);
  friend CComplex operator*(int x, const CComplex &y);
  friend CComplex operator*(double x, const CComplex &y);
  friend CComplex operator*(const CComplex &x, const CComplex &y);
  void operator*=(const CComplex &z);
  void operator*=(double z);
  void operator*=(int z);

  // Division
  CComplex operator/(const CComplex &z);
  CComplex operator/(double z);
  CComplex operator/(int z);
  friend CComplex operator/(int x, const CComplex &y);
  friend CComplex operator/(double x, const CComplex &y);
  friend CComplex operator/(const CComplex &x, const CComplex &y);
  void operator/=(const CComplex &z);
  void operator/=(double z);
  void operator/=(int z);

  // Equals
  void operator=(double z);
  void operator=(int z);

  // Tests
  BOOL operator==(const CComplex &z);
  BOOL operator==(double z);
  BOOL operator==(int z);
  BOOL operator!=(const CComplex &z);
  BOOL operator!=(double z);
  BOOL operator!=(int z);
};

double Re(const CComplex &a);
double Im(const CComplex &a);
double abs(const CComplex &x);
double arg(const CComplex &x);
CComplex conj(const CComplex &x);
CComplex exp(const CComplex &x);
CComplex sqrt(const CComplex &x);
CComplex tanh(const CComplex &x);
CComplex sinh(const CComplex &x);
CComplex cosh(const CComplex &x);
CComplex cos(const CComplex &x);
CComplex acos(const CComplex &x);
CComplex sin(const CComplex &x);
CComplex asin(const CComplex &x);
CComplex tan(const CComplex &x);
CComplex atan(const CComplex &x);
CComplex log(const CComplex &x);
CComplex pow(const CComplex &x, int y);
CComplex pow(const CComplex &x, double y);
CComplex pow(const CComplex &x, const CComplex &y);
