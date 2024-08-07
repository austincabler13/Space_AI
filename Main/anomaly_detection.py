import tensorflow as tf
from tensorflow.keras.models import load_model
import numpy as np

def detect_anomalies(data):
    model = load_model('anomaly_model.h5')
    predictions = model.predict(data)
    anomalies = predictions > 0.5
    return anomalies
