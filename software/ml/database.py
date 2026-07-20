import sqlite3
from datetime import datetime

# =====================================================
# DATABASE CONNECTION
# =====================================================

conn = sqlite3.connect("baby_data.db", check_same_thread=False)
cursor = conn.cursor()

# =====================================================
# CREATE TABLE
# =====================================================

def initialize_database():

    cursor.execute("""
    CREATE TABLE IF NOT EXISTS records (

        id INTEGER PRIMARY KEY AUTOINCREMENT,

        timestamp TEXT,

        cry_volume REAL,

        cry_frequency REAL,

        motion REAL,

        heart_rate INTEGER,

        state TEXT,

        confidence REAL

    )
    """)

    conn.commit()


# =====================================================
# INSERT RECORD
# =====================================================

def save_prediction(sensor_data, result):

    cursor.execute("""

    INSERT INTO records

    (

        timestamp,

        cry_volume,

        cry_frequency,

        motion,

        heart_rate,

        state,

        confidence

    )

    VALUES (?, ?, ?, ?, ?, ?, ?)

    """,

    (

        datetime.now().isoformat(),

        sensor_data["cry_volume"],

        sensor_data["cry_frequency"],

        sensor_data["motion_intensity"],

        sensor_data["heart_rate"],

        result["state"],

        result["confidence"]

    ))

    conn.commit()


# =====================================================
# LAST RECORDS
# =====================================================

def get_recent_records(limit=100):

    cursor.execute("""

    SELECT

        timestamp,

        cry_volume,

        cry_frequency,

        motion,

        heart_rate,

        state,

        confidence

    FROM records

    ORDER BY id DESC

    LIMIT ?

    """, (limit,))

    rows = cursor.fetchall()

    return [

        {

            "timestamp": row[0],

            "cry_volume": row[1],

            "cry_frequency": row[2],

            "motion": row[3],

            "heart_rate": row[4],

            "state": row[5],

            "confidence": row[6]

        }

        for row in rows

    ]


# =====================================================
# STATE DISTRIBUTION
# =====================================================

def get_state_distribution():

    cursor.execute("""

    SELECT state, COUNT(*)

    FROM records

    GROUP BY state

    """)

    rows = cursor.fetchall()

    return {

        state: count

        for state, count in rows

    }


# =====================================================
# DAILY HEART RATE
# =====================================================

def get_daily_average_hr():

    cursor.execute("""

    SELECT

        substr(timestamp,1,10),

        AVG(heart_rate)

    FROM records

    GROUP BY substr(timestamp,1,10)

    ORDER BY substr(timestamp,1,10) DESC

    LIMIT 7

    """)

    rows = cursor.fetchall()

    return [

        {

            "day": row[0],

            "avg_hr": row[1]

        }

        for row in rows

    ]