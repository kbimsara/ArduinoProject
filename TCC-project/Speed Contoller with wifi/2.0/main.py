import warnings
warnings.filterwarnings("ignore", category=UserWarning, module='google.protobuf')

import cv2
from cvzone.HandTrackingModule import HandDetector
import socket

def send_command(command):
    host = '192.168.105.169'  # Replace with the IP address of your ESP8266
    port = 80
    
    try:
        with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
            s.connect((host, port))
            s.sendall(command.encode())
            response = s.recv(1024)
            # Uncomment to print response for debugging
            # print('Received:', response.decode())
    except Exception as e:
        print(f"Failed to send command: {e}")

def main():
    prev_upCount = -1
    totalFingers = 0

    cap = cv2.VideoCapture(0)  # Change the camera index if needed
    cap.set(3, 1280)
    cap.set(4, 720) 

    detector = HandDetector(detectionCon=0.8)  # Increase detection confidence for better results

    while True:
        success, img = cap.read()
        if not success:
            break

        hands, img = detector.findHands(img)  # Find the hands and draw annotations

        if hands:
            hand = hands[0]  # Assuming the first hand is the right hand (cvzone does not distinguish between hands)
            fingers = detector.fingersUp(hand)
            totalFingers = sum(fingers)
            handType = hand['type']
        else:
            handType = ''

        if totalFingers != prev_upCount:
            send_command(str(totalFingers))  # Send the command to the ESP8266
            prev_upCount = totalFingers
            print(handType, totalFingers)

        cv2.putText(img, str(totalFingers), (256, 256), cv2.FONT_HERSHEY_PLAIN, 10, (255, 200, 0), 6)

        # Uncomment to show axis lines
        # x axis coordination
        # img = cv2.line(img, (128, 0), (128, img.shape[1]), (255, 0, 0), 3)
        img = cv2.line(img, (256, 0), (256, img.shape[1]), (0, 255, 0), 3)
        # img = cv2.line(img, (384, 0), (384, img.shape[1]), (0, 0, 255), 3)
        # y axis coordination
        # img = cv2.line(img, (0, 128), (img.shape[1], 128), (255, 0, 0), 3)
        img = cv2.line(img, (0, 256), (img.shape[1], 256), (0, 255, 0), 3)
        # img = cv2.line(img, (0, 384), (img.shape[1], 384), (0, 0, 255), 3)

        cv2.imshow("Smart Fan Control Using Image Processing", img)
        key = cv2.waitKey(1)
        if key == 27:
            break

    cap.release()
    cv2.destroyAllWindows()

if __name__ == "__main__":
    main()
