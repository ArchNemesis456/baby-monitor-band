# =====================================================
# PARENT BAND CONFIGURATION
# =====================================================

PARENT_IP = "10.30.109.117"
PARENT_PORT = 8080

PARENT_URL = f"http://{PARENT_IP}:{PARENT_PORT}/result"


# =====================================================
# DATABASE CONFIGURATION
# =====================================================

DATABASE_NAME = "baby_data.db"


# =====================================================
# SERVER CONFIGURATION
# =====================================================

SERVER_HOST = "127.0.0.1"
SERVER_PORT = 8000


# =====================================================
# HYBRID AI THRESHOLDS
# =====================================================

NO_CRY_THRESHOLD = 0.05

HIGH_HEART_RATE = 150

LOW_HEART_RATE = 110

HIGH_MOTION = 0.70

LOW_MOTION = 0.25

LOW_RESTLESSNESS = 0.25

LOW_CONFIDENCE = 0.55