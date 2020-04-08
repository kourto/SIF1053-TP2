/*************************************************************************************************************
    *   main.c                  Auteur: Courteau, Yves                                                  *
    *                                                                                                   *
    *   SIF1053, TP2                                                                                    *
    *                                                                                                   *
    *   Programme qui permet de faire la division de deux variables de type integer (16 bits)           *
    *   directement sur le code binaire.  Ecrit les calculs ainsi que le quotient et le                 *
    *   reste de chaque division dans un fichier tiers.                                                 *
    *                                                                                                   *
    *   Ensuite une fonction de test verifie si la fonction division a produit les bons resultats.      *
    *                                                                                                   *
*************************************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

#pragma warning(disable : 4996) // Ignore le code d'erreur C4996, produit par les fonctions fopen, scanf et fscanf sous Visual Studio Community

unsigned int division(unsigned int a, unsigned int b);
unsigned int addition(unsigned int a, unsigned int b);
unsigned int soustraction(unsigned int a, unsigned int b);
void testFonctionnement();

int main(void)
{
    unsigned int i, a, b, d, N;
    unsigned short c;

    FILE* rep;
    rep = fopen("response.txt", "w");

    if (rep == NULL)
    {
        printf("Une erreur s'est produite avec le fichier response.txt\n");
        exit(EXIT_FAILURE);
    }

    printf("Entrer le nombre de division a effectuer (min:1 - max:99): ");
    scanf("%i", &N);
    while ((N >= 100 || N <= 0) && isdigit(N) == 0)
    {
        printf("(min:1 - max:99): ");
        scanf("%i", &N);
    }

    printf("Entrer la ou les divisions a effectuer,\nde la facon suivante : a/b\n");

    for (i = 1; i <= N; i++)
    {
        scanf("%i / %i", &a, &b);
        while (a < 0 || a > 65535 || b <= 0 || b > 65535)
        {
            printf("\nLe dividende doit etre compris entre 0 et 65535 et le diviseur entre 1 et 65535\n");
            scanf("%i / %i", &a, &b);
        }

        d = division(a, b);
        c = ((unsigned short)(d));
        d = (d >> 16);

        fprintf(rep, "Division %i: %i/%i = %d reste %i\n", i, a, b, c, d);
    }
    fclose(rep);

    testFonctionnement();

    system("kate response.txt");

    return EXIT_SUCCESS;
}

//  division [Fait la division de deux int de 16 bits directement sur le code binaire]
//
//  INPUT   :   a = dividende, b = diviseur
//  OUTPUT  :   Le quotient et le restant de la division
unsigned int division(unsigned int a, unsigned int b)
{
    b = b << 16;

    for (int i = 0; i <= 15; i++)
    {
        a = a << 1;

        if (a >= b)
        {
            a = soustraction(a, b);
            a = addition(a, 1);
        }
    }

    return a;
}

//  addition [Fait l'addition de deux int de 16 bits directement sur le code binaire]
//
//  INPUT   :   a = premier terme, b = deuxieme terme
//  OUTPUT  :   La somme des deux termes
unsigned int addition(unsigned int a, unsigned int b)
{
    while (b != 0)
    {
        int tmp = a & b;
        a = a ^ b;
        b = tmp << 1;
    }

    return a;
}

//  soustraction [Fait la soustraction de deux int de 16 bits directement sur le code binaire]
//
//  INPUT   :   a = premier operande, b = deuxieme operande
//  OUTPUT  :   La difference des deux operandes
unsigned int soustraction(unsigned int a, unsigned int b)
{
    while (b != 0)
    {
        int tmp = (~a) & b;
        a = a ^ b;
        b = tmp << 1;
    }

    return a;
}

//  testFonctionnement [Teste si la fonction division fonctionne correctement]
//
//  Fait la lecture du fichier cree par l'utilisateur, test les resultats,
//  ajoute au fichier un message qui dit si il y a des erreurs ou pas.
void testFonctionnement()
{
    unsigned int a, b, c, d, i, count = 0;
    bool test[100];
    bool test_result = true;

    FILE* rep_test = fopen("response.txt", "a+");
    if (rep_test == NULL)
    {
        printf("Une erreur s'est produite avec le fichier response.txt\n");
        exit(EXIT_FAILURE);
    }

    while (fscanf(rep_test, "%*s %*d %*c %d %*c %d %*c %d %*s %d", &a, &b, &c, &d) != EOF)
    {
        if (c == a / b && d == a % b)
            test[count] = true;
        else
            test[count] = false;
        count++;
    }

    for (i = 0; i < count; i++)
    {
        if (test[i] == false)
        {
            fprintf(rep_test, "\nUne erreur s'est produite avec la fonction division.");
            test_result = false;
            system("notepad response.txt");
            exit(EXIT_FAILURE);
        }
        else
        {
            test_result = true;
        }
    }

    if (test_result == true)
    {
        fprintf(rep_test, "\nAucune erreur ne s'est produite lors de l'execution du programme.\n");
    }

    fclose(rep_test);
}
