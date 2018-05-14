#Lo primero es cargar las palabras con sus páginas web
arch_palabras = open("palabras.dat", "r")
palabras = {}
index = 0
for palabra in arch_palabras:
    valores = list(map(int, palabra.strip().split(" ")))
    del valores[0]
    palabras[index] = valores
    index += 1
arch_palabras.close()

#Ahora, cargamos el archivo de consultas
#Para las consultas, haremos la intersección de los conjuntos
#asociados a las páginas web de cada palabra
arch_salida = open("salida.dat", "w")
arch_consultas = open("consultas.dat", "r")
for consulta in arch_consultas:
    valores = list(map(int, consulta.strip().split(" ")))
    print("Consulta: "+str(valores[0])+" "+str(valores[1]))
    comunes = list(set(palabras[valores[0]]) & set(palabras[valores[1]]))
    if comunes == []:
        arch_salida.write("0\n")
    else:
        largo = str(len(comunes))
        comunes.sort()
        str_comunes = " ".join(map(str, comunes))
        arch_salida.write(largo+" "+str_comunes+"\n")
arch_salida.close()
