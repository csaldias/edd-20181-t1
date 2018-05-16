#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

//Constantes para el número de cursos y alumnos a generar
#define CANT_ALUM 100 //Numero de alumnos
#define CANT_NOTA 8   //Numero de notas por alumno

char randomString[12];
char nombreAlumno[7];
char apellidoAlumno[7];

//Structs para cursos y notas
typedef struct {
  char sigla[7];
  int semestre; //1 o 2
} curso;

typedef struct {
  char rolEstudiante[12];
  char siglaCurso[7];
  int nota;
} nota;

void genRol() {
  static char charset[] = "012345678";
  randomString[0] = '2';
  randomString[1] = '0';
  randomString[2] = '1';

  for (int n = 3; n < 9; n++) {
    int key = rand() % (int)(sizeof(charset) - 1);
    randomString[n] = charset[key];
  }

  randomString[9] = '-';
  int key = rand() % (int)(sizeof(charset) - 1);
  randomString[10] = charset[key];
  randomString[11] = '\0';
}

void genNombre() {
  static char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

  for (int n = 0; n < 6; n++) {
    int key = rand() % (int)(sizeof(charset) - 1);
    nombreAlumno[n] = charset[key];
  }
  nombreAlumno[6] = '\0';
  for (int n = 0; n < 6; n++) {
    int key = rand() % (int)(sizeof(charset) - 1);
    apellidoAlumno[n] = charset[key];
  }
  apellidoAlumno[6] = '\0';
}


int main(){
  srand(time(NULL));
  //8 cursos, 4 por semestre
  curso cursos[8] = {
    {"INF245",1},
    {"INF285",1},
    {"INF360",1},
    {"INF225",1},
    {"INF292",2},
    {"INF322",2},
    {"INF266",2},
    {"INF228",2}
  };

  //Gneración del archivo cursos.dat
  FILE* fp;
  fp = fopen("cursos.dat", "w");
  if( fp == NULL ){
    perror("No se pudo abrir el archivo");
    exit(1);
  }

  int n = 8;
  fwrite( &n, sizeof(int), 1, fp );
  fwrite( cursos, sizeof(curso),n,fp);
  fclose(fp);

  //Generamos una lista con roles
  char listaRol[CANT_ALUM][12] = {{""}};
  for (int index = 0; index < CANT_ALUM; index++) {
    genRol();
    strcpy(listaRol[index], randomString);
  }

  //Generamos el archivo con nombres
  fp = fopen("alumnos.txt", "w");
  if( fp == NULL ){
    perror("No se pudo abrir el archivo");
    exit(1);
  }

  //FIX: Numero total de alumnos
  fprintf(fp, "%d\n", CANT_ALUM);

  for (int i = 0; i < CANT_ALUM; i++) {
    char anio[5];
    anio[0] = listaRol[i][0];
    anio[1] = listaRol[i][1];
    anio[2] = listaRol[i][2];
    anio[3] = listaRol[i][3];
    anio[4] = '\0';
    genNombre();
    fprintf(fp, "%s %s %s %s\n", listaRol[i], nombreAlumno, apellidoAlumno, anio);
  }

  fclose(fp);

  //Ahora generamos las notas
  nota notas[CANT_ALUM*CANT_NOTA] = {{"", "", 0}};
  int index = 0;
  for (int i = 0; i < CANT_ALUM; i++) {
    for (int j = 0; j < CANT_NOTA; j++) {
      strcpy(notas[index].rolEstudiante, listaRol[i]);
      strcpy(notas[index].siglaCurso, cursos[j].sigla);
      notas[index].nota = rand() % 100 + 1;
      index++;
    }
  }
  //Gneración del archivo notas.dat
  fp = fopen("notas.dat","w");
  if( fp == NULL ){ perror("No se pudo abrir el archivo"); exit(1);}

  n = CANT_ALUM*CANT_NOTA;
  fwrite(&n,sizeof(int),1,fp);
  fwrite(notas,sizeof(nota),n,fp);
  fclose(fp);

  printf("Archivos escritos\n");

  return 0;
}
