#include <iostream>
#include <fstream>
#include <string>
#include<cstring>
using namespace std;
void Addbook(fstream &f);
int Search (fstream &f, string x);
void Readrecord(int &index,fstream &f);
void Writefield (char* word,fstream &f);
void printAll (fstream &f);
void printBook (fstream &f,string x);
void Delete (fstream &f,string x);
struct Book
{
    char ISBN[100];
    char title[100];
    char author[100];
    char year[100];
    char numofpages[100];
    char price[100];
};
ostream& operator<<(ostream & os, Book &b)
{
    os << "ISBN: " << b.ISBN<<" Book Title: "<<b.title <<" Author Name: "<<b.author<<" Year: "<<b.year;
    os << " Number of pages: " << b.numofpages << " Price: " <<b.price<< endl;
    return os;
}
int main()
{
    fstream f;
    f.open("test.txt",ios::in|ios::out|ios::binary );
    //while (true)
    //{
        cout << "1) Add Book\n2) Delete Book\n3) Update Book\n4) Print Book\n5) Print all Books\n0) Exit";
        int choice;
        cin >> choice;
        cin.ignore();
        if (choice==1)
            {Addbook(f);}
        else if (choice==2)
        {
            string word ;
            cout << "Enter ISBN: ";
            cin >> word;
            Delete(f,word);
        }
        else if (choice==3)
        {
            string word ;
            cout << "Enter ISBN: ";
            getline(cin,word);
            Delete(f,word);
            Addbook(f);
        }
        else if (choice==4)
        {
            string word2 ;
            cout << "Enter Title: ";
            getline(cin,word2);
            printBook(f,word2);
        }
        else if (choice==5)
        {
            printAll(f);
        }
       /* else
            break;
    }*/
    //Addbook(f);
    //printAll(f);
    //printBook(f,"book title1");
    //Delete(f,"22222");
    return 0;
}

void Readrecord(int &index,fstream &f)
{
    Book record;
    short length;
    char del[1];
    f.seekg(index,ios::beg);
    f.read((char*)&length,sizeof(length));
    f.read(record.ISBN , length);
    record.ISBN[length]='\0';
    f.read((char*)&length,sizeof(length));
    f.read(record.title,length);
    record.title[length]='\0';
    f.read((char*)&length,sizeof(length));
    f.read(record.author,length);
    record.author[length]='\0';
    f.read((char*)&length,sizeof(length));
    f.read(record.price,length);
    record.price[length]='\0';
    f.read((char*)&length,sizeof(length));
    f.read(record.year,length);
    record.year[length]='\0';
    f.read((char*)&length,sizeof(length));
    f.read(record.numofpages,length);
    record.numofpages[length]='\0';
    f.read(del,1);
    if (del[0] != '*')
        cout << record;
    index= f.tellg();
}
void printAll (fstream &f)
{
    string sent ;
    f.seekg(0,ios::beg);
    int index=0;
    while (getline(f,sent))
        Readrecord(index,f);
}
void Delete (fstream &f,string x)
{
    int index=Search(f,x);
    if (index == -1)
        cout << "Not found..";
    else
    {
        char * buffer=new char[100];
        short length;
        char* deletesign="*";
        f.seekg(index,ios::beg);
            f.read((char*)&length,sizeof(length));
            f.read(buffer , length);
            buffer[length-1]='\0';
        for (int i=0; i<5; i++)
        {
            f.read((char*)&length,sizeof(length));
            f.read(buffer , length);
            buffer[length]='\0';
        }
        index=f.tellg();
        f.seekp(index,ios::beg);
        f.seekp(index,ios::beg);
        f<< '*';
    }
}
int Search (fstream &f, string x)
{
    char * buffer=new char[100];
    short length;
    char* del=new char[5];
    while (!f.fail())
    {
        f.read(del,1);
        del[1]='\0';
        string y= "|",d="*";
        if (del ==d)
            continue;
        if (del != y && del !=d)
            f.seekg(-1,ios::cur);
        f.read((char*)&length,sizeof(length));
        f.read(buffer , length);
        buffer[length]='\0';
        if (buffer==x)
        {
            f.seekg(-(length+2),ios::cur);
            return f.tellg();
        }
    }
    return f.tellg();
}
void printBook (fstream &f,string x)
{
    int index = Search(f,x);
    if (index == -1)
        cout << "Not found..";
    else
    {
        index=index-7;
        Readrecord(index,f);
    }
}
/*void Addbook(fstream &f)
{
    f.seekp(0,ios::end);
    Book record;
    char*del ="|";
    cout << "Enter Book ISBN: ";
    cin.getline(record.ISBN,100);
    cout << "Enter Book title: ";
    cin.getline(record.title,100);
    cout << "Enter Author Name: ";
    cin.getline(record.author,100);
    cout << "Enter Book price: ";
    cin.getline(record.price,100);
    cout << "Enter Book Year: ";
    cin.getline(record.year,100);
    cout << "Enter number of book pages: ";
    cin.getline(record.numofpages,100);
    Writefield(record.ISBN ,f);
    Writefield(record.title ,f);
    Writefield(record.author,f);
    Writefield(record.price,f);
    Writefield(record.year,f);
    Writefield(record.numofpages,f);
    f.write(del,1);
    f.close();
}*/
void Addbook(fstream &f)
{
    cin.ignore();
    f.seekp(0,ios::end);
    Book record;
    char*del ="|";
    cout << "Enter Book ISBN: ";
    cin.getline(record.ISBN,100);
    cout << "Enter Book title: ";
    cin.getline(record.title,100);
    cout << "Enter Author Name: ";
    cin.getline(record.author,100);
    cout << "Enter Book price: ";
    cin.getline(record.price,100);
    cout << "Enter Book Year: ";
    cin.getline(record.year,100);
    cout << "Enter number of book pages: ";
    cin.getline(record.numofpages,100);
    Writefield(record.ISBN ,f);
    Writefield(record.title ,f);
    Writefield(record.author,f);
    Writefield(record.price,f);
    Writefield(record.year,f);
    Writefield(record.numofpages,f);
    f.write(del,1);
    //f.close();
}

void Writefield (char* word,fstream &f)
{
    short length = strlen(word);
    f.write((char*)&length, sizeof(length));
    f.write(word, length);
}
