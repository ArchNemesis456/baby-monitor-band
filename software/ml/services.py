from datetime import datetime
import requests
from validator import validate_sensor_data
from inference import final_decision
from database import save_prediction
from config import PARENT_URL
from history import (
    add_sensor_reading,
    get_sensor_data,
    history_ready
)


# =====================================================
# SEND TO PARENT BAND
# =====================================================

def send_to_parent_band(result):

    payload = {

        "timestamp": datetime.now().isoformat(),

        "state": result["state"],

        "confidence": round(result["confidence"], 2),

        "alert_level": result["alert_level"],
        
    }

    try:

        requests.post(

            PARENT_URL,

            json=payload,

            timeout=2

        )

        print("📤 SENT TO PARENT:", payload)

    except Exception as e:

        print("❌ FAILED TO SEND:", e)


# =====================================================
# MAIN PIPELINE
# =====================================================

def process_sensor_data(sensor_data):

    print("\n📡 RAW DATA:", sensor_data)

    # ============================================
    # VALIDATE SENSOR DATA
    # ============================================

    sensor_data = validate_sensor_data(sensor_data)

    # ============================================
    # STORE SENSOR READING
    # ============================================

    add_sensor_reading(sensor_data)
    if history_ready():
        print("🟢 History Buffer: FULL (Using Smoothed Data)")
    else:
        print("🟡 History Buffer: Filling...")

    # ============================================
    # USE SMOOTHED SENSOR DATA
    # ============================================

    smoothed_sensor = get_sensor_data()

    print("📊 SMOOTHED DATA:", smoothed_sensor)

    # ============================================
    # HYBRID AI
    # ============================================

    result = final_decision(smoothed_sensor)

    print("🧠 RESULT:", result)

    # ============================================
    # SAVE TO DATABASE
    # ============================================

    save_prediction(smoothed_sensor, result)

    # ============================================
    # SEND TO PARENT BAND
    # ============================================

    send_to_parent_band(result)

    return {

        "state": result["state"],

        "confidence": result["confidence"],

        "alert_level": result["alert_level"]

    }