"""
validator.py

Validates and sanitizes incoming sensor data before
it is passed to the ML inference engine.
"""


def clamp(value, minimum, maximum):
    """
    Restrict a value to a valid range.
    """
    return max(minimum, min(value, maximum))


def validate_sensor_data(sensor_data: dict):
    """
    Validate and sanitize sensor values.

    Returns:
        validated_data (dict)
    Raises:
        ValueError if required fields are missing.
    """

    required_fields = [
        "cry_volume",
        "cry_frequency",
        "motion_intensity",
        "restlessness",
        "heart_rate",
        "heart_rate_trend",
        "hr_variability"
    ]

    # -------------------------------------------------
    # Check for missing fields
    # -------------------------------------------------

    for field in required_fields:

        if field not in sensor_data:
            raise ValueError(f"Missing required field: {field}")

    validated = {

        "cry_volume":
            clamp(float(sensor_data["cry_volume"]), 0.0, 1.0),

        "cry_frequency":
            clamp(float(sensor_data["cry_frequency"]), 0.0, 5000.0),

        "motion_intensity":
            clamp(float(sensor_data["motion_intensity"]), 0.0, 1.0),

        "restlessness":
            clamp(float(sensor_data["restlessness"]), 0.0, 1.0),

        "heart_rate":
            clamp(int(sensor_data["heart_rate"]), 40, 220),

        "heart_rate_trend":
            clamp(int(sensor_data["heart_rate_trend"]), -50, 50),

        "hr_variability":
            clamp(float(sensor_data["hr_variability"]), 0.0, 1.0)
    }

    return validated