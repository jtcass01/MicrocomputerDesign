import smbus
import time
import os
from gpiozero import Button


BASEADDRESS = 0x68
bus = smbus.SMBus(1)
'''Enabling the interrupt'''
bus.write_byte_data(BASEADDRESS, 0x0e, 0)


def update_standard_time():
	update_month_register(1)
	update_year_register(18)
	update_day_register(1)
	update_minute_register(0)
	update_hour_register(12)

def menu():
	os.system('clear')
	display_time()
	print('1 ) Manually update date and time.')
	print('2 ) Reset time to standard.')
	print('0 ) exit')
	

def display_time():
	display_string = update_display_string()
	print(display_string)

'''ADDED SHIT'''
button = Button(23)
button.when_pressed = update_standard_time

trigger = Button(24)
trigger.when_pressed = menu
''' END ADDED SHIT'''

def pad_string(value, string_size):
	value_str = str(value)

	while(len(value_str) < string_size):
		value_str = '0' + value_str

	return value_str


def prompt_update_time():
	trigger.when_pressed = None
	update_month_register(input("What month is it (MM): "))
	update_year_register(input("What year is it (YY): "))
	update_day_register(input("What day is it (DD): "))
	update_minute_register(input("What minute is it (mm): "))
	update_hour_register(input("What hour is it (hh): "))
	trigger.when_pressed = menu

def update_display_string():
	display_string = ""

	display_string += pad_string(get_month_register(), 2) + "/"
	display_string += pad_string(get_day_register(), 2) + "/20"
	display_string += pad_string(get_year_register(),2) + " "
	display_string += pad_string(get_hour_register(),2) + ":"
	display_string += pad_string(get_minute_register(),2) + ":"
	display_string += pad_string(get_second_register(),2) + ' '
	display_string += str(get_temp()) + ' *C'

	return display_string


def update_month_register(new_month):
	'''MONTH'''
	write_byte = 0

	ten_month = new_month // 10
	write_byte = (ten_month << 4)

	new_month -= (ten_month * 10)	
	write_byte += new_month

	bus.write_byte_data(BASEADDRESS,5,write_byte)

def get_month_register():
	month_byte = bus.read_byte_data(BASEADDRESS,5)
	ten_month = ((month_byte & 16) >> 4)
	return str((ten_month * 10) + (month_byte & 15))

def update_year_register(new_year):
	'''YEAR'''
	write_byte = 0

	ten_year = new_year // 10
	write_byte = (ten_year << 4)

	new_year -= (ten_year * 10)	
	write_byte += new_year

	bus.write_byte_data(BASEADDRESS,6,write_byte)

def get_year_register():
	year_byte = bus.read_byte_data(BASEADDRESS,6)
	ten_year = ((year_byte & 240) >> 4)
	return str((ten_year * 10) + (year_byte & 15))

def update_day_register(new_day):
	'''DAY'''
	write_byte = 0

	ten_value = new_day // 10
	write_byte = (ten_value << 4)

	new_day -= (ten_value * 10)	
	write_byte += new_day

	bus.write_byte_data(BASEADDRESS,4,write_byte)


def get_day_register():
	data_byte = bus.read_byte_data(BASEADDRESS,4)
	ten_data = ((data_byte & 48) >> 4)
	return str((ten_data * 10) + (data_byte & 15))


def update_hour_register(new_hour):
	'''HOUR'''
	write_byte = 0

	ten_value = new_hour // 10
	write_byte = (ten_value << 4)

	new_hour -= (ten_value * 10)	
	write_byte += new_hour

	bus.write_byte_data(BASEADDRESS,2,write_byte)

def get_hour_register():
	data_byte = bus.read_byte_data(BASEADDRESS,2)
	ten_data = ((data_byte & 16) >> 4)

	return str((ten_data * 10) + (data_byte & 15))

def update_minute_register(new_minute):
	'''MINUTE'''
	write_byte = 0

	ten_value = new_minute // 10
	write_byte = (ten_value << 4)

	new_minute -= (ten_value * 10)	
	write_byte += new_minute

	bus.write_byte_data(BASEADDRESS,1,write_byte)

def get_minute_register():
	data_byte = bus.read_byte_data(BASEADDRESS,1)
	ten_data = ((data_byte & 112) >> 4)

	return str((ten_data * 10) + (data_byte & 15))

def get_second_register():
	data_byte = bus.read_byte_data(BASEADDRESS,0)
	ten_data = ((data_byte & 112) >> 4)

	return str((ten_data * 10) + (data_byte & 15))


def get_temp():
	temp_high = bus.read_byte_data(BASEADDRESS, 0x11)
	temp_low = bus.read_byte_data(BASEADDRESS, 0x12)

	return temp_high + (temp_low * .01)


def perform_action(response):
	if response == 0:
		pass
	elif response == 1:
		prompt_update_time()
	elif response == 2:
		update_standard_time()
	else:
		print('Invalid response')


if __name__ == "__main__":
	response = 1	

	while response != 0:
		response = input('What would you like to do : ')
		perform_action(response)
