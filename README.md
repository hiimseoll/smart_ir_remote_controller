# smart_ir_remote_controller

우리가 일상생활에서 TV, 에어컨 등 전자기기들을 사용할 때에 각각에 맞는 리모컨을 사용해야 하는 번거로움과, 리모컨을 잃어버리는 곤란한 상황에 처할 수 있다.<br/><br/>
이러한 불편함을 해소하고자 프로젝트를 기획했습니다.

## 🍀3D 모델
<img src="/images/SIR_3D_01.PNG" width="350" height="300">
- 리모컨 전면부
<br/><br/><br/>
<img src="/images/SIR_3D_02.PNG" width="350" height="300">
- 무선충전 거치대
<br/><br/><br/>
3D 프린팅 모델은 Autodesk Fusion 360 프로그램으로 제작되었습니다.<br/><br/>

Front:<br/>
&nbsp;&nbsp;&nbsp;Display, 3x3 Buttons.<br/>
Right Side:<br/>
&nbsp;&nbsp;&nbsp;Photo Transistor.<br/>
Top:<br/>
&nbsp;&nbsp;&nbsp;Power switch, IR LED.<br/><br/><br/>

## 🍀회로
<br/>
<img src="/images/SIR_fritzing.jpg" width="450" height="300"><br/>
연결 구성은 위 사진과 같으나,
Arduino를 쉽게 탈부착 할 수 있도록 IC 소켓을 잘라 PCB 기반에 납땜했으며, <br/>
 IR 송신 거리 증폭을 위한 Darlington pair amplifier와 배터리 충 방전 모듈, 무선 충전 모듈이 추가되었습니다.
 <br/><br/>
Arduino는 소켓에 부착되고, 대부분의 배선은 기판에 납땜이 되어있습니다.
<br/><br/><br/>

## 🍀작동 방법
<br/>

|1|2|2|
|:---:|:---:|:---:|
|4|5|6|
|추가|변경|삭제|

버튼의 구성은 위와 같습니다.
<br/><br/>

|PRESET 0|*PRESET 1|PRESET 2|PRESET 3|*PRESET 4|
|:---:|:---:|:---:|:---:|:---:|
|저장되지 않음|저장됨|저장되지 않음|저장되지 않음|저장됨|

프리셋(저장 가능한 리모컨의 수)은 총 5개 이며, 각 프리셋마다 1번 부터 6번 까지의 버튼에 필요한 신호를 저장할 수 있습니다.<br/>
"*"기호가 있는 프리셋은 값이 저장되어 있다는 뜻이며, [변경] 버튼을 통해 0번 부터 순서대로 프리셋을 변경할 수 있습니다.

<br/><br/>
프리셋에 리모컨의 신호를 저장하는 방법은 다음과 같습니다:<br/><br/>
1. 저장을 원하는 프리셋 번호를 화면에 띄운다.<br/><br/>
2. [추가]버튼을 누른다. (이 때 화면에는 "ADD MODE"라는 문구가 출력됩니다.)<br/><br/>
3. 등록을 원하는 리모컨의 버튼을 차례로 누른다. (정상적으로 값이 입력되면 "!!!"라는 문구가 출력됩니다.)
<br/><br/>
<img src="/images/SIR_ex01.gif" width="500" height="300"><br/>
<br/><br/>
<img src="/images/SIR_ex02.gif" width="500" height="300"><br/>


<br/><br/><br/><br/>

등록이 끝났다면 해당 프리셋의 앞 부분에 "*"기호가 생긴 것을 확인할 수 있습니다.
