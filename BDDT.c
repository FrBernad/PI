#include <stdio.h>
#include "TAD.h"

#define MAX 300
#define BLOQUE 10

//funcion que procesa la informacion de l archivo con las provincias
void processProvinceData(FILE * pData, BirthDateDataAnalizerADT BDDA);

//enum para etapas del strtok 
typedef enum provinceStage
{
	Stage_ID=0, 
	Stage_name
}tProvinceStage;



//funcion que procesa la informacion de l archivo con los nacimientos
void processBirthData(FILE * bData, BirthDateDataAnalizerADT BDDA);

//enum para etapas del strtok
typedef enum bornStage
{
	Stage_AN=0, 
	Stage_PROVRES,
	Stage_TIPPARTO,
	Stage_SEXO,
	Stage_IMEDAD,
	Stage_ITIEMGEST,
	Stage_IMINSTRUC,
	Stage_IPESONAC,
	Stage_CUENTA
}tBornStage;

//funcion que genera un string de manera eficiente y lo retorna
char * fillName(char * token);



void query1(BirthDateDataAnalizerADT BDDA);
void query2(BirthDateDataAnalizerADT BDDA);
void query3(BirthDateDataAnalizerADT BDDA);




int main(int argc, char const *argv[])
{

	if(argc!=3){
		 error(1, "Error en la cantidad de argumentos");
	}

	FILE * birthData=fopen(argv[1],"rt");
	FILE * provinces=fopen(argv[2],"rt");


	if( provinces == NULL || birthData == NULL){
		error(2, "Error al abrir los archivos");
	}

	
	printf("\n\n\n\t\t%sTRABAJO FINAL PROGRAMACION IMPERATIVA%s\n\n",
	"--/\\/--/\\/--/\\/--/\\/--/\\/--/\\/--",
	"--/\\/--/\\/--/\\/--/\\/--/\\/--/\\/--");

	printf("\t\t\t%s  Agustin Manfred --- Francisco Bernad ---- Patrick Day  %s\n\n",
		"<<>><<>><<>><<>>",
		"<<>><<>><<>><<>>");
	printf("\t\t\tCargando...\n\n\n");


	BirthDateDataAnalizerADT BDDA=newBirthDateDataAnalizer();

	processProvinceData(provinces,BDDA);

	processBirthData(birthData,BDDA);

	printf("\t\t\t<Completado>\n\n\n");

	query1(BDDA);

	query2(BDDA);

	query3(BDDA);

	freeBDDA(BDDA);

	printf("\t\t\tEncontrara los archivos en su directorio actual.\n\n\n");


return 0;
}


void processProvinceData(FILE * pData, BirthDateDataAnalizerADT BDDA)
{
	char * token;
	char s[]=",";
	char str[MAX];

	tProvinceStage stage;
	unsigned newID;
	char * provinceName;

	fgets(str,MAX,pData);

		while(fgets(str,MAX,pData))
		{
			stage=Stage_ID;

			token=strtok(str,s);

			while(token!=NULL)
			{
				if(stage==Stage_ID)
				{
					newID=atoi(token);
				}

				else if(stage==Stage_name)
				{
					provinceName=fillName(token);
				}

				stage++;

				token = strtok(NULL,s);
			}
			
			analizeProvince(BDDA,newID,provinceName);
		}

}

void processBirthData(FILE * bData, BirthDateDataAnalizerADT BDDA)
{
	char * token;
	char s[]=",";
	char str[MAX];

	int sex;
	unsigned year,searchedID;

	tBornStage stage;

	updateProvince(BDDA);

	fgets(str,MAX,bData);

		while(fgets(str,MAX,bData))
		{
			stage=Stage_AN;

			token=strtok(str,s);

			while(token!=NULL)
			{
				if(stage==Stage_AN)
				{
					year=atoi(token);
				}

				else if(stage==Stage_PROVRES)
				{	
					searchedID=atoi(token);
				}

				else if(stage==Stage_SEXO)
				{
					sex=atoi(token);
				}

				stage++;

				token = strtok(NULL,s);
			}

			analizeBirthData(BDDA,searchedID,year,sex);
		}	

}



char * fillName(char * token)
{
	char * s=NULL;
	int i;

		for (i = 0; token[i]!=0 && token[i]!='\n' && token[i]!='\r'; i++)
		{
			if(i%BLOQUE == 0)
			{
				s=realloc(s,i+BLOQUE);
			}

			s[i]=token[i];
		}

	s=realloc(s,i+1);  

	s[i]=0;

	return s;
}

