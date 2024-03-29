#include "TAD.h"

#define MAX 300
#define BLOQUE 10


//enum para etapas del strtok 
typedef enum provinceStage
{
	Stage_ID=0, 
	Stage_name
}tProvinceStage;

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


			/*DATA PROCESSING FUNCTIONS*/

//funcion que procesa la informacion del archivo con las provincias
void processProvinceData(FILE * pData, BirthDateDataAnalizerADT BDDA);

//funcion que procesa la informacion del archivo con los nacimientos
void processBirthData(FILE * bData, BirthDateDataAnalizerADT BDDA);

//funcion que genera un string de manera eficiente y lo retorna
char * fillName(const char * token);



			/*QUERY FUNCTIONS*/

void query1(BirthDateDataAnalizerADT BDDA);

void query2(BirthDateDataAnalizerADT BDDA);

void query3(BirthDateDataAnalizerADT BDDA);


		/*ERROR DETECTION FUNCTIONS*/

//funcion que verifica que no se haya producido un error, en caso de haberlo, libera el BDDA y aborta el programa
void checkProgramStatus(BirthDateDataAnalizerADT BDDA);

//imprime en stderr el error correspondiente y aborta con exit(errorCode)
void error(int errorCode, const char *s);




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

	printf("\t\t\t%s  Ignacio Manfredi ---- Francisco Bernad ---- Patrick Dey  %s\n\n",
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
					checkProgramStatus(BDDA);
				}

				stage++;

				token = strtok(NULL,s);
			}
			
			analizeProvince(BDDA,newID,provinceName);
			checkProgramStatus(BDDA);

		}

	updateProvince(BDDA);
	checkProgramStatus(BDDA);
}


void processBirthData(FILE * bData, BirthDateDataAnalizerADT BDDA)
{
	char * token;
	char s[]=",";
	char str[MAX];

	int sex;
	unsigned year,searchedID;

	tBornStage stage;

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
			checkProgramStatus(BDDA);

		}	

	updateYearsData(BDDA);
	checkProgramStatus(BDDA);
}



void query1(BirthDateDataAnalizerADT BDDA)
{
	char ** provincesName=NULL;
	long * births=NULL;
	int maxIndex=provinceAmmount(BDDA);

	FILE * query1_csv = fopen("query1.csv", "w");

	fprintf(query1_csv, "Provinica;Nacimientos\n");

	alphaOrder(BDDA);

	getProvinceData(BDDA,&provincesName,&births);
	if(errno!=0)
	{
		free(provincesName);
		free(births);
		checkProgramStatus(BDDA);
	}

	for (int i = 0; i < maxIndex; ++i)
	{
		fprintf(query1_csv, "%s;%ld\n",provincesName[i],births[i]);
	}

	free(provincesName);
	free(births);

	fclose(query1_csv);
}


void query2(BirthDateDataAnalizerADT BDDA)
{
	long * years=NULL;
	long * male=NULL;
	long * female=NULL;
	int maxIndex=yearAmmount(BDDA);


	FILE * query2_csv = fopen("query2.csv", "w");

	fprintf(query2_csv, "Año;Varon;Mujer\n");

	numericOrder(BDDA);

	getYearsData(BDDA,&years,&male,&female);
	if(errno!=0)
	{
		free(years);
		free(male);
		free(female);
		checkProgramStatus(BDDA);
	}

	for (int i = 0; i < maxIndex; ++i)
	{
		fprintf(query2_csv, "%ld;%ld;%ld\n",years[i],male[i],female[i]);
	}

	free(years);
	free(male);
	free(female);


	fclose(query2_csv);
}


void query3(BirthDateDataAnalizerADT BDDA)
{
	char ** provincesName=NULL;
	int * percentages=NULL;
	int maxIndex=provinceAmmount(BDDA);

	FILE * query3_csv = fopen("query3.csv", "w");

	fprintf(query3_csv, "Provincia;Porcentaje\n");

	percentageOrder(BDDA);

	getPercentages(BDDA,&provincesName,&percentages);
	if(errno!=0)
	{
		free(provincesName);
		free(percentages);
		checkProgramStatus(BDDA);
	}


	for (int i = 0; i < maxIndex; ++i)
	{
		fprintf(query3_csv, "%s;%d%%\n",provincesName[i],percentages[i]);
	}

	free(provincesName);
	free(percentages);

	fclose(query3_csv);
}

char * fillName(const char * token)
{
	char * s=NULL;
	int i;

		for (i = 0; token[i]!=0 && token[i]!='\n' && token[i]!='\r'; i++)
		{
			if(i%BLOQUE == 0)
			{
				s=realloc(s,i+BLOQUE);
				if(s==NULL)
					errno=ENOMEM;
					
			}

			s[i]=token[i];
		}

	s=realloc(s,i+1);  
	if(s==NULL)
		errno=ENOMEM;
		
	
	s[i]=0;

	return s;
}


void checkProgramStatus(BirthDateDataAnalizerADT BDDA)
{
	if(errno!=0)
	{
		free(BDDA);
		error(errno,strerror(errno));
	}
}

void error(int errorCode, const char *s){
    fprintf(stderr, "\n\nERROR: %s\n",s);
    exit(errorCode);
}