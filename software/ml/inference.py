import joblib
import pandas as pd
import numpy as np

# =====================================================
# LOAD TRAINED MODEL
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
# ALERT LEVEL MAP
# =====================================================

ALERT_LEVELS = {
    "Idle": "Low",
    "Sleepy": "Low",
    "Hungry": "Medium",
    "Discomfort": "Medium",
    "Uncertain": "Medium",
    "Stress": "High"
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

    predicted_index = int(np.argmax(probabilities))

    return {
        "state": LABEL_MAP[predicted_index],
        "confidence": float(probabilities[predicted_index])
    }


# =====================================================
# HYBRID RULE ENGINE
# =====================================================

def apply_rules(sensor, ml_result):

    state = ml_result["state"]
    confidence = ml_result["confidence"]

    cry = sensor["cry_volume"]
    motion = sensor["motion_intensity"]
    restlessness = sensor["restlessness"]
    heart_rate = sensor["heart_rate"]

    # -------------------------------------------------
    # RULE 1 : NO CRY DETECTED
    # -------------------------------------------------

    if cry < 0.05:

        return {
            "state": "Idle",
            "confidence": 1.00,
            "alert_level": ALERT_LEVELS["Idle"]
        }

    # -------------------------------------------------
    # RULE 2 : STRESS OVERRIDE
    # -------------------------------------------------

    if heart_rate > 150 and motion > 0.70:

        return {
            "state": "Stress",
            "confidence": 0.95,
            "alert_level": ALERT_LEVELS["Stress"]
        }

    # -------------------------------------------------
    # RULE 3 : SLEEP CONFIRMATION
    # -------------------------------------------------

    if (
        heart_rate < 110
        and motion < 0.25
        and restlessness < 0.25
    ):

        return {
            "state": "Sleepy",
            "confidence": 0.90,
            "alert_level": ALERT_LEVELS["Sleepy"]
        }

    # -------------------------------------------------
    # RULE 4 : LOW CONFIDENCE
    # -------------------------------------------------

    if confidence < 0.55:

        return {
            "state": "Uncertain",
            "confidence": round(confidence, 2),
            "alert_level": ALERT_LEVELS["Uncertain"]
        }

    # -------------------------------------------------
    # DEFAULT : TRUST THE ML MODEL
    # -------------------------------------------------

    return {

        "state": state,

        "confidence": round(confidence, 2),

        "alert_level": ALERT_LEVELS.get(
            state,
            "Medium"
        )
    }


# =====================================================
# FINAL DECISION PIPELINE
# =====================================================

def final_decision(sensor):

    ml_result = ml_predict(sensor)

    final_result = apply_rules(
        sensor,
        ml_result
    )

    return final_result