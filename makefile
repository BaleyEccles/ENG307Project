monitor: upload
	arduino-cli monitor -p /dev/ttyACM0 -b arduino:avr:uno

upload: compile
	arduino-cli upload -b arduino:avr:uno -p /dev/ttyACM0

compile:
	arduino-cli compile -b arduino:avr:uno -e
