#include <math.h>
#include <stdio.h>
#include "complex.h"

#define PI 3.141592653589793238462643383
//#define SmallNo 1.0e-14
//#define DEG 0.01745329251994329576923690768

#define TRUE true
#define FALSE false
#define I CComplex(0, 1)

CComplex::CComplex()
{
  re = 0.0;
  im = 0.0;
}
CComplex::CComplex(double x)
{
  re = x;
  im = 0.0;
}
CComplex::CComplex(int x)
{
  re = (double)x;
  im = 0.0;
}
CComplex::CComplex(double x, double y)
{
  re = x;
  im = y;
}

CComplex CComplex::Sqrt()
{
  double w, z;

  if ((re == 0) && (im == 0))
    w = 0;
  else if (fabs(re) > fabs(im))
  {
    z = im / re;
    w = sqrt(fabs(re)) * sqrt((1.0 + sqrt(1.0 + z * z)) / 2.0);
  }
  else
  {
    z = re / im;
    w = sqrt(fabs(im)) * sqrt((fabs(z) + sqrt(1.0 + z * z)) / 2.0);
  }

  CComplex y;
  if (w == 0)
  {
    y.re = 0;
    y.im = 0;
    return y;
  }

  if (re >= 0)
  {
    y.re = w;
    y.im = im / (2.0 * w);
    return y;
  }

  if (im >= 0)
  {
    y.re = fabs(im) / (2.0 * w);
    y.im = w;
    return y;
  }

  y.re = fabs(im) / (2.0 * w);
  y.im = (-w);
  return y;
}

CComplex CComplex::Conj()
{
  return CComplex(re, -im);
}

CComplex CComplex::Inv()
{
  double c;
  CComplex z;

  if (fabs(re) > fabs(im))
  {
    c = im / re;
    z.re = 1.0 / (re * (1.0 + c * c));
    z.im = (-c) * z.re;
  }
  else
  {
    c = re / im;
    z.im = (-1.0) / (im * (1.0 + c * c));
    z.re = (-c) * z.im;
  }

  return z;
}

void CComplex::Set(double x, double y)
{
  re = x;
  im = y;
}

double CComplex::Abs()
{
  if ((re == 0) && (im == 0))
    return 0.0;

  if (fabs(re) > fabs(im))
    return fabs(re) * sqrt(1.0 + (im / re) * (im / re));
  else
    return fabs(im) * sqrt(1.0 + (re / im) * (re / im));
}

double CComplex::Arg()
{
  if ((re == 0) && (im == 0))
    return 0.0;

  return atan2(im, re);
}

double CComplex::Re()
{
  return re;
}

double CComplex::Im()
{
  return im;
}

char *CComplex::ToString(char *s)
{
  if (im < 0)
    sprintf(s, "%.3e - j %.3e", re, fabs(im));
  else
    sprintf(s, "%.3e + j %.3e", re, im);
  return s;
}

//******* Addition ***************************************************
CComplex CComplex::operator+(const CComplex &z)
{
  return CComplex(re + z.re, im + z.im);
};
CComplex CComplex::operator+(double z)
{
  return CComplex(re + z, im);
};
CComplex CComplex::operator+(int z)
{
  return CComplex(re + ((double)z), im);
};
CComplex operator+(int x, const CComplex &y)
{
  return CComplex(((double)x) + y.re, y.im);
}
CComplex operator+(double x, const CComplex &y)
{
  return CComplex(x + y.re, y.im);
}
CComplex operator+(const CComplex &x, const CComplex &y)
{
  return CComplex(x.re + y.re, x.im + y.im);
}
void CComplex::operator+=(const CComplex &z)
{
  re += z.re;
  im += z.im;
};
void CComplex::operator+=(double z)
{
  re += z;
};
void CComplex::operator+=(int z)
{
  re += (double)z;
};

//******* Subtraction ***************************************************
CComplex CComplex::operator-()
{
  return CComplex(-re, -im);
}
CComplex CComplex::operator-(const CComplex &z)
{
  return CComplex(re - z.re, im - z.im);
};
CComplex CComplex::operator-(double z)
{
  return CComplex(re - z, im);
};
CComplex CComplex::operator-(int z)
{
  return CComplex(re - ((double)z), im);
};
CComplex operator-(int x, const CComplex &y)
{
  return CComplex(((double)x) - y.re, -y.im);
}
CComplex operator-(double x, const CComplex &y)
{
  return CComplex(x - y.re, -y.im);
}
CComplex operator-(const CComplex &x, const CComplex &y)
{
  return CComplex(x.re - y.re, x.im - y.im);
}
CComplex operator-(const CComplex &y)
{
  return CComplex(-y.re, -y.im);
}
void CComplex::operator-=(const CComplex &z)
{
  re -= z.re;
  im -= z.im;
};
void CComplex::operator-=(double z)
{
  re -= z;
};
void CComplex::operator-=(int z)
{
  re -= (double)z;
};

