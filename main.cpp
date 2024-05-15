#include "kNN.hpp"

// void tc1(){
//     Dataset dataset;
//     dataset.loadFromCSV("mnist.csv");
//     dataset.printHead();
//     dataset.printTail();
//     int nRows, nCols;
//     dataset.getShape(nRows, nCols);
//     cout << "Shape: " << nRows << "x" << nCols << endl;

//     kNN knn;
//     Dataset X_train, X_test, y_train, y_test;
//     Dataset feature = dataset.extract(0, -1, 1, -1);
//     Dataset label = dataset.extract(0, -1, 0, 0);
//     train_test_split(feature, label, 0.2, X_train, X_test, y_train, y_test);

//     knn.fit(X_train, y_train);
//     Dataset y_pred = knn.predict(X_test);
//     double accuracy = knn.score(y_test, y_pred);
//     cout << "Accuracy: " << accuracy << endl;
// }

int main()
{
    // tc1();
    // clock_t begin = clock();
    // Dataset dataset;
    // dataset.loadFromCSV("mnist.csv");
    // int nRows, nCols;

    // kNN knn;
    // Dataset X_train, X_test, y_train, y_test;
    // Dataset feature = dataset.extract(0, -1, 1, -1);
    // Dataset label = dataset.extract(0, -1, 0, 0);

    // train_test_split(feature, label, 0.2, X_train, X_test, y_train, y_test);
    // knn.fit(X_train, y_train);
    // Dataset y_pred = knn.predict(X_test);
    // double accuracy = knn.score(y_test, y_pred);
    // cout << "Accuracy: " << accuracy << endl;
    // clock_t end = clock();
    // cout << "\nexcute time: " << end - begin;
Dataset dataset;
dataset.loadFromCSV("mnist.csv");
dataset.printTail(20, 20);
// dataset.getData()->get(196)->print();
}