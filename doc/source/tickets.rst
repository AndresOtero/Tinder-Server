==============================================
**Gestión de tareas/Tickets**
==============================================

*APPLICATION SERVER*
======================================
| En esta entrega se basa en definir las bases de la aplicación para poder implementar la totalidad de la funcionalidad en las próximas entregas. A grandes rasgos esta entrega se compone de:

- Configuración/Investigación de tecnologías base: Cmake, Mongoose y RocksDB.
- Configuracion/Investigación de tecnologías secundarias: Gtests, Gmock, Curl, Sphinx, Docker y Travis.
- Diseño e integración de la base de datos.
- Integración de operaciones básicas con Shared Server.
- Diseño de componentes genéricos para generar una api rest.
- Arquitectura general de la aplicación.

Detalle de Tickets Github
-----------------------------
| **Tarea:** Startup del Application Server
| **Responsable:** Jonathan Tierno
| **Descripción:** Hacer la configuración básica del servidor con cmake.

| **Tarea:** Configuración de Base de datos
| **Responsable:** Matias Luraschi
| **Descripción:** Configurar RocksDB y hacerlo linkear con cmake

| **Tarea:** Diseño de la base de datos
| **Responsable:** Matias Luraschi
| **Descripción:** Definir qué se va almacenar en la base de datos y cómo.

| **Tarea:** Definir consultas a la Base de Datos
| **Responsable:** Matias Luraschi
| **Descripción:** Crear las clases que mapean la base de datos a la logica de la aplicación con sus respectivas consultas para obtener datos de la base..

| **Tarea:** Configurar Biblioteca REST
| **Responsable:** Jonathan Tierno
| **Descripción:** Configurar Mongoose.

| **Tarea:** Configuración tecnologías auxiliares
| **Responsable:** Jonathan Tierno
| **Descripción:** Configurar el sistema de log, cobertura, tests unitarios, documentación automática.

| **Tarea:** Generar estructura REST 
| **Responsable:** Jonathan Tierno
| **Descripción:** Generar una serie de clases que resuelvan el direccionamiento REST.

| **Tarea:** Conectar Shared y Application Server
| **Responsable:** Matias Luraschi
| **Descripción:** Se deben crear las clases en el Application Server para poder hacer consultas al Shared Server.

| **Tarea:** Configurar Integración continua
| **Responsable:** Matias Luraschi
| **Descripción:** Configurar Travis para mantener la integración continua

| **Tarea:** Realizar una correcta administración de las dependencias que requiera la aplicación servidor y para poder simplificar el proceso de despliegue (deploy) del mismo
| **Responsable:** Jonathan Tierno
| **Descripción:** Mediante el uso de la herramienta Docker

| **Tarea:** DAO de Usuarios
| **Responsable:** Matias Luraschi
| **Descripción:** Crear una DAO de acceso a datos de usuario para independizar a los connector. Qué connector se usa para obtener cada dato debería ser indistinto al servicio de perfiles. De esta forma se pueden intercambiar connectors sin la necesidad de alterar clases del modelo.

| **Tarea:** Manual de instalación y uso
| **Responsable:** Jonathan Tierno
| **Descripción:** Documentar cómo instalar y utilizar el application server.

| **Tarea:** Documentar las capas WEBSERVER, DISPATCHER y API de la aplicación
| **Responsable:** Jonathan Tierno
| **Descripción:** Generar los diagramas y la documentación correspondiente de estas capas

| **Tarea:** Documentar las capas Service, DAO y Connector
| **Responsable:** Jonathan Tierno
| **Descripción:** Documentar las capas inferiores de la aplicación con diagramas, etc.

| **Tarea:** Documentar arquitectura de la aplicación
| **Responsable:** Jonathan Tierno
| **Descripción:** Generar la documentación de la arquitectura de la aplicación

| **Tarea:** Configurar sphinx
| **Responsable:** Jonathan Tierno
| **Descripción:** Configurar sphinx para que tome la salida de doxygen y sume la documentación de clases

| **Tarea:** Endpoint De seguridad
| **Responsable:** Jonathan Tierno
| **Descripción:** Armar un endpoint que permita iniciar la sesión en el servidor devolviendo el jwt

| **Tarea:** Configurar docker
| **Responsable:** Jonathan Tierno
| **Descripción:** Configurar docker para poder hacer la entrega de este ejecutable

| **Tarea:** Subir la versión de libboost en Travis
| **Responsable:** Jonathan Tierno
| **Descripción:** Para instalar la 1.54 por tener ubuntu 14.04(trusty) e instalarla de los sources oficiales, hay que hacer que se instale la 1.58

