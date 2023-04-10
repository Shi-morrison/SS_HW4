// Kristian Michel, Shian Morrison

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

typedef struct
{
    int kind;      // const = 1, var = 2
    char name[12]; // name up to 11 chars
    int val;       // number
    int level;     // L level
    int addr;
    int mark; // M address
} symbol;

/*token Struct*/
typedef struct
{
    char name[11]; // name up to 11 chars
    char token_type[33];
} token;

typedef struct
{
    int L;
    int M;
    char op[50];
} operator;

int emit(char op[], int L, int M, int *cx, operator text[])
{
    // printf("%d", *cx);
    strcpy(text[*cx].op, op); // opcode
    text[*cx].L = L;          // lexicographical level
    text[*cx].M = M;
    printf("code entered at adress %d: name: %s, Level: %d, M: %d\n", *cx, text[*cx].op, text[*cx].L, text[*cx].M); // modifier
    int jmpaddr = *cx;
    *cx = *cx + 1;

    return jmpaddr;
}
/*Creates a new token struct and copies information from the parameters into it. Then, we return it*/
token insert(char token_type[], char name[])
{
    token new;
    strcpy(new.name, name);
    strcpy(new.token_type, token_type);
    printf("\nSYMBOL GENERATED %s %s\n", new.token_type, new.name);
    return new;
}
/*Collects the word from the file and inputs it into the latest incrementing index of the token struct array. We use memset to clear the char array of the word*/
int reservedWordCheck(char word[], token tokenArray[], int j)
{
    if (strcmp(word, "const") == 0)
    {
        tokenArray[j] = insert("28", "const");
        memset(&word[0], 0, sizeof(word));
        j++;
    }
    else if (strcmp(word, "procedure") == 0)
    {
        tokenArray[j] = insert("30", "procedure");
        j++;
        memset(&word[0], 0, sizeof(word));
    }
    else if (strcmp(word, "call") == 0)
    {
        tokenArray[j] = insert("27", "call");
        j++;
        memset(&word[0], 0, sizeof(word));
    }
    else if (strcmp(word, "begin") == 0)
    {
        tokenArray[j] = insert("21", "begin");
        j++;
        memset(&word[0], 0, sizeof(word));
    }
    else if (strcmp(word, "end") == 0)
    {
        tokenArray[j] = insert("22", "end");
        j++;
        memset(&word[0], 0, sizeof(word));
    }
    else if (strcmp(word, "if") == 0)
    {
        tokenArray[j] = insert("23", "if");
        j++;
        memset(&word[0], 0, sizeof(word));
    }
    else if (strcmp(word, "then") == 0)
    {
        tokenArray[j] = insert("24", "then");
        j++;
        memset(&word[0], 0, sizeof(word));
    }
    else if (strcmp(word, "else") == 0)
    {
        tokenArray[j] = insert("33", "else");
        j++;
        memset(&word[0], 0, sizeof(word));
    }
    else if (strcmp(word, "while") == 0)
    {
        tokenArray[j] = insert("25", "while");
        j++;
        memset(&word[0], 0, sizeof(word));
    }
    else if (strcmp(word, "do") == 0)
    {
        tokenArray[j] = insert("26", "do");
        j++;
        memset(&word[0], 0, sizeof(word));
    }
    else if (strcmp(word, "read") == 0)
    {
        tokenArray[j] = insert("32", "read");
        j++;
        memset(&word[0], 0, sizeof(word));
    }
    else if (strcmp(word, "write") == 0)
    {
        tokenArray[j] = insert("31", "write");
        j++;
        memset(&word[0], 0, sizeof(word));
    }
    else if (strcmp(word, "var") == 0)
    {
        tokenArray[j] = insert("29", "var");
        j++;
        memset(&word[0], 0, sizeof(word));
    }
    else if (strcmp(word, "odd") == 0)
    {
        tokenArray[j] = insert("8", "odd");
        j++;
        memset(&word[0], 0, sizeof(word));
    }
    return j;
}
/*Collects the special symbol from the file and inputs it into the latest incrementing index of the token struct array. We use memset to clear the char array of the word*/
int specialSymbolCheck(char word[], token tokenArray[], int j)
{
    if (strcmp(word, "<>") == 0)
    {
        tokenArray[j] = insert("10", "<>");
        j++;
        memset(&word[0], 0, sizeof(word));
    }
    if (strcmp(word, ":=") == 0)
    {
        tokenArray[j] = insert("20", ":=");
        j++;
        memset(&word[0], 0, sizeof(word));
    }
    if (strcmp(word, "!=") == 0)
    {
        tokenArray[j] = insert("10", "!=");
        j++;
        memset(&word[0], 0, sizeof(word));
    }
    if (strcmp(word, "<=") == 0)
    {
        tokenArray[j] = insert("12", "<=");
        j++;
        memset(&word[0], 0, sizeof(word));
    }
    if (strcmp(word, "+") == 0)
    {
        tokenArray[j] = insert("4", "+");
        j++;
        memset(&word[0], 0, sizeof(word));
    }
    if (strcmp(word, "-") == 0)
    {
        tokenArray[j] = insert("5", "-");
        j++;
        memset(&word[0], 0, sizeof(word));
    }
    if (strcmp(word, "*") == 0)
    {
        tokenArray[j] = insert("6", "*");
        j++;
        memset(&word[0], 0, sizeof(word));
    }
    if (strcmp(word, "/") == 0)
    {
        tokenArray[j] = insert("7", "/");
        j++;
        memset(&word[0], 0, sizeof(word));
    }
    if (strcmp(word, "=") == 0)
    {
        tokenArray[j] = insert("9", "=");
        j++;
        memset(&word[0], 0, sizeof(word));
    }
    if (strcmp(word, "<") == 0)
    {
        tokenArray[j] = insert("11", "<");
        j++;
        memset(&word[0], 0, sizeof(word));
    }
    if (strcmp(word, ">") == 0)
    {
        tokenArray[j] = insert("13", ">");
        j++;
        memset(&word[0], 0, sizeof(word));
    }
    if (strcmp(word, ",") == 0)
    {
        tokenArray[j] = insert("17", ",");
        j++;
        memset(&word[0], 0, sizeof(word));
    }
    if (strcmp(word, ";") == 0)
    {
        tokenArray[j] = insert("18", ";");
        j++;
        memset(&word[0], 0, sizeof(word));
    }
    if (strcmp(word, ".") == 0)
    {
        tokenArray[j] = insert("19", ".");
        j++;
        memset(&word[0], 0, sizeof(word));
    }
    if (strcmp(word, "(") == 0)
    {
        tokenArray[j] = insert("15", "(");
        j++;
        memset(&word[0], 0, sizeof(word));
    }
    if (strcmp(word, ")") == 0)
    {
        tokenArray[j] = insert("16", ")");
        j++;
        memset(&word[0], 0, sizeof(word));
    }
    return j;
}

