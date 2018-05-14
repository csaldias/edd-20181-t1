#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  char sigla[7];
  int semestre;  /* 1er o 2do semestre*/
} curso;

typedef struct {
  char rolEstudiante[12];
  char siglaCurso[7];
  int nota;
} nota;

typedef struct {
    char rol[12];
    char nombre[50];
    char apellido[50];
    int anio;
} alumno;

int main(){
    FILE *notasF, *cursosF, *alumnosF;
    curso *cursos;
    nota *notas;
    alumno *alumnos;
    int cAlumnos, cNotas, cCursos, semestre1 = 0, semestre2 = 0;
    int i,j,k;
    
    notasF = fopen("notas.dat", "rb");
    cursosF = fopen("cursos.dat", "rb");
    alumnosF = fopen("alumnos.txt", "r");
    
    fread(&cNotas, sizeof(int), 1, notasF);
    fread(&cCursos, sizeof(int), 1, cursosF);
    fscanf(alumnosF, "%d", &cAlumnos);
    
    cursos = (curso*)malloc(sizeof(curso)*cCursos);
    notas = (nota*)malloc(sizeof(nota)*cNotas);
    alumnos = (alumno*)malloc(sizeof(alumno)*cAlumnos);
    
    fread(cursos, sizeof(curso), cCursos, cursosF);
    fread(notas, sizeof(nota), cNotas, notasF);
    
    for(i = 0; i < cAlumnos; ++i){
        fscanf(alumnosF, "%s %s %s %d", alumnos[i].rol, alumnos[i].nombre, alumnos[i].apellido, &alumnos[i].anio);
    }
    
    fclose(notasF);
    fclose(cursosF);
    fclose(alumnosF);
    
    for(i = 0; i < cCursos; ++i){
        
        if(cursos[i].semestre == 1){
            ++semestre1;
        }
        else{
            ++semestre2;
        }
    }
    
    FILE *s1 = fopen("aprobados-s1.txt", "w");
    FILE *s2 = fopen("aprobados-s2.txt", "w");
    
    for(i = 0; i < cAlumnos; ++i){
        int aprobados1 = 0;
        int aprobados2 = 0;
        nota **apr1 = (nota**)malloc(sizeof(nota*)*semestre1);
        nota **apr2 = (nota**)malloc(sizeof(nota*)*semestre2);
        
        for(j = 0; j < cNotas; ++j){
            if(!strcmp(alumnos[i].rol, notas[j].rolEstudiante)){
                if(notas[j].nota >= 55){
                    for(k = 0; k < cCursos; ++k){
                        if(!strcmp(notas[j].siglaCurso, cursos[k].sigla)){
                            if(cursos[k].semestre == 1){
                                apr1[aprobados1] = &notas[j];
                                ++aprobados1;
                            }
                            
                            else{
                                apr2[aprobados2] = &notas[j];
                                ++aprobados2;
                            }
                        }
                    }
                }
            }
        }
        
        if(aprobados1 == semestre1){
            fprintf(s1, "%s %s %s", alumnos[i].nombre, alumnos[i].apellido, alumnos[i].rol);
            for(j = 0; j < semestre1; ++j){
                fprintf(s1, " %s %d", apr1[j] -> siglaCurso, apr1[j] -> nota);
            }
            fprintf(s1,"\n");
        }
        
        if(aprobados2 == semestre2){
            fprintf(s2, "%s %s %s", alumnos[i].nombre, alumnos[i].apellido, alumnos[i].rol);
            for(j = 0; j < semestre2; ++j){
                fprintf(s2, " %s %d", apr2[j] -> siglaCurso, apr2[j] -> nota);
            }
            fprintf(s2,"\n");
        }
        
        free((void*)apr1);
        free((void*)apr2);
    }
    
    fclose(s1);
    fclose(s2);
    free((void*)cursos);
    free((void*)notas);
    free((void*)alumnos);
    return 0;
}