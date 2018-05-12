#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
  char sigla[7];
  int semestre;
} curso ;

typedef struct {
  char rol_estudiante[12];
  char sigla_curso[7];
  int nota;
} nota;

int main(){
  //tres cursos - mate, fisica, progra
  curso curso_temp;
  nota nota_temp;
  FILE *fp;
  fp = fopen("cursos.dat","r");
  if( fp == NULL ){ perror("No se pudo abrir el archivo"); exit(1);}

  int n;
  fread(&n, sizeof(int), 1, fp);
  for(int i=0;i<n;i++){
    fread(&curso_temp,sizeof(curso),1,fp);
    printf("Curso %s %d\n",curso_temp.sigla,curso_temp.semestre);
  }
  fclose(fp);

  fp = fopen("notas.dat","r");
  if( fp == NULL ){ perror("No se pudo abrir el archivo"); exit(1);}

  fread(&n, sizeof(int), 1, fp);
  for(int i=0;i<n;i++){
    fread(&nota_temp,sizeof(nota),1,fp);
    printf("Nota %s %s %d\n",nota_temp.rol_estudiante, nota_temp.sigla_curso, nota_temp.nota);
  }
  fclose(fp);

  return 0;
}
