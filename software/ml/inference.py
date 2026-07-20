import joblib
import pandas as pd
import numpy as np

# =====================================================
# LOAD MODEL
# =====================================================
MODEL_PATH = "model/rf_baby_state_model.pkl"
model = joblib.load(MODEL_PATH)

# =====================================================
# LABEL MAP
# =====================================================
LABEL_MAP = {
    0: "Hungry",
    1: "Sleepy",
    2: "Discomfort",
    3: "Stress"
}

# =====================================================
# MACHINE LEARNING PREDICTION
# =====================================================
def ml_predict(sensor):

    features = pd.DataFrame([{
        "cry_volume": sensor["cry_volume"],
        "cry_frequency": sensor["cry_frequency"],
        "motion_intensity": sensor["motion_intensity"],
        "restlessness": sensor["restlessness"],
        "heart_rate": sensor["heart_rate"],
        "heart_rate_trend": sensor["heart_rate_trend"],
        "hr_variability": sensor["hr_variability"]
    }])

    probabilities = model.predict_proba(features)[0]

    idx = int(np.argmax(probabilities))

    return {
        "state": LABEL_MAP[idx],
        "confidence": float(probabilities[idx])
    }


# =====================================================
# RULE ENGINE
# =====================================================
def apply_rules(sensor, ml_result):

    state = ml_result["state"]
    confidence = ml_result["confidence"]

    hr = sensor["heart_rate"]
    motion = sensor["motion_intensity"]
    cry = sensor["cry_volume"]
    rest = sensor["restlessness"]

    # -----------------------------
    # Rule 1 : No Cry
    # -----------------------------
    if cry < 0.05:
        return {
            "state": "Idle",
            "confidence": 1.0
        }

    # -----------------------------
    # Rule 2 : Stress Override
    # -----------------------------
    if hr > 150 and motion > 0.70:
        return {
            "state": "Stress",
            "confidence": 0.95
        }

    # -----------------------------
    # Rule 3 : Sleep Confirmation
    # -----------------------------
    if hr < 110 and motion < 0.25 and rest < 0.25:
        return {
            "state": "Sleepy",
            "confidence": 0.90
        }

    # -----------------------------
    # Rule 4 : Low Confidence
    # -----------------------------
    if confidence < 0.55:
        return {
            "state": "Uncertain",
            "confidence": round(confidence, 2)
        }

    return {
        "state": state,
        "confidence": round(confidence, 2)
    }


# =====================================================
# FINAL DECISION
# =====================================================
def final_decision(sensor):

    ml_result = ml_predict(sensor)

    final_result = apply_rules(sensor, ml_result)

    return final_result