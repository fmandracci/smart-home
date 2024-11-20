#!/bin/bash

cp -av config/Crosstable.csv config/system.ini /local/etc/sysconfig/
cp -av config/splash.png                       /local/etc/sysconfig/img/
cp -av config/trend*.csv                       /local/data/customtrend/
cp -av hmi.qss                                 /local/root/

cp -av hmi.ini                                 /local/root/

#cp -av hmi_ter.ini                             /local/root/hmi.ini
#cp -av hmi_only                                /local/root/

