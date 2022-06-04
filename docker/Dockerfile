FROM ubuntu:22.04

#Useful command
#
#sudo su
#docker build .
#docker images
#docker run -ti <image_id>

WORKDIR /srv

# jammy is $(lsb_release -cs)
RUN echo "deb https://apache.bintray.com/couchdb-deb jammy main" | tee -a /etc/apt/sources.list


RUN apt update

RUN apt install -y ca-certificates

RUN apt update

RUN apt install -y vim wget git build-essential python2.7

RUN git config --global user.name "Mathieu Drapeau"
RUN git config --global user.email m.drapeau9@gmail.com 

#TODO give access to this command.
#RUN git clone git@github.com:mtiudaeu/home.git
