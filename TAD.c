#include "TAD.h"

/*=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-
   	           _                           _                                
              | |                         | |                               
   ___   ___  | |_   _ __   _   _    ___  | |_   _   _   _ __    __ _   ___ 
  / _ \ / __| | __| | '__| | | | |  / __| | __| | | | | | '__|  / _` | / __|
 |  __/ \__ \ | |_  | |    | |_| | | (__  | |_  | |_| | | |    | (_| | \__ \
  \___| |___/  \__| |_|     \__,_|  \___|  \__|  \__,_| |_|     \__,_| |___/

                                                                            
=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-*/

//Estructura que almacena los datos de una provincia
typedef struct tProvince
{
	char* name;
	long female;
	long male;
}tProvince;



//Estructura que actua como nodo de la lista de provincia
typedef struct tProvinceNode
{
	struct tProvinceNode * next;
	tProvince provinceData;
	unsigned ID;
}tProvinceNode;



//Estructura que representa la lista de provincias
typedef struct tProvinceList
{
	tProvinceNode* first;
	unsigned size;
}tProvinceList;



//Estructura que almacena los datos de un ano
typedef struct tYearData
{
	int year;
	long male;
	long female;
}tYearData;



//Estructura que actua como nodo de la lista de anos
typedef struct tYearDataNode
{
	struct tYearDataNode * next;
	tYearData yearData;
}tYearDataNode;



//Estructura que representa la lista de anos
typedef struct tYearsDataList
{
	tYearDataNode* first;
	tYearDataNode * current;
	size_t size;
}tYearsDataList;



//Estructura que representa un elemento del array de anos
typedef struct tYearDataArrayElem
{
	tYearDataNode * year;
	int number;//corresponde al numero de ano
}tYearDataArrayElem;



//Estructura que representa al array de anos
typedef struct tYearsDataArray
{
	size_t size;
	tYearDataArrayElem * array;
}tYearsDataArray;



//Estructura que representa un elemento del array de provincias
typedef struct tProvinceArrayElem
{
	tProvinceNode * province;
	int percentage;
	long totalBirths;
	size_t ID;
}tProvinceArrayElem;



//Estructura que representa al array de provincias
typedef struct tProvinceArray
{
	long totalBirths;
	size_t size;
	tProvinceArrayElem * array;
}tProvinceArray;



//Estructura del tipo abstracto de dato a utilizar
typedef struct BirthDateDataAnalizerCDT
{
	tProvinceList provinceList;
	tYearsDataList yearsDataList;
	tYearsDataArray yearsDataArray;
	tProvinceArray provinceArray;
}BirthDateDataAnalizerCDT;


/*=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-

        _             _     _             __                              
       | |           | |   (_)           / _|                             
  ___  | |_    __ _  | |_   _    ___    | |_   _   _   _ __     ___   ___ 
 / __| | __|  / _` | | __| | |  / __|   |  _| | | | | | '_ \   / __| / __|
 \__ \ | |_  | (_| | | |_  | | | (__    | |   | |_| | | | | | | (__  \__ \
 |___/  \__|  \__,_|  \__| |_|  \___|   |_|    \__,_| |_| |_|  \___| |___/
       

=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-*/
						
						/*BDDT FUNCTIONS*/

//agrega una provincia a la lista de provincias
static void addProvince(tProvinceList * provinceList, int newID, char * provinceName);


//funcion recursiva que agrega una provincia
static tProvinceNode * addProvinceRec(tProvinceNode * first,unsigned newID, char * provinceName);


//compara dos ints (se uso para comparar dos ID)
static int cmp(int a, int b);


//pasa la lista de provincias a un array
static void provinceListToArray(tProvinceList * provinceList, tProvinceArray * provinceArray);


//funcion utilizada por provinceListToArray para agregar cada elemento de la lista al vector recursivamente
static void fillProvinceArray(tProvinceNode * first, tProvinceArrayElem ** provinceArray, int i);


//rellena la lista de anos y aumenta la cantidad de nacidos por provincia y ano
static void fillBirthData(tProvinceArray * provinceArray, tYearsDataList * yearsDataList, unsigned searchedID, unsigned year, unsigned sex);


//funcjon utilizada por fillBirthData para agrega un ano a la lista recursivamente
static tYearDataNode * addYearRec(tYearDataNode * first,tYearDataNode ** current, int year, int * repeated);


//pasa la lista de anos a un array
static void yearsDataListToArray(tYearsDataList * yearsDataList, tYearsDataArray * yearsDataArray);


//funcion utilizada por yearsDataListToArray para agregar cada elemento de la lista al vector recursivamente
static void fillYearsDataArray(tYearDataNode * first, tYearDataArrayElem ** array, int i);