| **Tarea:** Doxygen
| **Responsable:** Jonathan Tierno
| **Descripción:** Configurar Doxygen para crear la documentación automática

| **Tarea:** Definir clases genéricas api rest
| **Responsable:** Jonathan Tierno
| **Descripción:** Armar las clases que resuelvan el problema de la api rest para luego poder implementar la funcionalidad

| **Tarea:** Configurar tests unitarios
| **Responsable:** Jonathan Tierno
| **Descripción:** Configuración de  tests unitarios para probar el app server

| **Tarea:** Almacenamiento de conversaciones
| **Responsable:** Matias Luraschi
| **Descripción:** El servidor debe persistir las conversaciones para que las mismas puedan existir en una ejecución posterior del servidor.

| **Tarea:** Servicio de Conversaciones
| **Responsable:** Matias Luraschi
| **Descripción:** El servidor brindará un servicio para el delivery de conversaciones. El servidor debe tener un registro de las conexiones activas en el servidor para saber hacia dónde dirigir el mensaje en curso. Para poder iniciar una conversación entre dos usuarios es necesario que exista un match entre ellos.

| **Tarea:** Servicio de Match
| **Responsable:** Matias Luraschi
| **Descripción:** En caso de que el usuario esté interesado en el candidato, el servidor deberá almacenar este interés para que en caso de que el candidato esté interesado, estos se puedan poner en contacto.

| **Tarea:** Servicio de Autenticación
| **Responsable:** Matias Luraschi
| **Descripción:** El servidor dispondrá de un servicio para la autenticación de los clientes. Este servicio consta de una solicitud de autenticación, que viene junto con las credenciales del usuario. La respuesta a la solicitud es un token (identificador) de la sesión del usuario.

| **Tarea:** Implementar POST, PUT y DELETE con el SharedServer
| **Responsable:** Matias Luraschi
| **Descripción:** Implementar las actualizaciones información de los usuarios desde el application server al shared server.


*SHARED SERVER*
======================================
En esta primer entrega se va a implementar la totalidad de la funcionalidad de este servidor, ya que es el puntapié inicial para poder implementar el resto de las aplicaciones que conformarán el sistema global.

Detalle de Tickets Github
-----------------------------
| **Tarea:** StartUp de aplicación Node.JS con Express.JS
| **Responsable:** Marcelo Cavazzoli
| **Descripción:** Generar el código preliminar que inicie el servidor Node con su interfaz REST.

| **Tarea:** Configurar Heroku
| **Responsable:** Marcelo Cavazzoli
| **Descripción:** Crear un nodo en heroku y configurarlo con el shared server

| **Tarea:** Configurar PostgresSQL
| **Responsable:** Marcelo Cavazzoli
| **Descripción:** Crear una db en Heroku PostgresSQL y conectarla con el shared server.

| **Tarea:** Modelo base de datos
| **Responsable:** Marcelo Cavazzoli
| **Descripción:** Diseñar el esquema de base de datos que permitirá almacenar la información para solventar la funcionalidad brindada.

| **Tarea:** Implementar la API REST
| **Responsable:** Marcelo Cavazzoli
| **Descripción:** Implementar la api propuesta por el enunciado en su totalidad.


| **Tarea:** Manejo de Errores API REST
| **Responsable:** Marcelo Cavazzoli
| **Descripción:** Implementar el manejo de los errores de la API REST


| **Tarea:** Web de administración
| **Responsable:** Uciel Rodriguez
| **Descripción:** Implementar la página web para administrar los usuarios del Shared Server.

| **Tarea:** Web de administración (formularios)
| **Responsable:** Uciel Rodriguez
| **Descripción:** En jquery y angularJS para la extracción y cargado de datos de usuarios.

| **Tarea:** Web de administración flujo de datos
| **Responsable:** Uciel Rodriguez
| **Descripción:** En jquery y angularJS para conectarse con la Restful API con el fin de hacer consultas y volcar datos a la base de datos.


| **Tarea:** Interfaz gráfica de la Web de administración
| **Responsable:** Uciel Rodriguez
| **Descripción:** Cargando estilos y formas de visualizar con bootstrap

| **Tarea:** Configurar Integración continua
| **Responsable:** Matias Luraschi
| **Descripción:** Configurar Travis para mantener la integración continua

| **Tarea:** Usar Json Params en vez de HTTP
| **Responsable:** Marcelo Cavazzoli
| **Descripción:** Para hacer más sencillo el manejo de datos

| **Tarea:** Correcciones en la web
| **Responsable:** Jonathan Tierno
| **Descripción:** Fix en las vistas