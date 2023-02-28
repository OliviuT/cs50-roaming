#include <cs50.h>
#include <stdio.h>

int get_size(void);
void print_blanks(int size);
void print_char(int i);
void print_newline(void);

int main(void)
{
    //ask for pyramid size
    int size = get_size(), hash_size = 2;

    //print pyramid
    for (int i = 1; i != size + 1; i++)
    {
        print_blanks(size - i);
        print_char(i);
        print_blanks(hash_size);
        print_char(i);
        print_newline();
    }
}
//-----------------------------------------------------
int get_size(void)
{
    int size;
    do
    {
        size = get_int("how tall should the pyramids be? ");
    }
    while (size < 1 || size > 8);
    return size;
}
//-----------------------------------------------------
void print_blanks(int size)
{
    for (; 0 < size ; size--)
    {
        printf(" ");
    }
}
//-----------------------------------------------------
void print_char(int i)
{
    for (; 0 < i; i--)
    {
        printf("#");
    }
}
//-----------------------------------------------------
void print_newline(void)
{
    printf("\n");
}