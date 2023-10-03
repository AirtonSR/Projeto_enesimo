#include <stdio.h>
#include <math.h>
#include <locale.h>

struct variables {
    double number;
    double lowerLimit;
    double upperLimit;
    double approximation;
    int precision;
    int *attempts;
    double errorMargin;
};

double calculateRoot(struct variables *root) {
    *(root->attempts) = 0;
    root->lowerLimit = 0.0;
    root->upperLimit = root->number;
    root->approximation = 1.0;

    while (root->approximation > 1.0 / pow(10, root->precision)) {
        double middle = (root->lowerLimit + root->upperLimit) / 2;
        double test = middle * middle;

        if (test > root->number) {
            root->upperLimit = middle;
        } else {
            root->lowerLimit = middle;
        }

        root->approximation = fabs(test - root->number);
        (*(root->attempts))++;
    }

    return (root->lowerLimit + root->upperLimit) / 2;
}

double calculateErrorMargin(struct variables *error) {
    error->lowerLimit = 0.0;
    error->upperLimit = error->number;
    error->approximation = 1.0;

    while (error->approximation > error->errorMargin) {
        double middle = (error->lowerLimit + error->upperLimit) / 2;
        double test = middle * middle;

        if (test > error->number) {
            error->upperLimit = middle;
        } else {
            error->lowerLimit = middle;
        }

        error->approximation = fabs(test - error->number);
    }

    return (error->lowerLimit + error->upperLimit) / 2;
}

int main() {
    struct variables root;
    int attempts;
    int option;

Beginning:
	setlocale(LC_ALL, "ptb");
    printf("Digite um número: ");
	scanf("%lf", &root.number);
	printf("----------------------------------------------------\n");
	
	printf("Digite a precisão desejada (número de casas decimais): ");
	scanf("%d", &root.precision);
	printf("----------------------------------------------------\n");
	
	printf("Digite a margem de erro: ");
	scanf("%lf", &root.errorMargin);
	printf("----------------------------------------------------\n\n");
	
	root.attempts = &attempts;
	
	double result = calculateRoot(&root);
	
	printf("A raiz quadrada aproximada de %.2lf é aproximadamente %.2lf\n\n", root.number, result);
	printf("Número de tentativas: %d\n\n", attempts);
	
	double errorMargin = calculateErrorMargin(&root);
	printf("Margem de erro: %.2lf%%\n\n", errorMargin);
	printf("-----------------------------------------------\n");

middle:

	printf("\nQuer calcular novamente? s - sim, n - não: ");

    getchar();
    option = tolower(getchar());
    printf("\n\n");

    switch (option) {
        case 's':
        	printf("------------------------------------------\n");
            goto Beginning;
            break;
        case 'n':
            goto end;
            break;
        default:
            goto middle;
            break;
    }

end:
    return 0;
}

