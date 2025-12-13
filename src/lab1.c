#include "../include/lab1.h"
int main1()
{
    

    FILE *myfile = fopen("test1.txt", "rt");
    if (!myfile) {
        perror("fopen");
        return 1;
    }

    char text[MAXLINE];
    int in_dq = 0;  // внутри двойных кавычек "
    int in_sq = 0;  // внутри одинарных кавычек '
    int in_mc = 0;  // внутри многострочного комментария /* */

    while (fgets(text, sizeof(text), myfile) != NULL) {
        int in_sc = 0;  // внутри однострочного комментария //

        for (int i = 0; text[i] != '\0' && text[i] != '\n'; i++) {

            // начало многострочного комментария
            if (!in_mc && !in_sc &&
                !in_dq && !in_sq &&
                text[i] == '/' && text[i + 1] == '*') {
                in_mc = 1;
                printf("%c%c", text[i], text[i + 1]);
                i++;
                continue;
            }

            // конец многострочного комментария
            if (in_mc && text[i] == '*' && text[i + 1] == '/') {
                in_mc = 0;
                printf("%c%c", text[i], text[i + 1]);
                i++;
                continue;
            }

            // начало однострочного комментария
            if (!in_mc && !in_sc &&
                !in_dq && !in_sq &&
                text[i] == '/' && text[i + 1] == '/') {
                in_sc = 1;
            }

            // печать комментариев как есть
            if (in_mc || in_sc) {
                printf("%c", text[i]);
                continue;
            }

            // отслеживание входа в строку/символьный литерал
            if (!in_dq && !in_sq) {
                if (text[i] == '"') {
                    in_dq = 1;
                } else if (text[i] == '\'') {
                    in_sq = 1;
                }
            } else if (in_dq && text[i] == '"' &&
                       (i == 0 || text[i - 1] != '\\')) {
                in_dq = 0;
            } else if (in_sq && text[i] == '\'' &&
                       (i == 0 || text[i - 1] != '\\')) {
                in_sq = 0;
            }

            // подсветка препроцессорной директивы (#...) до первого пробела
            if (!in_mc && !in_sc &&
                !in_dq && !in_sq && text[i] == '#') {
                int space = 0;
                for (int j = i; text[j] != '\0' && text[j] != '\n'; j++) {
                    if (text[j] == ' ')
                        space = 1;

                    if (space == 0) {
                        printf("\033[91m%c\033[0m", text[j]);
                    } else {
                        printf("%c", text[j]);
                    }
                }
                break;  // до конца строки уже всё напечатали
            } else {
                printf("%c", text[i]);
            }
        }

        printf("\n");
    }

    fclose(myfile);
    return 0;
}
