#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

typedef struct
{
    int age;
    double height;
    char name[64];
} Person;

void printPersonInfo(Person *p)
{
    printf("Person: %s, %d, %f\n", p->name, p->age, p->height);
}

int main (int argc, char *argv[])
{
    int numpeople;
    FILE *fp = NULL;
    int i;
    Person p = {35, 1.65, "xpto"};

    /* Validate number of arguments */
    if(argc != 2)
    {
        printf("USAGE: %s fileName\n", argv[0]);
        return EXIT_FAILURE;
    }

    /* Open the file provided as argument */
    errno = 0;
    fp = fopen(argv[1], "wb");
    if(fp == NULL)
    {
        perror ("Error opening file!");
        return EXIT_FAILURE;
    }

    printf("Quantas pessoas queres: ");
    scanf("%d", &numpeople);

    /* Write 10 itens on a file */
    for(i = 1 ; i <= numpeople ; i++)
    {   
        printf("Introduza a idade da pessoa %d: ", i);
        scanf("%d", &p.age);

        printf("Introduza a altura da pessoa %d: ", i);
        scanf("%lf", &p.height);

        int c;
        while ((c = getchar()) != '\n' && c != EOF);

        printf("Introduza o nome da pessoa %d: ", i);
        fgets(p.name, sizeof(p.name), stdin);
        p.name[strcspn(p.name, "\n")] = '\0';

        if (fwrite(&p, sizeof(Person), 1, fp) != 1) {
            perror("Erro ao escrever no ficheiro");
            fclose(fp);
            return EXIT_FAILURE;
        }

    }

    fclose(fp);

    return EXIT_SUCCESS;
}
