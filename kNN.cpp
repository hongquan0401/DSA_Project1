#include "kNN.hpp"

/* TODO: You can implement methods, functions that support your data structures here.
 * */

// Single Linked List

Dataset::Dataset()
{
    this->data = new ArrList<List<int> *>;
    this->label = new SLinkedList<string>;
}

Dataset::~Dataset()
{
    for (int i = 0; i < data->length(); i++)
    {
        data->get(i)->clear();
    }
    data->clear();
    label->clear();
}

Dataset::Dataset(const Dataset &other)
{
    this->data = new SLinkedList<List<int> *>();
    for (int i = 0; i < other.data->length(); i++)
    {
        this->data->push_back(new SLinkedList<int>(other.data->get(i)));
    }
    this->label = new SLinkedList<string>(other.label);
};

Dataset &Dataset::operator=(const Dataset &other)
{
    this->data = new ArrList<List<int> *>();
    for (int i = 0; i < other.data->length(); i++)
    {
        this->data->push_back(new ArrList<int>(other.data->get(i)));
    }
    this->label = new SLinkedList<string>(other.label);
    return *this;
};
bool Dataset::loadFromCSV(const char *fileName)
{
    ifstream input_file(fileName);
    if (!input_file.is_open())
    {
        return false;
    }
    for (int i = 0; i < data->length(); i++)
    {
        data->get(i)->clear();
    }
    data->clear();
    label->clear();
    string line;
    getline(input_file, line);
    stringstream header(line);
    string headerval;
    while (getline(header, headerval, ','))
    {
        label->push_back(headerval);
    }
    while (getline(input_file, line))
    {
        List<int> *row = new SLinkedList<int>();
        stringstream ss(line);
        string val;
        while (getline(ss, val, ','))
        {
            row->push_back(stoi(val));
        }
        data->push_back(row);
    }
    input_file.close();
    return true;
};

void Dataset::printHead(int nRows, int nCols) const
{
    nCols--; // ncol is from 0 to ncol-1
    this->label->print(0, nCols);
    cout << '\n'; // IN LABEL ROW\n
    nRows = min(nRows, data->length());
    for (int i = 0; i < nRows; i++)
    {
        nCols = min(nCols, data->get(i)->length());
        if (i == nRows - 1)
            data->get(i)->print(0, nCols);
        else
        {
            data->get(i)->print(0, nCols);
            cout << '\n';
        }
    }
};

void Dataset::printTail(int nRows, int nCols) const
{
    int len = label->length();
    this->label->print(len - nCols, len - 1);
    cout << '\n';
    nRows = min(nRows, data->length());
    for (int i = data->length() - nRows; i < data->length(); i++)
    {
        nCols = min(nCols, data->get(i)->length());
        int N = data->get(i)->length();
        if (i == data->length() - 1)
            data->get(i)->print(N - nCols, N);
        else
        {
            data->get(i)->print(N - nCols, N);
            cout << '\n';
        }
    }
};

bool Dataset::drop(int axis, int index, std::string columns)
{
    if (axis != 0 && axis != 1)
        return false;
    if (axis == 0)
    {
        if (index < 0 || index >= data->length()) return false;
        data->get(index)->clear();
        return true;
    }
    else
    {
        int idx = label->find(columns);
        if (idx == -1)
            return false;
        for (int i = 0; i < data->length(); i++)
        {
            data->get(i)->remove(idx);
        }
        return true;
    }
};
Dataset Dataset::extract(int startRow, int endRow, int startCol, int endCol) const
{
    Dataset result;
    if (endRow == -1)
        endRow = this->data->length() - 1;
    if (endCol == -1)
        endCol = this->label->length() - 1;
    for (int i = startCol; i <= endCol; i++)
    {
        result.label->push_back(this->label->get(i));
    }
    for (int i = startRow; i <= endRow; i++)
    {
        List<int> *newRow = new SLinkedList<int>();
        for (int j = startCol; j <= endCol; j++)
        {
            newRow->push_back(this->data->get(i)->get(j));
        }
        result.data->push_back(newRow);
    }
    return result;
};

