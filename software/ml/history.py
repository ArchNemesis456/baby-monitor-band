from collections import deque

# =====================================================
# CONFIGURATION
# =====================================================

WINDOW_SIZE = 5

history = deque(maxlen=WINDOW_SIZE)

# Features that benefit from smoothing
SMOOTHED_FEATURES = [
    "cry_volume",
    "cry_frequency"
]

# Features that should always use the latest reading
LATEST_FEATURES = [
    "motion_intensity",
    "restlessness",
    "heart_rate",
    "heart_rate_trend",
    "hr_variability"
]

# =====================================================
# ADD SENSOR READING
# =====================================================

def add_sensor_reading(sensor_data):

    history.append(sensor_data)


# =====================================================
# IS HISTORY READY?
# =====================================================

def history_ready():

    return len(history) == WINDOW_SIZE


# =====================================================
# GET SENSOR DATA
# =====================================================

def get_sensor_data():

    # Until the history buffer is full,
    # return the latest raw reading.
    if not history_ready():
        return history[-1]

    averaged = {}

    # -----------------------------
    # Average noisy features
    # -----------------------------
    for feature in SMOOTHED_FEATURES:

        averaged[feature] = sum(

            reading[feature]

            for reading in history

        ) / WINDOW_SIZE

    # -----------------------------
    # Keep latest physiological values
    # -----------------------------
    latest = history[-1]

    for feature in LATEST_FEATURES:

        averaged[feature] = latest[feature]

    return averaged


# =====================================================
# CLEAR HISTORY
# =====================================================

def clear_history():

    history.clear()