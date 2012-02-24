#!/bin/sh

input=
read input
name="${input}.sh"

touch $name
chmod u+x $name
echo "#!/bin/sh" > $name
echo "\n" >> $name

vim $name

#vim "$name.sh"
