#pragma once

#include "complex.h"

struct CFullMatrix
{
  CComplex **M; // Matrix on LHS
  CComplex *b;  // vector on RHS
  int n;        // dimension of the matrix

  // member functions
  CFullMatrix();
  CFullMatrix(int d);
  ~CFullMatrix();

  void Wipe();
  BOOL Create(int d);
  BOOL GaussSolve();
};

struct CComplexFullMatrix
{
  CComplex **M; // Matrix on LHS
  CComplex *b;  // vector on RHS
  int n;        // dimension of the matrix

  // member functions
  CComplexFullMatrix();
  CComplexFullMatrix(int d);
  ~CComplexFullMatrix();

  void Wipe();
  BOOL Create(int d);
  BOOL GaussSolve();
};