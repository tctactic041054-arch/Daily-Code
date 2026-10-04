import os
import time
import psutil

def get_cpu_temp():
    try:
        # อ่านค่าความร้อน CPU บน Linux kernel
        temps = psutil.sensors_temperatures()
        if 'coretemp' in temps:
            return temps['coretemp'][0].current
        elif 'cpu_thermal' in temps:
            return temps['cpu_thermal'][0].current
    except Exception:
        pass
    return 0.0

def render_dashboard():
    os.system('clear')
    cpu_usage = psutil.cpu_percent(interval=1)
    ram_info = psutil.virtual_memory()
    temp = get_cpu_temp()
    
    print("==========================================")
    print("      CYBERDECK SYSTEM MONITOR v1.0       ")
    print("==========================================")
    print(f" CPU Usage : [{cpu_usage:>5.1f}%] ")
    print(f" CPU Temp  : [{temp:>5.1f}°C] ")
    print(f" RAM Usage : [{ram_info.percent:>5.1f}%] ({ram_info.used // (1024**2)}MB / {ram_info.total // (1024**2)}MB)")
    print("==========================================")
    print(" Status    : OPERATIONAL | OFF-GRID READY ")
    print("==========================================")

if __name__ == "__main__":
    while True:
        render_dashboard()
        time.sleep(2)