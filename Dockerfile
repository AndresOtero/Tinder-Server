
####################################################
## Dockerfile para el uso del Application Server  ##
## Basado en Ubuntu 14.04               		  ##
####################################################

# Imagen Ubuntu oficial versión 14.04
FROM jtierno/tinderapplicationserver

MAINTAINER jtierno jtierno

COPY ./ /home

RUN cd /home && chmod 777 config.sh
RUN cd /home && ./config.sh
WORKDIR /home/build

CMD ["bash"]