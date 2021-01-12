### Sistemas Operativos

# Tarea3-SO

Este repositorio contiene la elaboración de la Tarea 3 de la asignatura Sistemas Operativos de la UTFSM.

Consiste en el uso de **threads** en el lenguaje de programación `Java`.

Desarrollado por Tomás Guttmann y Guillermo Fuentes

## Problema 1

**Objetivo**

resolver ecuaciones de funciones dependientes entre sí.

**Input**

* Archivo `funciones.txt` cuya primera línea son el número de funciones a utilizar y las siguientes líneas son dichas funciones.
* Se debe ingresar por consola la operación a realizar con las funciones del archivo de texto.

**Consideraciones**

* Se debe generar un `thread` para resolver la ecuación.
* Se debe generar un `thread` para funciones anidadas.

## Problema 2

**Objetivo**

Probar dos algoritmos de ordenamiento, uno sin `threads` y otro utilizando `threads`.

**Input**

Archivo `input.txt` que contiene en su primera línea la cantidad de conjuntos de números y a continuación, dicha cantidad de secuencias en líneas distintas.

## Instrucciones de Compilación

**Problema 1**

Utilizar make compile-problem-1 para compilar
Utilizar make run-problem-1

**Problema 2**

Utilizar make compile-problem-2 para compilar
Utilizar make run-problem-2 

## Análisis del Problema 2

Se utilizó el algoritmo QuickSort, con y sin hebras. Su uso, en este caso, no beneficia este algoritmo de ordenamiento, pues como se puede apreciar en la salida por consola, nomejora el tiempo de ejecución.
