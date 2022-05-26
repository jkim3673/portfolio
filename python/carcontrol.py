import cv2
import uart
import img_preprocess

def drive():
    camera = cv2.VideoCapture(-1)
    camera.set(3, 640)
    camera.set(4, 480)
    
    while( camera.isOpened() ):
        
        keyValue = cv2.waitKey(100)
        
        if keyValue == ord('q'):
            break
        elif keyValue == 82:
            print("go")
            carState = "go"
            uart.uart('g')
        elif keyValue == 84:
            print("back")
            carState = "back"
            uart.uart('b')
        elif keyValue == 81:
            print("left")
            carState = "left"
            uart.uart('l')
        elif keyValue == 83:
            print("right")
            carState = "right"
            uart.uart('r')
        elif keyValue == ord('s'):
            print("stop")
            carState = "stop"
            uart.uart('s')
        
        
        _, image = camera.read()
        image = cv2.flip(image,-1)
        cv2.imshow('Original', image)
        img_preprocess.preprocessing(image)
    
def close():
    cv2.destroyAllWindows()
