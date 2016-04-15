# Tinder Application

Esta es una aplicación realizada dentro del marco de trabajo práctico propuesto para la asignatura 75.52 Taller de Programación II


## Información General

- [:link: Página Web del poryecto](http://tinder2team.github.io/Tinder-Server/)
- [:book: Repositorio de servidor de Aplicación](http://tinder2team.github.io/Tinder-Server/)
- [:book: Repositorio del Shared Server](https://github.com/Tinder2Team/Tinder-Shared)
- [:book: Repositorio del Cliente Android](https://github.com/Tinder2Team/Tinder-Client)

## Status

[![Build Status](https://travis-ci.org/Tinder2Team/Tinder-Server.svg?branch=master)](https://travis-ci.org/Tinder2Team/Tinder-Server)
[![Docker Pulls](https://img.shields.io/docker/pulls/martineq/tp7552.svg)](https://hub.docker.com/r/martineq/tp7552/)

##Docker

Para correr el servidor con Docker, la imágen del servidor se encuentra publicada, con lo cual es posible correrla de la siguiente manera:

```sh
$ sudo docker run -p 0.0.0.0:8000:8000 jtierno/tinder-server /bin/sh -c "./server/server"
```