# Machine Learning Module – Baby Monitoring System

This module implements a **Random Forest–based machine learning model** used to analyze baby sensor data and assist in generating alerts for the parent monitoring band.

---

## 📌 Objective
To classify the baby’s state (e.g., normal, discomfort, alert condition) based on sensor inputs collected from the baby band.

---

## 📂 Folder Structure
ml/
├── train.py # Model training script
├── inference.py # Inference / prediction logic
├── requirements.txt # Python dependencies
├── data/
│ └── synthetic_data.csv # Training dataset
└── model/
└── rf_baby_state_model.pkl # Trained Random Forest model


---

## 🧪 Features Used
The model is trained using features derived from baby-band sensors such as:
- Motion / activity level
- Physiological indicators (e.g., temperature)
- Derived statistical features from sensor readings

*(Exact features can be extended as more sensors are integrated.)*

---

## 🧠 Model Details
- Algorithm: **Random Forest Classifier**
- Reason for choice:
  - Handles non-linear sensor data well
  - Robust to noise
  - Low risk of overfitting
  - Suitable for real-time inference

---

## ⚙️ Training
To train the model:

```bash
python train.py