void insertSymbol(int kind, char name[], int val, int level, int addr, int *symbolTablePtr, symbol symbolTable[])
{
    symbol newSymbol;
    newSymbol.kind = kind;
    strcpy(newSymbol.name, name);
    newSymbol.val = val;
    newSymbol.level = level;
    newSymbol.addr = addr;
    newSymbol.mark = 1;
    symbolTable[*symbolTablePtr] = newSymbol;
    printf("new symbol added kind: %d , Name: %s, Val: %d, Level: %d, Addr: %d\n ", newSymbol.kind, newSymbol.name, newSymbol.val, newSymbol.level, newSymbol.addr);
    *symbolTablePtr = *symbolTablePtr + 1;
}

int symbolTableCheck(symbol symbolTable[], char name[])
{
    for (int i = 0; i < 500; i++)
    {
        if (strcmp(name, symbolTable[i].name) == 0)
        {
            return i;
        }
    }

    return -1;
}

token getToken(token tokenArray[], int *tokenArrayPtr)
{

    token returnToken;
    returnToken = tokenArray[*tokenArrayPtr];
    printf("\nCurrent token %s \n", returnToken.name);
    *tokenArrayPtr = *tokenArrayPtr + 1;
    return returnToken;
}

token constDeclaration(token tokenArray[], token token, int *tokenArrayPtr, symbol symbolTable[], int *symbolTablePtr)
{
    char name[50];
    int num, check = 0;

    if (strcmp(token.token_type, "28") == 0) // const sym
    {

        do
        {
            token = getToken(tokenArray, tokenArrayPtr);
            if (strcmp(token.token_type, "2") != 0) // identsym
            {
                printf("Error: Const keyword must be followed by identifier\n");
                exit(0);
            }
            if (symbolTableCheck(symbolTable, token.name) != -1)
            {
                printf("Symbol already exists\n");
                exit(0);
            }
            strcpy(name, token.name);
            token = getToken(tokenArray, tokenArrayPtr);

            if (strcmp(token.token_type, "9") != 0)
            {
                printf("Error: constants must be assigned with =\n"); // eqlsym
                exit(0);
            }
            token = getToken(tokenArray, tokenArrayPtr);
            if (strcmp(token.token_type, "3") != 0)
            {
                printf("Error: constants must be assigned an integer value\n");
                exit(0);
            }
            num = (int)strtol(token.name, (char **)NULL, 10);
            insertSymbol(1, name, num, 0, 0, symbolTablePtr, symbolTable);
            token = getToken(tokenArray, tokenArrayPtr);
        } while (strcmp(token.token_type, "17") == 0); // comma sym
        if (strcmp(token.token_type, "18") != 0)
        {
            printf("Error: constant declarations must be followed by a semicolon\n");
            exit(0);
        }
    }
    else
    {
        return token;
    }

    return getToken(tokenArray, tokenArrayPtr);
}