//compara dos elementos del array de provincias
static int cmpProvince(tProvinceArrayElem * a, tProvinceArrayElem * b);


						/*FREE FUNCTIONS*/


//free de la lista de provincias
static void freeProvinceList(tProvinceList * provinceList);


//funcion utilizada por freeProvinceList para hacer free de cada nodo
static void freeProvinceListRec(tProvinceNode * first);


//free de la lista de anos
static void freeYearsDataList(tYearsDataList * yearsDataList);


//funcion utilizada por freeYearsDataList para hacer free de cada nodo
static void freeYearDataListRec(tYearDataNode * first);


						/*QUERYS FUNCTIONS*/


/*QUERY 1*/

//ordena el vector de provincias en orden alfabetico
static void alphaOrderProvince(tProvinceArray * provinceArray);


//funcion de comparacion utiliza para el qsort en el query1
static int cmp_Query_1(tProvinceArrayElem * a, tProvinceArrayElem * b);


//rellena los arrays recibidos con la provincia y la cantidad de nacidos de cada una respectivamente
static void fillProvinceData(tProvinceArray * provinceArray,char *** provincesName,long ** births);


/*QUERY 2*/

//ordena el vector de anos en orden ascendente
static void numericOrderYears(tYearsDataArray * yearsDataArray);


//funcion de comparacion utiliza para el qsort en el query2
static int cmp_Query_2(tYearDataArrayElem * a, tYearDataArrayElem * b);


//rellena los arrays recibidos con el ano y la cantidad de hombres y mujeres nacidos de cada uno respectivamente
static void fillYearsData(tYearsDataArray * yearsDataArray, long  ** year, long **male ,long **female);




/*QUERY 3*/

//ordena el vector de provincias segun el orden de porcentajes
static void percentageOrderProvinces(tProvinceArray * provinceArray);


//funcion de comparacion utiliza para el qsort en el query3
static int cmp_Query_3(tProvinceArrayElem * a,tProvinceArrayElem * b);


//rellena los arrays recibidos con la provincia y el porcentaje de cada una respectivamente
static void fillPercentages(tProvinceArray * provinceArray, char *** provincesName, int ** percentages);





/*=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-
					                     _        
					                    | |       
					   ___    ___     __| |   ___ 
					  / __|  / _ \   / _` |  / _ \
					 | (__  | (_) | | (_| | |  __/
					  \___|  \___/   \__,_|  \___|
                              
=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-*/

//devuelve nuevo BDDT
BirthDateDataAnalizerADT newBirthDateDataAnalizer(void)
{
	BirthDateDataAnalizerCDT * aux=calloc(1,sizeof(BirthDateDataAnalizerCDT));
	if(aux==NULL)
		error(3,"Memory error");

	return aux;
}


/*-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=--=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-*/

/*-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=--=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-*/




//agrega provincia a la lista de provincias
void analizeProvince(BirthDateDataAnalizerADT BDDA, unsigned newID, char * provinceName)
{
	addProvince(&BDDA->provinceList,newID,provinceName);
}

static void addProvince(tProvinceList * provinceList, int newID, char * provinceName)
{
	provinceList->first=addProvinceRec(provinceList->first,newID,provinceName);
	provinceList->size++;
}

static tProvinceNode * addProvinceRec(tProvinceNode * first,unsigned newID, char * provinceName)
{
	if(first==NULL || cmp(newID,first->ID)<0)
	{
		tProvinceNode * newNode=calloc(1,sizeof(tProvinceNode));
		if(newNode==NULL)
			error(3,"Memory error");
		newNode->ID=newID;
		newNode->provinceData.name=provinceName;
		newNode->next=first;
		return newNode;
	}

	first->next=addProvinceRec(first->next,newID,provinceName);

	return first;
}

static int cmp(int a, int b)
{
	return a-b;
}




/*-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=--=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-*/

/*-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=--=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-*/




//pasa la lista de provincias a un array
void updateProvince(BirthDateDataAnalizerADT BDDA)
{
	provinceListToArray(&BDDA->provinceList,&BDDA->provinceArray);
}


static void provinceListToArray(tProvinceList * provinceList, tProvinceArray * provinceArray)
{
	int i=0,size=provinceList->size;

	provinceArray->array=calloc(size,sizeof(tProvinceArrayElem));

	if(provinceArray->array==NULL)
		error(3,"Memory error");

	fillProvinceArray(provinceList->first,&provinceArray->array,i);

	provinceArray->size=size;

}

static void fillProvinceArray(tProvinceNode * first, tProvinceArrayElem ** array, int i)
{
	if(first==NULL)
		return;

	(*array)[i].province=first;
	(*array)[i].ID=first->ID;

	fillProvinceArray(first->next,array,i+1);
}





