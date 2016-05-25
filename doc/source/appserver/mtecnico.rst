Manual técnico
======================================
Configuración del proyecto
--------------------------
Dentro del directorio raíz del proyecto existe un script que permite configurar la aplicación.
Se puede listar una ayuda completa mediante la ejecución de:

``$ ./config.sh -h``

Obteniendo la siguiente salida

.. code-block:: console

     Uso: ./config.sh [option...]. 
          -h, --help         Imprimir esta ayuda.
          -g++-5             Flag g++-5 para cmake.
          -oldboost          Compatibilidad de boost para linux version 14.04.
          -test              Habilita los tests.
          -coverage          Habilita coverage y agrega -test.
          -doxydoc           Habilita documentación doxy.
          -dependencies      Instala dependencias.
          -dev               Atajo para -test -doxydoc -coverage.


Tests
--------------------------
Para correr la suit de tests de la aplicación, es necesario configurar el proyecto con **'-test'** y luego parado en la raiz del proyecto, se debe ejecutar:

``$ ./build/test/applib/testapp``

Lo cual ejecuta los tests sobre la funcionalidad de la aplicación.

Tests de Integración
--------------------------







Code Coverage
--------------------------
Es posible generar un reporte de cobertura de tests mediante el correspondiente target de make, dentro del directorio build:

``$ make coverage``

La sentencia anterior genera el archivo “build/coverage-report/index.html” el cual se puede abrir con cualquier navegador. En éste se puede ver el reporte generado.
Para poder ejecutar este target de make previamente el proyecto se debe haber configurado con la opción **'-coverage'**

Documentación automática
--------------------------
Previamente habiendo configurado el proyecto con el flag **'-doxydoc'**
Para generar el reporte del código automática, parado dentro de la carpeta build, se debe ejecutar el siguiente target del make

``$ make doxyDoc``

Esto genera el archivo “doxyDoc/html/index.html” que se puede abrir con cualquier navegador y permite visualizar la información referente al código de la aplicación.