int varDeclaration(token tokenArray[], token token, int *tokenArrayPtr, symbol symbolTable[], int *symbolTablePtr, int level)
{
    int numVars = 0, check = 0;
    if (strcmp(token.token_type, "29") == 0)
    {
        check = 1;

        do
        {
            numVars++;
            token = getToken(tokenArray, tokenArrayPtr);
            if (strcmp(token.token_type, "2") != 0)
            {
                printf("Error: Var keyword must be followed by identifier\n");
                exit(0);
            }
            if (symbolTableCheck(symbolTable, token.name) != -1)
            {
                printf("Error: Symbol name has already been declared\n");
                exit(0);
            }
            insertSymbol(2, token.name, 0, level, (numVars + 2), symbolTablePtr, symbolTable);
            token = getToken(tokenArray, tokenArrayPtr);

        } while (strcmp(token.token_type, "17") == 0);
        if (strcmp(token.token_type, "18") != 0)
        {
            printf("Error: variable declarations must be followed by a semicolon\n");
            exit(0);
        }
        return numVars;
    }
    else
    {
        return check;
    }
}

token Expression(token tokenArray[], token token, symbol symbolTable[], int *tokenArrayPtr, int *cx, operator text[]);
token Factor(token tokenArray[], token token, symbol symbolTable[], int *tokenArrayPtr, int *cx, operator text[]);
token Term(token tokenArray[], token token, symbol symbolTable[], int *tokenArrayPtr, int *cx, operator text[]);
token Condition(token tokenArray[], token token, symbol symbolTable[], int *tokenArrayPtr, int *cx, operator text[]);
token Statement(token tokenArray[], token token, symbol symbolTable[], int *tokenArrayPtr, int *cx, operator text[]);
token Block(token tokenArray[], token token, symbol symbolTable[], int *tokenArrayPtr, int *symbolTablePtr, int *cx, operator text[]);

token proDeclaration(token tokenArray[], token token, int *tokenArrayPtr, symbol symbolTable[], int *symbolTablePtr, int *cx, operator text[], int level)
{

    while (strcmp(token.token_type, "30") == 0)
    { // procedure symbol

        token = getToken(tokenArray, tokenArrayPtr);
        if (strcmp(token.token_type, "2") != 0)
        { // identifer symbol
            printf("Error: procedure declarations must be followed by a identifier");
        }

        insertSymbol(3, token.name, 0, level, *cx + 1, symbolTablePtr, symbolTable);
        printf("In Procedure %s \n", token.name);
        token = getToken(tokenArray, tokenArrayPtr);
        if (strcmp(token.token_type, "18") != 0) // semi-colon
        {
            printf("Error: procedure declarations must be followed by a semicolon");
        }
        token = getToken(tokenArray, tokenArrayPtr);
        token = Block(tokenArray, token, symbolTable, tokenArrayPtr, symbolTablePtr, cx, text);
        if (strcmp(token.token_type, "18") != 0)
        {
            printf("Error: procedure declarations must be followed by a semicolon");
        }

        return token;
    }
}

int level = -1, tx = 0;

