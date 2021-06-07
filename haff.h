#include <iostream>
#include <map>
#include <vector>
#include <list>
#include <algorithm>
#include <iterator>
#include <fstream>
#include <bitset>
using namespace std;
void show_vector(vector<int>& a)
{
    for (vector<int>::iterator it = a.begin(); it != a.end(); ++it)   cout << *it;
}
class Uzel
{
public:
    char s;
    int key;
    Uzel* left, * right;
    Uzel();
    Uzel(char, int);
    Uzel(const Uzel&);
    Uzel(Uzel*, Uzel*);
    friend class Haffman;
};
Uzel:: Uzel()
{
    left = NULL;
    right = NULL;
}
Uzel :: Uzel(char a, int k)
{
    left = NULL;
    right = NULL;
    s = a;
    key = k;
}
Uzel :: Uzel(const Uzel& p)
{
    left = p.left;
    right = p.right;
    s = p.s;
    key = p.key;
}
Uzel :: Uzel(Uzel* L, Uzel* R)
{
    key = L->key + R->key;
    left = L;
    right = R;
}


vector<int>code;
class Haffman
{
public:
    map<char, int>CharMap;
    void PrintMap();
    void CreateMap(ifstream&);
    Uzel* CreateList();
    static bool comp(Uzel* l, Uzel* r)
    {
        return l->key < r->key;
    };
    void Tree(Uzel*, map<char, vector<int>>&);
    unsigned long long Cap(ifstream&);
};

void Haffman :: Tree(Uzel* Head, map<char, vector<int>>& Table)
{
    if (Head->left)
    {
        code.push_back(0);
        Tree(Head->left, Table);
    }
    if (Head->right)
    {
        code.push_back(1);
        Tree(Head->right, Table);
    }
    if (((Head->right) == NULL) && ((Head->left) == NULL))
    {
        Table[Head->s] = code;
        cout << Head->s << " ";
        show_vector(code);
        cout << endl;
    }
    if (!code.empty()) code.pop_back();
}


unsigned long long Haffman :: Cap(ifstream& In)
{
    int key, kol;
    unsigned long long len = 0;
    In.read((char*)&kol, sizeof(kol));
    char s;
    for (int i = 0; i < kol; i++) 
    {
        In.read((char*)&s, sizeof(s));
        In.read((char*)&key, sizeof(key));
        CharMap[s] = key;
        len += key;
    }
    return len;
}

void Haffman::PrintMap()
{
    for (auto it = CharMap.begin(); it != CharMap.end(); it++)
    {
        cout << it->first << " - " << it->second << endl;
    }
}

void Haffman::CreateMap(ifstream& In)
{
    char s;
    for (In.get(s); !In.eof(); In.get(s)) CharMap[s]++;
    In.clear();
    In.seekg(0, ios_base::beg);
}

Uzel* Haffman::CreateList()
{
    list<Uzel*> List;
    for (auto it = CharMap.begin(); it != CharMap.end(); it++)
    {
        Uzel* p = new Uzel(it->first, it->second);
        List.push_back(p);
    }
    while (List.size() != 1)
    {
        List.sort(comp);
        Uzel* R = List.front();
        List.pop_front();
        Uzel* L = List.front();
        List.pop_front();
        Uzel* p = new Uzel(L, R);
        List.push_back(p);
    }
    //cout « (List.front()->left->left->s);

    return List.front();
}





