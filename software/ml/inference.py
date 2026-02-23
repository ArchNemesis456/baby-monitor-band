import joblib
import pandas as pd
import numpy as np

# -----------------------------
# Load trained audio model
# -----------------------------
MODEL_PATH = "model/rf_baby_state_model.pkl"
model = joblib.load(MODEL_PATH)

# -----------------------------
# Label mapping (must match training)
# -----------------------------
LABEL_MAP = {
    0: "Hungry",
    1: "Sleepy",
    2: "Discomfort",
    3: "Stress"
}

# -----------------------------
# Audio-only ML prediction
# -----------------------------
def audio_ml_predict(cry_volume, cry_frequency):
    features = pd.DataFrame([{
        "cry_volume": cry_volume,
        "cry_frequency": cry_frequency
    }])

    probabilities = model.predict_proba(features)[0]
    idx = int(np.argmax(probabilities))

    return {
        "state": LABEL_MAP[idx],
        "confidence": float(probabilities[idx])
    }

# -----------------------------
# FINAL MULTIMODAL DECISION
# -----------------------------
def final_decision(sensor):
    """
    sensor = dict from ESP32
    """

    cv = sensor["cry_volume"]
    cf = sensor["cry_frequency"]
    motion = sensor["motion_intensity"]
    rest = sensor["restlessness"]
    hr = sensor["heart_rate"]

    # -----------------------------
    # RULE 1: Sensor sanity
    # -----------------------------
    
    # -----------------------------
    # RULE 2: No cry detected
    # -----------------------------
    if cv < 0.05:
        return {
            "state": "Idle",
            "confidence": 1.0
        }

    # -----------------------------
    # ML AUDIO PREDICTION
    # -----------------------------
    ml_result = audio_ml_predict(cv, cf)

    # -----------------------------
    # RULE 3: Stress override
    # -----------------------------
    if hr > 150 and motion > 0.7:
        return {
            "state": "Stress",
            "confidence": 0.95
        }

    # -----------------------------
    # RULE 4: Sleepy confirmation
    # -----------------------------
    if hr < 110 and motion < 0.3 and cv < 0.2:
        return {
            "state": "Sleepy",
            "confidence": 0.9
        }

    # -----------------------------
    # RULE 5: Low confidence fallback
    # -----------------------------
    if ml_result["confidence"] < 0.55:
        return {
            "state": "Uncertain",
            "confidence": round(ml_result["confidence"], 2)
        }

    # -----------------------------
    # DEFAULT: Trust ML
    # -----------------------------
    return {
        "state": ml_result["state"],
        "confidence": round(ml_result["confidence"], 2)
    }