int main(int argc, char **argv)
{
    /*Creating a token array of 500 to store 500 words, we then create file pointers to loop through the file.*/
    token tokenArray[500];
    operator text[500];
    FILE *ptr, *printer_pointer, *output;
    char buffer[256], comment_checker[2] = {'.', '.'};
    // ptr = fopen("C:/Users/Shi-shi/Desktop/HW_3-desktop/input.txt", "r+");
    // printer_pointer = fopen("C:/Users/Shi-shi/Desktop/HW_3-desktop/input.txt", "r+");
    ptr = fopen(argv[1], "r+");
    printer_pointer = fopen(argv[1], "r+");

    // output = fopen("output.txt", "w+");
    /*Creating variables we use to loop through the input file*/
    int i = 0, j = 0, flag = 0;
    int cx_number = 0;
    int *cx = &cx_number;
    char c, d, e;
    char word[11];
    memset(&word[0], 0, sizeof(word));
    /*reserve words and special symbols we are looking for*/
    char reservedWords[15][20] = {"null", "begin", "call", "const", "do", "else", "end", "if", "odd", "procedure", "read", "then", "var", "while", "write"};
    char specialSymbols[16][3] = {"+", "-", "(", ")", "=", ",", ".", "<", ">", "$", ";", ">=", "<=", ":=", "<>", "*"};
    int error = 0;
    int validSymbol = 0;
    int reservedWord = 0;
    int comment = 0;
    /*goes through the file and checks to see if there's any comments that start and do not finish
      within the file*/
    while (!feof(printer_pointer))
    {
        c = fgetc(printer_pointer);

        if (strcmp(&c, "/") == 0 && flag == 0 && comment_checker[0] == 46 && comment_checker[1] == 46)
        {
            comment_checker[0] = '/';
            flag = 1;
            continue;
        }
        if (strcmp(&c, "*") == 0 && flag == 1 && comment_checker[0] == 47 && comment_checker[1] == 46)
        {
            comment_checker[1] = '*';
            flag = 2;
            continue;
        }
        if (strcmp(&c, "*") == 0 && flag == 2 && comment_checker[0] == 47 && comment_checker[1] == 42)
        {
            comment_checker[1] = '.';
            flag = 1;
            continue;
        }
        if (strcmp(&c, "/") == 0 && flag == 1 && comment_checker[0] == 47 && comment_checker[1] == 46)
        {
            comment_checker[0] = '.';
            flag = 0;
            continue;
        }
    }

    /*if flag variable does not reset to 0, that means there was an unfinished comemnt and we return an error.*/

    if (flag != 0)
    {
        printf("Error input ends during a comment\n");
        return 0;
    }

    /* loops through the file and checks for error cases*/
    while (!feof(ptr))
    {
        validSymbol = 0;
        reservedWord = 0;
        if (error == 1)
        {
            break;
        }
        error = 0;
        comment = 0;
        i = 0;
        c = fgetc(ptr);
        /* if identifier is more than 11 characters, we return identifier too long error*/
        if (isalpha(c))
        {
            while (isalpha(c) || isdigit(c))
            {
                if (i > 10)
                {
                    printf("Error found: Identifier too long\n");
                    error = 1;
                    return 0;
                }
                word[i] = c;
                i++;
                c = fgetc(ptr);
            }
            for (i = 0; i < 15; i++)
            {
                if (strcmp(word, reservedWords[i]) == 0)
                {
                    j = reservedWordCheck(word, tokenArray, j);
                    reservedWord = 1;
                }
            }
            i = 0;
            if (reservedWord != 1)
            {
                tokenArray[j] = insert("2", word);
                j++;
                memset(&word[0], 0, sizeof(word));
                i = 0;
            }
            if (isdigit(c))
            {
                i = 0;
                /*if digit is longer than 5 digits, we return identifier longer than error*/
                while (isdigit(c))
                {
                    if (i > 4)
                    {
                        printf("Error found: Identifier too long\n");
                        error = 1;
                        return 0;
                    }
                    word[i] = c;
                    /*if the identifier is a character but contains numbers, we return an error*/
                    if (isalpha(c))
                    {
                        error = 1;
                        printf("Error found: Identifiers cannot start with a digit\n");
                        return 0;
                    }
                    i++;
                    c = fgetc(ptr);
                }
                if (error == 1)
                {
                    break;
                }
                else
                {
                    tokenArray[j] = insert("3", word);
                    j++;
                    memset(&word[0], 0, sizeof(word));
                    i = 0;
                }
            }
            /*if we find a blank or control block, we return our i (num of chars in a word counter) back to 0*/
            if (isblank(c) || iscntrl(c))
            {
                i = 0;
            }
            if (ispunct(c))
            {
                comment = 0;
                while (ispunct(c))
                {
                    if (comment == 1)
                    {
                        break;
                    }
                    word[i] = c;
                    i++;
                    if (c == 47)
                    {
                        d = fgetc(ptr);
                        if (d == 42)
                        {
                            d = fgetc(ptr);
                            while (d != 42)
                            {
                                d = fgetc(ptr);
                                if (d == 42)
                                {
                                    e = fgetc(ptr);
                                    if (e == 47)
                                    {
                                        comment = 1;
                                        break;
                                    }
                                    else
                                    {
                                        strcpy(&d, &e);
                                    }
                                }
                            }
                        }
                        else
                        {
                            break;
                        }
                    }
                    else
                    {
                        c = fgetc(ptr);
                    }
                }
                /*if we are not in a comment, we activate special symbol check to input the word into our token array*/
                if (comment == 1)
                {
                }
                else
                {
                    for (i = 0; i < 16; i++)
                    {
                        if (strcmp(word, specialSymbols[i]) == 0)
                        {
                            j = specialSymbolCheck(word, tokenArray, j);
                            i = 0;
                            validSymbol = 1;
                        }
                    }
                    if (validSymbol == 0)
                    {
                        printf("Error found: Invalid symbol\n");
                        return 0;
                    }
                }
            }
        }
        /*checks to see if we are looping through a commment, if we are we skip the comment*/
        else if (ispunct(c))
        {
            comment = 0;
            while (ispunct(c))
            {
                if (comment == 1)
                {
                    break;
                }
                word[i] = c;
                i++;
                if (c == 47)
                {
                    d = fgetc(ptr);
                    if (d == 42)
                    {
                        d = fgetc(ptr);
                        while (d != 42)
                        {
                            d = fgetc(ptr);
                            if (d == 42)
                            {
                                e = fgetc(ptr);
                                if (e == 47)
                                {
                                    comment = 1;
                                    break;
                                }
                                else
                                {
                                    strcpy(&d, &e);
                                }
                            }
                        }
                    }
                    else
                    {
                        break;
                    }
                }
                else
                {
                    c = fgetc(ptr);
                }
            }
            /*if we are not in a comment, we activate special symbol check to input the word into our token array*/
            if (comment == 1)
            {
            }
            else
            {
                for (i = 0; i < 16; i++)
                {
                    if (strcmp(word, specialSymbols[i]) == 0)
                    {
                        j = specialSymbolCheck(word, tokenArray, j);
                        // i = 0;
                        validSymbol = 1;
                    }
                }
                i = 0;
                if (validSymbol == 0)
                {
                    printf("Error found: Invalid symbol\n");
                    return 0;
                }
            }
        }
        else if (isdigit(c))
        {
            while (isdigit(c))
            {
                if (i > 4)
                {
                    printf("Error found: Digits too long\n");
                    return 0;
                    error = 1;
                }
                word[i] = c;
                i++;
                c = fgetc(ptr);
                if (isalpha(c))
                {
                    error = 1;
                    printf("Error found: Identifiers cannot start with a digit\n");
                    return 0;
                }
            }
            if (error == 1)
            {
                break;
            }
            else
            {
                tokenArray[j] = insert("3", word);
                j++;
                memset(&word[0], 0, sizeof(word));
                i = 0;
            }
            if (ispunct(c))
            {
                word[i] = c;
                for (i = 0; i < 15; i++)
                {
                    if (strcmp(word, specialSymbols[i]) == 0)
                    {
                        j = specialSymbolCheck(word, tokenArray, j);
                        i = 0;
                        validSymbol = 1;
                    }
                }
                if (validSymbol == 0)
                {
                    printf("Error found: Invalid comment\n");
                    return 0;
                }
            }
        }
    }
    if (error == 1)
    {
    }
    else
    {

        fclose(printer_pointer);
    }

    // PARSER CODE STARTS
    symbol symbolTable[500];

    symbolTable[0].kind = 3;
    symbolTable[0].val = 0;
    symbolTable[0].level = 0;
    symbolTable[0].addr = 3;
    symbolTable[0].mark = 1;
    strcpy(symbolTable->name, "main");

    int symbolTableNum = 1, tokenArrayNum = 0, numVars = 0, check = 0;
    int *symbolTablePtr = &symbolTableNum;
    int *tokenArrayPtr = &tokenArrayNum;

    token token = getToken(tokenArray, tokenArrayPtr); // First getToken in BLOCK

    token = Block(tokenArray, token, symbolTable, tokenArrayPtr, symbolTablePtr, cx, text);
    // if (strcmp(token.token_type, "19") != 0)
    // {
    //     printf("Error: Program must end with period\n");
    //     exit(0);
    // }
    printf("\nAssembly Code:\n");
    printf("Line  OP    L    M\n");

    // JMP IMPLEMENTED IN BLOCK
    // printf("%d    %.5s    %d    %d\n", 0, "JMP", 0, 3);

    for (int i = 0; i < *cx; i++)
    {
        printf("%.1d    %.4s    %.1d    %.1d\n", i + 1, text[i].op, text[i].L, text[i].M);
    }

    // emit("SYS", 0, 3, cx, text);
    // printf("%d    %.4s    %d    %d\n", *cx, text[*cx - 1].op, text[*cx - 1].L, text[*cx - 1].M);
    printf("\n");
    printf("Symbol Table:\n");
    printf("Kind | Name   |   Value | Level | Address | Mark\n");
    for (int j = 0; j < *symbolTablePtr; j++)
    {
        printf("%d      %5s  |     %d   |   %d    |   %d    |   %d\n", symbolTable[j].kind, symbolTable[j].name, symbolTable[j].level, symbolTable[j].val, symbolTable[j].addr, symbolTable[j].mark);
    }

    return 0;
}

