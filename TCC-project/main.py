import cv2
from cvzone.HandTrackingModule import HandDetector
import serial # pip install pyserial

ser = serial.Serial('COM7', 115200) # Change the COM port to the one you are using
prev_upCount = -1
totalFingers = 0

handType=''

cap = cv2.VideoCapture(0) # Change the camera index to the one you are using
cap.set(3, 1280)
cap.set(4, 720)

detector = HandDetector(detectionCon=0.8) # Increase the detection confidence for better results

while True:
    success, img = cap.read()
    if not success:
        break

    hands, img = detector.findHands(img)  # Find the hands and draw annotations

    if hands:
        hand = hands[0]  # Assuming the first hand is the right hand (cvzone does not distinguish between hands)
        fingers = detector.fingersUp(hand)
        totalFingers = sum(fingers)
        # print(hand['type'] , totalFingers)
        handType=hand['type']

    if totalFingers != prev_upCount:
        ser.write(str(totalFingers).encode()) # Send the data to the Arduino
        prev_upCount = totalFingers
        print(handType , totalFingers)

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

# Close the serial port
ser.close()
cap.release()
cv2.destroyAllWindows()
