#include "kNN.hpp"

/* TODO: You can implement methods, functions that support your data structures here.
 * */

// Single Linked List

// void Dataset::printHead(int nRows, int nCols) const {
//     this->columns();
//     cout << '\n';
//     nRows = min(nRows,data->length());
//     ////// print rows without last col
//     for (int i = 0; i < nRows; i++){
//         nCols = min(nCols,data->get(i)->length());
//         //////print col without last col
//         for (int j = 0; j < nCols - 1; j++) {
//             cout << data->get(i)->get(j) << " ";
//         }
//         if (i != nRows - 1) cout << data->get(i)->get(nCols - 1) << '\n'; // print end of row (last col)
//         else cout << data->get(i)->get(nCols - 1);                        // the last element of table
//     }
// }