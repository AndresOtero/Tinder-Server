======================================
Especificación de la API
======================================
En esta sección se idica la especificación completa de la interfaz de la aplicación. La misma es una api tipo REST con interacciones en formato JSON.

* :ref:`codigos-docs`
* :ref:`seguridad-docs`
* :ref:`auth-docs`

****

.. _codigos-docs:


Códigos de error
================

Cualquier respuesta de la aplicacón, ademas del uso de los clásicos códigos de status HTTP pueden estar acompañados de un código interno de status para proveer mas información al cliente.

Mientras una respuesta común es del tipo

.. code-block:: jsonld

   {"response": "", "status": "XXX"}


Donde 
	- response: Respuesta esperada.
	- status: Código de estado interno.

El código XXX es un número de estado del listado siguiente

* 200: No hay información extra, la petición se completó con éxito;
* 101: Es necesario crear un perfíl de usuario.
* 102: El usuario ya existe.
* 103: Se alcancó el límite diario de candidatos consultados.

****

.. _seguridad-docs:


Token de Seguridad
====================

Para cualquier petición que requiera seguridad, además de los parámetros es necesario proporcionar el encabezado http de uso interno con el correspondiente token de seguridad brindado al autenticar en la aplicación

- Nombre: ``SECURITY-TOKEN``
- Valor: El token proporcionado por la aplicación al autenticar.


****

.. _auth-docs:

Autenticación
===============

Permite a un usuario gestionar su registro que es la información mínima para poder operar con la aplicación.

Registrar Usuario
------------------

Crea un registro en la aplicación para posteriormente poder loguear en la misma.

- *Método HTTP:* ``POST``
- *URL:* ``/auth``
- *Seguridad:* ``Sin seguridad``

*Ejemplo de request*

.. code-block:: jsonld

   {"user":"usuario", "password":"pass"}

*Respuesta*

.. code-block:: jsonld  

	{
	   "response":{
	      "token":"eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9Cg==.eyJleHAiOiJXZWQgTWF5IDI1IDE2OjU3OjA1IDIwMTZcbiIsImlzcyI6IlRpbmRlcjItU2hhcmVkIiwibmFtZSI6ImNoZWxvNCJ9Cg==.eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9Cg==eyJleHAiOiJXZWQgTWF5IDI1IDE2OjU3OjA1IDIwMTZcbiIsImlzcyI6IlRpbmRlcjItU2hhcmVkIiwibmFtZSI6ImNoZWxvNCJ9Cg=="
	   },
	   "status":101
	}

Como se puede ver indica el status code 101, y además devuelve el token de seguridad que indica que el usuario ya puede operar con la aplicación utilizándolo.


Autenticar
------------------

Permite autenticar en el servidor con un registro ya creado.

- *Método HTTP:* ``PUT``
- *URL:* ``/auth``
- *Seguridad:* ``Sin seguridad``

*Ejemplo de request*

.. code-block:: jsonld

   {"user":"usuario", "password":"pass"}

*Respuesta*

.. code-block:: jsonld  

	{
	  "response": {
	    "token": "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9Cg==.eyJleHAiOiJXZWQgTWF5IDI1IDE3OjA5OjE2IDIwMTZcbiIsImlzcyI6IlRpbmRlcjItU2hhcmVkIiwibmFtZSI6ImNoZWxvMyJ9Cg==.eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9Cg==eyJleHAiOiJXZWQgTWF5IDI1IDE3OjA5OjE2IDIwMTZcbiIsImlzcyI6IlRpbmRlcjItU2hhcmVkIiwibmFtZSI6ImNoZWxvMyJ9Cg=="
	  },
	  "status": 200
	}

Como se puede ver indica el status code 200, y además devuelve el token de seguridad que indica que el usuario ya puede operar con la aplicación utilizándolo.


Eliminar Registro
------------------

Elimina el registro del sistema con toda su información relacionada.

- *Método HTTP:* ``DELETE``
- *URL:* ``/auth``
- *Seguridad:* ``Con seguridad``

*Ejemplo de request*

.. code-block:: jsonld

   {"password":"usuario"}

*Respuesta*

 ``http status code: 200``

Responde con el http status code correspondiente para la operación.

.. _user-docs:

Usuario
===============

Permite a un usuario administrar su información de perfil.

Actualizar Perfil
------------------

Permite actualizar la información de perfil del usuario logueado.

- *Método HTTP:* ``POST``
- *URL:* ``/user``
- *Seguridad:* ``Con seguridad``

*Ejemplo de request*

.. code-block:: jsonld

   {
        "name": "jose",
        "age": 35,
        "sex": "M",
        "alias": "pepe",
        "email": "jose@tumail.com",
        "location": {
            "longitude": 21,
            "latitude": 12
        },
        "interests": [
            {
                "value": "river",
                "category": "futbol"
            },
            {
                "value": "pizza",
                "category": "comida"
            },
            {
                "value": "helado",
                "category": "comida"
            }
        ]
    }

*Respuesta*

 ``http status code: 200``

Responde con el http status code correspondiente para la operación.

Consultar Perfil
------------------------------

Obtiene la información del perfil del usuario logueado.

- *Método HTTP:* ``GET``
- *URL:* ``/user``
- *Seguridad:* ``Con seguridad``

*Respuesta*

