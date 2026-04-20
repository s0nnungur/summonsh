#include "shell.h"

void calc (char *value1, char *op, char *value2) {
    //chamar func calc ( ... argumentos ...)

    int flag=0;
    double v1=atof(value1),v2=atof(value2),resultado;
    if (strcmp(op, "+") == 0) 
        resultado = v1 + v2;
    else if (strcmp(op, "-") == 0) 
        resultado = v1 - v2;
    else if (strcmp(op, "*") == 0)
        resultado = v1 * v2;
    else if (strcmp(op, "/") == 0) {
        if(fabs(v2) < FLT_EPSILON) {
            flag=1;
            printf("Erro! divisão por zero\n");

        } else {
            resultado = v1 / v2;
        }
    }
    else if (strcmp(op, "^") == 0)
        resultado = pow(v1,v2);    
    
    if (flag==0)
        printf("Resultado calc %f %s %f = %f\n", v1, op, v2, resultado);
}

void bits(char *op1, char *op, char *op2) {

    unsigned short a=atoi(op1), b=atoi(op2), resultado;
    int flag=0;

    if (strcmp(op, "&") == 0) 
        resultado = a & b;
    else if (strcmp(op, "^") == 0) 
        resultado = a ^ b;
    else if (strcmp(op, "|") == 0)
        resultado = a | b;
    else if (strcmp(op, "~") == 0) {
        if(a!=0) {
            flag = 1;
            printf("Error! ~ é unário, verificar apenas com primeiro argumento igual a 0!\n");
        }
        resultado = ~b;
    } else if (strcmp(op, "<<") == 0)
        resultado = a << b;
    else if (strcmp(op, ">>") == 0)
        resultado = a >> b; 
    if (flag==0)
        printf("Resultado calc %hu %s %hu = %hu\n", a, op, b, resultado);
}