token Expression(token tokenArray[], token token, symbol symbolTable[], int *tokenArrayPtr, int *cx, operator text[])
{

    if (strcmp(token.token_type, "5") == 0) // minussym
    {
        token = getToken(tokenArray, tokenArrayPtr);
        token = Term(tokenArray, token, symbolTable, tokenArrayPtr, cx, text);
        // EMIT NEG
        emit("NEG", 0, 0, cx, text);

        while ((strcmp(token.token_type, "4") == 0) || (strcmp(token.token_type, "5") == 0)) // plussym || minussym
        {
            if (strcmp(token.token_type, "4") == 0)
            {
                token = getToken(tokenArray, tokenArrayPtr);
                token = Term(tokenArray, token, symbolTable, tokenArrayPtr, cx, text);
                // EMIT ADD
                emit("OPR", 0, 1, cx, text);
            }
            else
            {
                token = getToken(tokenArray, tokenArrayPtr);
                token = Term(tokenArray, token, symbolTable, tokenArrayPtr, cx, text);
                // EMIT SUB
                emit("OPR", 0, 2, cx, text);
            }
        }
    }
    else
    {
        if (strcmp(token.token_type, "4") == 0) // plussym
        {
            token = getToken(tokenArray, tokenArrayPtr);
        }
        token = Term(tokenArray, token, symbolTable, tokenArrayPtr, cx, text);
        while ((strcmp(token.token_type, "4") == 0) || (strcmp(token.token_type, "5") == 0)) // plussym || minussym
        {
            if (strcmp(token.token_type, "4") == 0)
            {
                token = getToken(tokenArray, tokenArrayPtr);
                token = Term(tokenArray, token, symbolTable, tokenArrayPtr, cx, text);
                // EMIT ADD
                emit("OPR", 0, 1, cx, text);
            }
            else
            {
                token = getToken(tokenArray, tokenArrayPtr);
                token = Term(tokenArray, token, symbolTable, tokenArrayPtr, cx, text);
                // EMIT SUB
                emit("OPR", 0, 2, cx, text);
            }
        }
    }
    return token;
}

