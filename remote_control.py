import struct
import paho.mqtt.publish as publish

packet = struct.pack("<BBff",0xA1,1,0.25,0.0)

publish.single("rover/cmd", packet, hostname="test.mosquitto.org")