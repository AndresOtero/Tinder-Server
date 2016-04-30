==============================================
**Share Server**
==============================================

*Tecnologías principales*
======================================
#. Notepad++: como editor de texto para el desarrollo de código.
#. HTML como estándar utilizado a la hora de desarrollar la aplicaciones web para definir su estructura básica.
#. Jquery: como biblioteca de JavaScript para simplificar la manera de cómo interactuar con los documentos HTML, manipular el árbol DOM, manejar eventos, desarrollar animaciones y agregar interacción con la técnica AJAX a la aplicaciones web.
#. Boostrap: como framework (conjunto de herramientas) para el diseño con tipografía, formularios, botones, cuadros, menús de #. navegación y otros elementos de diseño basado en HTML y CSS, así como, extensiones de JavaScript opcionales adicionales en la aplicaciones web.
#. AngularJS: como framework de JavaScript para crear y mantener la aplicación web con el objetivo de aumentar la aplicación (basada en navegador con capacidad de Modelo Vista Controlador (MVC), en un esfuerzo para hacer que el desarrollo y las pruebas sean más fáciles).

*Descripción de solución implementada*
======================================
#. Dentro de la carpeta “views” se encuentran los .html que contienen toda la estructura de la aplicación web (inputs, formularios, botones, labels, etc). El objetivo de estos archivos es que el usuario pueda ir navegando a través de la página web y realizar las consultas que él considere necesarias y a medida que lo hace pueda hacer cambios sobre la base de datos.
#. Dentro de la carpeta “views” se encuentra el controller.js que es un archivo de JavaScript que contiene la lógica de cómo extraer/agregar/consultar información de los datos y que maneja el flujo e intercambio de estos con la base de datos. También encontramos jquery.js que contiene toda la librería para poder utilizar las funciones que nos provee Jquery.

*Manual de usuario*
===================

Web de administración
---------------------
Para poder administrar los datos almacenados en el servidor se proporciona una página web con las operaciones básicas sobre intereses y usuarios.

URL:  http://tinder-shared.herokuapp.com

Home
----
- URL: http://tinder-shared.herokuapp.com/#/users
- Navegación: “Usuarios/Listar”

En esta sección es posible listar todos los usuarios y filtrarlos por id.


Creación de usuario
-------------------
- URL: http://tinder-shared.herokuapp.com/#/users/add
- Navegación: “Usuarios/Listar”

En esta sección es posible crear un usuario completando el formulario y seleccionando los intereses.


Edición de foto de usuario
--------------------------
- URL: http://tinder-shared.herokuapp.com/#/user/edit/photo
- Navegación: “Usuarios/Editar Foto”

En esta sección es posible editar la foto de un usuario como una url (actualmente la misma no se encuentra reflejada en el usuario, más adelante funcionará para subir la foto de un usuario, aunque es posible que esto se fusione con la edición de usuario.

Edición de usuario
--------------------------
- URL: http://tinder-shared.herokuapp.com/#/users/edit
- Navegación: “Usuarios/Modificar”

Allí podemos ingresar el ID del y presionando el botón se cargan los datos del usuario.. Una vez completo el formulario, con el botón “Modificar usuario” se confirman los datos, obteniendo el correspondiente mensaje del estado de la operación.


Visualización de usuario
--------------------------
- URL: http://tinder-shared.herokuapp.com/#/user/8 (8 es el id del usuario)
- Navegación: Desde el listado de usuarios, clickear en el botón “Ver” de un usuario.

Aquí se puede tener una vista más detallada de los usuarios.



Creación de intereses
--------------------------
- URL: http://tinder-shared.herokuapp.com/#/interests/add
- Navegación: “Intereses/Crear”


Allí podemos ingresar los datos del interés a registrar. Finalmente haciendo clic en el botón “Agregar Interés” se agregara a la base de datos ese interés. Ya sea que la operación haya sido exitosa o no, se informará con un mensaje del estado final.




Listar intereses
--------------------------
- URL: http://tinder-shared.herokuapp.com/#/interests
- Navegación: “Intereses/Listar”

En esta sección es posible listar todos los intereses agrupados por categorías.


Servidor
--------------------------
Para poder ejecutar el servidor de forma local es necesario tener instaladas las siguientes dependencias:
- NodeJs
- Npm for NodeJs

Una vez instaladas las dependencias es necesario pararse en el directorio raíz de la aplicación y ejecutar el comando

``$ npm start``

Al finalizar el startup de la aplicación el servidor quedará escuchando peticiones en la siguiente url:

http://localhost:3000