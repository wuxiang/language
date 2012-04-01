#!/bin/sh

sudo apt-get install python-software-properties
sudo add-apt-repository ppa:pitti/postgresql
sudo apt-get update
#sudo apt-get install debian-archive-keyring
#cd /etc/apt/sources.list.d/
#ls
#gpg -keyserver keyserver.ubuntu.com --recv-key 99B656EA8683D8A2
#gpg --keyserver keyserver.ubuntu.com --recv-key 99B656EA8683D8A2
#gpg -a --export 99B656EA8683D8A2 | sudo apt-key add -
#sudo apt-get install -y postgresql-9.1 postgresql-client-9.1 postgresql-contrib-9.1
#cd
#sudo apt-get install -y postgresql-9.1 postgresql-client-9.1 postgresql-contrib-9.1
#sudo apt-get update

sudo apt-get install -y postgresql-9.1 postgresql-client-9.1 postgresql-contrib-9.1
cd /etc/init.d/
sudo ./postgresql stop

cd /var/run/
sudo chmod -R 777 postgresql/
sudo apt-get install libpq-dev
exit 0
