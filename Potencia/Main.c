#include <stdio.h>
#include <stdlib.h>
#include "Lista.h"


void somar(Lista * l1, Lista * l2);
void multiplicar(Lista * l1, Lista * l2);
void multiplicarPorNumero(Lista * l, Lista * resultado, int numero);
void exponenciar(Lista * base, Lista * expoente, Lista * resultado);
void preencherListas(Lista * base, Lista * expoente);
void preencherListaComString(Lista * lista, char * string);

void main(char args[]) {

	Lista * base = criar();
	Lista * expoente = criar();
	Lista * resultado = criar();
	preencherListas(base, expoente);
	if (ler_pos(expoente, 0) != 0) {
		exponenciar(base, expoente, resultado);
	}
	else {
		inserir_primeiro(resultado, 1);
	}
	printf("Resultado:\n");
	imprimir(resultado);
	getchar();
	destruir(base);
	destruir(expoente);
	destruir(resultado);
}

void preencherListas(Lista * base, Lista * expoente) {
	char * entrada = malloc(sizeof(char) * 100);
	printf("Digite a base:\n");
	gets(entrada);
	preencherListaComString(base, entrada);
	printf("Digite o expoente:\n");
	gets(entrada);
	preencherListaComString(expoente, entrada);
	free(entrada);
}

void preencherListaComString(Lista * lista, char * string) {
	char * aux;
	for (aux = string; *aux != '\0'; aux++) {
		inserir_ultimo(lista, *aux - '0');
	}
}

void exponenciar(Lista * base, Lista * expoente, Lista * resultado) {
	int indice, i, casaDecimal = 1;
	for (indice = tamanho(expoente) - 1; indice >= 0; indice--)
	{
		if (ler_pos(expoente, indice) != 0) {
			for (i = ler_pos(expoente, indice) * casaDecimal; i > 0; i--) {
				multiplicar(resultado, base);
			}
		}
		casaDecimal *= 10;
	}
}

void multiplicar(Lista * l1, Lista * l2) {
	int i;

	if (tamanho(l1) < 1) {
		for (i = tamanho(l2) - 1; i >= 0; i--) {
			inserir_primeiro(l1, ler_pos(l2, i));
		}
		return;
	}

	Lista * resultado = criar();
	Lista * auxiliar = criar();
	int zeroDireita = 1;

	for (i = tamanho(l2) - 1; i >= 0; i--)
	{
		Lista * resultadoParcial = criar();
		multiplicarPorNumero(l1, auxiliar, ler_pos(l2, i));
		multiplicarPorNumero(auxiliar, resultadoParcial, zeroDireita);
		somar(resultadoParcial, resultado);
		zeroDireita *= 10;
		limpar(auxiliar);
		destruir(resultadoParcial);
	}
	limpar(l1);
	for (i = tamanho(resultado) - 1; i >= 0; i--) {
		inserir_primeiro(l1, ler_pos(resultado, i));
	}
	destruir(resultado);
	destruir(auxiliar);
}

void somar(Lista * l, Lista * resultado) {
	Lista * resultadoParcial = criar();
	int i, carry = 0;
	int j = tamanho(resultado) - 1;
	for (i = tamanho(l) - 1; i >= 0; i--)
	{
		int r, unidade;
		if (j >= 0) {
			r = (ler_pos(l, i) + ler_pos(resultado, j--)) + carry;
		}
		else {
			r = ler_pos(l, i) + carry;
		}
		carry = r / 10;
		unidade = r % 10;
		inserir_primeiro(resultadoParcial, unidade);
	}
	if (carry > 0) {
		inserir_primeiro(resultadoParcial, carry);
	}
	limpar(resultado);

	for (i = tamanho(resultadoParcial) - 1; i >= 0; i--) {
		inserir_primeiro(resultado, ler_pos(resultadoParcial, i));
	}
	destruir(resultadoParcial);
}

void multiplicarPorNumero(Lista * l, Lista * resultado, int numero)
{
	int i, carry = 0;
	for (i = tamanho(l) - 1; i >= 0; i--)
	{
		int r = (ler_pos(l, i) * numero) + carry;
		carry = r / 10;
		inserir_primeiro(resultado, r % 10);
	}
	if (carry > 0)
		inserir_primeiro(resultado, carry);
}
