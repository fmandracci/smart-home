#!/bin/bash
sudo rm -f /usr/lib/x86_64-linux-gnu/nymea/plugins/libnymea_integrationpluginmect.so
sudo sync
sudo cp /extra/share/git.mect.it/smart-home/nymea-plugin/build-mect-Desktop-Debug/libnymea_integrationpluginmect.so  /usr/lib/x86_64-linux-gnu/nymea/plugins/
sudo sync
ls -al /usr/lib/x86_64-linux-gnu/nymea/plugins/
# sudo nymead -n -d Mect  -d ThingManager
