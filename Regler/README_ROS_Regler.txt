ROS-Anleitung für das Einbinden der Reglerknoten und Verbindung mit Arduino: 

1. Regler Knoten (stanley_querregler und pi_laengsregler) in catkin_ws laden!

2. in catkin_ws: catkin_make ausführen

3. source devel/setup.bash ausführen, um Knoten zu erstellen.

3.5 roscore
-> Starten des ROS

4. rosrun stanley_querregler stanley_querregler_node 
   rosrun pi_laengsregler pi_laengsregler_node
-> solange Knoten verwendet werden, laufen lassen!

5. rostopic list / rosnode list 
-> Schauen, ob Knoten erfolgreich eingebunden wurden

6. rostopic pub /trj_targetSpeed std_msgs/Float32 "Wert"
   rostopic pub /trj_deltaY std_msgs/Float32 "Wert"
   rostopic pub /trj_enableLateralControl std_msgs/Bool 1  -> Für Stanley-Querregelung, 0 für Steuerung von: rostopic pub /trj_steeringAngle std_msgs/Float32 "Wert"
-> Zum Testen der einzelnen Knoten

7. rostopic echo /ctl_motorRpm 
   rostopic echo /ctl_servoAngle
-> Ausgeben der Aktorikwerte, die auf dem Arduino ankommen sollten

Für den Arduino:
8. evtl. sudo chmod a+rw /dev/ttyACM0
         rosrun rosserial_python serial_node.py /dev/ttyACM0
-> Erstellen der rosserial-Verbindung zur Ansteuerung der Aktorik und auswerten der Sensorik
-> ROS-Serial muss dafür runtergeladen sein. Falls nicht installiert, installieren!

