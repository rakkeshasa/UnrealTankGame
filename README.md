# UnrealTankGame
언리얼엔진을 이용한 탱크 게임

게임 소개
---
### <간단한 소개>
플레이어가 탱크를 조작하여 타워를 부수는 게임입니다.

### <게임 플레이 화면>
![1](https://user-images.githubusercontent.com/77041622/193404751-2e515bfa-80f2-4380-b092-275f5fbcff1f.PNG)
<br>맵 내에서 움직이는 탱크

![4](https://user-images.githubusercontent.com/77041622/193404804-72beaf3c-3ec8-4b24-9b08-0a2eaa764c25.PNG)
<br>탱크를 공격하는 포탑

### <첫 시작 시>
![2](https://user-images.githubusercontent.com/77041622/193404784-c18ca17d-7550-4c87-b3c7-f586c07b5be3.PNG)

### <게임 오버 시>
![3](https://user-images.githubusercontent.com/77041622/193404797-ab128210-ff1b-4373-924b-1887510868d6.PNG)

게임 목적 및 대상
---
게임의 목적은 맵에 존재하는 모든 타워를 제거하는 것입니다.
타워는 맵 곳곳에 존재하며 플레이어는 맵을 돌아다니면서 타워를 찾으면서 제거해야합니다.
타워 또한 플레이어처럼 일정 거리 안에 들어오면 공격을 하고, 타워의 공격에 자신의 탱크가 부셔지면 실패하게 됩니다.
모든 타워를 파괴하는데 성공하면, 스테이지가 클리어 되며 다음 스테이지에 넘어가게 됩니다.

게임을 플레이하는 대상은 플래시게임을 즐기는 유저나 낮은 연령층을 노려 아기자기한 이미지를 사용하였습니다.

스크립트 관련
---
### <탱크 이동 기능>
![1](https://user-images.githubusercontent.com/77041622/193412187-421ee1ee-3c88-458a-abda-25fa38605240.PNG)
![2](https://user-images.githubusercontent.com/77041622/193412190-97b52371-8289-424b-8183-f88831a61f13.PNG)
<br>
프로젝트 세팅에서 Axis Mapping와 Action Mapping 설정한 후 SetupPayerInputComponent로 연결해주기
<br>그 후 BindAction()에다가 세팅에서 지정해준 이름과, 탱크 오브젝트, 기능 함수 를 넣어준 후
<br>기능 함수에다가 기능을 구현할 코드를 작성해준다.

### <타워 기능 구현>
![3](https://user-images.githubusercontent.com/77041622/193412337-054201bf-a1ba-4d84-8978-7c7bba2aa482.PNG)
![4](https://user-images.githubusercontent.com/77041622/193412340-d988df1e-3442-43fb-8ca3-e255c06ada19.PNG)
<br>
현재 액터와 탱크의 거리를 빼서 거리를 구한다.
<br> 일정 거리 안에 탱크가 들어올 시 타워는 포탑의 방향을 탱크 방향으로 회전시킨 후 발포한다.
<br><br>
![5](https://user-images.githubusercontent.com/77041622/193412416-2ca37a31-9766-4e8c-9ae4-15fd1cdaea2c.PNG)
발포와 포탑 회전 관련 코드

### <발사체 기능 구현>
![6](https://user-images.githubusercontent.com/77041622/193412475-88c5d56d-cb94-4e4f-89c5-fceab93dd913.PNG)
<br>
발사체가 어떤 물체에 부딪혔을 때 OnHit함수를 호출함.
<br>부딪힌 액터가 실존하거나, 자기 자신이 아니거나 발사체가 아니라면 데미지를 입힘
<br>ApplyDamage()를 이용하여 부딪힌 액터에 지정한 수치의 데미지를 입힘.
<br>그 아래 코드는 충돌 시 효과 처리 부분

### <승패 관련 기능>
![7](https://user-images.githubusercontent.com/77041622/193412577-f25b86b6-7146-4e98-92a9-13ed39ee4bb2.PNG)
<br>
각 액터는 HP가 0이하가 되면 액터 클래스에 있는 HandleDestruction()함수가 호출 되면서 파괴됨.
<br>탱크가 파괴되면 GameOver()함수에 false값이 들어가면서 패배 처리가 됨.
<br>맵 상에 있는 모든 타워가 파괴되면 GameOver()함수에 true값이 들어가면서 승리 처리 화면이 나오면서 다음 스테이지로 넘어감.
