#include "kNN.hpp"

/* TODO: You can implement methods, functions that support your data structures here.
 * */

// Single Linked List

Dataset::Dataset(){
    this->data = new SLinkedList<List<int>*>;
    this->label = new SLinkedList<string>;
}

Dataset::~Dataset(){
    for (int i = 0; i < data->length(); i++){
        data->get(i)->clear();
    }
    data->clear();
    label->clear();
}

Dataset::Dataset(const Dataset& other) {
    this->data = new SLinkedList<List<int>*>();
    for (int i = 0; i < other.data->length(); i++){
        this->data->push_back(new SLinkedList<int>(other.data->get(i)));
    }
    this->label = new SLinkedList<string>(other.label);
};

Dataset& Dataset::operator=(const Dataset& other){
    // Dataset pData;
    // pData.data = new SLinkedList<List<int>*>();
    // for (int i = 0; i < other.data->length(); i++){
    //     pData.data->push_back(new SLinkedList<int>(other.data->get(i)));
    // }
    // pData.label = new SLinkedList<string>(other.label);
    // return pData;
    this->data = new SLinkedList<List<int>*>();
    for (int i = 0; i < other.data->length(); i++){
        this->data->push_back(new SLinkedList<int>(other.data->get(i)));
    }
    this->label = new SLinkedList<string>(other.label);
    return *this;
};
bool Dataset::loadFromCSV(const char* fileName) {
    ifstream input_file(fileName);
    if (!input_file.is_open())
    {
        return false;
    }
    for (int i = 0; i < data->length(); i++){
        data->get(i)->clear();
    }
    data->clear();
    label->clear();
    string line;
    getline(input_file,line);
    stringstream header(line);
    string headerval;
    while (getline(header,headerval,',')){
        label->push_back(headerval);
    }
    while (getline(input_file,line))
    {
        List<int>* row = new SLinkedList<int>();
        stringstream ss(line);
        string val;
        while (getline(ss,val,',')){
            row->push_back(stoi(val));
        }
        data->push_back(row);
    }
    input_file.close();
    return true;
};

void Dataset::printHead(int nRows, int nCols) const{
    nCols--; // ncol is from 0 to ncol-1
    this->label->print(0,nCols); cout << '\n'; // IN LABEL ROW\n
    nRows = min(nRows,data->length());
    for (int i = 0; i < nRows; i++) {
        nCols = min(nCols,data->get(i)->length());
        if (i == nRows - 1) data->get(i)->print(0,nCols);
        else {
            data->get(i)->print(0,nCols); cout << '\n';
        }
    }
};

void Dataset::printTail(int nRows, int nCols) const{
    int len = label->length();
    this->label->print(len-nCols,len - 1); cout << '\n';
    nRows = min(nRows,data->length());
    for (int i = 0; i < nRows; i++){
        nCols = min(nCols,data->get(i)->length());
        int N = data->get(i)->length();
        if (i == nRows - 1) data->get(i)->print(N - nCols,N);
        else{
            data->get(i)->print(N - nCols,N); cout << '\n';
        }
    }
};

bool Dataset::drop(int axis, int index, std::string columns){
    if (axis != 0 || axis != 1) return false;
    if (index >= data->length() || index < 0) return false;
    if ( axis == 0 ){
        data->get(index)->clear();
        return true;
    }else {
        int idx = label->find(columns);
        if ( idx == -1) return false;
        for (int i = 0; i < data->length(); i++){
            data->get(i)->remove(idx);
        }
        return true;
    }
};
Dataset Dataset::extract(int startRow, int endRow, int startCol, int endCol) const {
    Dataset result;
    if(endRow == -1) endRow = this->data->length() - 1; 
    if(endCol == -1) endCol = this->label->length() - 1;
    for (int i = startCol; i <= endCol; i++){
        result.label->push_back(this->label->get(i));
    }
    for (int i = startRow; i <= endRow; i++) {
        List<int>* newRow = new SLinkedList<int>();
        for (int j = startCol; j <= endCol; j++)
        {
            newRow->push_back(this->data->get(i)->get(j));
        }
        result.data->push_back(newRow);
    }
    return result;
};

List<List<int>*>* Dataset::getData() const {
    return data;
};

void train_test_split(Dataset& X, Dataset& y, double test_size, 
                        Dataset& X_train, Dataset& X_test, Dataset& y_train, Dataset& y_test)
                        {
                            int nRowX = 0, nRowY = 0;
                            X.getShape(nRowX,nRowY);
                            int nTest = ceil(test_size * nRowX);
                            int nTrain = nRowX - nTest;

                            X_train = X.extract(0, nTrain - 1, 0, -1);
                            y_train = y.extract(0, nTrain - 1, 0, 0);
                            X_test = X.extract(nTrain, nRowX - 1, 0, -1);
                            y_test = y.extract(nTrain,nRowX - 1, 0, 0);
                        }