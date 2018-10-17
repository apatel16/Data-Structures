
#include <iostream>
#include <stdio.h>
#include <string>
#include <stdlib.h>

using namespace std;

struct item{
    unsigned int index;
    int data;
    item *next;
    item(unsigned int i, int d, item* t)
    {
        index = i; data = d; next = t;
    }
};

typedef item* link;

struct MatRow{
    unsigned int size;
    link first;
    link last;
};

class Matrix
{
public:
    Matrix(unsigned short row, unsigned short col);      // Construction
    bool add(unsigned short row, unsigned short col, int data);        // Adds a new item to the matrix
    void show();                             // show all items of matrix
    Matrix operator + (Matrix&);
    link getfirst(int r);
private:
    MatRow *Head;                    // A pointer to show array of the "item" pointer
    unsigned short rowN;            // how many row matrix has
    unsigned short colN;        // how many col matrix has
};

Matrix::Matrix(unsigned short row, unsigned short col){
    rowN = row;
    colN = col;
    
    Head = new MatRow[row];
    
    for(int i=0; i<rowN; i++){
        Head[i].first = Head[i].last = NULL;
        Head[i].size = 0;
    }
}

bool Matrix::add(unsigned short row, unsigned short col, int data){
    link AddItem = new item(col, data, NULL );
    if(AddItem == NULL){
        return false;
    }
    
    if(Head[row].first == NULL){
        Head[row].first = AddItem;
        Head[row].last = AddItem;
    }else{
        Head[row].last->next = AddItem;
        Head[row].last = AddItem;
    }
    
    Head[row].size++;
    return true;
}

link Matrix::getfirst(int r)
{
    return Head[r].first;
}

Matrix Matrix::operator+(Matrix &param){
    Matrix MC(rowN, colN);
    
    for(int i=0; i<rowN; i++){
        link itA = Head[i].first;
        link itB = param.getfirst(i);
        
        cout<<i<<endl;
        while(itA != NULL | itB != NULL){
            if(itA == NULL){
                MC.add(i, itB->index, itB->data);
                itB = itB->next;
                continue;
            }
            
            if(itB == NULL){
                MC.add(i, itA->index, itA->data);
                itA = itA->next;
                continue;
            }
            
            if(itA->index < itB->index){
                MC.add(i, itA->index, itA->data);
                itA = itA -> next;
            }
            else if(itB->index > itB->index){
                MC.add(i,itB->index, itB->data);
                itB = itB->next;
            }
            else{
                MC.add(i,itA->index, itA->data + itB->data);
                itA = itA -> next;
                itB = itB->next;
            }
            
        }
        
    }
    return MC;
}

void Matrix::show(){
    link it;
    for(unsigned short rowC =0; rowC < rowN; rowC++){
        it = Head[rowC].first;
        
        for(unsigned short colC=0; colC < colN; colC++){
            if(it!= NULL){
                if(colC < it->index){
                    cout << "(" << rowC << "," << colC << ")" << ":0 ";
                }
                else{
                    cout << "(" << rowC << "," << colC << "):";
                    cout << it->data << " ";
                    it = it->next;
                }
                
            }
            else{
                cout<< "(" << rowC << "," << colC << ")" << ":0";
            }
        }
        cout<<endl;
    }
}

int main(int argc, const char * argv[])
{
    Matrix A(3, 3);
    A.add(0, 0, 10);
    A.add(2, 2, 10);
    A.show();
    
    cout << endl;
    
    Matrix B(3, 3);
    B.add(0, 0, 3);
    B.add(1, 1, 7);
    B.show();
    
    cout<<endl;
    
    Matrix C(3, 3);
    C = A + B;
    
    C.show();
    return 0;
}