token Factor(token tokenArray[], token token, symbol symbolTable[], int *tokenArrayPtr, int *cx, operator text[])
{
    int symIdx;
    if (strcmp(token.token_type, "2") == 0)
    {
        symIdx = symbolTableCheck(symbolTable, token.name);
        if (symIdx == -1)
        {
            printf("Error: undeclared identifier\n");
            exit(0);
        }
        if (symbolTable[symIdx].kind == 1)
        {
            // EMIT LIT
            emit("LIT", 0, symbolTable[symIdx].val, cx, text);
        }
        else
        {
            // EMIT LOD

            emit("LOD", level, symbolTable[symIdx].addr, cx, text);
        }
        return getToken(tokenArray, tokenArrayPtr);
    }
    else if (strcmp(token.token_type, "3") == 0)
    {
        // EMIT LIT
        int num = (int)strtol(token.name, (char **)NULL, 10);
        emit("LIT", 0, num, cx, text);
        return getToken(tokenArray, tokenArrayPtr);
    }
    else if (strcmp(token.token_type, "15") == 0) // lparent
    {
        token = getToken(tokenArray, tokenArrayPtr);
        token = Expression(tokenArray, token, symbolTable, tokenArrayPtr, cx, text);
        if (strcmp(token.token_type, "16") != 0) // rparent
        {
            printf("Error: right parenthesis must follow left parenthesis\n");
            exit(0);
        }
        return getToken(tokenArray, tokenArrayPtr);
    }
    else
    {
        printf("Error: arithmetic equations must contain operands, parentheses, numbers, or symbols\n");
        exit(0);
    }
}

token Term(token tokenArray[], token token, symbol symbolTable[], int *tokenArrayPtr, int *cx, operator text[])
{

    token = Factor(tokenArray, token, symbolTable, tokenArrayPtr, cx, text);

    while ((strcmp(token.token_type, "6") == 0) || (strcmp(token.token_type, "7") == 0))
    {
        if (strcmp(token.token_type, "6") == 0) // Multisym
        {
            token = getToken(tokenArray, tokenArrayPtr);
            token = Factor(tokenArray, token, symbolTable, tokenArrayPtr, cx, text);
            // EMIT MULT
            emit("OPR", 0, 3, cx, text);
        }
        else if (strcmp(token.token_type, "7") == 0) // Slashsym
        {
            token = getToken(tokenArray, tokenArrayPtr);
            token = Factor(tokenArray, token, symbolTable, tokenArrayPtr, cx, text);
            // EMIT DIV
            emit("OPR", 0, 4, cx, text);
        }
    }
    return token;
}

