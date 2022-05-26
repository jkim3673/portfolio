import cv2 #opencv 사용
import numpy as np  #numpy 사용
import time

def main(): 
    camera = cv2.VideoCapture(-1) # -1 기본값
    camera.set(3, 640)
    camera.set(4, 480)
    #filepath = "/home/pi/AI_CAR/video/test" # 파일의 경로와 저장될 이름을 대입한다.
    #i = 0 # 사진 번호를 붙일 숫자값 변수를 만들고 0으로 초기화한다.

    while (camera.isOpened()): # 카메라 동작하면 (+ 키값 읽어 출력하는 부분)
        keyValue = cv2.waitKey(10) # 키보드 값을 입력받는다, 0.001초 동안 읽히지 않으면 timeout 발생
    
        if keyValue == ord('q'): # q값을 입력받으면 break
            break
       
        #img_preprocessing    
        _, image = camera.read() # 프레임 값을 읽어 image변수에 저장
        image = cv2.flip(image, -1) # -1은 180도 이미지를 뒤집는다
        cv2.imshow ('Original', image) # 원본 출력
        
        preprocessed = img_preprocess(image)
        cv2.imshow('preprocess', preprocessed) # 전처리 출력

def preprocessing(image):
    height, _, _ = image.shape # 높이를 변수에 저장한다
    image = image[int(height/2):,:,:] 
    # 높이를 이용해 가로로 1/2 중간지점을 자르고 -> 윗부분 날리고 아랫부분 남김

    image = cv2.cvtColor(image, cv2.COLOR_BGR2YUV) 
    # 색변환 -> 인공지능학습을 위한 전처리, 효율적으로 특징을 잡아내 인식율 up
    
    rows = image.shape[0]
    cols = image.shape[1]
    imglog = np.log1p(np.array(image, dtype='float') / 255) 
    #y값을 0~1사이로 조정 후 log(x+1)
    
    M = 2*rows + 1
    N = 2*cols + 1
 
    ### gaussian mask 생성 sigma = 10
    sigma = 10
    (X, Y) = np.meshgrid(np.linspace(0, N-1, N), np.linspace(0, M-1, M)) 
    # 0~N-1(and M-1) 까지 1단위로 space를 만듬
    
    Xc = np.ceil(N/2) # 올림 연산
    Yc = np.ceil(M/2)
    gaussianNumerator = (X - Xc)**2 + (Y - Yc)**2 # 가우시안 분자 생성
 
    ### low pass filter와 high pass filter 생성
    LPF = np.exp(-gaussianNumerator / (2*sigma*sigma))
    HPF = 1 - LPF
 
    ### LPF랑 HPF를 0이 가운데로 오도록iFFT함. 
    ### shuffling을 수행한 효과
    ### 에너지를 각 귀퉁이로 모아 줌
    LPF_shift = np.fft.ifftshift(LPF.copy())
    HPF_shift = np.fft.ifftshift(HPF.copy())
 
    ### Log를 씌운 이미지를 FFT해서 LPF와 HPF를 곱해 LF성분과 HF성분을 나눔
    img_FFT = np.fft.fft2(imglog.copy(), (M, N))
    img_LF = np.real(np.fft.ifft2(img_FFT.copy() * LPF_shift, (M, N))) # low frequency 성분
    img_HF = np.real(np.fft.ifft2(img_FFT.copy() * HPF_shift, (M, N))) # high frequency 성분
 
    ### 각 LF, HF 성분에 scaling factor를 곱해주어 조명값과 반사값을 조절함
    gamma1 = 0.3
    gamma2 = 1.5
    img_adjusting = gamma1*img_LF[0:rows, 0:cols] + gamma2*img_HF[0:rows, 0:cols]
 
    ### 조정된 데이터를 이제 exp 연산을 통해 이미지로 만들어줌
    img_exp = np.expm1(img_adjusting) # exp(x) + 1
    img_exp = (img_exp - np.min(img_exp)) / (np.max(img_exp) - np.min(img_exp)) # 0~1사이로 정규화
    img_out = np.array(255*img_exp, dtype = 'uint8') # 255를 곱해서 intensity값을 만들어줌
    image = cv0.resize(image, (200,66)) # 사이즈변환 -> 속도 up
    image = cv2.GaussianBlur(image,(5,5),0) 
    # 블러처리 -> 픽셀간의 차이를 낮춘다 -> 영상에 존재하는 잡음의 영향을 제거해 인식률 up
    _,image = cv2.threshold(image,160,255,cv2.THRESH_BINARY_INV) 
    # 임계점 이상의 값을 최대값으로 바꾸어 라인 인식율을 증가시킴
    # 입계점 설정에 따라서 선을 인식하는 범위가 틀려진다. 
    #빛과 라인 색상에 따라 틀리다 -> 상황에 맞게 설정하기
    return image

        #cv2. imwrite("%S_%05d.png" % (filepath, i), image) # 이미지를 저장하는 함수
        #i = i + 1

        #time.sleep(1.0) # 1초마다 사진이 갱신된다
    
    # cv2.destroyAllWindows() # 모든 opencv 창 종료