/*-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=--=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-*/

/*-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=--=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-*/







//rellena la lista de anos y aumenta cantidad de nacidos por provincia y ano
void analizeBirthData(BirthDateDataAnalizerADT BDDA, unsigned searchedID, unsigned year, int sex)
{
	fillBirthData(&BDDA->provinceArray,&BDDA->yearsDataList,searchedID,year,sex);
}


static void fillBirthData(tProvinceArray * provinceArray, tYearsDataList * yearsDataList, unsigned searchedID, unsigned year, unsigned sex)
{
	tProvinceArrayElem * currentProvince;
	tProvinceArrayElem searchedProvince;

	int repeated=1;

			yearsDataList->first=addYearRec(yearsDataList->first,&yearsDataList->current,year,&repeated);
			if(!repeated)
				yearsDataList->size++;

			searchedProvince.ID=searchedID;
			currentProvince=bsearch((void*)&searchedProvince,(void*)provinceArray->array,provinceArray->size,sizeof(tProvinceArrayElem),(int (*)(const void *, const void *))cmpProvince);

			if(sex==1)
			{
				currentProvince->province->provinceData.male++;
				yearsDataList->current->yearData.male++;
			}

			else if(sex==2)
			{
				currentProvince->province->provinceData.female++;
				yearsDataList->current->yearData.female++;
			}

			currentProvince->totalBirths++;
			provinceArray->totalBirths++;
}

static tYearDataNode * addYearRec(tYearDataNode * first,tYearDataNode ** current, int year, int * repeated)
{
	int c;
	if(first==NULL || (c=cmp(year,first->yearData.year))<0)
	{
		tYearDataNode * newNode=calloc(1,sizeof(tYearDataNode));
		if(newNode==NULL)
			error(3,"Memory error");
		newNode->yearData.year=year;
		newNode->next=first;
		*current=newNode;
		*repeated=0;
		return newNode;
	}

	else if(c==0)
	{
		*current=first;
		return first;
	}

	first->next=addYearRec(first->next,current, year, repeated);

	return first;
}

static int cmpProvince(tProvinceArrayElem * a, tProvinceArrayElem * b)
{
	return a->ID-b->ID;
}






/*-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=--=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-*/

/*-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=--=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-*/







//pasa la lista de anos a un array
void updateYearsData(BirthDateDataAnalizerADT BDDA)
{
    yearsDataListToArray(&BDDA->yearsDataList,&BDDA->yearsDataArray);
}


static void yearsDataListToArray(tYearsDataList * yearsDataList, tYearsDataArray * yearsDataArray)
{
	int i=0,size=yearsDataList->size;

	yearsDataArray->array=realloc(yearsDataArray->array,size*sizeof(tYearDataArrayElem));
	if(yearsDataArray->array==NULL)
			error(3,"Memory error");

	fillYearsDataArray(yearsDataList->first,&yearsDataArray->array,i);

	yearsDataArray->size=size;
}

static void fillYearsDataArray(tYearDataNode * first, tYearDataArrayElem ** array, int i)
{
	if(first==NULL)
		return;

	(*array)[i].year=first;
	(*array)[i].number=first->yearData.year;

	fillYearsDataArray(first->next,array,i+1);
}





/*-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=--=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-*/

/*-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=--=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-*/





//ordena vector de provincias alfabeticamente
void alphaOrder(BirthDateDataAnalizerADT BDDA)
{
   alphaOrderProvince(&BDDA->provinceArray);
}

static void alphaOrderProvince(tProvinceArray * provinceArray)
{
	qsort(&provinceArray->array[0],provinceArray->size,sizeof(tProvinceArrayElem),(int(*)(const void*,const void*))cmp_Query_1);

}

static int cmp_Query_1(tProvinceArrayElem * a, tProvinceArrayElem * b)
{
	return strcmp(a->province->provinceData.name,b->province->provinceData.name);
}


//devuelve la cantidad de provincias
int provinceAmmount(BirthDateDataAnalizerADT BDDA)
{
	return BDDA->provinceArray.size;
}



//rellena los vectores con las provincias y la cantidad de nacimientos de cada una
void getProvinceData(BirthDateDataAnalizerADT BDDA, char *** provincesName,long ** births)
{
	fillProvinceData(&BDDA->provinceArray,provincesName,births);
}

static void fillProvinceData(tProvinceArray * provinceArray,char *** provincesName,long ** births)
{
	int size=provinceArray->size;
	*provincesName=realloc(*provincesName,size*sizeof(char*));
	if(*provincesName==NULL)
			error(3,"Memory error");
	*births=realloc(*births,size*sizeof(long));
	if(*births==NULL)
			error(3,"Memory error");

	for (int i = 0; i < size; ++i)
	{
		(*provincesName)[i]=provinceArray->array[i].province->provinceData.name;
		(*births)[i]=provinceArray->array[i].totalBirths;
	}

}



