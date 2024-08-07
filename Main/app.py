from flask import Flask, render_template, Response, jsonify
import psutil
import cv2
import datetime

app = Flask(__name__)

# Initialize camera
camera = cv2.VideoCapture(0)

@app.route('/')
def index():
    return render_template('index.html')

@app.route('/connect')
def connect():
    return render_template('connect.html')

@app.route('/performance')
def performance():
    return render_template('performance.html')

@app.route('/report')
def report():
    # Example data for damage/maintenance report
    report_data = {
        'Last Check': datetime.datetime.now().strftime("%Y-%m-%d %H:%M:%S"),
        'Status': 'All systems operational'
    }
    return render_template('report.html', data=report_data)

@app.route('/api/performance')
def api_performance():
    cpu_usage = psutil.cpu_percent()
    memory_info = psutil.virtual_memory()
    uptime = datetime.datetime.now() - datetime.datetime.fromtimestamp(psutil.boot_time())

    performance_data = {
        'cpu_usage': f"{cpu_usage}%",
        'memory_usage': f"{memory_info.percent}%",
        'uptime': str(uptime).split('.')[0]  # format uptime as HH:MM:SS
    }
    return jsonify(performance_data)

def generate_frames():
    while True:
        success, frame = camera.read()
        if not success:
            break
        else:
            detect_obstacles(frame)
            ret, buffer = cv2.imencode('.jpg', frame)
            frame = buffer.tobytes()
            yield (b'--frame\r\n'
                   b'Content-Type: image/jpeg\r\n\r\n' + frame + b'\r\n')

@app.route('/video_feed')
def video_feed():
    return Response(generate_frames(), mimetype='multipart/x-mixed-replace; boundary=frame')

def detect_obstacles(frame):
    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    edges = cv2.Canny(cv2.GaussianBlur(gray, (5, 5), 1.5), 50, 150)
    contours, _ = cv2.findContours(edges, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)
    for contour in contours:
        if cv2.contourArea(contour) > 100:
            cv2.rectangle(frame, cv2.boundingRect(contour), (0, 255, 0), 2)

if __name__ == '__main__':
    app.run(debug=True)
