void create_error(int lineErr,char *typeErr,char *tokenErr);

int nbr_sm_errors(char * tab);

char * print_sm_error(int line,char * error);

typedef struct{
    char *type;
    char *text;
    int line;
}error;