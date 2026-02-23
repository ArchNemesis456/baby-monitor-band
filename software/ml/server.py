from fastapi import FastAPI
from pydantic import BaseModel
from inference import final_decision
import requests
from datetime import datetime

app = FastAPI(title="Baby Band ML Server")

# =================================================
# CONFIG: Parent ESP32
# =================================================
PARENT_ESP32_IP = "10.30.109.117"  
PARENT_ESP32_PORT = 8080
PARENT_URL = f"http://10.30.109.117:8080/result"


# =================================================
# Data model (Baby ESP32 → Laptop)
# =================================================
class BabySensorData(BaseModel):
    cry_volume: float
    cry_frequency: float
    motion_intensity: float
    restlessness: float
    heart_rate: int
    heart_rate_trend: int
    hr_variability: float


# =================================================
# Helper: Send result to Parent ESP32
# =================================================
def send_to_parent_band(result: dict, bpm: int):
    payload = {
        "timestamp": datetime.now().isoformat(),
        "state": result["state"],
        "confidence": round(result["confidence"], 2),
        "bpm": bpm
    }

    try:
        requests.post(PARENT_URL, json=payload, timeout=2)
        print("📤 SENT TO PARENT ESP32:", payload)
    except Exception as e:
        print("❌ FAILED TO SEND TO PARENT ESP32:", e)


# =================================================
# MAIN ENDPOINT
# Baby ESP32 → Laptop → ML → Parent ESP32
# =================================================
@app.post("/predict")
def predict(data: BabySensorData):

    # 1️⃣ Receive data from baby band
    sensor_data = data.model_dump()
    print("\n📡 DATA FROM BABY ESP32:")
    print(sensor_data)

    # 2️⃣ Classify using Random Forest + rules
    result = final_decision(sensor_data)
    print("🧠 ML RESULT:")
    print(result)

    # 3️⃣ Send result + BPM to parent band
    send_to_parent_band(
        result=result,
        bpm=sensor_data["heart_rate"]
    )

    # 4️⃣ Return result (for Swagger / curl)
    return {
        "state": result["state"],
        "confidence": result["confidence"],
        "bpm": sensor_data["heart_rate"]
    }


# =================================================
# Health check
# =================================================
@app.get("/")
def root():
    return {"status": "ML server running"}
