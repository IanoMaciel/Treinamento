/* Maximizar   z = 60 x1 + 100 x2 + 120 x3
   s.a.        100 x1 + 20 x2 + 30 x3 <= 50
               0 <= xi <= 1*/

#include <stdlib.h>
#include <stdio.h>
#include <C:\glpk-4.65\src\glpk.h>

int main() {
	glp_prob* lp; // Variavel que vai receber o problema
	int ia[1 + 1000], ja[1 + 1000];
	double ar[1 + 1000], z, x1, x2, x3;

	/* Cria um problema inicialmente vazio */
	lp = glp_create_prob();

	/* Cria um nome para o problema */
	glp_set_prob_name(lp, "Mochila fracionaria");

	/* Cria criterio de otimizacao */
	glp_set_obj_dir(lp, GLP_MAX);

	/* Adiciona linhas ao problema */
	glp_add_rows(lp, 1);

	/* Cria um nome simbolico para a linha "p" */
	glp_set_row_name(lp, 1, "p");

	/* Cria um limite superior para a primeira linha */
	glp_set_row_bnds(lp, 1, GLP_UP, 0.0, 50.0);
	glp_add_cols(lp, 3);

	/* Adiciona um nome simbolico para a primeira coluna */
	glp_set_col_name(lp, 1, "x1");
	glp_set_col_name(lp, 2, "x2");
	glp_set_col_name(lp, 3, "x3");

	/* Define um limite inferior para a coluna */
	glp_set_col_bnds(lp, 1, GLP_UP, 0, 1);
	glp_set_col_bnds(lp, 2, GLP_UP, 0, 1);
	glp_set_col_bnds(lp, 3, GLP_UP, 0, 1);

	/* Define o coeficiente da FO para a primeira coluna */
	glp_set_obj_coef(lp, 1, 60);
	glp_set_obj_coef(lp, 2, 100);
	glp_set_obj_coef(lp, 3, 120);

	/* Define coeficientes da matriz de restricoes */
	ia[1] = 1, ja[1] = 1, ar[1] = 10.0; /* a[1,1] = 10 */
	ia[2] = 1, ja[2] = 2, ar[2] = 20.0; /* a[1,2] = 20 */
	ia[3] = 1, ja[3] = 3, ar[3] = 30.0; /* a[1,3] = 30 */

	/* Carrega a matriz de restricoes */
	glp_load_matrix(lp, 3, ia, ja, ar);

	/* Carrega metodo simplex para resolver o problema */
	glp_simplex(lp, NULL);

	/* Carrega o valor da Funcao Objetivo(FO) */
	z = glp_get_obj_val(lp);

	/* Carregar os valores das variaveis de decisao obtidos */
	x1 = glp_get_col_prim(lp, 1);
	x2 = glp_get_col_prim(lp, 2);
	x3 = glp_get_col_prim(lp, 3);


	/* Escreve a saida */
	printf("\nz = %g; x1 = %g; x2 = %g; x3 = %g\n", z, x1, x2, x3);

	/* Libera a memoria alocada para o problema */
	glp_delete_prob(lp);

	return 0;
}