#ifndef _TAD_H_

	#define _TAD_H_

	#include <stdio.h>

	#include <stdlib.h>

	#include <string.h>

	#include <errno.h>

	__attribute__((used)) static void error(int errorCode, const char *s){
		fprintf(stderr, "\n\nERROR: %s",s);
		exit(errorCode);
	}


//=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-//


/* Tipo de dato:  		BirthDateDataAnalizerADT	
 * -------------------------------------------------------------------
 * Descripción: 		almacenara todo los datos necesarios de las provincias y los anos
 * -------------------------------------------------------------------
*/
typedef struct BirthDateDataAnalizerCDT * BirthDateDataAnalizerADT;


//=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-//





/* Funcion:  		newBirthDateDataAnalizer	
 * -------------------------------------------------------------------
 * Descripción: 	devuelve el tipo de dato abstracto de alias BDDT
 * -------------------------------------------------------------------
 * Parametros: 		void
 *--------------------------------------------------------------------
*/
BirthDateDataAnalizerADT newBirthDateDataAnalizer(void);





/* Funcion:  		analizeProvince
 * -------------------------------------------------------------------
 * Descripción: 	rellena la lista de provincias.
 * -------------------------------------------------------------------
 * Parametros: 		recibe el BDDT, el ID y el nombre de la nueva provincia
 *--------------------------------------------------------------------
*/
void analizeProvince(BirthDateDataAnalizerADT BDDA, unsigned newID, char * provinceName);





/* Funcion:  		analizeBirthData
 * -------------------------------------------------------------------
 * Descripción: 	rellena la lista de anos y va aumentando la cantidad de personas nacidas por ano y provincia
 * -------------------------------------------------------------------
 * Parametros: 		recibe el BDDT, el ID de la provincia, el ano y el sexo del nacido
 *--------------------------------------------------------------------
*/
void analizeBirthData(BirthDateDataAnalizerADT BDDA, unsigned searchedID, unsigned year, int sex);




/* Funcion:  		updateYearsData	
 * -------------------------------------------------------------------
 * Descripción: 	pasa la lista de anos a un array de anos
 * -------------------------------------------------------------------
 * Parametros: 		recibe el BDDA
 *--------------------------------------------------------------------
*/
void updateYearsData(BirthDateDataAnalizerADT BDDA);






/* Funcion: 		updateProvince 		
 * -------------------------------------------------------------------
 * Descripción: 	pasa la lista de provincias a un array de provincias
 * -------------------------------------------------------------------
 * Parametros: 		recibe el BDDA
 *--------------------------------------------------------------------
*/
void updateProvince(BirthDateDataAnalizerADT BDDA);





/* Funcion:  		freeBDDA	
 * -------------------------------------------------------------------
 * Descripción: 	libera toda la memoria ocupada por el BDDA
 * -------------------------------------------------------------------
 * Parametros: 		recibe el BDDA
 *--------------------------------------------------------------------
*/
void freeBDDA(BirthDateDataAnalizerADT BDDA);



//=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-//


						/*QUERY 1 RELATED*/

/* Funcion:  		alphaOrder	
 * -------------------------------------------------------------------
 * Descripción: 	ordena las provincias del BDDA por orden alfabetico
 * -------------------------------------------------------------------
 * Parametros: 		recibe el BDDA
 *--------------------------------------------------------------------
*/
void alphaOrder(BirthDateDataAnalizerADT BDDA);





/* Funcion:  		provinceAmmount
 * -------------------------------------------------------------------
 * Descripción: 	devuelve la cantidad de provincias procesadas en el BDDA
 * -------------------------------------------------------------------
 * Parametros: 		recibe el BDDA
 *--------------------------------------------------------------------
*/
int provinceAmmount(BirthDateDataAnalizerADT BDDA);





/* Funcion:  		getProvinceData
 * -------------------------------------------------------------------
 * Descripción: 	rellena dos vectores de entrada con las provincias y sus respectivos nacimientos en orden alfabetico
 * -------------------------------------------------------------------
 * Parametros: 		recibe el BDDA, un vector para los nombres de las provincias y un vector para la cantidad de nacidos
 *--------------------------------------------------------------------
*/
void getProvinceData(BirthDateDataAnalizerADT BDDA,char *** provincesName,long ** births);



//=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-//



						/*QUERY 2 RELATED*/

/* Funcion:  		numericOrder
 * -------------------------------------------------------------------
 * Descripción: 	ordena los anos del BDDA por orden ascendente
 * -------------------------------------------------------------------
 * Parametros: 		recibe el BDDA
 *--------------------------------------------------------------------
*/
void numericOrder(BirthDateDataAnalizerADT BDDA);





/* Funcion:  		getYearsData
 * -------------------------------------------------------------------
 * Descripción: 	rellena tres vectores de entrada con los datos de los anos y sus respectivos numeros de hombres y mujeres nacidos
 * -------------------------------------------------------------------
 * Parametros: 		recibe el BDDA, un vector para los anos, dos vectores para la cantidad de mujeres y hombres nacidos
 *--------------------------------------------------------------------
*/
void getYearsData(BirthDateDataAnalizerADT BDDA,long ** years,long ** male,long ** female);





/* Funcion:  		yearAmmount
 * -------------------------------------------------------------------
 * Descripción: 	devuelve la cantidad de anos procesados en el BDDA
 * -------------------------------------------------------------------
 * Parametros: 		recibe el BDDA
 *--------------------------------------------------------------------
*/
int yearAmmount(BirthDateDataAnalizerADT BDDA);



//=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-//



						/*QUERY 3 RELATED*/

/* Funcion:  		percentageOrder	
 * -------------------------------------------------------------------
 * Descripción: 	ordena las provincias del BDDA segun el porcentaje total de nacidos
 * -------------------------------------------------------------------
 * Parametros: 		recibe el BDDA
 *--------------------------------------------------------------------
*/
void percentageOrder(BirthDateDataAnalizerADT BDDA);





/* Funcion:  		getPercentages
 * -------------------------------------------------------------------
 * Descripción: 	rellena dos vectores de entrada con el nombre de la provincia y su porcentaje respectivo
 * -------------------------------------------------------------------
 * Parametros: 		recibe el BDDA, un vector de nombres de provincias y un vector de porcentajes
 *--------------------------------------------------------------------
*/
void getPercentages(BirthDateDataAnalizerADT BDDA,char *** provincesName,int ** percentages);

//---------------------------------------------------------------------------------//


#endif