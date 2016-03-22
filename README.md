# Tinder-Server

## Configurar proyecto eclipse

1. Correr el archivo **_"configEclipse.sh"_** parado en la raiz del proyecto, va a crear una carpeta llamada **_"build"_**.
2. Dentro de eclipse **_"import.. -> Existing Project into Workspace"_**.
3. Como root del proyecto hay que buscar el directorio **_"build"_** creado en el paso 1.
4. Darle finish y con eso queda importado el proyecto en eclipse.

Hasta nuevo aviso, si se agrega un nuevo archivo, hay que correr
**_cmake ../project/ -Dtest=on_**

Hay que instalar el paquete libboost-all-dev
Para RocksDB hay que asegurarse de tener instalado libsnappy-dev libbz2-dev zlib1g-dev

