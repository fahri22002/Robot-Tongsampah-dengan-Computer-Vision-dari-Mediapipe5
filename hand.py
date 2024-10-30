import cv2
import mediapipe as mp
import math
import serial
import time
ser = serial.Serial('COM8', 9600)  # Ganti 'COM8' dengan port yang sesuai
time.sleep(2)  # Tunggu beberapa detik untuk memastikan koneksi serial stabil

# Inisialisasi MediaPipe Hands
mp_drawing = mp.solutions.drawing_utils
mp_pose = mp.solutions.pose

# Fungsi untuk menghitung jarak Euclidean
def calculate_distance(x1, y1, x2, y2):
    return math.sqrt((x2 - x1) ** 2 + (y2 - y1) ** 2)

# Fungsi utama untuk deteksi pose
def detect_hand_raised():
    cap = cv2.VideoCapture(0)  # Menangkap video dari kamera
    with mp_pose.Pose(min_detection_confidence=0.5, min_tracking_confidence=0.5) as pose:
        while cap.isOpened():
            success, frame = cap.read()
            if not success:
                print("Gagal menangkap gambar.")
                break

            # Mengonversi gambar ke RGB
            image = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)
            image.flags.writeable = False
            
            # Proses deteksi pose
            results = pose.process(image)

            # Kembalikan gambar ke BGR untuk ditampilkan di OpenCV
            image.flags.writeable = True
            image = cv2.cvtColor(image, cv2.COLOR_RGB2BGR)
            direction_code = ""
            # Jika hasil deteksi ditemukan
            if results.pose_landmarks:
                mp_drawing.draw_landmarks(
                    image, results.pose_landmarks, mp_pose.POSE_CONNECTIONS)

                # Ambil koordinat tangan kiri dan kanan
                landmarks = results.pose_landmarks.landmark
                left_wrist = landmarks[mp_pose.PoseLandmark.LEFT_WRIST.value]
                right_wrist = landmarks[mp_pose.PoseLandmark.RIGHT_WRIST.value]

                # Ambil koordinat bahu kiri dan kanan
                left_shoulder = landmarks[mp_pose.PoseLandmark.LEFT_SHOULDER.value]
                right_shoulder = landmarks[mp_pose.PoseLandmark.RIGHT_SHOULDER.value]

                # Cek apakah tangan kiri diangkat (koordinat Y tangan lebih tinggi dari bahu)
                if left_wrist.y < left_shoulder.y:
                    distance_left = calculate_distance(left_wrist.x, left_wrist.y, left_shoulder.x, left_shoulder.y)
                    print(f"Tangan kiri diangkat: X={left_wrist.x}, Y={left_wrist.y}, Jarak={distance_left:.4f}")
                    cv2.putText(image, f'Left Hand Raised, Dist: {distance_left:.4f}', (50, 50), cv2.FONT_HERSHEY_SIMPLEX, 1, (0, 255, 0), 2, cv2.LINE_AA)

                    # Kode biner untuk tangan kiri
                    if left_wrist.x < 0.3:
                        direction_code += "L"  # Kiri
                    elif left_wrist.x > 0.7:
                        direction_code += "R"  # Kanan
                    else:
                        # Cek jarak untuk maju/mundur
                        if distance_left < 0.3:
                            direction_code += "F"  # Maju
                        elif distance_left > 0.7:
                            direction_code += "B"  # Mundur
                        else:
                            direction_code += "S"
                    print(f"Kode biner tangan kiri: {direction_code}")

                # Cek apakah tangan kanan diangkat (koordinat Y tangan lebih tinggi dari bahu)
                elif right_wrist.y < right_shoulder.y:
                    distance_right = calculate_distance(right_wrist.x, right_wrist.y, right_shoulder.x, right_shoulder.y)
                    print(f"Tangan kanan diangkat: X={right_wrist.x}, Y={right_wrist.y}, Jarak={distance_right:.4f}")
                    cv2.putText(image, f'Right Hand Raised, Dist: {distance_right:.4f}', (50, 100), cv2.FONT_HERSHEY_SIMPLEX, 1, (0, 255, 0), 2, cv2.LINE_AA)

                    # Kode biner untuk tangan kanan
                    
                    # Cek nilai x untuk kiri/kanan
                    if right_wrist.x < 0.3:
                        direction_code += "L"  # Kiri
                    elif right_wrist.x > 0.7:
                        direction_code += "R"  # Kanan
                    else:
                        # Cek jarak untuk maju/mundur
                        if distance_right < 0.3:
                            direction_code += "F"  # Maju
                        elif distance_right > 0.7:
                            direction_code += "B"  # Mundur
                        else:
                            direction_code += "S"
                        

                    print(f"Kode biner tangan kanan: {direction_code}")
                else :
                    direction_code += "R"
            ser.write(direction_code.encode('utf-8'))
            # Tampilkan gambar
            cv2.imshow('Hand Raised Detection', image)

            if cv2.waitKey(5) & 0xFF == 27:  # Tekan 'Esc' untuk keluar
                break

    cap.release()
    cv2.destroyAllWindows()
    ser.close()
if __name__ == "__main__":
    detect_hand_raised()
