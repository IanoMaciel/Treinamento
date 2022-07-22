/* Minimizar  z = 2 x1 + 4 x2 + 1.5 x3 + x4
s. a.         2 x1 + 2 x2 + 10 x3 + 20 x4 >= 11
              50 x1 + 20 x2 + 10 x3 + 30 x4 >= 70
			  80 x1 + 70 x2 + 10 x3 + 80 x4 >= 250
			  x1 >= 0, x2 >= 0, x3 >= 0, x4 >= 0*/

#include <stdlib.h>
#include <stdio.h>
#include <C:\glpk-4.65\src\glpk.h>

int main() {
	glp_prob* lp; // Variavel que vai receber o problema
	int ia[1 + 1000], ja[1 + 1000];
	double ar[1 + 1000], z, x1, x2, x3, x4;

	/* Cria um problema inicialmente vazio */
	lp = glp_create_prob();

	/* Cria um nome para o problema */
	glp_set_prob_name(lp, "Problema da Dieta");

	/* Cria criterio de otimizacao */
	glp_set_obj_dir(lp, GLP_MIN);

	/* Adiciona linhas ao problema */
	glp_add_rows(lp, 3);

	/* Cria um nome simbolico para a linha "p" */
	glp_set_row_name(lp, 1, "vit_A");
	glp_set_row_name(lp, 2, "vit_C");
	glp_set_row_name(lp, 3, "vit_D");

	/* Cria um limite superior para a primeira linha */
	glp_set_row_bnds(lp, 1, GLP_LO, 11.0, 11.0);
	glp_set_row_bnds(lp, 2, GLP_LO, 70.0, 70.0);
	glp_set_row_bnds(lp, 3, GLP_LO, 250.0, 250.0);

	glp_add_cols(lp, 4);

	/* Adiciona um nome simbolico para a primeira coluna */
	glp_set_col_name(lp, 1, "x1");
	glp_set_col_name(lp, 2, "x2");
	glp_set_col_name(lp, 3, "x3");
	glp_set_col_name(lp, 4, "x4");

	/* Define um limite inferior para a coluna */
	glp_set_col_bnds(lp, 1, GLP_LO, 0, 1);
	glp_set_col_bnds(lp, 2, GLP_LO, 0, 1);
	glp_set_col_bnds(lp, 3, GLP_LO, 0, 1);
	glp_set_col_bnds(lp, 4, GLP_LO, 0, 1);

	/* Define o coeficiente da FO para a primeira coluna */
	glp_set_obj_coef(lp, 1, 2.0);
	glp_set_obj_coef(lp, 2, 4.0);
	glp_set_obj_coef(lp, 3, 1.5);
	glp_set_obj_coef(lp, 4, 1.0);

	/* Define coeficientes da matriz de restricoes */
	ia[1] = 1, ja[1] = 1, ar[1] = 2.0; /* a[1,1] = 2 */
	ia[2] = 1, ja[2] = 2, ar[2] = 2.0; /* a[1,2] = 2 */
	ia[3] = 1, ja[3] = 3, ar[3] = 10.0; /* a[1,3] = 10 */
	ia[4] = 1, ja[4] = 4, ar[4] = 20.0; /* a[1,4] = 20 */

	ia[1] = 2, ja[1] = 1, ar[1] = 50.0; /* a[2,1] = 50 */
	ia[2] = 2, ja[2] = 2, ar[2] = 20.0; /* a[2,2] = 20 */
	ia[3] = 2, ja[3] = 3, ar[3] = 10.0; /* a[2,3] = 10 */
	ia[4] = 2, ja[4] = 4, ar[4] = 30.0; /* a[2,4] = 30 */

	ia[1] = 3, ja[1] = 1, ar[1] = 80.0; /* a[3,1] = 80 */
	ia[2] = 3, ja[2] = 2, ar[2] = 70.0; /* a[3,2] = 70 */
	ia[3] = 3, ja[3] = 3, ar[3] = 10.0; /* a[3,3] = 10 */
	ia[4] = 3, ja[4] = 4, ar[4] = 80.0; /* a[3,4] = 80 */

	/* Carrega a matriz de restricoes */
	glp_load_matrix(lp, 4, ia, ja, ar);

	/* Carrega metodo simplex para resolver o problema */
	glp_simplex(lp, NULL);

	/* Carrega o valor da Funcao Objetivo(FO) */
	z = glp_get_obj_val(lp);

	/* Carregar os valores das variaveis de decisao obtidos */
	x1 = glp_get_col_prim(lp, 1);
	x2 = glp_get_col_prim(lp, 2);
	x3 = glp_get_col_prim(lp, 3);
	x4 = glp_get_col_prim(lp, 4);


	/* Escreve a saida */
	printf("\nz = %g; x1 = %g; x2 = %g; x3 = %g; x4 = %g\n", z, x1, x2, x3, x4);

	/* Libera a memoria alocada para o problema */
	glp_delete_prob(lp);

	return 0;
}

