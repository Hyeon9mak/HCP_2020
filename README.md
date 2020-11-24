# 광운대학교 컴퓨터정보공학부 2020학년도 2학기 고급C프로그래밍 팀프로젝트
## 포켓몬 길찾기 게임 소개
![image](https://user-images.githubusercontent.com/37354145/95642672-fd189500-0ae4-11eb-960d-35753b44e278.png)

- 격자로 이루어진 게임판에 출발지점과 도착지점을 입력하면  
스스로 최적화된 경로를 찾아내는 강화학습 게임.
- Frozen lake game 과 포켓몬스터 게임에서  
아이디어 착안.
### 4 x 4 Map
![image](/동작영상/44_45.gif)

### 7 x 7 Map
![image](/동작영상/77_45.gif)

### 10 x 10 Map #[10 x 10 Map 실제 동작 영상 링크](https://youtu.be/ZSPgoS3yVrI)
![image](/동작영상/1010_45.gif)

이 외에도, Map.txt 파일 편집을 통해 자유롭게 맵 구성 가능!

## 게임 설명
### 게임 시작 전
![image](/동작영상/before_game.png)
- Map.txt 파일을 이용한 게임 맵 구성
- Txy -> xy는 지름길/함정 출구의 좌표
- 정확한 맵 구성을 이용하지 않을 시 에러 발생!

### 게임 중
![image](/동작영상/in_game.png)
- 순서대로 우, 좌, 상, 하 기대 값 의미
- 6/30 회로 표현되지만 실제 6,000/30,000 회임
- 1,000 단위로 화면에 출력되는 상태

### 게임 종료 후
![image](/동작영상/after_game.png)
- 최종적으로 플레이어가 이동한 최적의 경로 표현
- Enter 키 입력을 통한 종료

## 프로젝트 세부
### 팀원
- 팀장 박정훈 컴퓨터정보공학부 2020202074
- 팀원 김현중 컴퓨터정보공학부 2020202041
- 팀원 최성우 컴퓨터정보공학부 2019202081
- 팀원 최현구 컴퓨터정보공학부 2015722010

### 주제 선정 과정
![image](https://user-images.githubusercontent.com/37354145/95642716-394bf580-0ae5-11eb-8b0f-3c958580a82c.png)

- 알파고 이후 강화학습 AI 관심 증가
- Q-learning, E-greedy 학습을 통한 개발 가능성 확인

### 프로젝트 스케쥴링
![image](https://user-images.githubusercontent.com/37354145/95642792-c8590d80-0ae5-11eb-8a27-977fb1ae7614.png)
![image](https://user-images.githubusercontent.com/37354145/95642797-d0b14880-0ae5-11eb-96f9-0d538946b2fe.png)


### 핵심 알고리즘
- Q-learning
- E-greedy

### 참고
- [삼성 sds saida 팀 스타크래프트 인공지능](http://m.hani.co.kr/arti/economy/it/870696.html#cb)
- [시행착오 없는 길찾기 인공지능](http://m.hani.co.kr/arti/science/future/926150.html)
- [홍콩 과기대 김성훈 교수님 강의](https://hunkim.github.io/ml/)
- [텐서플로우 프레임워크 q-learning 설명](https://www.tensorflow.org/agents/tutorials/0_intro_rl)
- [Frozen lake game](https://colab.research.google.com/github/simoninithomas/Deep_reinforcement_learning_Course/blob/master/Q_Learning_with_FrozenLakev2.ipynb)