List<List<int> *> *Dataset::getData() const
{
    return data;
};

kNN::kNN(int k) : k(k), X_train(Dataset()), y_train(Dataset()), nRow_train(0), nCol_train(0){};

void kNN::fit(const Dataset &X_train, const Dataset &y_train)
{
    this->X_train = X_train;
    this->y_train = y_train;
    X_train.getShape(this->nRow_train, this->nCol_train);
};

double distance(List<int> *A, List<int> *B)
{
    double d = 0.0;
    int len = A->length();
    for (int i = 0; i < len; i++)
    {
        d += pow(A->get(i) - B->get(i), 2);
    }
    return sqrt(d);
}

Dataset kNN::predict(const Dataset &X_test)
{
    Dataset y_pred;
    y_pred.getLabel()->push_back(y_train.getLabel()->get(0)); // get col name (label)
    // get dynamic size for matrix
    int row = X_test.getData()->length(), col = X_train.getData()->length();

    // declare maxtrix 2D (distance)
    double **matrix = new double *[row]; // matrix 2D
    for (int i = 0; i < row; i++)
    {
        matrix[i] = new double[col];
    }
    // X_test.getData()->_to_Array();
    // X_train.getData()->_to_Array();
    // y_train.getData()->_to_Array();
    for (int i = 0; i < row; i++)
    {
        int mode_array[10] = {0};
        for (int j = 0; j < col; j++)
        {
            matrix[i][j] = distance(X_test.getData()->get(i), X_train.getData()->get(j));
        }
        /// get k smallest distance in a row
        if (this->k > col)
            k = col;

        double *idx_arr = new double[k];
        int *ref_arr = new int[k];

        for (int j = 0; j < k; j++)
        {
            int min_idx = 0, min_dis = matrix[i][0];
            for (int z = 1; z < col; z++)
            {
                if (matrix[i][z] == -1)
                    continue;
                else if (matrix[i][z] < min_dis)
                {
                    min_dis = matrix[i][z];
                    min_idx = z;
                }
            }
            idx_arr[j] = min_idx;
            matrix[i][min_idx] = -1;
        }
        y_train.getData()->_to_Array();
        for (int j = 0; j < k; j++)
        {
            ref_arr[j] = y_train.getData()->get(idx_arr[j])->get(0);
        }

        for (int j = 0; j < k; j++)
        {
            mode_array[ref_arr[j]]++;
        }
        int max_freq = mode_array[0], max_idx = 0;
        for (int j = 1; j < 10; j++)
        {
            if (mode_array[j] > max_freq)
            {
                max_idx = j;
                max_freq = mode_array[j];
            }
        }
        // push mode number to y_pred
        List<int> *row = new SLinkedList<int>();
        row->push_back(max_idx);
        y_pred.getData()->push_back(row);

        // free mem for dynamic array;
        delete[] ref_arr;
        delete[] idx_arr;
    }

    // free matrix 2D
    for (int i = 0; i < row; i++)
    {
        delete[] matrix[i];
    }
    delete[] matrix;
    return y_pred;
};

double kNN::score(const Dataset &y_test, const Dataset &y_pred)
{
    int S = y_test.getData()->length(); // Mau S tong so anh
    int nCorrect_img = 0;
    for (int i = 0; i < S; i++)
    {
        if (y_test.getData()->get(i)->get(0) == y_pred.getData()->get(i)->get(0))
            nCorrect_img++;
    }
    double accuracy = (double)nCorrect_img / S;
    return accuracy;
};

void train_test_split(Dataset &X, Dataset &y, double test_size,
                      Dataset &X_train, Dataset &X_test, Dataset &y_train, Dataset &y_test)
{
    int nRowX = 0, nRowY = 0;
    X.getShape(nRowX, nRowY);
    int nTest = ceil(test_size * nRowX);
    int nTrain = nRowX - nTest;

    X_train = X.extract(0, nTrain - 1, 0, -1);
    y_train = y.extract(0, nTrain - 1, 0, 0);
    X_test = X.extract(nTrain, nRowX - 1, 0, -1);
    y_test = y.extract(nTrain, nRowX - 1, 0, 0);
}