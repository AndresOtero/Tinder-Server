Manual de usuario
======================================
Para poder utilizar este servidor, existen dos posibilidades Nativo, o por Docker, cada una se explica a continuación.

Nativo (Solo Ubuntu 14.04 y 15.10)
------------------------------------------
Es necesario tener instalado git y hacer una copia del repositorio donde se encuentra el proyecto:

``git clone git@github.com:Tinder2Team/Tinder-Server.git``

Luego es necesario correr el script que descarga todas las dependencias necesarias y deja la aplicación lista para correr:

* Ubuntu 14.04: ``$ sudo config.h -oldboost``
* Ubuntu 15.10: ``$ sudo config.h``

Y luego se la aplicación se puede correr con:

``$ ./build/server/server``

Docker (Plataformas compatibles con Docker)
---------------------------------------------
Para este método sólo es necesario tener instalado Docker, de esta manera, sólo se debe ejecutar:

``$ sudo docker run -p 0.0.0.0:8000:8000 jtierno/tinder-server /bin/sh -c "./server/server"``

y el servidor en ambos qué casos queda levantado en el puerto 8000 esperando por peticiones.

Configuración externa
---------------------
Para poder parametrizar ciertos parámetros del servidor se puede proveer un archivo de configuración de la siguiente forma:

``/server -config config.json``

Donde ``config.json`` es un archivo en formato json, como por ejemplo:

.. code-block:: jsonld

	{
	  "Log_Level" : "debug",
	  "Shared_URL" : "http://tinder-shared.herokuapp.com",
	  "Local_DB" : "/tmp"
	}

Pudiendo variar los siguientes Parámetros

- **Log_Level:** Indica el nivel de log del servidor, las opciones habilitadas son:

	- trace
	- debug
	- info
	- warning
	- error
	- fatal

- **Shared_URL:** Es la dirección del shared server a donde hacer las consultas de perfiles de usuario.
- **Local_DB:** Directorio donde se almacena la base de datos.