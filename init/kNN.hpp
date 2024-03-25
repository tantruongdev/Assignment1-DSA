
#include "main.hpp"

template <typename T>
class List
{
public:
    //! HÃ m cá»§a tháº§y
    virtual ~List() = default;
    virtual void push_back(T value) = 0;
    virtual void push_front(T value) = 0;
    virtual void insert(int index, T value) = 0;
    virtual void remove(int index) = 0;
    virtual T &get(int index) const = 0;
    virtual int length() const = 0;
    virtual void clear() = 0;
    virtual void print() const = 0;
    virtual void reverse() = 0;

    //! HÃ m há»— trá»£ thÃªm
    virtual int getIndex(T value) = 0;
    virtual List<T> *subList(int start, int end) = 0;
    virtual void printHeadHelper(int start, int end) const = 0;
    virtual void printTailHelper(int start, int end) const = 0;
};

//
// class Image
template <typename T>
class Image : public List<T>
{
private:
    class Node
    {
    public:
        T pointer;
        Node *next;

    public:
        Node(T pointer, Node *next = nullptr) : pointer(pointer), next(next) {}
    };

private:
    Node *head;
    Node *tail;
    int size;

public:
    Image()
    {
        head = tail = nullptr;
        size = 0;
    }
    ~Image()
    {
        this->clear();
    }
    void push_back(T value)
    {
        // TODO: implement task 1
        Node *newNode = new Node(value);
        if (head == nullptr)
        {
            head = tail = newNode;
        }
        else
        {
            tail->next = newNode;
            tail = newNode;
        }
        size++;
    }
    void push_front(T value)
    {
        // TODO: implement task 1
        Node *newNode = new Node(value, head);
        if (head == nullptr)
        {
            head = tail = newNode;
        }
        else
        {
            head = newNode;
        }
        size++;
    }
    void insert(int index, T value)
    {
        if (index < 0 || index > size)
            return;

        // TODO: implement task 1
        if (index == 0)
        {
            push_front(value);
        }
        else if (index == size)
        {
            push_back(value);
        }
        else
        {
            Node *temp = head;
            for (int i = 0; i < index - 1; i++)
            {
                temp = temp->next;
            }
            Node *newNode = new Node(value, temp->next);
            temp->next = newNode;
            size++;
        }
    }
    void remove(int index)
    {
        if (index < 0 || index >= size)
            return;

        // TODO: implement task 1
        if (index == 0)
        {
            Node *deleteNode = head;
            head = head->next;
            delete deleteNode;
        }
        else
        {
            Node *temp = head;
            for (int i = 0; i < index - 1; i++)
            {
                temp = temp->next;
            }
            Node *deleteNode = temp->next;
            temp->next = deleteNode->next;
            if (deleteNode == tail)
            {
                tail = temp;
            }
        }
        size--;
    }

    T &get(int index) const
    {
        if (index < 0 || index >= this->size)
            throw std::out_of_range("get(): Out of range");

        // TODO: implement task 1
        if (index == 0)
        {
            return head->pointer;
        }
        else if (index == size - 1)
        {
            return tail->pointer;
        }
        else
        {
            Node *temp = head;
            for (int i = 0; i < index; i++)
            {
                temp = temp->next;
            }
            return temp->pointer;
        }
    }

    int getIndex(T value)
    {
        Node *temp = head;
        for (int i = 0; i < this->size; i++)
        {
            if (temp->pointer == value)
            {
                return i;
            }
            temp = temp->next;
        }
        return -1;
    }

    int length() const
    {
        return size;
    }

    void clear()
    {
        // TODO: implement task 1
        while (head != nullptr)
        {
            Node *deleteNode = head;
            head = head->next;
            delete deleteNode;
        }
        head = tail = nullptr;
        size = 0;
    }

    void print() const
    {
        if (size == 0)
            return;
        Node *temp = head;
        for (int i = 0; i < this->size; i++)
        {
            if (i == this->size - 1)
                // cout << temp->pointer << " " << endl;
                cout << temp->pointer;
            else
                cout << temp->pointer << " ";
            temp = temp->next;
        }
    }

