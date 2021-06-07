#include "Haff.h"
int main()
{
    ifstream In("Text.txt", ios::binary);
    if (!In.is_open())
    {
        cout << "error1";
        return 0;
    }
    ofstream Out("Encode.txt", ios::binary);
    if (!Out.is_open())
    {
        cout << "error2";
        return 0;
    }
    Haffman a;
    map<char, vector<bool>> Table;
    a.CreateMap(In);
    a.Tree(a.CreateList(), Table);
    char s, ptr = 0;
    int count = 0;
    int kol = Table.size();
    Out.write((char*)&kol, sizeof(kol)); // Записываем кол-во символов
    for (auto it = a.CharMap.begin(); it != a.CharMap.end(); it++) // Записываем Map
    {
        Out.write((char*)&it->first, sizeof(it->first));
        Out.write((char*)&it->second, sizeof(it->second));
    }

    while (In.get(s)) // Запись кода
    {
        vector<int> Tr = Table[s];
        //show_vector(Tr);
        for (int i = 0; i < Tr.size(); i++)
        {
            ptr = ptr | (Tr[i] << (7 - count));
            count++;
            if (count == 8)
            {
                count = 0;
                Out.put(ptr);
                //cout << bitset<sizeof(ptr)* CHAR_BIT>(ptr) << "\n";
               // cout << ptr;
                ptr = 0;
            }
        }
    }
    if (ptr) Out.put(ptr);
    //cout << endl;
    In.close();
    Out.close();
    return 0;
}
