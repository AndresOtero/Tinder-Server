Manual técnico
======================================
Para las siguientes tareas, es necesario previamente haber configurado el proyecto (ver Manual de Usuario)

Tests
--------------------------
Para correr la suit de tests de la aplicación, parado en la raiz del proyecto, se debe ejecutar:

``$ ./build/test/applib/testapp``

Lo cual ejecuta los tests sobre la funcionalidad de la aplicación.

Code Coverage
--------------------------
Es posible generar un reporte de cobertura de tests mediante el uso del script apropiado ubicado dentro del directorio raíz del repositorio:

``$ ./codeCoverage.sh``

La sentencia anterior genera el archivo “build/coverage-report/index.html” el cual se puede abrir con cualquier navegador. En éste se puede ver el reporte generado.

Documentación automática
--------------------------
Para generar el reporte del código automática, parado dentro de la carpeta build, se debe ejecutar el siguiente target del make

``$ make doxyDoc``

Esto genera el archivo “doxyDoc/html/index.html” que se puede abrir con cualquier navegador y permite visualizar la información referente al código de la aplicación.