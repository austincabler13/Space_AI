import tkinter as tk
from tkinter import ttk
import time
import threading
import psutil
import GPUtil

# Mock the system monitoring functions for demo (replace with actual functions from above)
def get_mock_data():
    # Simulate system info for demo purposes
    return {
        "CPU Usage": f"{psutil.cpu_percent()}%",
        "RAM Usage": f"{psutil.virtual_memory().percent}%",
        "GPU Usage": f"{GPUtil.getGPUs()[0].load * 100}%" if GPUtil.getGPUs() else "N/A",
        "Disk Usage": f"{psutil.disk_usage('/').percent}%",
        "Network Sent": f"{psutil.net_io_counters().bytes_sent / (1024 ** 3):.2f} GB",
        "Network Received": f"{psutil.net_io_counters().bytes_recv / (1024 ** 3):.2f} GB"
    }

def update_ui():
    while True:
        system_status = get_mock_data()
        for key, value in system_status.items():
            labels[key].config(text=f"{key}: {value}")
        time.sleep(1)  # Refresh every 1 second

# Initialize the Tkinter window
root = tk.Tk()
root.title("Spacecraft System Monitoring")
root.geometry("600x400")
root.resizable(False, False)

# Create a style for the UI
style = ttk.Style()
style.configure("TLabel", font=("Helvetica", 14))

# Create and place labels for each subsystem
labels = {}
for i, subsystem in enumerate(["CPU Usage", "RAM Usage", "GPU Usage", "Disk Usage", "Network Sent", "Network Received"]):
    label = ttk.Label(root, text=f"{subsystem}: Loading...", style="TLabel")
    label.grid(row=i, column=0, padx=10, pady=10, sticky=tk.W)
    labels[subsystem] = label

# Start a thread to update the UI in real-time
update_thread = threading.Thread(target=update_ui, daemon=True)
update_thread.start()

root.attributes("-fullscreen", True)  # Fullscreen mode
root.bind("<Escape>", lambda e: root.attributes("-fullscreen", False))  # Escape to exit full-screen

# Start the Tkinter loop
root.mainloop()
update_thread.join()
