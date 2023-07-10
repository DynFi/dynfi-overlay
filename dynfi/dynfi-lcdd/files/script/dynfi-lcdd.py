import socket
import re
import subprocess
import time
import os

def create_screen(sock, screen_name):
    sock.sendall('screen_add {}\n'.format(screen_name).encode())
    sock.sendall('screen_set {0} -name {0}\n'.format(screen_name).encode())

def create_widget(sock, screen_name, widget_name, widget_value, y_position):
    sock.sendall('widget_add {0} {1} string\n'.format(screen_name, widget_name).encode())
    sock.sendall('widget_set {0} {1} 1 {2} "{3}"\n'.format(screen_name, widget_name, y_position, widget_value).encode())

def show_screen(sock, value1, value2="", sleep=5):
    create_screen(sock, "dynfi")
    for i, output in enumerate([value1, value2], start=1):
        create_widget(sock, "dynfi", "dynfi_widget_{}".format(i), output, i)
    time.sleep(sleep)
    sock.sendall('screen_del dynfi\n'.encode())

def get_cpu_usage():
    process = subprocess.Popen(["top", "-b", "-p", "1"], stdout=subprocess.PIPE, encoding="utf-8")
    output = process.communicate()[0]

    cpu_idle_line = re.search(r"CPU:.*?(\d+\.\d+)%\s*idle", output)
    idle_percentage = cpu_idle_line.group(1)
    return "{:4.2f}".format(100 - float(idle_percentage))

def get_ram_usage():
    ram = int(subprocess.check_output(["sysctl", "-n", "hw.realmem"]).decode().strip())
    ram_mbs = ram / (1024 ** 2)
    output = subprocess.check_output(["sysctl", "-n", "vm.stats.vm.v_free_count"]).decode().strip()
    free_memory = int(output) * 4096 / (1024 ** 2)
    return "{:4.2f}".format(100.0 - free_memory / ram_mbs * 100)

def get_ips():
    output1 = subprocess.check_output(["ifconfig", "-l"]).decode("utf-8")

    interfaces = [interface for interface in output1.split() if not interface.startswith("lo")]

    for interface in interfaces:
        output2 = subprocess.check_output(["ifconfig", interface]).decode("utf-8")
        for line in output2.split("\n"):
            if "inet " in line:
                parts = line.split()
                yield interface, parts[1]

def get_version():
    return subprocess.check_output(["dynfi-version"]).decode("utf-8").strip()

def cpu_screen(sock):
    for _ in range(5):
        show_screen(sock, " DynFi Firewall ", f"CPU usage: {get_cpu_usage()}", sleep=1)

def ram_screen(sock):
    for _ in range(5):
        show_screen(sock, " DynFi Firewall ", f"RAM usage: {get_ram_usage()}", sleep=1)

def ips_screen(sock):
    for intf, ip in get_ips():
        show_screen(sock, f"{intf}: ", f"  {ip}", sleep=2)

def hello_screen(sock):
    show_screen(sock, " DynFi Firewall ", ">>> dynfi.com")

def version_screen(sock):
    version = get_version()
    show_screen(sock, " DynFi Firewall ", f"Ver: {version}")

def main():
    sock = socket.create_connection(("localhost", 13666))

    sock.sendall("hello\n".encode())

    while True:
        hello_screen(sock)
        version_screen(sock)
        if not os.path.exists('/usr/local/etc/dynfi-lcd-simple'):
           cpu_screen(sock)
           ram_screen(sock)
           ips_screen(sock)

    sock.close()

if __name__ == "__main__":
    main()
