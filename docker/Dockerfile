FROM ubuntu:22.04

#Useful command
#
#sudo su
#docker build .
#docker images
#docker run -ti <image_id>

WORKDIR /docker_install

# jammy is $(lsb_release -cs)
RUN echo "deb https://apache.bintray.com/couchdb-deb jammy main" | tee -a /etc/apt/sources.list


RUN apt update

RUN apt install -y ca-certificates

RUN apt update

RUN apt install -y vim wget git build-essential python2.7

RUN git clone https://github.com/emscripten-core/emsdk.git
RUN git config --global user.name "Mathieu Drapeau"
RUN git config --global user.email m.drapeau9@gmail.com 

RUN ln -s /usr/bin/python2.7 /usr/bin/python2 
RUN ln -s /usr/bin/python2 /usr/bin/python

WORKDIR /docker_install/emsdk

RUN ./emsdk install latest
RUN ./emsdk activate latest
RUN echo '. "emsdk_env.sh"' >> $HOME/.bashrc