//******* Multiplication ***************************************************
CComplex CComplex::operator*(const CComplex &z)
{
  return CComplex(re * z.re - im * z.im, re * z.im + im * z.re);
};
CComplex CComplex::operator*(double z)
{
  return CComplex(re * z, im * z);
};
CComplex CComplex::operator*(int z)
{
  return CComplex(re * ((double)z), im * ((double)z));
};
CComplex operator*(int x, const CComplex &y)
{
  return CComplex(((double)x) * y.re, ((double)x) * y.im);
}
CComplex operator*(double x, const CComplex &y)
{
  return CComplex(x * y.re, x * y.im);
}
CComplex operator*(const CComplex &x, const CComplex &y)
{
  return CComplex(x.re * y.re - x.im * y.im, x.re * y.im + x.im * y.re);
}
void CComplex::operator*=(const CComplex &z)
{
  CComplex x(re * z.re - im * z.im, re * z.im + im * z.re);
  re = x.re;
  im = x.im;
};
void CComplex::operator*=(double z)
{
  re *= z;
  im *= z;
};
void CComplex::operator*=(int z)
{
  re *= (double)z;
  im *= (double)z;
};

//******* Division ***************************************************
CComplex CComplex::operator/(const CComplex &z)
{
  double c;
  CComplex y;

  if (fabs(z.re) > fabs(z.im))
  {
    c = z.im / z.re;
    y.re = 1.0 / (z.re * (1.0 + c * c));
    y.im = (-c) * y.re;
  }
  else
  {
    c = z.re / z.im;
    y.im = (-1.0) / (z.im * (1.0 + c * c));
    y.re = (-c) * y.im;
  }

  return *this * y;
};
CComplex CComplex::operator/(double z)
{
  return CComplex(re / z, im / z);
};
CComplex CComplex::operator/(int z)
{
  return CComplex(re / ((double)z), im / ((double)z));
};
CComplex operator/(int x, const CComplex &z)
{
  double c;
  CComplex y;

  if (fabs(z.re) > fabs(z.im))
  {
    c = z.im / z.re;
    y.re = 1.0 / (z.re * (1.0 + c * c));
    y.im = (-c) * y.re;
  }
  else
  {
    c = z.re / z.im;
    y.im = (-1.0) / (z.im * (1.0 + c * c));
    y.re = (-c) * y.im;
  }

  y.re *= (double)x;
  y.im *= (double)x;

  return y;
}
CComplex operator/(double x, const CComplex &z)
{
  double c;
  CComplex y;

  if (fabs(z.re) > fabs(z.im))
  {
    c = z.im / z.re;
    y.re = 1.0 / (z.re * (1.0 + c * c));
    y.im = (-c) * y.re;
  }
  else
  {
    c = z.re / z.im;
    y.im = (-1.0) / (z.im * (1.0 + c * c));
    y.re = (-c) * y.im;
  }

  y.re *= x;
  y.im *= x;

  return y;
}
CComplex operator/(const CComplex &x, const CComplex &z)
{
  double c;
  CComplex y;

  if (fabs(z.re) > fabs(z.im))
  {
    c = z.im / z.re;
    y.re = 1.0 / (z.re * (1.0 + c * c));
    y.im = (-c) * y.re;
  }
  else
  {
    c = z.re / z.im;
    y.im = (-1.0) / (z.im * (1.0 + c * c));
    y.re = (-c) * y.im;
  }

  return x * y;
}
void CComplex::operator/=(const CComplex &z)
{
  *this = *this / z;
};
void CComplex::operator/=(double z)
{
  re /= z;
  im /= z;
};
void CComplex::operator/=(int z)
{
  re /= (double)z;
  im /= (double)z;
};

//****** Equals definitions ********************************
void CComplex::operator=(double z)
{
  re = z;
  im = 0;
}
void CComplex::operator=(int z)
{
  re = (double)z;
  im = 0;
}

