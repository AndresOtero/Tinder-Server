=====================
Solución Implementada
=====================

Estructura general
==================


.. image:: images/arq1.png
   :height: 300px
   :width: 300px
   :scale: 100%
   :alt: Layers
   :align: center

La arquitectura del cliente de android es bastante robusta. A continuación se representa en forma reducida mediante un diagrama.

Cada Android Activity (X Activity: UserActivity, LoginActivity, etc), utiliza algun servicio. 

Existen varios tipos de Service: AccountService, UserService, MatchService, ChatService, etc). Son encargados de resolver las distintas funcionalidades: Cuentas, Usuarios, Matchs, Chats, etc.

Los Servicios utilizan por detrás un Connector, el cual es un Singleton que contiene un wrapper de Volley. 
Este conector es el encargado de comunicarse con el servidor mediante la REST API.

.. image:: images/arq2.png
   :height: 300px
   :width: 300px
   :scale: 100%
   :alt: Layers
   :align: center
   


**Dispatcher:** Módulo encargado de crear los pedidos que realiza el connector. Cada Dispatcher conoce la parte de la API REST que le corresponde.


**Receiver:** Módulo encargado de recibir y parsear las respuestas del connector. Sabe cómo interpretar las respuestas y crear los elementos necesarios.

**Linker:** Este módulo se encarga de trasladar la información procesada por el Receiver a la Activity que corresponde. Conoce los elementos de la UI y sabe cómo debe impactarlos. También sabe cómo trasladar los errores a la UI.


.. image:: images/arq3.png
   :height: 500px
   :width: 500px
   :scale: 100%
   :alt: Layers
   :align: center


En el esquema superior, se muestra un ejemplo tomando el caso del AccountService. Como observamos, el AccountService esta compuesto por un AccountReceiver, AccountLinker y AccountDispatcher.

En este caso, el AccountDispatcher conoce los pedidos que debe realizar. Estos pedidos son: Account Login, Account Register. 
El Account Receiver conoce las respuestas que devuelve el servidor, sabe cómo interpretarlas y actuar en base a ello. Algunas respuestas: Invalid Account, Account Created OK, etc.
El AccountLinker en este caso conoce la actividad que lo esté invocando. En este caso puede llamarse de 2 actividades: LoginActivity, RegisterActivity. Es el encargado de realizar los cambios visuales en esta actividades.

Lo mismo se realiza para los demás Service.




Casos Particulares
==================

Location 
---------

.. image:: images/loc.png
   :height: 300px
   :width: 300px
   :scale: 100%
   :alt: Layers
   :align: center

La ubicacion del usuario es actualizada cada una cierta cantidad de tiempo (ej: 30 minutos). Esto se realiza corriendo una tarea de fondo en Android.

Esto se realiza utilizando un “IntentService” provisto por la SDK de android. 


En este service se solicita la ubicacion del dispositivo (previamente se debe haber aceptado el permiso) y se envia constantemente al App Server.



Chat Service
------------

.. image:: images/Chat.png
   :height: 400px
   :width: 400px
   :scale: 100%
   :alt: Layers
   :align: center

Algo similar se utiliza en el lado del chat. Donde se cuenta con un Intent Service en este caso para analizar si existen nuevas notificaciones.

En el caso de existir nuevas notificaciones, se levanta una notificación nativa utilizando el Notification Service.


Workflow
==========


.. image:: images/workflow.png
   :height: 600px
   :width: 800px
   :scale: 100%
   :alt: Layers
   :align: center

A continuación se representa el flujo de trabajo más común.
Se comienza realizando un intento de Login. Se puede producir un error debido a credenciales inválidas (email, password), en el caso de error se marcan los elementos inválidos y se le da otra oportunidad. 

En el caso exitoso, pueden ocurrir dos cosas. La primera, que el usuario no haya creado un perfil. En tal caso el usuario debe completar sus datos en la actividad correspondiente. Si el usuario ya ha creado su perfil, entonces directamente se procede al Main Activity.

En el Main Activity, los usuarios puede proceder a encontrar nuevos contactos. De ser asi, se solicita al servidor por nuevos candidatos. 

La cantidad de candidatos que el servidor envía, esta limitada a una cierta cantidad por dia. Superando este límite, los usuarios no podrán obtener más candidatos.

El servidor analiza la posición geográfica del usuario y le envía supuestos candidatos al mismo. Se procede a la actividad que permite visualizar estos candidatos. Esta actividad utiliza una estética denominada “Swipe Cards”. El usuario puede deslizar hacia la izquierda o la derecha los candidatos que le interese.

Completado esto, el usuario queda a la espera de la respuesta de otro usuario para que se produzca un match. Esto sucede en un workflow diferente.


