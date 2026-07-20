from pydantic import BaseModel


# =====================================================
# BABY SENSOR REQUEST MODEL
# =====================================================

class BabySensorData(BaseModel):

    cry_volume: float

    cry_frequency: float

    motion_intensity: float

    restlessness: float

    heart_rate: int

    heart_rate_trend: int

    hr_variability: float


# =====================================================
# ML RESPONSE MODEL
# =====================================================

class PredictionResponse(BaseModel):

    state: str

    confidence: float

    bpm: int