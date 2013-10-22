#!/bin/bash
KEYFILE="flickr_key.txt"
MYSQLKF="mysqlpass.txt"
PHPDIR="server"
PHPFILE="weather.php"
FK="`cat $KEYFILE`"
MYSQLHOST="`grep mysql $MYSQLKF`"
MYSQLPSW="`head -n 1 $MYSQLKF`"
MYSQLUSER="`grep user $MYSQLKF`"
DBNAME="`tail -n 1 $MYSQLKF`"


sed -e "s/xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx/$FK/" $PHPDIR/yahoo-$PHPFILE > $PHPFILE

sed -i -e "s/xxxxxxxx/$MYSQLPSW/" $PHPFILE
sed -i -e "s/host\.domain/$MYSQLHOST/" $PHPFILE
sed -i -e "s/username/$MYSQLUSER/" $PHPFILE
sed -i -e "s/dbname/$DBNAME/" $PHPFILE
