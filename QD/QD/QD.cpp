/* Maximizar  z = 3000 x1 + 5000 x2
s. a.         0.5 x1 + 0.2 x2 <= 16
              0.25 x1 + 0.3 x2 <= 11
			  0.25 x1 + 0.5 x2 <= 15
			  x1 >= 0, x2 >= 0*/

#include <stdlib.h>
#include <stdio.h>
#include <C:\glpk-4.65\src\glpk.h>

int main() {
	glp_prob* lp; // Variavel que vai receber o problema
	int ia[1 + 1000], ja[1 + 1000];
	double ar[1 + 1000], z, x1, x2;

	/* Cria um problema inicialmente vazio */
	lp = glp_create_prob();

	/* Cria um nome para o problema */
	glp_set_prob_name(lp, "Problema das Ligas Metalicas");

	/* Cria criterio de otimizacao */
	glp_set_obj_dir(lp, GLP_MAX);

	/* Adiciona linhas ao problema */
	glp_add_rows(lp, 3);

	/* Cria um nome simbolico para a linha "p" */
	glp_set_row_name(lp, 1, "Cobre");
	glp_set_row_name(lp, 2, "Zinco");
	glp_set_row_name(lp, 3, "Chumbo");

	/* Cria um limite superior para a primeira linha */
	glp_set_row_bnds(lp, 1, GLP_UP, 0.0, 16.0);
	glp_set_row_bnds(lp, 2, GLP_UP, 0.0, 11.0);
	glp_set_row_bnds(lp, 3, GLP_UP, 0.0, 15.0);

	glp_add_cols(lp, 2);

	/* Adiciona um nome simbolico para a primeira coluna */
	glp_set_col_name(lp, 1, "x1");
	glp_set_col_name(lp, 2, "x2");

	/* Define um limite inferior para a coluna */
	glp_set_col_bnds(lp, 1, GLP_UP, 0, 100);
	glp_set_col_bnds(lp, 2, GLP_UP, 0, 100);

	/* Define o coeficiente da FO para a primeira coluna */
	glp_set_obj_coef(lp, 1, 3000.0);
	glp_set_obj_coef(lp, 2, 5000.0);

	/* Define coeficientes da matriz de restricoes */
	ia[1] = 1, ja[1] = 1, ar[1] = 0.50; /* a[1,1] = 0.5 */
	ia[2] = 1, ja[2] = 2, ar[2] = 0.20; /* a[1,2] = 0.2 */

	ia[1] = 2, ja[1] = 1, ar[1] = 0.25; /* a[2,1] = 0.25 */
	ia[2] = 2, ja[2] = 2, ar[2] = 0.30; /* a[2,2] = 0.3 */

	ia[1] = 3, ja[1] = 1, ar[1] = 0.25; /* a[3,1] = 0.25 */
	ia[2] = 3, ja[2] = 2, ar[2] = 0.50; /* a[3,2] = 0.5 */

	/* Carrega a matriz de restricoes */
	glp_load_matrix(lp, 2, ia, ja, ar);

	/* Carrega metodo simplex para resolver o problema */
	glp_simplex(lp, NULL);

	/* Carrega o valor da Funcao Objetivo(FO) */
	z = glp_get_obj_val(lp);

	/* Carregar os valores das variaveis de decisao obtidos */
	x1 = glp_get_col_prim(lp, 1);
	x2 = glp_get_col_prim(lp, 2);

	/* Escreve a saida */
	printf("\nz = %g; x1 = %g; x2 = %g\n", z, x1, x2);

	/* Libera a memoria alocada para o problema */
	glp_delete_prob(lp);

	return 0;
}