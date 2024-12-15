# FPSDemo
2024腾讯游戏客户端公开课相关  
基于UE5.4的游戏First Person模板开发

# 课堂笔记
## 第一周
[《UE入门》](https://www.mubu.com/doc/2oJdnkSXkXl)

## 第二周
[《游戏模式》](https://www.mubu.com/doc/2pDGzonBRkl)

## 第三周
[《UE5的C++代码规范》](https://www.mubu.com/doc/1smLSvCujOB)

## 第四周
[《UMG界面》](https://www.mubu.com/doc/1I4ao6djV2B)

## 第五周
[《UE5的骨骼动画》](https://www.mubu.com/doc/AejDxU9ZfB)

# 作业完成情况
## 第一周
- [x] 源码编译UE5，创建C++工程（First Person模板）  
- [x] 编译构建安装包，可以在安卓机运行（画质好差~未上传apk ~~github lfs 容量超载了~~）

## 第二周
### 物件规则：
- [x] 1. 射击命中方块，获得积分X (Score) 分
- [x] 2. 子弹命中方块后销毁
- [x] 3. 方块被子弹命中后，缩放为Y (HitScale) 倍，再次被命中后销毁  
[查看积分、缩放设置面板](#CubeInfo)  

### 游戏流程：
- [x] 1. 游戏开始时随机N (ImportantGoalCount) 个方块成为“重要目标”，射击命中后获得双倍积分
- [x] 2. 游戏开始后限时T (Seconds) 秒，时间到后游戏结算，打印日志输出每个玩家获得的积分和所有玩家获得的总积分  
[查看时间，重要目标设置面板](#GameInfo)  
[击中大小对比](#HitShowImg)

### 附加题
- [x] 1. 利用UMG制作结算UI替代日志打印  
[结算面板展示](#ScorePanelImg)
- [ ] 2. 支持多人联机


## 第四周
- [x] 1.实现登录界面（需要输入用户名和密码，其中密码加密显示，有确认按钮）  
[登陆页面展示](#LoginImg)
- [x] 2.实现加载界面（要有动画表传达正在加载）  
[加载页面展示](#LoadingImg)
- [x] 3.实现射击游戏操作面板（要有血条，子弹数，击中玩家会发生变化的准星  
[操作面板展示](#UIImg)

## 第五周
- [ ] 1.实现敌人的基础移动动画蓝图，并尽可能优化表现。
- [ ] 2.实现敌人的死亡动画，并尽可能优化表现（如添加多方向死亡动画等）。
- [ ] 3.实现近战击败敌人的功能和动画表现。（选做）


# 完成情况说明

## 截图展示

#### 积分、缩放设置面板
<a name="CubeInfo"></a>
![积分、缩放设置面板](https://github.com/Aptal/FPSDemo/blob/main/HomeworkScreenshot/SecondHomework/2-1.png?raw=true "积分、缩放设置面板")

#### 时间，重要目标设置面板
<a name="GameInfo"></a>
![时间，重要目标设置面板](https://github.com/Aptal/FPSDemo/blob/main/HomeworkScreenshot/SecondHomework/2-2.png?raw=true "时间，重要目标设置面板")

#### 击中大小、重要目标对比
“重要目标”被标记为黄金色，击中一次缩小一倍，两次消失
<a name="HitShowImg"></a>
![击中大小对比](https://github.com/Aptal/FPSDemo/blob/main/HomeworkScreenshot/SecondHomework/2-3.png?raw=true)

#### 结算面板（每个玩家分数，总分数）
<a name="ScorePanelImg"></a>
![结算面板](https://github.com/Aptal/FPSDemo/blob/main/HomeworkScreenshot/SecondHomework/2-4.png?raw=true)

#### 登陆页面
<a name="LoginImg"></a>
![结算面板](https://github.com/Aptal/FPSDemo/blob/main/HomeworkScreenshot/4Homework/4-1.png?raw=true)

#### 加载页面
登陆页面点击登录后，加载界面（强制delay 3s）右下角使用ue自带的转圈，中间的字体添加抖动动画，3s后自动进入游戏界面
<a name="LoadingImg"></a>
![结算面板](https://github.com/Aptal/FPSDemo/blob/main/HomeworkScreenshot/4Homework/4-2.png?raw=true)

#### 操作面板
持枪时初始10个子弹，击中玩家后准星会从黑色变红色
<a name="UIImg"></a>
![结算面板](https://github.com/Aptal/FPSDemo/blob/main/HomeworkScreenshot/4Homework/4-3.png?raw=true)


### 12.16
- 射击者的获取有点问题

### 12.15
- 新建gameinstance会出现访问不到map（索引为空，打开level失败）的情况，暂时采用从ButtonClick中 清空widget->打开loading widget-> delay 3s->打开新level


### 12.04
- 第二周目标基本完成：作业中的游戏相关属性括号内的名称均在蓝图中暴露
- 差多人网络同步：未开始
- UMG结算UI：类似当前HUD的形式，框架基本完成