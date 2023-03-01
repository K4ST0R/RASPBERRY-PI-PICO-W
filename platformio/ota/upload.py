from os.path import basename
import requests

Import('env')

try:
    import configparser
except ImportError:
    import ConfigParser as configparser
project_config = configparser.ConfigParser()
project_config.read("platformio.ini")
upload_url = project_config.get("env:pico", "upload_url")

def upload_firmware(source, target, env):
    firmware_path = str(source[0])
    firmware_name = basename(firmware_path)
    print("OTA : " + firmware_path)

    files = {'image': open(firmware_path, 'rb')}
    r = requests.post(upload_url, files=files)
    print(r.text)

env.Replace(PROGNAME="firmware", UPLOADCMD=upload_firmware)