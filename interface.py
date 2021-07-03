
import smbus
import psutil

Bus = smbus.SMBus(1)

while True:
	for cpu,percent in enumerate(psutil.cpu_percent(interval=1, percpu=True)):
		Bus.write_byte_data(0x14, cpu, int(percent))