    void reverse()
    {
        if (head == nullptr || head->next == nullptr)
        {
            return;
        }
        // TODO: implement task 1
        Node *left = head;

        for (int i = 0; i < size / 2; i++)
        {
            Node *temp = left;
            for (int j = 0; j < size - (2 * i + 1); j++)
            {
                temp = temp->next;
            }
            T value = left->pointer;
            left->pointer = temp->pointer;
            temp->pointer = value;

            left = left->next;
        }
    }

    void printHeadHelper(int start, int end) const
    {
        Node *temp = head;
        for (int i = start; i < end && i < this->size; i++)
        {
            if (i == end - 1 || i == this->size - 1)
                cout << temp->pointer;
            else
                cout << temp->pointer << " ";
            temp = temp->next;
        }
    }

    void printTailHelper(int start, int end) const
    {
        Node *temp = head;
        for (int i = 0; i < start; i++)
        {
            temp = temp->next;
        }
        for (int i = start; i < end && i < this->size; i++)
        {
            if (i == end - 1 || i == this->size - 1)
                cout << temp->pointer;
            else
                cout << temp->pointer << " ";
            temp = temp->next;
        }
    }

    List<T> *subList(int start, int end)
    {

        if (this->size <= start)
            return nullptr;
        List<T> *result = new Image<T>();

        // TODO: implement task 1
        Node *temp = head;
        int i = 0;
        for (i; i < start; i++)
        {
            temp = temp->next;
        }
        if (end >= size)
            end = size;
        while (i < end)
        {
            result->push_back(temp->pointer);
            temp = temp->next;
            i++;
        }

        return result;
    }
};

