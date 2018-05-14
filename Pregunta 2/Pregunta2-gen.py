from random import randint, choice

#Definimos la cantidad de palabras, sitios web y consultas
cant_palabras  = 300
cant_sitiosweb = 50
cant_consultas = 100

#Cuántos sitios web (max) por cada palabra?
max_web_palabra = 20

#Generamos el archivo de palabras
arch_palabras = open("palabras.dat", "w")
for _ in range(cant_palabras):
    valores = []

    num_webs = randint(1, max_web_palabra)
    valores.append(str(num_webs))
    #Los sitios web de una palabra NO se repiten entre sí
    webs = list(range(1, cant_sitiosweb+1))

    for _ in range(num_webs):
        #Necesitamos que los sitios web de una palabra NO se repitan entre sí
        num_web = choice(webs)
        webs.remove(num_web)
        valores.append(str(num_web))

    linea = " ".join(valores)
    arch_palabras.write(linea+"\n")
arch_palabras.close()

#Generamos el archivo de consultas
arch_consultas = open("consultas.dat", "w")
for _ in range(cant_consultas):
    palabra_1 = randint(0, cant_palabras-1)
    palabra_2 = randint(0, cant_palabras-1)
    while (palabra_1 == palabra_2):
        palabra_2 = randint(0, cant_palabras-1)
    arch_consultas.write(str(palabra_1)+" "+str(palabra_2)+"\n")
arch_consultas.close()
