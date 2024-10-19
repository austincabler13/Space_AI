import psutil
import GPUtil
import platform
from datetime import datetime

def get_system_info():
    # Gather system information
    uname = platform.uname()
    system_info = {
        "System": uname.system,
        "Node Name": uname.node,
        "Release": uname.release,
        "Version": uname.version,
        "Machine": uname.machine,
        "Processor": uname.processor,
    }
    return system_info

def get_cpu_info():
    # CPU information
    cpu_percent = psutil.cpu_percent(interval=1)
    cpu_freq = psutil.cpu_freq().current
    return {
        "CPU Usage (%)": cpu_percent,
        "CPU Frequency (MHz)": cpu_freq
    }

def get_ram_info():
    # Memory information
    virtual_mem = psutil.virtual_memory()
    return {
        "Total Memory (GB)": virtual_mem.total / (1024 ** 3),
        "Used Memory (GB)": virtual_mem.used / (1024 ** 3),
        "Available Memory (GB)": virtual_mem.available / (1024 ** 3),
        "Memory Usage (%)": virtual_mem.percent
    }

def get_gpu_info():
    # GPU information
    gpus = GPUtil.getGPUs()
    if gpus:
        gpu = gpus[0]
        return {
            "GPU Name": gpu.name,
            "GPU Load (%)": gpu.load * 100,
            "GPU Memory Usage (%)": gpu.memoryUtil * 100,
            "GPU Temperature (C)": gpu.temperature
        }
    return {}

def get_disk_info():
    # Disk information
    disk_usage = psutil.disk_usage('/')
    return {
        "Total Disk (GB)": disk_usage.total / (1024 ** 3),
        "Used Disk (GB)": disk_usage.used / (1024 ** 3),
        "Free Disk (GB)": disk_usage.free / (1024 ** 3),
        "Disk Usage (%)": disk_usage.percent
    }

def get_network_info():
    # Network information
    net_io = psutil.net_io_counters()
    return {
        "Bytes Sent (GB)": net_io.bytes_sent / (1024 ** 3),
        "Bytes Received (GB)": net_io.bytes_recv / (1024 ** 3)
    }

def get_system_status():
    # Collect all system data
    status = {
        "System Info": get_system_info(),
        "CPU Info": get_cpu_info(),
        "RAM Info": get_ram_info(),
        "GPU Info": get_gpu_info(),
        "Disk Info": get_disk_info(),
        "Network Info": get_network_info(),
    }
    return status

if __name__ == "__main__":
    system_status = get_system_status()
    for key, value in system_status.items():
        print(f"{key}:")
        for k, v in value.items():
            print(f"  {k}: {v}")
