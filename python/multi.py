import cv2
import img_preprocess
import time,board,busio
import numpy as np
import adafruit_mlx90640
import max_temp
import concurrent.futures

def open():
    camera = cv2.VideoCapture(-1)
    camera.set(3, 640)
    camera.set(4, 480)

    _, image = camera.read() # 프레임 값을 읽어 image변수에 저장
    image = cv2.flip(image, -1) # -1은 180도 이미지를 뒤집는다

    #filepath = "/home/pi/AI_CAR/video/test" # 파일의 경로와 저장될 이름을 대입한다.
    #i = 0 # 사진 번호를 붙일 숫자값 변수를 만들고 0으로 초기화한다.
    height, _, _ = image.shape # 높이를 변수에 저장한다
    
    # 높이를 절반으로 잘라 아래부분 영상 저장
    image = image[int(height/2):,:,:] 
    
    # 학습 정확도 향상위해 색 변환
    image = cv2.cvtColor(image, cv2.COLOR_BGR2YUV)
    
    image = cv2.resize(image, (350,200))    # 사이즈 변환 -> 속도 up

    # 블러로 픽셀간 차이를 줄여 인식률 향상   
    image = cv2.GaussianBlur(image,(5,5),0) 

    _,image = cv2.threshold(image,160,255,cv2.THRESH_BINARY_INV) 
    # 임계점 이상의 값을 최대값으로 바꾸어 라인 인식율을 증가시킴
    # 입계점 설정에 따라서 선을 인식하는 범위가 틀려진다. 
    #빛과 라인 색상에 따라 틀리다 -> 상황에 맞게 설정하기
    
    image = image / 255
    cv2.imshow('pre', image)

def main():
    while True:
        with concurrent.futures.ProcessPoolExecutor() as executor:
            executer.submit()

if __name__ == "__main__":
    main()
    cv2.destroyAllWindows()