token Condition(token tokenArray[], token token, symbol symbolTable[], int *tokenArrayPtr, int *cx, operator text[])
{
    if (strcmp(token.token_type, "8") == 0)
    { // ODDSYM
        token = getToken(tokenArray, tokenArrayPtr);
        token = Expression(tokenArray, token, symbolTable, tokenArrayPtr, cx, text);
        // EMIT ODD
        emit("ODD", 0, 0, cx, text);
    }
    else
    {
        token = Expression(tokenArray, token, symbolTable, tokenArrayPtr, cx, text);
        if (strcmp(token.token_type, "9") == 0)
        { // EQLSYM
            token = getToken(tokenArray, tokenArrayPtr);
            token = Expression(tokenArray, token, symbolTable, tokenArrayPtr, cx, text);
            // EMIT EQL
            emit("OPR", 0, 5, cx, text);
        }
        else if (strcmp(token.token_type, "10") == 0) // NEQSYM
        {
            token = getToken(tokenArray, tokenArrayPtr);
            token = Expression(tokenArray, token, symbolTable, tokenArrayPtr, cx, text);
            // EMIT NEQ
            emit("OPR", 0, 6, cx, text);
        }
        else if (strcmp(token.token_type, "11") == 0) // LESSYM
        {
            token = getToken(tokenArray, tokenArrayPtr);
            token = Expression(tokenArray, token, symbolTable, tokenArrayPtr, cx, text);
            // EMIT LSS
            emit("OPR", 0, 7, cx, text);
        }
        else if (strcmp(token.token_type, "12") == 0) // LEQSYM
        {
            token = getToken(tokenArray, tokenArrayPtr);
            token = Expression(tokenArray, token, symbolTable, tokenArrayPtr, cx, text);
            // EMIT LEQ
            emit("OPR", 0, 8, cx, text);
        }
        else if (strcmp(token.token_type, "13") == 0) // GTRSYM
        {
            token = getToken(tokenArray, tokenArrayPtr);
            token = Expression(tokenArray, token, symbolTable, tokenArrayPtr, cx, text);
            // EMIT GTR
            emit("OPR", 0, 9, cx, text);
        }
        else if (strcmp(token.token_type, "14") == 0) // GEQSYM
        {
            token = getToken(tokenArray, tokenArrayPtr);
            token = Expression(tokenArray, token, symbolTable, tokenArrayPtr, cx, text);
            // EMIT GEQ
            emit("OPR", 0, 10, cx, text);
        }
        else
        {
            printf("Error: condition must contain comparison operator");
            exit(0);
        }
    }
    return token;
}

