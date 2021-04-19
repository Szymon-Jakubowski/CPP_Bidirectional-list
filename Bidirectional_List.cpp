#include <time.h>
#include <stdlib.h>

template <typename T>
class MyList
{
    public:
        MyList()
        {
            first = NULL;
            last = NULL;
            n = 0;
        }
        ~MyList()
        {
            clearAll();
        }

        int getSize() { return n; }

        void addAfter(const T& data, int index)
        {
            if (index >= 0 && index < n - 1)
            {
                MyElement<T>* newElement = new MyElement<T>();
                newElement->data = data;
                newElement->prev = NULL;
                newElement->next = NULL;

                MyElement<T>* curElement = first;

                for (int i = 0; i < n - 1; i++)
                {
                    if (i == index)
                    {
                        break;
                    }
                    curElement = curElement->next;
                }

                MyElement<T>* prevElement = curElement;
                MyElement<T>* nextElement = curElement->next;
                prevElement->next = newElement;
                newElement->prev = prevElement;
                newElement->next = nextElement;
                nextElement->prev = newElement;

                n++;
            }
        }
        // a)
        void addL(const T& data) 
        {
            MyElement<T>* newElement = new MyElement<T>();
            newElement->data = data;
            newElement->prev = NULL;
            newElement->next = NULL;

            if (n == 0)
            {
                first = newElement;
                last = newElement;
            }
            else
            {
                MyElement<T>* tmp = last;
                tmp->next = newElement;
                newElement->prev = tmp;
                last = newElement;
            }

            n++;
        }
        // b)
        void addF(const T& data)
        {
            MyElement<T>* newElement = new MyElement<T>();
            newElement->data = data;
            newElement->prev = NULL;
            newElement->next = NULL;

            if (n == 0)
            {
                first = newElement;
                last = newElement;
            }
            else
            {
                MyElement<T>* tmp = first;
                tmp->prev = newElement;
                newElement->next = tmp;
                first = newElement;
            }

            n++;
        } 
        // c)
        void delL() 
        {
            if (n>0)
            {
                if (n == 1)
                {
                    delete first;
                    first = nullptr;
                    last = nullptr;
                }
                else
                {
                    MyElement<T>* tmp = last->prev;
                    tmp->next = NULL;
                    delete last;
                    last = tmp;
                }
                n--;
            }
        } 
        // d)
        void delF() 
        {
            if (n>0)
            {
                if (n < 2)
                {
                    delete first;
                    first = NULL;
                    last = NULL;
                }
                else
                {
                    MyElement<T>* tmp = first->next;
                    tmp->prev = NULL;
                    delete first;
                    first = tmp;
                }

                n--;
            }
        }
        // e)
        T getDataFromIndex(int index)
        {
            if (index >= n || n < 0)
            {
                std::cout << "Index nieprawidlowy" << std::endl;
            }
            else
            {
                MyElement<T>* curElement = first;
                for (int i = 0; i < n - 1; i++)
                {
                    if (i == index) break;
                    curElement = curElement->next;
                }

                return curElement->data;
                //std::cout << "Index: " << index << ", " << curElement->data << std::endl;
            }
        }
        // f)
        void swapIndex(int index, const T& data) 
        {
            if (index >= n)
            {
                std::cout << "Index nieprawidlowy" << std::endl;
            }
            else
            {
                MyElement<T>* curElement = first;
                for (int i = 0; i < n - 1; i++)
                {
                    if (i == index) break;
                    curElement = curElement->next;
                }

                curElement->data = data;
                std::cout << "Index: " << index << ", Podmieniono" << std::endl;
            }
        }
        // g) //Do poprawy dla template
        MyElement<T>* search(const T& data) 
        {
            int i = 0;
            MyElement<T>* curElement = first;
            bool isFound = false;

            for (i = 0; i < n - 1; i++)
            {
                if (curElement->data == data)
                {
                    isFound = true;
                    break;
                }
                curElement = curElement->next;
            }

            if (isFound)
            {
                std::cout << "Index: " << i << " zwracam." << std::endl;
                return curElement;
            }
            else
            {
                std::cout << "Nie znaleziono." << std::endl;
                return NULL;
            }
        }
        // h) //Do poprawy dla template
        bool searchAndDestroy(const T& wzorzec) 
        {
            int i;
            MyElement<T>* curElement = first;
            bool isFound = false;

            for (i = 0; i < n; i++)
            {
                if (curElement->data == wzorzec)
                {
                    isFound = true;
                    break;
                }
                curElement = curElement->next;
            }

            if (isFound)
            {
                if (curElement->next == NULL) delL();
                else if (curElement->prev == NULL) delF();
                else
                {
                    MyElement<T>* tempPrev = curElement->prev;
                    MyElement<T>* tempNext = curElement->next;
                    delete curElement;
                    tempPrev->next = tempNext;
                    tempNext->prev = tempPrev;
                }

                n--;
                return true;
            }
            else
            {
                return false;
            }
        }
        // i) //Do poprawy dla template
        void filterAdd(const T& data)
        {
            MyElement<T>* curElement = first; 
          
            for (int i = 0; i < n; i++)
            {
                if (data > curElement->data) {
                    addAfter(data, i);
                    break;
                }
                curElement = curElement->next;
            }
        }
        // j)
        void clearAll()
        {
            while (n > 0) delL();
        }
        // k)
        void printAll()   
        {
            static int CAP_OF_ELEMENTS_TO_SHOW = 3;
            MyElement<T>* curElement = first;
            for (int i = 0; i < n; i++)
            {
                if (i > CAP_OF_ELEMENTS_TO_SHOW - 1 && i < n - CAP_OF_ELEMENTS_TO_SHOW)
                {
                    curElement = curElement->next;
                    continue;
                }
                else 
                {                  
                    std::cout << "Index: " << i << ", " << curElement->data << std::endl;
                    curElement = curElement->next;
                }
            }
        }
    private:
        MyElement<T>* first, * last;
        int n;
};

