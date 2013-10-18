#!/bin/bash
KEYFILE="flickr_key.txt"
PHPDIR="server"
PHPFILE="weather.php"
FK="`cat $KEYFILE`"

sed -e "s/xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx/$FK/" $PHPDIR/yahoo-$PHPFILE > $PHPFILE
