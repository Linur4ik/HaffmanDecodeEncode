#include <iostream>
#include <map>
#include <vector>
#include <list>
#include <algorithm>
#include <iterator>
using namespace std;
void show_vector( vector<int>&a)
{
for (vector<int>::iterator it = a.begin() ; it!=a.end() ; ++it)
cout<<*it;
}
class Uzel
{
public:
char s;
int key;
Uzel* left, *right;
Uzel()
{
left = NULL;
right = NULL;
}
Uzel(char a, int k)
{
left = NULL;
right = NULL;
s = a;
key = k;
}
Uzel(const Uzel &p)
{
left=p.left;
right=p.right;
s=p.s;
key=p.key;
}
Uzel(Uzel* L, Uzel* R)
{
key = L->key + R->key;
left = L;
right = R;
}
friend class Haffman;
};

list<Uzel*> List;
vector<int>code;
map<char, vector<int>>Table;
class Haffman
{
public :
map<char, int>CharMap;
// Haffman();
// ~Haffman();
void PrintMap();
void CreateMap(char* s);
Uzel* CreateList();
static bool comp(Uzel *l,Uzel *r)
{
return l->key<r->key;
};
void Tree(Uzel *Head)
{
if(Head->left)
{
code.push_back(0);
Tree(Head->left);
}
if(Head->right)
{
code.push_back(1);
Tree(Head->right);
}
if(((Head->right) == NULL) && ((Head->left) == NULL))
{
 Table[Head->s]=code;   
}
if(!code.empty()) code.pop_back();
}

};

void Haffman :: PrintMap()
{
    for(auto it = CharMap.begin(); it!= CharMap.end(); it++)
    {
        cout << it-> first << " - " << it -> second << endl;
    }
}

void Haffman :: CreateMap(char *s)
{
int i = 0;
while (s[i] != '\0')
{
CharMap[s[i]]=0;
i++;
}
i = 0;
while (s[i] != '\0')
{
CharMap[s[i]]++;
i++;
}
}

Uzel* Haffman :: CreateList()
{
for(auto it = CharMap.begin(); it!= CharMap.end(); it++)
{
Uzel *p = new Uzel(it->first,it->second);
List.push_back(p);
}
while(List.size() != 1)
{
List.sort(comp);
Uzel *R=List.front();
List.pop_front();
Uzel *L=List.front();
List.pop_front();
Uzel *p= new Uzel(L,R);
List.push_back(p);
}
//cout « (List.front()->left->left->s);

return List.front();
}

int main(void)
{
Haffman a;
char b[]={"abcdefasdasdbasdasdasczxc"};
a.CreateMap(b);
a.Tree(a.CreateList());
a.PrintMap();
for(auto it = Table.begin(); it!= Table.end(); it++)
{
 cout << it->first;
show_vector(it->second);
cout << endl;
}
}