//***** Tests ***********************************************
BOOL CComplex::operator==(const CComplex &z)
{
  if ((z.im == im) && (z.re == re))
    return TRUE;
  return FALSE;
}
BOOL CComplex::operator==(double z)
{
  if ((z == re) && (im == 0))
    return TRUE;
  return FALSE;
}
BOOL CComplex::operator==(int z)
{
  if ((re == (double)z) && (im == 0))
    return TRUE;
  return FALSE;
}
BOOL CComplex::operator!=(const CComplex &z)
{
  if ((z.re == re) && (z.im == im))
    return FALSE;
  return TRUE;
}
BOOL CComplex::operator!=(double z)
{
  if ((re != z) || (im != 0))
    return TRUE;
  return FALSE;
}
BOOL CComplex::operator!=(int z)
{
  if ((re != (double)z) || (im != 0))
    return TRUE;
  return FALSE;
}

//***** Useful functions ************************************
double Re(const CComplex &a)
{
  return a.re;
}
double Im(const CComplex &a)
{
  return a.im;
}
double abs(const CComplex &x)
{
  if ((x.re == 0) && (x.im == 0))
    return 0.0;

  if (fabs(x.re) > fabs(x.im))
    return fabs(x.re) * sqrt(1.0 + (x.im / x.re) * (x.im / x.re));
  else
    return fabs(x.im) * sqrt(1.0 + (x.re / x.im) * (x.re / x.im));
}
double arg(const CComplex &x)
{
  if ((x.re == 0) && (x.im == 0))
    return 0.0;

  return atan2(x.im, x.re);
}

CComplex conj(const CComplex &x)
{
  return CComplex(x.re, -x.im);
}

CComplex exp(const CComplex &x)
{
  CComplex y;

  y.re = cos(x.im) * exp(x.re);
  y.im = sin(x.im) * exp(x.re);

  return y;
}

CComplex sqrt(const CComplex &x)
{
  double w, z;

  if ((x.re == 0) && (x.im == 0))
    w = 0;
  else if (fabs(x.re) > fabs(x.im))
  {
    z = x.im / x.re;
    w = sqrt(fabs(x.re)) * sqrt((1.0 + sqrt(1.0 + z * z)) / 2.0);
  }
  else
  {
    z = x.re / x.im;
    w = sqrt(fabs(x.im)) * sqrt((fabs(z) + sqrt(1.0 + z * z)) / 2.0);
  }

  CComplex y;
  if (w == 0)
  {
    y.re = 0;
    y.im = 0;
    return y;
  }

  if (x.re >= 0)
  {
    y.re = w;
    y.im = x.im / (2.0 * w);
    return y;
  }

  if (x.im >= 0)
  {
    y.re = fabs(x.im) / (2.0 * w);
    y.im = w;
    return y;
  }

  y.re = fabs(x.im) / (2.0 * w);
  y.im = (-w);

  return y;
}

CComplex tanh(const CComplex &x)
{
  CComplex y;
  if (x.re > 0)
    y = (1 - exp(-2 * x)) / (1 + exp(-2 * x));
  else
    y = (exp(2 * x) - 1) / (exp(2 * x) + 1);
  return y;
}

CComplex sinh(const CComplex &x)
{
  return (exp(x) - exp(-x)) / 2;
}

CComplex cosh(const CComplex &x)
{
  return (exp(x) + exp(-x)) / 2;
}

CComplex cos(const CComplex &x)
{
  return (exp(I * x) + exp(-I * x)) / 2;
}

CComplex acos(const CComplex &x)
{
  return PI / 2.0 - arg(I * x + sqrt(1 - x * x)) + I * log(abs(I * x + sqrt(1 - x * x)));
}

CComplex sin(const CComplex &x)
{
  return (exp(I * x) - exp(-I * x)) / (2 * I);
}

CComplex asin(const CComplex &x)
{
  return arg(I * x + sqrt(1 - x * x)) - I * log(abs(I * x + sqrt(1 - x * x)));
}

CComplex tan(const CComplex &x)
{
  return sin(x) / cos(x);
}

CComplex atan(const CComplex &x)
{
  return (arg(1 + I * x) - arg(1 - I * x) - I * (log(abs(1 + I * x) / abs(1 - I * x)))) / 2;
}

CComplex log(const CComplex &x)
{
  CComplex y;
  y.im = arg(x);
  y.re = log(abs(x));
  return y;
}

CComplex pow(const CComplex &x, double y)
{
  return exp(y * log(x));
}

CComplex pow(const CComplex &x, int y)
{
  if (y == 0)
    return CComplex(1, 0);

  CComplex z;

  if (y > 0)
  {
    z = x;
    for (int i = 1; i < y; i++)
      z *= x;
  }
  else
  {
    z = 1 / x;
    CComplex w = z;
    for (int i = 1; i < (-y); i++)
      z *= w;
  }

  return z;
}

CComplex pow(const CComplex &x, const CComplex &y)
{
  return exp(y * log(x));
}