.. code-block:: jsonld  

	{
	  "response": {
	    "age": 35,
	    "alias": "pepe",
	    "email": "pepe@unemail.com",
	    "externalId": 95,
	    "id": "pepe@unemail.com",
	    "interests": null,
	    "location": {
	      "latitude": 12,
	      "longitude": 21
	    },
	    "name": "jose",
	    "photo_profile": "",
	    "sex": "M"
	  },
	  "status": 200
	}

Responde con estado interno 200 y la información del usuario.


Ubicación
===============

Permite a un usuario gestionar su ubicación geográfica.

Actualizar Ubicación
--------------------

Actualiza las coordenadas de ubicación del usuario.

- *Método HTTP:* ``POST``
- *URL:* ``/location``
- *Seguridad:* ``Con seguridad``

*Ejemplo de request*

.. code-block:: jsonld

	{
	    "longitude": 33223,
	    "latitude": 12
	}
        
*Respuesta*

 ``http status code: 200``


Intereses
===============

Permite a un usuario gestionar sus.

Obtener Intereses
--------------------

Lista los intereses disponibles

- *Método HTTP:* ``GET``
- *URL:* ``/interest``
- *Seguridad:* ``Con seguridad``
        
*Respuesta*

.. code-block:: jsonld

	{
	  "response": {
	    "interests": [
	      {
	        "category": "musica",
	        "value": "beatles"
	      },
	      {
	        "category": "musica",
	        "value": "los redondos"
	      },
	      {
	        "category": "comida",
	        "value": "alfajor"
	      }]
	  },
	  "status": 200
	}


Agregar Intereses
--------------------

Actualiza la lista de intereses del usuario

- *Método HTTP:* ``POST``
- *URL:* ``/interest``
- *Seguridad:* ``Con seguridad``

*Ejemplo de request*

.. code-block:: jsonld

	{
	    "interests": [
	            {
	                "category":"futbol",
	                "value": "river"
	            },{
	                "category":"futbol",
	                "value": "Aldosivi"
	            },{
	                "category":"futbol",
	                "value": "independiente"
	            }
	    ]
	}
        
*Respuesta*

 ``http status code: 200``


Eliminar Interés
--------------------

Elimina un Interés de un usuario

- *Método HTTP:* ``DELETE``
- *URL:* ``/interest``
- *Seguridad:* ``Con seguridad``

*Ejemplo de request*

.. code-block:: jsonld

	{
	    "category":"futbol",
	    "value": "independiente"

	}
        
*Respuesta*

 ``http status code: 200``



Candidatos
===============

Permite al usuario conocer la lista diaria de candidatos a match.

- *Método HTTP:* ``GET``
- *URL:* ``/candidates``
- *Seguridad:* ``Con seguridad``
        
*Respuesta*

.. code-block:: jsonld

	{
	   "response":{
	      "candidates":[
	         {
	            "age":28,
	            "alias":"caca",
	            "email":"unemail@gmail.com",
	            "externalId":94,
	            "id":"unemail@gmail.com",
	            "interests":[
	               {
	                  "category":"futbol",
	                  "value":"racing"
	               },
	               {
	                  "category":"musica",
	                  "value":"la renga"
	               },
	               {
	                  "category":"comida",
	                  "value":"pastel"
	               },
	               {
	                  "category":"comida",
	                  "value":"pizza"
	               }
	            ],
	            "location":{
	               "latitude":0,
	               "longitude":0
	            },
	            "name":"Bufarini",
	            "photo_profile":"",
	            "sex":"M"
	         },
	         {
	            "age":18,
	            "alias":"jj",
	            "email":"@",
	            "externalId":43,
	            "id":"@",
	            "interests":[
	               {
	                  "category":"music",
	                  "value":"beatles"
	               },
	               {
	                  "category":"comida",
	                  "value":"pizza"
	               }
	            ],
	            "location":{
	               "latitude":65.966700000000003,
	               "longitude":-18.533300000000001
	            },
	            "name":"hh",
	            "photo_profile":"",
	            "sex":"M"
	         }
	      ]
	   },
	   "status":200
	}


Matching
===============

Permite al usuario conectar con otros usuarios.


Obtener Matchs
---------------

Lista todos los matchs de un usuario.

- *Método HTTP:* ``GET``
- *URL:* ``/match``
- *Seguridad:* ``Con seguridad``
        
*Respuesta*

.. code-block:: jsonld

	{
	   "response":{
	      "candidates":[
	         {
	            "age":28,
	            "alias":"caca",
	            "email":"unemail@gmail.com",
	            "externalId":94,
	            "id":"unemail@gmail.com",
	            "interests":[
	               {
	                  "category":"futbol",
	                  "value":"racing"
	               },
	               {
	                  "category":"musica",
	                  "value":"la renga"
	               },
	               {
	                  "category":"comida",
	                  "value":"pastel"
	               },
	               {
	                  "category":"comida",
	                  "value":"pizza"
	               }
	            ],
	            "location":{
	               "latitude":0,
	               "longitude":0
	            },
	            "name":"Bufarini",
	            "photo_profile":"",
	            "sex":"M"
	         },
	         {
	            "age":18,
	            "alias":"jj",
	            "email":"@",
	            "externalId":43,
	            "id":"@",
	            "interests":[
	               {
	                  "category":"music",
	                  "value":"beatles"
	               },
	               {
	                  "category":"comida",
	                  "value":"pizza"
	               }
	            ],
	            "location":{
	               "latitude":65.966700000000003,
	               "longitude":-18.533300000000001
	            },
	            "name":"hh",
	            "photo_profile":"",
	            "sex":"M"
	         }
	      ]
	   },
	   "status":200
	}