template <typename T>
class MyElement
{
public:
    MyElement()
    {
        prev = NULL;
        next = NULL;
    }
    MyElement<T>* prev , * next;
    T data;
};

//using namespace
using namespace std;

struct some_object
{
public:
    some_object()
    {
        field_1 = 0;
        field_2 = 'a';
    }
    int field_1;
    char field_2;

    friend ostream& operator <<(ostream& os, const some_object& so)
    {
        os << "Int Field:" << so.field_1 << ", Char Field: " << so.field_2;
        return os;
    }
    friend bool operator ==(const some_object& first, const some_object& second)
    {
        if (first.field_1 == second.field_1 && first.field_2 == second.field_2) return true;
        else return false;
    }
    
    some_object& operator = (const some_object& so)
    {
        field_1 = so.field_1;
        field_2 = so.field_2;
        return *this;
    }

    friend bool operator > (const some_object& so1, const some_object& so2)
    {
        if (so1.field_2 < so2.field_2) return true;
        else return false;
    }
    friend bool operator < (const some_object& so1, const some_object& so2)
    {
        if (so1.field_2 > so2.field_2) return true;
        else return false;
    }
};

int main()
{
    srand(time(NULL));
    const unsigned int MAX_ORDER = 6;
    MyList<some_object> * lista = new MyList<some_object>();

    for (unsigned int o = 0; o < MAX_ORDER; o++)
    {
        const int SIZE = pow(10, o);
        // dodawanie do listy
        clock_t c1 = clock();
        for (int i = 0; i < SIZE; i++)
        {     
            some_object so;
            so.field_1 = rand() % 10000;
            so.field_2 = 'a' + rand() % 26;
   
            lista->addL(so);
        }
        clock_t c2 = clock();
        
        //wypisywanie
        double time = (c2 - c1) / (double)CLOCKS_PER_SEC;
        cout << "============================================" << endl;
        cout << "Tworzenie " << SIZE << " elementu/ow trwalo: " << time << " s" << endl;
        cout << "============================================" << endl;
        lista->printAll();
        // szukanie elementow
        const int ATTEMPTS = pow(10, 4);
        c1 = clock();
        for (int i = 0; i < ATTEMPTS; i++)
        {
            some_object so;
            so.field_1 = rand() % 10000;
            so.field_2 = 'a' + rand() % 26;
            lista->searchAndDestroy(so);
        }
        c2 = clock();
        time = (c2 - c1) / (double)CLOCKS_PER_SEC;
        cout << "============================================" << endl;
        cout << "Szukanie elementow trwalo: " << time << " s" << endl;
        lista->clearAll();
        cout << "============================================" << endl;
    }

    delete lista;
    return 0;
}


