# Tinder Application

Esta es una aplicación realizada dentro del marco de trabajo práctico propuesto para la asignatura 75.52 Taller de Programación II


## Información General

- [:link: Página Web del proyecto](http://tinder2team.github.io/Tinder-Server/)
- [:book: Repositorio de servidor de Aplicación](http://tinder2team.github.io/Tinder-Server/)
- [:book: Repositorio del Shared Server](https://github.com/Tinder2Team/Tinder-Shared)
- [:book: Repositorio del Cliente Android](https://github.com/Tinder2Team/Tinder-Client-2)

## Status

[![Build Status](https://travis-ci.org/Tinder2Team/Tinder-Server.svg?branch=master)](https://travis-ci.org/Tinder2Team/
Tinder-Server)
[![Coverage Status](https://coveralls.io/repos/github/Tinder2Team/Tinder-Server/badge.svg?branch=HEAD)](https://coveralls.io/github/Tinder2Team/Tinder-Server?branch=HEAD)

##Docker

Para correr el servidor con Docker, la imágen del servidor se encuentra publicada, con lo cual es posible correrla de la siguiente manera:

```sh
$ 	sudo docker run -p 0.0.0.0:8000:8000 jtierno/tinder-server /bin/sh -c "./server/server"
```
