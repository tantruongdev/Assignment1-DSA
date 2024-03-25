#include "kNN.hpp"

/* TODO: You can implement methods, functions that support your data structures here.
 * */
#ifndef KNN_CPP
#define KNN_CPP

// Định nghĩa của hàm train_test_split
void train_test_split(Dataset &X, Dataset &Y, double test_size,
                      Dataset &X_train, Dataset &X_test, Dataset &Y_train, Dataset &Y_test)
{
  if (X.getData()->length() != Y.getData()->length() || test_size >= 1 || test_size <= 0)
    return;

  double minD = 1.0e-15;
  int nRows = X.getData()->length();
  double rowSplit = nRows * (1 - test_size);

  if (abs(round(rowSplit) - rowSplit) < minD * nRows)
    rowSplit = round(rowSplit);

  X_train = X.extract(0, rowSplit - 1, 0, -1);
  Y_train = Y.extract(0, rowSplit - 1, 0, -1);

  X_test = X.extract(rowSplit, -1, 0, -1);
  Y_test = Y.extract(rowSplit, -1, 0, -1);
}

#endif // KNN_CPP
