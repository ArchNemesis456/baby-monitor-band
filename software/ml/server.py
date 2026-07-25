from fastapi import FastAPI
from fastapi.middleware.cors import CORSMiddleware

from models import BabySensorData
from services import process_sensor_data
from database import (
    initialize_database,
    get_recent_records,
    get_state_distribution,
    get_daily_average_hr
)

# =====================================================
# INITIALIZE DATABASE
# =====================================================

initialize_database()

# =====================================================
# LATEST PREDICTION CACHE
# =====================================================

latest_prediction = {
    "state": "Waiting",
    "confidence": 0.0,
    "alert_level": "Low"
}

# =====================================================
# FASTAPI
# =====================================================

app = FastAPI(
    title="Baby Band ML Server",
    version="1.0.0"
)

app.add_middleware(
    CORSMiddleware,
    allow_origins=["*"],
    allow_credentials=True,
    allow_methods=["*"],
    allow_headers=["*"],
)

# =====================================================
# HEALTH CHECK
# =====================================================

@app.get("/")
def root():

    return {

        "status": "ML Server Running"

    }


# =====================================================
# PREDICTION
# =====================================================

@app.post("/predict")
def predict(data: BabySensorData):

    global latest_prediction

    result = process_sensor_data(
        data.model_dump()
    )

    latest_prediction = result

    return result

# =====================================================
# LATEST PREDICTION
# =====================================================

@app.get("/latest")
def latest():

    return latest_prediction

# =====================================================
# RECENT RECORDS
# =====================================================

@app.get("/stats")
def stats():

    return get_recent_records()


# =====================================================
# STATE DISTRIBUTION
# =====================================================

@app.get("/stats/state-distribution")
def state_distribution():

    return get_state_distribution()


# =====================================================
# DAILY HEART RATE
# =====================================================

@app.get("/stats/daily-avg-hr")
def daily_average_hr():

    return get_daily_average_hr()