token Statement(token tokenArray[], token token, symbol symbolTable[], int *tokenArrayPtr, int *cx, operator text[])
{
    int symIdx;
    if (strcmp(token.token_type, "2") == 0) // Identsym
    {
        symIdx = symbolTableCheck(symbolTable, token.name); // get token index
        if (symIdx == -1)
        {
            printf("Error: undeclared identifier %s \n", token.name); // check if symbol exists
            exit(0);
        }
        // if (symbolTable[symIdx].kind != 2)
        // {
        //     printf("Error: only variable values may be altered\n"); // check if symbol is a var
        //     exit(0);
        // }
        token = getToken(tokenArray, tokenArrayPtr);
        if (strcmp(token.token_type, "20") != 0) // BECOMES SYM
        {
            printf("Error: assignment statements must use :=\n");
            exit(0);
        }
        token = getToken(tokenArray, tokenArrayPtr);
        token = Expression(tokenArray, token, symbolTable, tokenArrayPtr, cx, text);
        // EMIT STO (M = table[symIdx].addr)
        emit("STO", level, symbolTable[symIdx].addr, cx, text);
        return token;
    }
    if (strcmp(token.token_type, "27") == 0) // CAllSYM
    {
        token = getToken(tokenArray, tokenArrayPtr);
        if (strcmp(token.token_type, "2") != 0) // Identsym
        {
            printf("Error: undeclared identifier after call\n");
        }
        symIdx = symbolTableCheck(symbolTable, token.name);
        if (symIdx == -1)
        {
            printf("Error: undeclared identifier %s \n", token.name); // check if symbol exists
            exit(0);
        }
        if (symbolTable[symIdx].kind == 3)
        {
            emit("CAL", level - symbolTable[symIdx].level, symbolTable[symIdx].addr, cx, text);
        }
        token = getToken(tokenArray, tokenArrayPtr);
    }
    if (strcmp(token.token_type, "21") == 0) // BEGINSYM
    {
        do
        {
            token = getToken(tokenArray, tokenArrayPtr);
            token = Statement(tokenArray, token, symbolTable, tokenArrayPtr, cx, text);
        } while (strcmp(token.token_type, "18") == 0); // SEMICOLONSYM
        if (strcmp(token.token_type, "22") != 0)       // ENDSYM
        {
            printf("Error: begin must be followed by end\n");
            exit(0);
        }
        token = getToken(tokenArray, tokenArrayPtr);
        return token;
    }
    if (strcmp(token.token_type, "23") == 0) // IFSYM
    {
        token = getToken(tokenArray, tokenArrayPtr);
        token = Condition(tokenArray, token, symbolTable, tokenArrayPtr, cx, text);
        // JPC = CODE INDEX
        // EMIT JPC
        int jpc = *cx;
        emit("JPC", 0, 0, cx, text);
        if (strcmp(token.token_type, "24") != 0) // THENSYM
        {
            printf("Error: if must be followed by then\n");
            exit(0);
        }
        token = getToken(tokenArray, tokenArrayPtr);
        token = Statement(tokenArray, token, symbolTable, tokenArrayPtr, cx, text);
        // CODE[JPCINDX].M = CODE INDEX
        text[jpc].M = *cx;
        return token;
    }
    if (strcmp(token.token_type, "25") == 0) // WHILESYM
    {
        token = getToken(tokenArray, tokenArrayPtr);
        // LoopIDX = Current code index
        int loopidx = *cx;
        token = Condition(tokenArray, token, symbolTable, tokenArrayPtr, cx, text);
        if (strcmp(token.token_type, "26") != 0) // DOSYM
        {
            printf("Error: while must be followed by do\n");
            exit(0);
        }
        token = getToken(tokenArray, tokenArrayPtr);
        // JpcIDX= current code index
        int jpcidx = *cx;
        //  EMIT JPC
        emit("JPC", 0, 0, cx, text);
        token = Statement(tokenArray, token, symbolTable, tokenArrayPtr, cx, text);
        // EMIT JMP (M=loopIDX)
        emit("JMP", 0, loopidx, cx, text);
        // code[jpcidx].M = current code index
        emit("JPC", 0, 0, loopidx, text);
        text[jpcidx].M = *cx;
        return token;
    }
    if (strcmp(token.token_type, "32") == 0) // READSYM
    {
        token = getToken(tokenArray, tokenArrayPtr);
        if (strcmp(token.token_type, "2") != 0) // IDENTSYM
        {
            printf("Error: Read keyword must be followed by identifier\n");
            exit(0);
        }
        symIdx = symbolTableCheck(symbolTable, token.name);
        if (symIdx == -1)
        {
            printf("Error: undeclared identifier");
            exit(0);
        }
        if (symbolTable[symIdx].kind != 2)
        {
            printf("Symbol not a var\n");
            exit(0);
        }
        token = getToken(tokenArray, tokenArrayPtr);
        // EMIT READ
        emit("SYS", 0, 2, cx, text);
        // EMIT STO (M = table[symidx].addr)
        emit("STO", level, symbolTable[symIdx].addr, cx, text);
        return token;
    }

    if (strcmp(token.token_type, "31") == 0) // WRITESYM
    {
        token = getToken(tokenArray, tokenArrayPtr);
        token = Expression(tokenArray, token, symbolTable, tokenArrayPtr, cx, text);
        // EMIT WRITE
        emit("SYS", 0, 1, cx, text);
        return token;
    }
    return token;
}
token Block(token tokenArray[], token token, symbol symbolTable[], int *tokenArrayPtr, int *symbolTablePtr, int *cx, operator text[])
{
    level++;
    // int space = 4;
    int jmpaddr = emit("JMP", 0, 0, cx, text);

    if (level > 100)
    {
        printf("ERROR LEV MAX\n");
    }
    token = constDeclaration(tokenArray, token, tokenArrayPtr, symbolTable, symbolTablePtr);
    // token = getToken(tokenArray, tokenArrayPtr);
    int numVars = varDeclaration(tokenArray, token, tokenArrayPtr, symbolTable, symbolTablePtr, level); // VAR-DECLARATION
    // token = getToken(tokenArray, tokenArrayPtr);
    token = proDeclaration(tokenArray, token, tokenArrayPtr, symbolTable, symbolTablePtr, cx, text, level);
    printf("\nnumVars is %d", numVars);
    if (numVars == -1)
    {
        return token;
    }
    else if (numVars > 0)
    {
        // space = numVars + space;
        token = getToken(tokenArray, tokenArrayPtr);
    }

    // EMIT INC (M=3+NumVARS)
    // int nextCode = *cx - 1;
    text[jmpaddr].M = *cx + 1;
    printf("\nJmp addr is now %d\n", *cx);
    // printf("\nSpace is %d\n", space);
    emit("INC", 0, 3 + numVars, cx, text);
    if (strcmp(token.token_type, "30") != 0 && strcmp(token.token_type, "29") != 0 && strcmp(token.token_type, "28") != 0)
    {
        token = Statement(tokenArray, token, symbolTable, tokenArrayPtr, cx, text);
    }
    else
    {
        Block(tokenArray, token, symbolTable, tokenArrayPtr, symbolTablePtr, cx, text);
    }
    token = Statement(tokenArray, token, symbolTable, tokenArrayPtr, cx, text);
    if (strcmp(token.token_type, "19") != 0) // does not equal period
    {
        token = getToken(tokenArray, tokenArrayPtr);
    }
    else
    {
        emit("SYS", 0, 3, cx, text);
        return token;
    }
    // token = Statement(tokenArray, token, symbolTable, tokenArrayPtr, cx, text);
    // else if (strcmp(token.token_type, "19") != 0)
    // {
    //     printf("Error: Program must end with period\n");
    //     exit(0);
    // }
    emit("OPR", 0, 0, cx, text);
    level--;
    return token;
}
