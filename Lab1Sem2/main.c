#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//Название книги 2 автор 3 год издания 4 язык

enum language {
    Russian,
    English,
    Chinese,
    Spanish,
    Arabic,
    Other
};

struct Book {
    char* name;
    char* author;
    int year;
    enum language language;
};

static char* LanguageName[] =
        {
                "Russian",
                "English",
                "Chinese",
                "Spanish",
                "Arabic",
                "Other"
        };

char* getString() {
    int maxLength = 16;
    int length = 0;
    char* str = malloc(maxLength * sizeof(char));
    int i = getchar(); // используем переменную типа int
    char c; // создаем переменную типа char
    while (i != '\n') {
        c = (char)i; // явно приводим тип int к типу char
        str[length] = c;
        length++;

        if (length >= maxLength) {
            maxLength += 2;
            str = realloc(str, maxLength * sizeof(char));
        }

        i = getchar();
    }

    str[length] = '\0';

    return str;
}

void printStruct(struct Book* books,const int* n)
{
    for (int i = 0; i < *n; i++) {
        printf("Enter name #%d book::", i + 1);
        getchar();
        books[i].name = getString();

        printf("Enter author #%d book::", i + 1);
        books[i].author = getString();

        printf("Enter year #%d book::", i + 1);
        scanf_s("%d", &books[i].year);

        printf("Enter language::(0 - Rus; 1 - Eng; 2 - Chin; 3 - Span; 4 - Arab; 5 - Oth.)::");
        scanf_s("%d", &books[i].language);
    }
}

void outputStruct(struct Book* books,const int* n)
{
    for (int i = 0; i < *(n); i++)
    {
        printf("Name:%s\t Author:%s\t Year:%d\t Language:%s\n", books[i].name, books[i].author, books[i].year, LanguageName[books[i].language]);
    }
}

void sortStructByName(struct Book* books, const int* size)
{
    int flag;
    struct Book swap;
    for (int gap = *(size) / 2; gap > 0; gap /= 2)
    {
        do
        {
            flag = 0;
            for (int i = 0, j = gap; j < *size; i++, j++)
            {
                int cmp = strcmp(books[i].name, books[j].name);
                if (cmp > 0 || (cmp == 0 && strcmp(books[i].author, books[j].author) > 0))
                {
                    swap = books[j];
                    books[j] = books[i];
                    books[i] = swap;
                    flag = 1;
                }
            }
        } while (flag);
    }
}

void sortStructByAuthor(struct Book* books,const int* size) {
    {
        int flag;
        struct Book swap;
        for (int gap = *(size) / 2; gap > 0; gap /= 2) {
            do {
                flag = 0;
                for (int i = 0, j = gap; j < *size; i++, j++) {
                    int cmp = strcmp(books[i].author, books[j].author);
                    if (cmp > 0 || (cmp == 0 && books[i].year > books[j].year)) {
                        swap = books[j];
                        books[j] = books[i];
                        books[i] = swap;
                        flag = 1;
                    }
                }
            } while (flag);
        }
    }
}

void sortStructByYear(struct Book* books,const int* size)
{
    {
        int flag;
        struct Book swap;
        for (int gap = *(size) / 2; gap > 0; gap /= 2)
        {
            do
            {
                flag = 0;
                for (int i = 0, j = gap; j < *size; i++, j++)
                {
                    if ( books[i].year > books[j].year || (books[i].year - books[j].year == 0 && books[i].name > books[j].name)) {
                        swap = books[j];
                        books[j] = books[i];
                        books[i] = swap;
                        flag = 1;
                    }
                }
            } while (flag);
        }
    }
}

void sortStructByLanguage(struct Book* books,const int* size)
{
    {
        int flag;
        struct Book swap;
        for (int gap = *(size) / 2; gap > 0; gap /= 2)
        {
            do
            {
                flag = 0;
                for (int i = 0, j = gap; j < *size; i++, j++)
                {
                    if ( books[i].language > books[j].language || (books[i].language - books[j].language == 0 && books[i].name > books[j].name)) {
                        swap = books[j];
                        books[j] = books[i];
                        books[i] = swap;
                        flag = 1;
                    }
                }
            } while (flag);
        }
    }
}

void deleteStruct(struct Book* books, int* n)
{
    int x;
    printf("Enter the number delete struct::");
    scanf_s("%d", &x);
    struct Book temp;
    for (int i = x - 1; i < *(n) - 1; i++)
    {
        temp = books[i + 1];
        books[i + 1] = books[i];
        books[i] = temp;
    }
    *n = *n - 1;
    books = (struct Book*)realloc(books, *n * sizeof(struct Book));
}

int menu()
{
    int arg;
    printf("Enter:\n");
    printf("1 - To sort the structure by book title\n");
    printf("2 - To sort the structure by author name\n");
    printf("3 - To sort the structure by year of issue\n");
    printf("4 - To sort the structure by language\n");
    printf("5 - To delete a structure by book number\n");
    printf("6 - To exit the program\n");

    scanf_s("%d", &arg);
    return arg;
}


int main()
{
    int n;

    printf("Enter the number of books to add::");
    scanf_s("%d", &n);
    int* pn = &n;
    printf("%d", *pn);

    struct Book* books;
    books = (struct Book*)malloc(n * sizeof(struct Book));
    printStruct(books, pn);
    outputStruct(books, pn);

    while (1)
    {
        switch (menu())
        {
            case 1:
                sortStructByName(books, pn);
                outputStruct(books, pn);
                break;
            case 2:
                sortStructByAuthor(books, pn);
                outputStruct(books, pn);
                break;
            case 3:
                sortStructByYear(books, pn);
                outputStruct(books, pn);
                break;
            case 4:
                sortStructByLanguage(books, pn);
                outputStruct(books, pn);
                break;
            case 5:
                deleteStruct(books, pn);
                outputStruct(books, pn);
                break;
            case 6:
                return 0;
        }
    }
}
