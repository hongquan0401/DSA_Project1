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

int main() {
    //tc1();
    
    List<int> *p2 = new SLinkedList<int>();
    for (int i = 0; i < 10; i++)
    {
        p2->push_back(i);
    }
    List<int> *p1 = new SLinkedList<int>(p2);
    // cout << &(p1->get(0)) << " " << &(p2->get(0));
    p1->print(-2,100);
    cout << '\n';
    p2->clear();
    p2->print(2,4);
    p1->print(3,5);
    return 0;
}