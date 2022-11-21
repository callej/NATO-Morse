#include <stdio.h>
#include <ctype.h>
#include <windows.h>

#define SIZE 128

#define BOLD "\x1b[1m"
#define UNDERLINE "\x1b[4m"
#define REVERSED "\x1b[7m"
#define TXT "\x1b[38;2;255;0;0;48;2;212;175;55m"
#define NORMAL "\x1b[m"

#define DOT 1
#define DASH 3
#define SYMBOL_SPACE 1
#define LETTER_SPACE 3
#define WORD_SPACE 7
#define WPM 20        // Words per minute (PARIS)
#define LENGTH 1200 / WPM
#define TONE 400

void print_nato(char *phrase)
{
    const char *nato[] = {
        "Alfa", "Bravo", "Charlie", "Delta", "Echo", "Foxtrot",
        "Golf", "Hotel", "India", "Juliett", "Kilo", "Lima",
        "Mike", "November", "Oscar", "Papa", "Quebec", "Romeo",
        "Sierra", "Tango", "Uniform", "Victor", "Whiskey",
        "Xray", "Yankee", "Zulu"
    };

    const char *ndigit[] = {
        "Zero", "One", "Two", "Three", "Four",
        "Five", "Six", "Seven", "Eight", "Nine"
    };
    
    char ch;
    int i;
 
     i = 0;
    while (phrase[i])
    {
        ch = toupper(phrase[i]);
        if (isalpha(ch))
            printf("%s%s %s %s", BOLD, TXT, nato[ch-'A'], NORMAL);
        else if (isdigit(ch))
            printf("%s%s %s %s", BOLD, TXT, ndigit[ch-'0'], NORMAL);
        else if (ch == ' ')
            printf(" ");
        i++;
        if ( i==SIZE )
            break;
    }
    putchar('\n');
}

void send_code(const char *code)
{
    int i = 0;

    while (code[i])
    {
        if (code[i] == '.')
            Beep(TONE, DOT * LENGTH);
        else
            Beep(TONE, DASH * LENGTH);
        Sleep(SYMBOL_SPACE * LENGTH);
        i++;
    }
    
}

void send_morse(char *phrase)
{
    const char *morse[] = {
        ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....",
        "..", ".---", "-.-.", ".-..", "--", "-.", "---", ".--.",
        "--.-", ".-.", "...", "-", "..-", "...-", ".--", "-..-",
        "-.--", "--.."
    };

    const char *mdigit[] = {
        "-----", ".----", "..---", "...--", "....-",
        ".....", "-....", "--...", "---..", "----."
    };

    char ch;
    int i;

     i = 0;
    while (phrase[i])
    {
        ch = toupper(phrase[i]);
        if (isalpha(ch))
        {
            printf("%c: %s\n", ch, morse[ch-'A']);
            send_code(morse[ch-'A']);
            Sleep((LETTER_SPACE - SYMBOL_SPACE) * LENGTH);
        }
        else if (isdigit(ch))
        {
            printf("%c: %s\n", ch, mdigit[ch-'0']);
            send_code(mdigit[ch-'0']);
            Sleep((LETTER_SPACE - SYMBOL_SPACE) * LENGTH);
        }
        else if (ch == ' ')
        {
            printf("\n");
            Sleep((WORD_SPACE - LETTER_SPACE) * LENGTH);
        }
        i++;
        if ( i==SIZE )
            break;
    }
    putchar('\n');
}
 
int main()
{
    char phrase[SIZE];

    printf("Enter a word or phrase: ");
    fgets(phrase,SIZE,stdin);
    print_nato(phrase);
    send_morse(phrase);

    return(0);
}