class Dataset
{
private:
    List<List<int> *> *data;
    List<string> *nameCol;
    // You may need to define more
public:
    // HÃ m khá»Ÿi táº¡o
    Dataset()
    {
        this->nameCol = new Image<string>();
        this->data = new Image<List<int> *>();
    }
    // HÃ m há»§y
    ~Dataset()
    { // xóa cấp phát động của các cột
        for (int i = 0; i < data->length(); i++)
        {
            data->get(i)->clear();
        }
        // xóa cập phát động của hàng
        for (int i = 0; i < data->length(); i++)
        {
            delete this->data->get(i);
        }
        // xóa data tự động gọi tới hàm hủy của image và gọi tới clear() để xóa các cấp phát động của data
        delete data;
        delete nameCol;
    }
    Dataset(const Dataset &other)
    {
        this->nameCol = new Image<string>();
        this->data = new Image<List<int> *>();
        // TODO: implement Task 2
        // Num of cols
        int cols = other.nameCol->length();
        // Num of rows
        int rows = other.data->length();
        this->nameCol = other.nameCol->subList(0, cols);
        if (rows != 0)
        {
            cols = max(other.data->get(0)->length(), cols);
            for (int i = 0; i < rows; i++)
            {
                this->data->push_back(other.data->get(i)->subList(0, cols));
            }
            // this->nameCol = other.nameCol->subList(0, cols);
        }
    }
    Dataset &operator=(const Dataset &other)
    {
        // TODO: implement Task 2
        if (this == &other) // Check for self-assignment
            return *this;

        this->~Dataset(); //! xóa đi cấp phát của this

        // Initialize data
        this->data = new Image<List<int> *>();

        int cols = other.nameCol->length();
        // Num of rows
        int rows = other.data->length();
        if (rows != 0)
        {
            cols = max(other.data->get(0)->length(), cols);
            for (int i = 0; i < rows; i++)
            {
                this->data->push_back(other.data->get(i)->subList(0, cols));
            }
            this->nameCol = other.nameCol->subList(0, cols);
        }
        return *this;
    }
    bool loadFromCSV(const char *fileName)
    {
        ifstream file(fileName);
        if (file.is_open())
        {
            string str;
            int number;

            file >> str;
            for (int i = 0; i < str.length(); i++)
            {
                if (str[i] == ',')
                    str[i] = ' ';
            }
            stringstream ss(str);
            while (ss >> str)
                nameCol->push_back(str);

            while (file >> str)
            {
                for (int i = 0; i < str.length(); i++)
                {
                    if (str[i] == ',')
                        str[i] = ' ';
                }
                stringstream ss(str);
                List<int> *temp = new Image<int>();
                while (ss >> number)
                    temp->push_back(number);
                data->push_back(temp);
            }
            return true;
        }
        return false;
    }
    void getShape(int &nRows, int &nCols) const
    {
        nRows = 0, nCols = 0;
        // TODO: implement Task 2
        if (this->data->length() == 0 || this->nameCol->length() == 0)
        {
            return;
        }
        nRows = this->data->length();
        if (nRows != 0)
            nCols = this->data->get(0)->length();
        else
            nCols = this->nameCol->length();
    }
    void columns() const
    {
        // TODO: implement Task 2
        if (this->nameCol->length() == 0)
            return;
        this->nameCol->print();
    }
    void printHead(int nRows = 5, int nCols = 5) const
    {
        // TODO: implement Task 2
        if (nRows <= 0 || nCols <= 0)
            return;

        // Tính lại nRows, nCols;
        int numRows = this->data->length();      // Số lượng dòng trong bảng
        int numCols = (this->nameCol->length()); // Số lượng cột trong bảng
        if (numRows != 0)
        {
            numCols = max(numCols, this->data->get(0)->length());
        }

        nRows = (nRows > numRows) ? numRows : nRows;
        nCols = (nCols > numCols) ? numCols : nCols;

        // Dòng đầu tiên, in ra tên các cột của bảng dữ liệu
        this->nameCol->printHeadHelper(0, nCols);
        if (numRows != 0)
            cout << endl;
        // Các dòng sau in giá trị của mỗi ô trong bảng, mỗi phần tử cách nhau bằng khoảng
        // trắng, không có khoảng trắng dư ở cuối dòng
        // cout << "Số dòng " << nRows << endl;
        for (int i = 0; i < nRows; i++)
        {
            data->get(i)->printHeadHelper(0, nCols);
            // cout << i << " :  ";
            if (i == nRows - 1)
            {
                break;
            }

            cout << endl;
        }
    }
    void printTail(int nRows = 5, int nCols = 5) const
    {

        if (nRows <= 0 || nCols <= 0)
            return;

        int numRows = this->data->length();    // Số lượng dòng trong bảng
        int numCols = this->nameCol->length(); // Số lượng cột trong bảng
        if (numRows != 0)
        {
            numCols = max(numCols, this->data->get(0)->length());
        }

        // Tính toán chỉ số bắt đầu của dòng và cột cần in
        int startRow = (nRows < numRows) ? (numRows - nRows) : 0;
        int startCol = (nCols < numCols) ? (numCols - nCols) : 0;

        // TODO: implement Task 2

        // In ra tên các cột của bảng dữ liệu
        this->nameCol->printTailHelper(startCol, numCols);
        cout << endl;
        // In giá trị của mỗi ô trong bảng, mỗi phần tử cách nhau bằng khoảng trắng,
        // không có khoảng trắng dư ở cuối dòng
        for (int i = startRow; i < numRows; i++)
        {
            this->data->get(i)->printTailHelper(startCol, numCols);
            if (i != numRows - 1) //! bỏ endl ở cuối
                cout << endl;
        }
    }
    bool drop(int axis = 0, int index = 0, std::string columns = "")
    {
        // TODO: implement Task 2
        if (axis != 0 && axis != 1)
        {
            return false;
        }
        if (axis == 0)
        {
            int numRows = this->data->length(); // Số lượng dòng trong bảng
            if (index < 0 || index >= numRows)
                return false;

            this->data->remove(index);
            return true;
        }
        else
        {
            int delCol = this->nameCol->getIndex(columns);
            int numRows = this->data->length(); // Số lượng dòng trong bảng

            if (delCol == -1)
                return false;

            this->nameCol->remove(delCol);
            // int numRows = this->data->length(); // Số lượng dòng trong bảng
            if (numRows == 0)
                return true;

            // int col = (this->nameCol->length, this->data->get(0)->length());

            if (this->data->get(0)->length() <= delCol)
                return true;

            // this->nameCol->remove(delCol);

            for (int i = 0; i < numRows; i++)
            {
                this->data->get(i)->remove(delCol);
            }

            return true;
        }

        return false;
    }
    Dataset extract(int startRow = 0, int endRow = -1, int startCol = 0, int endCol = -1) const
    {
        // TODO: implement Task 2

        Dataset result;
        // delete result.nameCol;
        // delete result.data;
        int numRows = this->data->length(); // Số lượng dòng trong bảng
        int numCols = this->nameCol->length();
        if (numRows != 0)
        {
            numCols = this->data->get(0)->length(); // Số lượng cột trong bảng
            // cout << "Check cột " << startCol << ' ' << endCol << endl;
            // cout << "Số cột " << numCols << endl;
        }
        if (startRow < -1 || endRow < -1 || startCol < -1 || endCol < -1)
            throw std::out_of_range("get(): Out of range");

        if ((startRow > endRow && endRow != -1) || (startCol > endCol && endCol != -1))
            throw std::out_of_range("get(): Out of range");

        // cout << startRow << ' ' << numRows << endl;
        if (startRow >= numRows || startCol >= numCols)
        {
            // cout << "LỖi ở đây";

            return result;
        }
        // Nếu start > end -> return
        if (endRow != -1 && startRow > endRow || endCol != -1 && startCol > endCol)
            return result;

        // Nếu start > row -> return
        // if (startRow >= numRows || startCol >= numCols)
        // {
        //     // cout << "LỖi ở đây";
        //     return result;
        // }

        //   Dungf sublist  SRow->ERow
        endCol = (endCol == -1 || endCol >= numCols) ? numCols : endCol + 1;
        endRow = (endRow == -1 || endRow >= numRows) ? numRows : endRow + 1;

        delete result.nameCol;
        result.nameCol = this->nameCol->subList(startCol, endCol);

        for (int i = startRow; i < endRow; i++)
        {
            result.data->push_back(data->get(i)->subList(startCol, endCol));
        }

        return result;
    }

