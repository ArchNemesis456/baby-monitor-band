import numpy as np
import pandas as pd
import random
import joblib

from sklearn.model_selection import train_test_split
from sklearn.ensemble import RandomForestClassifier
from sklearn.metrics import classification_report


# -----------------------------
# 1. Label mapping
# -----------------------------
LABEL_MAP = {
    0: "Hungry",
    1: "Sleepy",
    2: "Discomfort",
    3: "Stress",
    4: "Normal"
}


# -----------------------------
# 2. Synthetic data generator
# -----------------------------
def generate_sample():
    # Audio features
    cry_volume = np.random.rand()
    cry_frequency = np.random.rand()

    # Motion features
    motion_intensity = np.random.rand()
    restlessness = np.random.rand()

    # Heart rate history (simulate 5 readings)
    hr_history = [random.randint(90, 180) for _ in range(5)]
    heart_rate = hr_history[-1]
    heart_rate_trend = hr_history[-1] - hr_history[0]
    hr_variability = np.std(hr_history) / 30  # normalized approx

    # Label logic
    if cry_volume > 0.7 and motion_intensity > 0.6:
        label = 0  # Hungry
    elif cry_volume < 0.3 and motion_intensity < 0.3 and heart_rate_trend <= 0:
        label = 1  # Sleepy
    elif restlessness > 0.7:
        label = 2  # Discomfort
    elif heart_rate > 160 or heart_rate_trend > 10:
        label = 3  # Stress
    else:
        label = 4  # Normal

    return [
        cry_volume,
        cry_frequency,
        motion_intensity,
        restlessness,
        heart_rate,
        heart_rate_trend,
        hr_variability,
        label
    ]


# -----------------------------
# 3. Create dataset
# -----------------------------
data = [generate_sample() for _ in range(1500)]

columns = [
    "cry_volume",
    "cry_frequency",
    "motion_intensity",
    "restlessness",
    "heart_rate",
    "heart_rate_trend",
    "hr_variability",
    "label"
]

df = pd.DataFrame(data, columns=columns)
df.to_csv("data/synthetic_data.csv", index=False)


# -----------------------------
# 4. Train-test split
# -----------------------------
X = df.drop("label", axis=1)
y = df["label"]

X_train, X_test, y_train, y_test = train_test_split(
    X, y, test_size=0.2, random_state=42
)


# -----------------------------
# 5. Train Random Forest
# -----------------------------
model = RandomForestClassifier(
    n_estimators=120,
    max_depth=12,
    random_state=42
)

model.fit(X_train, y_train)


# -----------------------------
# 6. Evaluation
# -----------------------------
y_pred = model.predict(X_test)

print("\nClassification Report:\n")
print(classification_report(y_test, y_pred, target_names=LABEL_MAP.values()))


# -----------------------------
# 7. Save model
# -----------------------------
joblib.dump(model, "model/rf_baby_state_model.pkl")
print("\n✅ Model trained and saved to model/rf_baby_state_model.pkl")
