right_ssid="testco"
hostIP="8.8.8.8"

#On attend que le wifi soit up
essid="$(sudo iwlist wlp3s0 scan | grep \"$right_ssid\" | cut -f 21 -d " ")"
while test "$essid" != "ESSID:\"$right_ssid\""
do essid="$(sudo iwlist wlp3s0 scan | grep \"$right_ssid\" | cut -f 21 -d " ")"
done

echo $essid a ete trouve

#Connexion au wifi 
#-B pour background, wlp3s0 est a remplacer par le nom de la carte wifi
#Si nl80211 n'est pas disponible, utiliser un autre driver, 
#Editer le wpa_supplicant.conf avec wpa_passphrase <ssid> <passphrase> >> wpa_supplicant.conf
wpa_supplicant -B -iwlp3s0 -c/etc/wpa_supplicant.conf -Dnl80211

#Attente de la connexion
wifi="$(iwgetid -r)"
while test "$wifi" != "$rightssid"
do wifi="$(iwgetid -r)"
done

#Attente de la connexion
pid="$(ps ax | grep "wpa_supplicant -B -iwlp3s0 -c/etc/wpa_supplicant.conf -Dnl80211" | cut -f 1 -d " " | head -n 1)"
echo "with process ID : $pid"
#wait $pid
#echo Connexion etablie avec $essid

#sleep 5

#Reset son IP
dhclient -r

#Envoie une requete pour une nouvelle IP
dhclient wlp3s0

#test de la connexion
bytes="$(ping $hostIP -c 1 | cut -f 1 -d " " | sed -n 2p)"
if test $bytes != 64
then echo "lol ca marche pas"
else echo "ca marche"
fi

#TODO : signaler au serveur qu'on est connecté
