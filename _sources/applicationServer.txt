==============================================
**Application Server**
==============================================

*Tecnologías principales*
======================================
- C++: Lenguaje base.
- Mongoose (Cesanta): Servidor web embebido para gestión de las conexiones web.
- RocksDB: Base de datos tipo Clave-Valor utilizada en el almacenamiento interno.
- JSONCpp: Conversión de datos JSON.
- CURL: Conexión con el Shared Server.


*Descripción de solución implementada*
======================================
Estructura general
---------------------
La arquitectura básica de la aplicación es una estructura por capas de la siguiente manera:

.. figure:: images/layers.png
   :align:   center

WEBSERVER y DISPATCHER se pueden ver como dos subcapas  de una misma capa diseñada para resolver el problema de recibir las peticiones y delegar correctamente su procesamiento.
En la capa WEBSERVER se manejan las conexiones web entrantes y adapta los datos que las componen para ser interpretados en la capa DISPATCHER. DISPATCHER determina el handler correcto para la petición y delega su procesamiento. Estos handlers se encuentran ubicados en la capa API, la cual se encarga de enviar el procesamiento a los objetos con la lógica de negocio ubicados en la capa SERVICE, que como su nombre lo indica, tiene los servicios que proveen el core de la funcionalidad. En una instancia inferior están DAO y CONNECTOR, quienes proveen un acceso homogéneo a datos y conexión a los sistemas adyacentes (la base de datos y el Shared Server) respectivamente.

Webserver
------------
En esta capa se encuentran una serie de clases que hacen el manejo de las conexiones entrantes.

.. figure:: images/webserver.png
   :align:   center

Donde WebServer tiene la responsabilidad de recibir las peticiones  y delegarlas al RequestDispatcher, encargado de procesarlo y generar la respuesta adecuada. Por otro lado RestRequest brinda el acceso a los datos de la petición, y RestResponse se encarga de recibir los datos que se transformarán luego en la respuesta a la petición web.

Dispatcher  
------------
Una vez recibida la petición es necesario determinar si hay un handler o no para atender la petición, esto es manejado por esta capa:

.. figure:: images/dispatching.png
   :align:   center

En este caso ApiDispatcher es encargado de delegar a una cadena de EndPoints distinta según el método HTTP de la petición (PUT, POST, GET y DELETE). Los EndPoints forman una Chain of Responsability donde si no se puede manejar la petición, es lanzada una excepción capturada por el dispatcher y da como resultado un 403 Forbidden. WebContext es como un contenedor de más alto nivel para la petición y su respuesta, este crecerá para brindar un contexto más rico al contexto del handler de la petición. Por otro lado se encuentra la interfaz RestResource que será implementada por todas aquellas clases que proveen handlers para una serie de peticiones relacionadas, como pueden ser los métodos relacionados la entidad Usuario.

Secuencia de respuesta a una petición web
------------------------------------------
.. figure:: images/secuenciarespuesta.png
   :align:   center

API
------------
Dentro de esta capa se encontrarán las diferentes implementaciones de RestResource quienes serán los handlers concretos a los pedidos. Actualmente no hay ningún endpoint habilitado para ser consultado.

Service
------------
En esta capa se proveen los servicios básicos del modelo de negocios, proveyendo las funcionalidades necesarias para resolver los requests recibidos, más no poseen ningún conocimiento sobre cómo son almacenados estos datos. Para ello, hacen uso de alguno de los DAO ofrecidos. Los servicios provistos son: autenticación, administración de perfiles de usuario,  conversaciones y búsqueda de candidatos(no implementado aun). 

DAO
------------
Se trata de una capa intermedia entre la de connectors y la de servicios. Aquí se mapean los datos recibidos de las distintas fuentes con las clases del modelo de negocio utilizadas por la capa superior. Dentro se encuentra ChatDAO que provee funcionalidad para obtener los mensajes del chat que usando un DBConnector permite obtener y guardar mensajes que un usuario origen envía a otro usuario destino. 
Otro de los componentes de esta capa es  MatchDAO que brinda la posibilidad de almacenar y recuperar matches que se dan entre dos usuarios.

Connector
------------
Esta última capa es la encargada de las comunicaciones entre los distintos componentes que forman la aplicación, en este caso la base de datos (RocksDB) y el Shared Server. En ambos connectors se ofrecen todos los metodos necesario para intercambiar información con su par del otro lado. Sin embargo, no poseen ningún tipo de conocimiento sobre la forma de los datos que están enviando o recibiendo. Su única función es proveer una interfaz de comunicación.

*Manual de usuario*
======================================
Para poder utilizar este servidor, existen dos posibilidades Nativo, o por Docker, cada una se explica a continuación.

Nativo (Solo Ubuntu 14.04 y 15.10)
------------------------------------------
Es necesario tener instalado git y hacer una copia del repositorio donde se encuentra el proyecto:

``git clone git@github.com:Tinder2Team/Tinder-Server.git``

Luego es necesario correr el script que descarga todas las dependencias necesarias y deja la aplicación lista para correr:

| Ubuntu 14.04: ``$ sudo config.h -oldboost``

Ubuntu 15.10: ``$ sudo config.h``

Y luego se la aplicación se puede correr con:

``$ ./build/server/server``

Docker (Plataformas compatibles con Docker)
---------------------------------------------
Para este método sólo es necesario tener instalado Docker, de esta manera, sólo se debe ejecutar:

``$ sudo docker run -p 0.0.0.0:8000:8000 jtierno/tinder-server /bin/sh -c "./server/server"``

y el servidor en ambos qué casos queda levantado en el puerto 8000 esperando por peticiones.

*Manual técnico*
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