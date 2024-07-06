#include <iostream>

class Node {
public:
    int row, col, value;
    Node* next;

    Node(int r, int c, int v) : row(r), col(c), value(v), next(nullptr) {}
};

class SparseMatrix {
private:
    int totalRows, totalColumns;
    Node* head;

public:
    SparseMatrix(int rows, int cols) : totalRows(rows), totalColumns(cols), head(nullptr) {}

    void addElement(int row, int col, int value) {
        if (row >= totalRows || col >= totalColumns || row < 0 || col < 0) {
            std::cout << "Invalid index" << std::endl;
            return;
        }
        if (value == 0) {
            std::cout << "Value is zero, not adding to sparse matrix" << std::endl;
            return;
        }

        Node* newNode = new Node(row, col, value);
        if (!head) {
            head = newNode;
            return;
        }

        Node* current = head;
        Node* prev = nullptr;

        while (current && (current->row < row || (current->row == row && current->col < col))) {
            prev = current;
            current = current->next;
        }

        newNode->next = current;

        if (prev) {
            prev->next = newNode;
        }
        else {
            head = newNode;
        }
    }

    void printSparseMatrix() const {
        Node* current = head;
        std::cout << "Row Column Value" << std::endl;
        while (current) {
            std::cout << current->row << "    " << current->col << "      " << current->value << std::endl;
            current = current->next;
        }
    }

    void printMatrix() const {
        std::cout << "Full Matrix Representation:" << std::endl;
        Node* current = head;
        for (int i = 0; i < totalRows; ++i) {
            for (int j = 0; j < totalColumns; ++j) {
                if (current && current->row == i && current->col == j) {
                    std::cout << current->value << " ";
                    current = current->next;
                }
                else {
                    std::cout << "0 ";
                }
            }
            std::cout << std::endl;
        }
    }
};

int main() {
    int rows = 4;
    int cols = 5;
    SparseMatrix sparseMatrix(rows, cols);

    sparseMatrix.addElement(0, 1, 3);
    sparseMatrix.addElement(1, 2, 5);
    sparseMatrix.addElement(2, 0, 9);
    sparseMatrix.addElement(3, 3, 12);
    sparseMatrix.addElement(3, 4, 15);

    sparseMatrix.printSparseMatrix();
    std::cout << std::endl;
    sparseMatrix.printMatrix();

    return 0;
}
