#include "Haff.h"
int main()
{
    ifstream In("Encode.txt", ios::binary);
    if (!In.is_open()) 
    { 
        cout << "error"; 
        return 0; 
    }
    ofstream Out("Decode.txt", ios::binary);
    if (!Out.is_open()) 
    { 
        cout << "error"; 
        return 0; 
    }


    Haffman a;
    map<char, vector<int>> Table;
    unsigned long long len = a.Cap(In);
    Uzel* Head = a.CreateList();
    a.Tree(Head, Table);
    a.PrintMap();
 
    char s, ptr;
    Uzel* it = Head;
    while (In.get(s)) {
        for (int i = 0; i < 8 && len>0; i++) 
        {
            ptr = s & (1 << (7 - i));
            if (ptr) 
            {
                it = it->right;
            }
            else 
                if (!ptr) 
            {
                it = it->left;
            }
            if ((it->left == NULL) && (it->right == NULL)) 
            {
                Out.put(it->s);
                len--;
                it = Head;
            }
        }
    }
    In.close();
    Out.close();

}