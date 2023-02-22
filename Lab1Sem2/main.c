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
        scanf("%d", &books[i].year);

        printf("Enter language::(0 - Rus; 1 - Eng; 2 - Chin; 3 - Span; 4 - Arab; 5 - Oth.)::");
        scanf("%d", &books[i].language);
    }
}

void outputStruct(struct Book* books,const int* n)
{
    for (int i = 0; i < *n; i++)
    {
        if (i >= 0 && i < *n)
            printf("\tName:%s\t Author:%s\t Year:%d\t Language:%s\n", books[i].name, books[i].author, books[i].year, LanguageName[books[i].language]);
    }
}

int compareByName(struct Book book1, struct Book book2)
{
    int cmp = strcmp(book1.name, book2.name);
    if (cmp == 0)
    {
        return strcmp(book1.author, book2.author);
    }
    return cmp;
}

int compareByAuthor(struct Book book1, struct Book book2)
{
    int cmp = strcmp(book1.author, book2.author);
    if (cmp == 0)
    {
        return book1.year - book2.year;
    }
    return cmp;
}

int compareByYear(struct Book book1, struct Book book2)
{
    int cmp = book1.year - book2.year;
    if (cmp == 0)
    {
        return strcmp(book1.name, book2.name);
    }
    return cmp;
}

int compareByLanguage(struct Book book1, struct Book book2)
{
    int cmp = book1.language - book2.language;
    if (cmp == 0)
    {
        return strcmp(book1.name, book2.name);
    }
    return cmp;
}

void sortStruct(struct Book* books, const int* size, int key)
{
    struct Book swap;
    int gap = *size / 2;

    while (gap > 0) {

        for (int i = 0, j = gap; j < *size; i++, j++) {
            int cmp = 0;
            if (key == 1) {
                cmp = compareByName(books[i], books[j]);
            }
            else if (key == 2) {
                cmp = compareByAuthor(books[i], books[j]);
            }
            else if (key == 3) {
                cmp = compareByYear(books[i], books[j]);
            }
            else if (key == 4) {
                cmp = compareByLanguage(books[i], books[j]);
            }

            if (cmp > 0) {
                swap = books[j];
                books[j] = books[i];
                books[i] = swap;
            }
        }

        gap /= 2;
    }
}


void deleteStruct(struct Book** books, int* n)
{
    int x;
    printf("Enter the number of the struct to delete:");
    scanf("%d", &x);
    if (x < 1 || x > *n) {
        printf("Invalid input\n");
        return;
    }
    for (int i = x - 1; i < *n - 1; i++)
    {
        (*books)[i] = (*books)[i + 1];
    }
    *n = *n - 1;
    struct Book* temp = (struct Book*)realloc(*books, *n * sizeof(struct Book));
    if (temp != NULL) {
        *books = temp;
    } else {
        printf("Error: memory allocation failed.\n");
        return;
    }
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

    scanf("%d", &arg);
    return arg;
}


int main()
{
    int n;

    printf("Enter the number of books to add::");
    scanf("%d", &n);
    int* pn = &n;

    struct Book* books;
    books = (struct Book*)malloc(n * sizeof(struct Book));
    printStruct(books, pn);
    outputStruct(books, pn);

    while (1)
    {
        switch (menu())
        {
            case 1:
                sortStruct(books, pn,1);
                outputStruct(books, pn);
                break;
            case 2:
                sortStruct(books, pn,2);
                outputStruct(books, pn);
                break;
            case 3:
                sortStruct(books, pn,3);
                outputStruct(books, pn);
                break;
            case 4:
                sortStruct(books, pn,4);
                outputStruct(books, pn);
                break;
            case 5:
                deleteStruct(&books, pn);
                outputStruct(books, pn);
                break;
            case 6:
                printf("Exiting program\n");
                free(books);
                exit(0);
                break;

            default:
                printf("Invalid input\n");
                break;
        }
    }
}
