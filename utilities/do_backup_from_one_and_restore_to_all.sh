#!/bin/bash

VERSION="2.0_03"

V0_ADDR="192.168.5.243"

#V1_ADDR="192.168.5.19"
V2_ADDR="192.168.5.50"
V3_ADDR="192.168.5.45"
#V4_ADDR="192.168.5.120"

EP_ADDR="192.168.5.20"
#T1_ADDR="192.168.5.21"
#T2_ADDR="192.168.5.22"
#T3_ADDR="192.168.5.23"
T4_ADDR="192.168.5.24"
T5_ADDR="192.168.5.25"
T6_ADDR="192.168.5.26"
BA_ADDR="192.168.5.27"

#X0_ADDR="192.168.0.60"
#X1_ADDR="192.168.0.61"
#X2_ADDR="192.168.0.62"
#X3_ADDR="192.168.0.63"
#X4_ADDR="192.168.0.64"
#X5_ADDR="192.168.0.65"
#X6_ADDR="192.168.0.66"
#X7_ADDR="192.168.0.67"
#X8_ADDR="192.168.0.68"
#X9_ADDR="192.168.0.69"

	echo "------------------ SmartHome_v$VERSION ------------------"

	test "$USER" = "root"                                             || { echo "please run with: sudo $0"; exit; }
	eval $(ssh-agent -s)                                              || { echo "cannot setup ssh client"; exit; }
	trap 'ssh-agent -k' EXIT

	ssh-add /root/.ssh/the_key                                        || { echo "cannot add the Jolly key"; exit; }

FOLDER="SmartHome_v$VERSION"
	mkdir $FOLDER                                                     || { echo "cannot create folder $FOLDER"; exit; } 
	mkdir $FOLDER/local                                               || { echo "cannot create folder $FOLDER/local"; exit; } 

	echo "------------------ stopping $V0_ADDR ------------------"
	ssh root@$V0_ADDR /etc/rc.d/init.d/autoexec stop                  || { echo "cannot stop the application in $V0_ADDR"; exit; } 
	ssh root@$V0_ADDR rm -f /local/data/alarms/*.log                  || { echo "cannot remove alarm logs in $V0_ADDR"; exit; } 

	echo "------------------ backup from $V0_ADDR ------------------"
	rsync -Hax root@$V0_ADDR:/local/control/  $FOLDER/local/control/  || { echo "cannot backup the local/control/ files"; exit; } 
	rsync -Hax root@$V0_ADDR:/local/data/     $FOLDER/local/data/     || { echo "cannot backup the local/data/ files"; exit; } 
	rsync -Hax root@$V0_ADDR:/local/etc/      $FOLDER/local/etc/      || { echo "cannot backup the local/etc/ files"; exit; } 
	rsync -Hax root@$V0_ADDR:/local/retentive $FOLDER/local/retentive || { echo "cannot backup the local/retentive file"; exit; } 
	rsync -Hax root@$V0_ADDR:/local/root/     $FOLDER/local/root/     || { echo "cannot backup the local/root/ files"; exit; } 

for XX_ADDR in $EP_ADDR $T1_ADDR $T2_ADDR $T3_ADDR $T4_ADDR $T5_ADDR $T6_ADDR $BA_ADDR $V1_ADDR $V2_ADDR $V3_ADDR $V4_ADDR $X0_ADDR $X1_ADDR $X2_ADDR $X3_ADDR $X4_ADDR $X5_ADDR $X6_ADDR $X7_ADDR; do

	echo "------------------ stopping $XX_ADDR ------------------"
	ssh root@$XX_ADDR /etc/rc.d/init.d/autoexec stop                  || { echo "cannot stop the application"; exit; } 
done

for XX_ADDR in $EP_ADDR $T1_ADDR $T2_ADDR $T3_ADDR $T4_ADDR $T5_ADDR $T6_ADDR $BA_ADDR $V1_ADDR $V2_ADDR $V3_ADDR $V4_ADDR $X0_ADDR $X1_ADDR $X2_ADDR $X3_ADDR $X4_ADDR $X5_ADDR $X6_ADDR $X7_ADDR $X8_ADDR $X9_ADDR; do

	echo "------------------ restore to $XX_ADDR ------------------"
	rsync -Haxc --delete $FOLDER/local/control/ root@$XX_ADDR:/local/control/     || { echo "cannot restore the local/control/ files to $XX_ADDR"; exit; } 
	rsync -Haxc --delete $FOLDER/local/data/    root@$XX_ADDR:/local/data/ \
		--exclude store \
		--exclude alarms                                                      || { echo "cannot restore the local/data/ files to $XX_ADDR"; exit; } 
	rsync -Haxc --delete $FOLDER/local/etc/     root@$XX_ADDR:/local/etc/ \
		--exclude sysconfig/net.conf \
		--exclude wpa_supplicant/default.conf \
		--exclude ppp                                                         || { echo "cannot restore the local/etc/ files to $XX_ADDR"; exit; } 
	# NO: rsync -Haxc --delete $FOLDER/local/retentive root@$XX_ADDR:/local/retentive || { echo "cannot rsync the local/retentive file to $XX_ADDR"; exit; } 
	rsync -Haxc --delete $FOLDER/local/root/     root@$XX_ADDR:/local/root/ \
		--exclude fcrts                                                       || { echo "cannot restore the local/root/ files to $XX_ADDR"; exit; } 
	# NB: neither --exclude hmi.ini nor --exclude hmi.qss

	ssh root@$XX_ADDR sync                                                        || { echo "cannot sync the filesystem in $XX_ADDR"; exit; } 
done

	echo "------------------ restarting $V0_ADDR ------------------"
	ssh root@$V0_ADDR /sbin/reboot                                    || { echo "cannot reboot $V0_ADDR"; exit; } 

for XX_ADDR in $EP_ADDR $T1_ADDR $T2_ADDR $T3_ADDR $T4_ADDR $T5_ADDR $T6_ADDR $BA_ADDR $V1_ADDR $V2_ADDR $V3_ADDR $V4_ADDR $X0_ADDR $X1_ADDR $X2_ADDR $X3_ADDR $X4_ADDR $X5_ADDR $X6_ADDR $X7_ADDR $X8_ADDR $X9_ADDR; do

	echo "------------------ restarting $XX_ADDR ------------------"
	ssh root@$XX_ADDR /sbin/reboot                                    || { echo "cannot reboot $XX_ADDR"; exit; } 
done

	echo "------------------ ok, done ------------------"
