#! /bin/bash
echo "user name = ${USER}"
echo " UID" = ${UID} [$(grep ${UID} /etc/passwd | awk -F: '{print $1}')]
echo EUID = ${EUID} [$(grep ${EUID} /etc/passwd | awk -F: '{print $1}')]
