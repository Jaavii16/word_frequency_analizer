# Analizador de Frecuencia de Palabras (C++)

Este es un proyecto académico de la asignatura "Programming Techniques", desarrollado durante mi estancia Erasmus.

El programa es una aplicación de consola en C++ diseñada para analizar un gran corpus de documentos de texto (~7600 archivos). Calcula la frecuencia de cada palabra y proporciona herramientas para buscar palabras y generar informes.

## Características Principales

* **Procesamiento de Archivos:** Carga y procesa miles de archivos de texto, agrupándolos en tres diccionarios de diferente tamaño (documentos 1-100, 1-1000 y 1-7600).
* **Estructura de Datos Eficiente:** Utiliza `unordered_map` (tabla hash) de C++ para almacenar los diccionarios, permitiendo una **búsqueda de palabras con un coste medio de O(1)**.
* **Búsqueda de Palabras:** Permite al usuario buscar una palabra específica y el programa informa si existe y en qué diccionarios (rangos de documentos) ha sido encontrada.
* **Generación de Informes HTML:** Crea automáticamente archivos HTML para cada diccionario. Cada informe contiene una tabla con todas las palabras, su **frecuencia absoluta** (conteo total) y su **frecuencia relativa** (porcentaje sobre el total).

## Funcionalidad del Menú

La aplicación se controla a través de un menú de consola interactivo:

1.  **Cargar Diccionarios:** Inicia el proceso de lectura de los ~7600 archivos .txt.
2.  **Buscar una Palabra:** Solicita una palabra al usuario y la busca en los diccionarios cargados.
3.  **Generar Salida HTML:** Crea los archivos `dictionary1.html`, `dictionary2.html` y `dictionary3.html` con los informes de frecuencia.
4.  **Salir:** Cierra el programa.