    List<List<int> *> *getData() const
    {
        return this->data;
    }

    double distanceEuclidean(const List<int> *x, const List<int> *y) const
    {
        // TODO: implement Task 2 copy code tá»« implement Task 1 chá»‰nh
        double distance = 0.0;
        // TODO: implement task 1
        //^ gợi ý dùng length, get
        int i = 0, j = 0, size1 = x->length(), size2 = y->length();
        while (i < size1 && j < size2)
        {
            int value1 = x->get(i);
            int value2 = y->get(j);
            distance += (value1 - value2) * (value1 - value2);
            i++;
            j++;
        }
        while (i < size1)
        {
            int value1 = x->get(i);
            distance += (value1 * value1);
            i++;
        }

        while (j < size2)
        {
            int value2 = y->get(j);
            distance += (value2 * value2);
            j++;
        }

        return sqrt(distance);
    }

    Dataset predict(const Dataset &X_train, const Dataset &Y_train, const int k) const
    {

        // TODO: implement Task 3
        if (k > X_train.data->length())
        {
            throw std::out_of_range("get(): Out of range");
        }
        // Khởi tạo Dataset mới
        Dataset result;

        // Lấy tên cột đầu tiên của Y_train
        string firstColName;
        if (Y_train.nameCol->length() != 0)
            firstColName = Y_train.nameCol->get(0);
        // string firstColName = "label";

        // Thêm tên cột đầu tiên vào result
        result.nameCol->push_back(firstColName);

        // Lấy số hàng của X_train và Y_train
        int numRowsXTrain = X_train.data->length();
        // int numRowsYTrain = Y_train.data->length();

        // Lặp qua từng hàng trong X_test (this)
        int numRowsXTest = this->data->length();
        for (int i = 0; i < numRowsXTest; ++i)
        {
            List<int> *rowXTest = this->data->get(i); // Lấy hàng hiện tại từ X_test

            // Khởi tạo mảng lưu khoảng cách và label tương ứng
            double distances[numRowsXTrain];
            int labels[numRowsXTrain];

            // Lặp qua từng hàng trong X_train
            for (int j = 0; j < numRowsXTrain; ++j)
            {
                List<int> *rowXTrain = X_train.data->get(j); // Lấy hàng hiện tại từ X_train

                // Tính khoảng cách giữa hàng hiện tại của X_test và hàng của X_train
                double distance = distanceEuclidean(rowXTest, rowXTrain);

                // Lấy label từ Y_train
                int label = Y_train.data->get(j)->get(0); // Giả sử cột đầu tiên là label

                // Lưu khoảng cách và label vào mảng distances và labels
                distances[j] = distance;
                labels[j] = label;
            }

            // Sắp xếp mảng distances theo khoảng cách tăng dần (sử dụng Bubble Sort)
            for (int m = 0; m < numRowsXTrain - 1; ++m)
            {
                for (int n = 0; n < numRowsXTrain - m - 1; ++n)
                {
                    if (distances[n] > distances[n + 1])
                    {
                        swap(distances[n], distances[n + 1]);
                        swap(labels[n], labels[n + 1]);
                    }
                }
            }

            // Tạo mảng đếm tần suất xuất hiện của mỗi label
            int freq[10] = {0}; // Giả sử có tối đa 10 labels

            // Lặp qua k hàng gần nhất (k hàng có khoảng cách nhỏ nhất)
            for (int m = 0; m < k; ++m)
            {
                int label = labels[m]; // Lấy label của hàng m

                // Tăng tần suất xuất hiện của label lên 1
                ++freq[label];
            }

            // Tìm label có tần suất xuất hiện lớn nhất
            int maxFreqLabel = 0;
            int maxFreq = 0;
            for (int n = 0; n < 10; ++n)
            { // Giả sử có tối đa 10 labels
                if (freq[n] > maxFreq)
                {
                    maxFreq = freq[n];
                    maxFreqLabel = n;
                }
            }

            // Thêm label có tần suất xuất hiện lớn nhất vào result
            List<int> *newRow = new Image<int>();
            newRow->push_back(static_cast<int>(maxFreqLabel));

            result.data->push_back(newRow);
            // delete newRow;
        }

        return result;
        // Tra ve Y_pred
        // return Dataset();
    }
    double score(const Dataset &y_test) const
    {
        // TODO: implement Task 3
        // Kiểm tra tỷ lệ gióng nhau giữa this vs other int numRowsYTest = y_test.data->length();
        int numRowsYTest = y_test.data->length();
        int numRowsResult = this->data->length();
        if (numRowsYTest == 0)
            return -1;
        if (numRowsYTest != numRowsResult)
        {
            return -1;
        }

        int correctPredictions = 0;

        for (int i = 0; i < numRowsYTest; ++i)
        {
            int actualLabel = y_test.data->get(i)->get(0);
            int predictedLabel = this->data->get(i)->get(0);

            if (actualLabel == predictedLabel)
            {
                ++correctPredictions;
            }
        }

        double accuracy = 1.0 * (correctPredictions) / numRowsYTest;
        return accuracy;
    }
};

class kNN
{
private:
    int k;
    Dataset X_train;
    Dataset Y_train;
    // You may need to define more
public:
    kNN(int k = 5) : k(k){};
    void fit(const Dataset &X_train, const Dataset &y_train)
    {
        this->X_train = X_train;
        this->Y_train = y_train;
        return;
    }
    Dataset predict(const Dataset &X_test)
    {
        return X_test.predict(this->X_train, this->Y_train, this->k);
    }
    double score(const Dataset &y_test, const Dataset &y_pred)
    {
        return y_test.score(y_pred);
    }
};

// Please add more or modify as needed
void train_test_split(Dataset &X, Dataset &Y, double test_size,
                      Dataset &X_train, Dataset &X_test, Dataset &Y_train, Dataset &Y_test);