/*
Donde cada línea de la salida contenga, separados por “;”, el nombre de la provincia y la
cantidad de nacimientos en esa provincia.
El orden de impresión es alfabético por provincia.
❏ ​ Nombre del archivo:​ ​ query1.csv
❏ ​ Salida de ejemplo:
Provincia;Nacimientos
Buenos Aires;262721
Catamarca;125901
Chaco;105884
*/

void query1(BirthDateDataAnalizerADT BDDA)
{
	char ** provincesName=NULL;
	long * births=NULL;

	FILE * query1_csv = fopen("query1.csv", "w");

	fprintf(query1_csv, "Provinica;Nacimientos\n");

	alphaOrder(BDDA);

	getProvinceData(BDDA,&provincesName,&births);

	for (int i = 0; i < provinceAmmount(BDDA); ++i)
	{
		fprintf(query1_csv, "%s;%ld\n",provincesName[i],births[i]);
	}

	free(provincesName);
	free(births);

	fclose(query1_csv);
}

/*Query 2: Nacimientos por año y por sexo
Donde cada línea de la salida contenga, separados por “;”, el año, la cantidad de nacimientos
de varones (código 1) en ese año y la cantidad de nacimientos de mujeres (código 2) en ese año.
El orden de impresión es ascendente por año.
❏ ​ Nombre del archivo:​ ​ query2.csv
❏ ​ Salida de ejemplo:
Año;Varón;Mujer
2015;162721;183742
2016;225901;292358
2017;105884;129469*/

void query2(BirthDateDataAnalizerADT BDDA)
{
	long * years=NULL;
	long * male=NULL;
	long * female=NULL;

	updateYearsData(BDDA);

	FILE * query2_csv = fopen("query2.csv", "w");

	fprintf(query2_csv, "Año;Varon;Mujer\n");

	numericOrder(BDDA);

	getYearsData(BDDA,&years,&male,&female);

	for (int i = 0; i < yearAmmount(BDDA); ++i)
	{
		fprintf(query2_csv, "%ld;%ld;%ld\n",years[i],male[i],female[i]);
	}

	free(years);
	free(male);
	free(female);

	fclose(query2_csv);
}


/*Donde cada línea de la salida contenga separados por “;” el nombre de la provincia y el
porcentaje de nacimientos ocurridos en esa provincia (contabilizando todos los nacimientos que
ocurrieron en esa provincia respecto del total de nacimientos que ocurrieron en todas las
provincias).
El orden de impresión es descendente por el porcentaje de nacimientos y luego
alfabéticamente por nombre de la línea.
El porcentaje a mostrar debe ser entero (truncar el valor real obtenido).*/

void query3(BirthDateDataAnalizerADT BDDA)
{
	char ** provincesName=NULL;
	int * percentages=NULL;

	FILE * query3_csv = fopen("query3.csv", "w");

	fprintf(query3_csv, "Provincia;Porcentaje\n");

	percentageOrder(BDDA);

	getPercentages(BDDA,&provincesName,&percentages);

	for (int i = 0; i < provinceAmmount(BDDA); ++i)
	{
		fprintf(query3_csv, "%s;%d%%\n",provincesName[i],percentages[i]);
	}

	free(provincesName);
	free(percentages);

	fclose(query3_csv);
}



//PARA PROBAR MAIN (AGREGAR DATA.C)
/*	printf("\n\n\n\n");

		//long mujeres1=0,hombres1=0, mujeres2=0,hombres2=0;

		for (int i = 0; i < BDDA->provinceArray.size; ++i)
		{
			//hombres1+=BDDA->provinceArray.array[i].province->provinceData.male;
			//mujeres1+=BDDA->provinceArray.array[i].province->provinceData.female;

			printf("ID:%ld || Provincia: %s || Hombres: %ld || Mujeres: %ld\n",
			BDDA->provinceArray.array[i].ID,BDDA->provinceArray.array[i].province->provinceData.name,BDDA->provinceArray.array[i].province->provinceData.male,BDDA->provinceArray.array[i].province->provinceData.female);
		}

		printf("\n\n\n\n");

	    for (int i = 0; i < BDDA->yearsDataArray.size; ++i)
		{
			//hombres2+=BDDA->yearsDataArray.array[i].year->yearData.male;
			//mujeres2+=BDDA->yearsDataArray.array[i].year->yearData.female;

			printf("Year: %d || Hombres: %ld || Mujeres: %ld \n",
			BDDA->yearsDataArray.array[i].number,
			BDDA->yearsDataArray.array[i].year->yearData.male,
			BDDA->yearsDataArray.array[i].year->yearData.female);
		}


		//printf("MUJERES: %ld %ld, HOMBRES: %ld %ld\n",mujeres2,mujeres1,hombres2,hombres1);*/
