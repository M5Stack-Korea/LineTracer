M5STACK을 이용한 라인 트레이스(Line Tracer) 만들기

M5STACK은 기존 Arduino와 유사한 Open Hardware Platform에서 외장 Case와 독특한 Stack Up연결 구조를 가지며,  외부 Color LCD와 3개의 button 스위치를 이용해서 
별도의 Shield나 확장 보드 없이 독립적인 다양한 Project를 수행할 수 있습니다.
![M5STACK](https://www.wiznetian.com/wp-content/uploads/2019/04/U1.png)
사진 출처 https://cdn.instructables.com/F9V/EER4/IWE4IOVN/F9VEER4IWE4IOVN.LARGE.jpg?auto=webp&width=642&crop=3:2

먼저 라인트레이스를 제작하기 위해서는 M5STACK의 Basic 모듈을 사용합니다. 아래 그림을 보시면 전체 Stack Up 되어 있는 상태에서 
아래 모듈을 제거하고 LCD가 있는 부분을 뒤집어 보면 아래 내부 그림을 보실 수 있습니다.

![M5STACK](https://www.wiznetian.com/wp-content/uploads/2019/04/U2.png "M5STACK")

1.라인트레이서란?
![M5STACK](https://www.wiznetian.com/wp-content/uploads/2019/04/U3_0.jpg)

적외선 센스는 검은색은 흡수되고, 흰색은 반사하는 성질이 있습니다. 이것을 이용해서 바닥에 검은선을 따라 가도록 만든 것을 라인트레이서라고 표현하며
적외선 센스가 검은색 선을 벗어나면 좌우 모터 속도를 조절하여 원상태로 되돌려야 합니다.

![M5STACK](https://www.wiznetian.com/wp-content/uploads/2019/04/U3_1.png)

2.필터 (Filter) 설계
적외선은 우리가 생활하는 가정내의 형광등에서도 발생합니다.
따라서 이러한 다른 신호를 제거하고 순수하게 라인트레이서에서 발생하는 적외선 만을 받도록 설계하는데 이때 사용되는 기술이 필터 기술입니다. 
로우패스 필터는 특정 주파수 이하의 신호만 통과시키는 회로, 하이패스 필터는 특정 주파수 이상에서만 신호를 통과시킵니다.
필터링 주파수= 1/(2* 3.141592 * R * C ) 
라인트레이서의 경우 형광등이 60Hz이기 때문에 60Hz 이상의 파형을 구동 시키고 값을 받도록 설계를 해야 됩니다. 
출처: https://rootfriend.tistory.com/entry/회로내에서-간섭-제거법 [A Kind of Magic]
이번 라이트레이스를 만들면서 상용 제품을 사용하다 보니 지속적으로 적외선 센서 발신 부는 ON으로 되어있고, 수신부도 값을 비교해서 ON/OFF만 출력하도록 되어 있습니다.
![M5STACK](https://www.wiznetian.com/wp-content/uploads/2019/04/U3_2.png)


##STEP 1. 준비물

2개의 Timer Interrupt를 사용하기 위해서는 아래를 미리 준비해야 됩니다. 아래 링크를 따라서 하나씩 진행하시기 바랍니다.
•	M5STACK Basic 구매하기: [구매처](http://shop.wiznet.co.kr/front/contents/product/view.asp?cateid=97&pid=1346)

•	Arduino IDE 설치: [설치하기](https://www.wiznetian.com/%ec%95%84%eb%91%90%ec%9d%b4%eb%85%b8-ide-%ec%84%a4%ec%b9%98-%eb%b0%8f-git-%ec%84%a4%ec%b9%98-%eb%b0%a9%eb%b2%95-windows/)

•	M5Core Quick Start 가이드: [가이드](https://www.wiznetian.com/m5core-quick-start-%ea%b0%80%ec%9d%b4%eb%93%9c-windows-aaduino/)

•	Arduino 예제 코드 다운받기:[예제코드 다운받기](https://www.dropbox.com/sh/klvylv1wklkyeht/AAAXvjTirQLdIV04XW_VZeiha?dl=0 )


##STEP 2.Arduino 컴파일 하기

다운받은 압축 파일을 풀고 아래 그림처럼 MultiTask.ino을 더블 클릭합니다.
![M5STACK](https://www.wiznetian.com/wp-content/uploads/2019/04/U3_3.png)
(단 앞에 사전 준비 사항을 반드시 해야 됩니다. Arduino IDE설치나 M5STACK Core 사용이 Arduino에 제대로 설정이 안되어 있으면 컴파일상에 무수한 Error 멧세지를 보실 수 있습니다.)

아래 그림과 같이 Arduino IDE가 실행되면서 Code가 보입니다. 혹시 모르니 다시 한번 확인하겠습니다.
Arduino 파일 -> 환경설정에 아래와 같이 제대로 설정되었는지 확인해 주십시오.
안되 있다면 추가적인 보드 매니저 URLs에 아래 링크를 추가하시면 됩니다.
https://github.com/espressif/arduino-esp32/releases/download/1.0.1-rc1/package_esp32_dev_index.json

![M5STACK](https://www.wiznetian.com/wp-content/uploads/2019/04/U4.png)

두번째는 Arduino -> 툴 -> 보드 -> M5Stack-Core-ESP32가 제대로 설정되었는지 확인해 주십시오.
![M5STACK](https://www.wiznetian.com/wp-content/uploads/2019/04/U5.png)


그리고 일단 컴파일하고 Error가 없는지 확인합니다.
아래 화면과 같이 정상적으로 컴파일이 되면 메모리 사이즈를 보여 줍니다.
![M5STACK](https://www.wiznetian.com/wp-content/uploads/2019/04/U6.png)


##STEP 4.M5STACK Basic에 Program 다운로딩 하기 
PC와 M5STACK Basic를 Micro USB Type C로 각각 연결합니다. 
![M5STACK](https://www.wiznetian.com/wp-content/uploads/2019/04/U7.png)

Arduino IDE에서 아래 자동으로 인식된 COM Port를 확인해줘야 합니다.
Arduino IDE는 기존 포트를 저장하고 있기 때문에 문제가 나중에 다른 포트로 되어 있으면 다운로딩시 Error 발생됩니다.
(아래 그림에서 실제 M5STACK이 잡히는 포트는 COM3입니다.)
![M5STACK](https://www.wiznetian.com/wp-content/uploads/2019/04/U8.png)

제대로 Port가 맞지 않으면 아래처럼 됩니다.
![M5STACK](https://www.wiznetian.com/wp-content/uploads/2019/04/U9.png)

이제 컴파일후 업로딩을 하게 되면 아래와 같이 출력됩니다.
![M5STACK](https://www.wiznetian.com/wp-content/uploads/2019/04/U10.png)

M5STACK이 자동 Reset 되면서 M5STACK화면에 나타납니다.


코드를 보면 다음과 같습니다. 
소스 코드를  보게 되면 MultiTask를 기반으로 3개의 Task를 생성합니다.
Task1,2는 Stepping 모터를 구동하고 나머지 Task3은 적외선 센서를 받아서 모터 Task1,2의 발생 주기를 조정합니다. 
<GPIO 설정> 
모터는 총 5개의 M5STACK의 출력 신호를 사용하고, 적외선센스 입력을 위해서 1개의 Digital 입력과, 3개의 Analog 입력 핀을 사용합니다.
![M5STACK](https://www.wiznetian.com/wp-content/uploads/2019/04/U11-1.png)


Task1,2: Stepping Motor Clock 주기 
아래에서 Left_Timer, Right_Timer가 적외선 센스 값에 의해서 Task 생성 주기가 변하는 값입니다.
![M5STACK](https://www.wiznetian.com/wp-content/uploads/2019/04/U12.png)


Task3: 적외선 입력 값에 따른 Stepping Motor Task 생성 주기 발생
![M5STACK](https://www.wiznetian.com/wp-content/uploads/2019/04/U13-1.png)

동영상은 아래를 참고하십시오
https://www.facebook.com/minsu.jeun/videos/2248013138611363/


####Curator: Lucd
####Email: <lucid@wiznet.io>