/*-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=--=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-*/

/*-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=--=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-*/




//ordena los anos por orden ascendente
void numericOrder(BirthDateDataAnalizerADT BDDA)
{
	numericOrderYears(&BDDA->yearsDataArray);
}

static void numericOrderYears(tYearsDataArray * yearsDataArray)
{
	qsort(&yearsDataArray->array[0],yearsDataArray->size,sizeof(tYearDataArrayElem),(int(*)(const void*,const void*))cmp_Query_2);
}

static int cmp_Query_2(tYearDataArrayElem * a, tYearDataArrayElem * b)
{
	return a->number - b->number;
}


void getYearsData(BirthDateDataAnalizerADT BDDA,long ** years,long ** male,long ** female)
{
	fillYearsData(&BDDA->yearsDataArray,years,male,female);
}


static void fillYearsData(tYearsDataArray * yearsDataArray, long  ** year, long **male ,long **female)
{
	int size=yearsDataArray->size;
	*year=realloc(*year,size*sizeof(long));
	if(*year==NULL)
			error(3,"Memory error");
	*male=realloc(*male,size*sizeof(long));
	if(*male==NULL)
			error(3,"Memory error");
	*female=realloc(*female,size*sizeof(long));
	if(*female==NULL)
			error(3,"Memory error");


	for (int i = 0; i < size; ++i)
	{
		(*year)[i]=yearsDataArray->array[i].number;
		(*male)[i]=yearsDataArray->array[i].year->yearData.male;
		(*female)[i]=yearsDataArray->array[i].year->yearData.female;
	}
}


//devuelve la cantidad de anos procesados
int yearAmmount(BirthDateDataAnalizerADT BDDA)
{
	return BDDA->yearsDataArray.size;
}





/*-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=--=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-*/

/*-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=--=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-*/




//ordena el vector de provincias segun el procentaje de nacimientos de cada una
void percentageOrder(BirthDateDataAnalizerADT BDDA)
{
	percentageOrderProvinces(&BDDA->provinceArray);
}


static void percentageOrderProvinces(tProvinceArray * provinceArray)
{
	for (int i = 0; i < provinceArray->size; ++i)
	{
		provinceArray->array[i].percentage=(double)provinceArray->array[i].totalBirths/(double)provinceArray->totalBirths*100;
	}
	qsort(&provinceArray->array[0],provinceArray->size,sizeof(tProvinceArrayElem),(int(*)(const void*,const void*))cmp_Query_3);
}

static int cmp_Query_3(tProvinceArrayElem * a,tProvinceArrayElem * b)
{
	int result=b->percentage-a->percentage;
	if(result==0)
		result=strcmp(a->province->provinceData.name,b->province->provinceData.name);

	return result;
}


void getPercentages(BirthDateDataAnalizerADT BDDA,char *** provincesName,int ** percentages)
{
	fillPercentages(&BDDA->provinceArray,provincesName,percentages);
}

static void fillPercentages(tProvinceArray * provinceArray, char *** provincesName, int ** percentages)
{
	int size=provinceArray->size;
	*percentages=realloc(*percentages,size*sizeof(int));
	if(*percentages==NULL)
			error(3,"Memory error");
	*provincesName=realloc(*provincesName,size*sizeof(char*));
	if(*provincesName==NULL)
			error(3,"Memory error");

	for (int i = 0; i < provinceArray->size; ++i)
	{
		(*percentages)[i]=provinceArray->array[i].percentage;
		(*provincesName)[i]=provinceArray->array[i].province->provinceData.name;
	}
}

/*-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-*/


//hace free del BDDA
void freeBDDA(BirthDateDataAnalizerADT BDDA)
{
	freeProvinceList(&BDDA->provinceList);
	freeYearsDataList(&BDDA->yearsDataList);
	free(BDDA->provinceArray.array);
	free(BDDA->yearsDataArray.array);
	free(BDDA);
}

static void freeProvinceList(tProvinceList * provinceList)
{
	freeProvinceListRec(provinceList->first);
}

static void freeProvinceListRec(tProvinceNode * first)
{
	if(first==NULL)
	{
		return;
	}

	freeProvinceListRec(first->next);
	free(first->provinceData.name);
	free(first);
}

static void freeYearsDataList(tYearsDataList * yearsDataList)
{
	freeYearDataListRec(yearsDataList->first);
}

static void freeYearDataListRec(tYearDataNode * first)
{
	if(first==NULL)
	{
		return;
	}

	freeYearDataListRec(first->next);
	free(first);
}