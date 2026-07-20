from datetime import datetime
import requests

from inference import final_decision
from database import save_prediction
from config import PARENT_URL


# =====================================================
# SEND TO PARENT BAND
# =====================================================

def send_to_parent_band(result, bpm):

    payload = {

        "timestamp": datetime.now().isoformat(),

        "state": result["state"],

        "confidence": round(result["confidence"], 2),

        "bpm": bpm

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

    print("\n📡 DATA:", sensor_data)

    result = final_decision(sensor_data)

    print("🧠 RESULT:", result)

    save_prediction(sensor_data, result)

    send_to_parent_band(

        result,

        sensor_data["heart_rate"]

    )

    return {

        "state": result["state"],

        "confidence": result["confidence"],

        "bpm": sensor_data["heart_rate"]

    }