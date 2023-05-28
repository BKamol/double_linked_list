#include <fstream>
#include <iostream>
#include <string>

using namespace std;

struct elem
{
    int info;
    elem* next;
};

struct elem2
{
    int info;
    elem2* prev;
    elem2* next;
};

elem* create_list(string file_name)
{
    ifstream in(file_name);
    //пустой первый элемент
    elem* top = new elem;
    top->info = -1;
    top->next = NULL;

    elem* p = top;
    int i = 0;
    while (in >> i)
    {
        p->next = new elem;
        p = p->next;
        p->info = i;
    }
    p->next = NULL;
    return top;
}

void show(elem* top)
{
    if (top == NULL) cout << "Empty" << endl;
    top = top->next;
    while (top != NULL)
    {
        cout << top->info << ' ';
        top = top->next;
    }
    cout << endl;
}

elem2* transform(elem* top)
{
    elem2* top1;
    elem2* p1;

    top1 = new elem2;
    top1->info = top->next->info;
    top1->prev = NULL;
    top = top->next;
    p1 = top1;

    while (top->next != NULL)
    {
        p1->next = new elem2;
        p1->next->prev = p1;
        p1 = p1->next;
        p1->info = top->next->info;
        top = top->next;
    }
    p1->next = NULL;
    return top1;
}

void show(elem2* top)
{
    if (top == NULL) cout << "Empty";
    while (top != NULL)
    {
        cout << top->info << " ";
        top = top->next;
    }
    cout << endl;
}

void del(elem2* &top)
{
    while (top->next != NULL)
    {
        top = top->next;
        delete top->prev;
    }
    delete top;
    top = NULL;

}

void del_x(elem2* &top, int x)
{
    elem2* q;
    elem2* p;

    while (top->next != NULL && top->next->info == x)
    {
        top = top->next;
        delete top->prev;
        top->prev = NULL;
    }
    p = top;
    while (p->next != NULL) //обработка середины
    {
        if (p->next->info == x)
        {
            q = p;
            q->prev->next = q->next;
            q->next->prev = q->prev;
            p = p->next;
            delete q;
        }
        else
        {
            p = p->next;
        }
    }

    
}

void insert_y_after_x(elem2* top, int x, int y)
{
    elem2* p = top;
    elem2* q;
    while (p->next != NULL)
    {
        if (p->info == x)
        {
            q = p->next;
            p->next = new elem2;
            p->next->prev = p;
            p = p->next;
            p->info = y;
            p->next = q;
        }
        p = p->next;
    }
    if (p->info == x)
    {
        p->next = new elem2;
        p->next->prev = p;
        p = p->next;
        p->info = y;
        p->next = NULL;
    }

}

elem* create_cirlce(string file_name)
{
    ifstream in(file_name);

    elem* top;
    top = new elem;
    int info;
    in >> top->info;
    elem* p = top;

    while (in >> info)
    {
        p->next = new elem;
        p = p->next;
        p->info = info;
    }
    p->next = top;

    in.close();

    return top;
}

void show(elem* top, int circle_len)
{
    for (int i = 0; i < circle_len; i++)
    {
        cout << top->info << ' ';
        top = top->next;
    }
    cout << endl;
}

void del(elem* &top)
{
    elem* q = NULL;
    if (top != NULL)
    {
        q = top;
        top = top->next;
        q->next = NULL;
    }

    while (top != NULL)
    {
        q = top;
        top = top->next;
        delete q;
    }

}

void del_circle(elem* top, int p)
{
    elem* q;
    int n = 10;
    if (top == NULL) cout << "Empty" ;
    while (top != top->next)
    {

        for (int i = 0; i < p-1; i++)
        {
            top = top->next;
        }
        q = top->next;
        top->next = q->next;
        //cout << q->info << ' ';
        show(top, --n);
        delete q;
    }
    cout << top->info << endl;
    delete top;

}

int main()
{
    elem* top1 = create_list("nums1.txt");
    //show(top1);

    elem2* top2 = transform(top1);
    show(top2);

    //del(top2);
    //show(top2);

    //del_x(top2, 1);
    //show(top2);

    //insert_y_after_x(top2, 1, 1);
    //show(top2);

    elem* circle = create_cirlce("nums1.txt");
    show(circle, 10);

    //del(circle);
    del_circle(circle, 2);

}

