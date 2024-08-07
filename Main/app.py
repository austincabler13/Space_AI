from flask import Flask, render_template, Response
import cv2

app = Flask(__name__)

# Global variable for video capture
camera = cv2.VideoCapture(0)

@app.route('/')
def index():
    return render_template('index.html')

@app.route('/connect')
def connect():
    return render_template('connect.html')

@app.route('/performance')
def performance():
    # Dummy data for AI performance
    performance_data = {
        'CPU Usage': '20%',
        'Memory Usage': '1.5GB',
        'Uptime': '3 hours'
    }
    return render_template('performance.html', data=performance_data)

@app.route('/report')
def report():
    # Dummy data for damage/maintenance report
    report_data = {
        'Last Check': '2024-08-07',
        'Status': 'All systems operational'
    }
    return render_template('reports.html', data=report_data)

def generate_frames():
    while True:
        success, frame = camera.read()
        if not success:
            break
        else:
            ret, buffer = cv2.imencode('.jpg', frame)
            frame = buffer.tobytes()
            yield (b'--frame\r\n'
                   b'Content-Type: image/jpeg\r\n\r\n' + frame + b'\r\n')

@app.route('/video_feed')
def video_feed():
    return Response(generate_frames(), mimetype='multipart/x-mixed-replace; boundary=frame')

if __name__ == '__main__':
    app.run(debug=True)
