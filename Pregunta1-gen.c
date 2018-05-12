#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//Constantes para el número de cursos y alumnos a generar
#define CANT_ALUM 100

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

int main(){
  //20 cursos, 10 por semestre
  curso cursos[20] = {
    {"INF245",1},
    {"INF285",1},
    {"INF360",1},
    {"INF225",1},
    {"INF256",1},
    {"INF239",1},
    {"INF236",1},
    {"INF280",1},
    {"INF152",1},
    {"INF295",1},
    {"INF292",2},
    {"INF322",2},
    {"INF266",2},
    {"INF228",2},
    {"INF155",2},
    {"INF276",2},
    {"INF246",2},
    {"INF260",2},
    {"INF309",2},
    {"INF221",2}
  };

  //Gneración del archivo cursos.dat
  FILE* fp;
  fp = fopen("cursos.dat", "w");
  if( fp == NULL ){
    perror("No se pudo abrir el archivo");
    exit(1);
  }

  int n = 20;
  fwrite( &n, sizeof(int), 1, fp );
  fwrite( cursos, sizeof(curso),20,fp);
  fclose(fp);

  //CANT_ALUM notas
  nota notas[CANT_ALUM] = {};

  //Gneración del archivo notas.dat
  fp = fopen("notas.dat","w");
  if( fp == NULL ){ perror("No se pudo abrir el archivo"); exit(1);}

  n = CANT_ALUM;
  fwrite(&n,sizeof(int),1,fp);
  fwrite(notas,sizeof(nota),n,fp);
  fclose(fp);

  printf("Archivos escritos\n");

  return 0;
}
